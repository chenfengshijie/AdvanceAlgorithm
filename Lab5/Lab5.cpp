// ReSharper disable CppClangTidyBugproneNarrowingConversions
#include"Lab5.h"
#include<vector>
#include<unordered_map>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<numeric>
#include<random>

void read_data(std::string file_name, Table& table)
{
	std::ifstream fin;
	fin.open(file_name, std::ios_base::in);
	std::ios::sync_with_stdio(false);
	if (fin.is_open())
	{
		int a, b;
		while (fin >> a >> b)
		{
			table.data.emplace_back(std::make_pair(a, b));
			table.value2id.insert(std::make_pair(a, table.data.size() - 1));

		}
	}
	else
	{
		std::cout << "can't read file with filename";
	}
	return;
}

void DataBase::exact_weight(std::vector<Table>& database)
{
	const auto n = database.size();
	database[n - 1].weight.assign(database[n - 1].data.size(), 1);

	for (int i = n - 2; i >= 0; i--)
	{
		database[i].weight.resize(database[i].data.size());
		int m = database[i].data.size();
		for (int j = 0; j < m; j++)
		{
			int b = database[i].data[j].second;
			int tot = 0;
			auto s = database[i + 1].value2id.equal_range(b);
			for (auto iter = s.first; iter != s.second; iter++)
				tot += database[i + 1].weight[iter->second];
			database[i].weight[j] = tot;
		}
	}
	return;
}

void DataBase::olken_weight(std::vector<Table>& database)
{
	const auto n = database.size();
	database[n - 1].weight.assign(database[n - 1].data.size(), 1);

	for (int i = n - 2; i >= 0; i--)
	{
		int max_before = 0;
		max_before = *std::max_element(database[i + 1].weight.begin(), database[i + 1].weight.end());
		database[i].weight.resize(database[i].data.size());
		std::fill(database[i].weight.begin(), database[i].weight.end(), database[i + 1].weight[0] * max_before);
	}
	return;
}
//TODO : implemte random walk
void DataBase::random_walk(std::vector<Table>& database)
{
	const auto n = database.size();
	database[n - 1].weight.assign(database[n - 1].data.size(), 1);

}

std::vector<int> DataBase::sample()
{
	std::vector<int> ans;
	ans.reserve(n);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::discrete_distribution<int>sample_dis(database[n - 1].weight.begin(), database[n - 1].weight.end());
	std::uniform_real_distribution<> reject_dis(0, 1);
	double reject;
	int index = sample_dis(gen);
	ans.push_back(database[n - 1].data[index].first);
	for (int i = 1; i < n; i++)
	{
		auto s = database[i].value2id.equal_range(database[i - 1].data[index].second);
		std::vector<int> weight;
		weight.reserve(std::distance(s.second, s.first));
		for (auto it = s.first; it != s.second; ++it)
			weight.push_back(database[i + 1].weight[it->second]);
		int tot_weight = std::accumulate(weight.begin(), weight.end(), 0);
		reject = 1.0 - static_cast<double>(tot_weight) / database[i - 1].weight[index];
		if (reject_dis(gen) < reject)
			return std::vector<int>(0);
		std::discrete_distribution<int>dis(weight.begin(), weight.end());
		index = dis(gen);
		ans.push_back(database[i + 1].data[index].first);
	}
	return ans;
}

