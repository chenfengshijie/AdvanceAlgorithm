// ReSharper disable CppClangTidyBugproneNarrowingConversions
#include"Lab5.h"
#include<vector>
#include<unordered_map>
#include<iostream>
#include<fstream>

void read_data(const char* file_name, Table& table)
{
	std::ifstream fin;
	fin.open(file_name, std::ios_base::in);
	std::ios::sync_with_stdio(false);
	if (fin.is_open())
	{
		int a, b;
		while (fin >> a >> b)
		{
			table.data.push_back(std::make_pair(a, b));
			table.value2id.insert(std::make_pair(a, table.data.size() - 1));

		}
	}
	else
	{
		std::cout << "can't read file with filename";
	}
	return;
}

void exact_weight(std::vector<Table>& database)
{
	const auto n = database.size();
	database[n - 1].weight.assign(database[n - 1].data.size(), 1);

	for (int i = n - 2; i >= 0; i--)
	{
		database[i].weight.resize(database[i].data.size());
		for(auto &each:database[i].weight)
		{
			
		}
	}
}