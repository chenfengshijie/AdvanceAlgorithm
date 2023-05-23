#pragma once
#include <unordered_map>

class Table
{

public:
	std::vector<int> weight;
	std::vector<std::pair<int,int>> data;
	std::unordered_multimap<int,int>value2id;

	/**
	 * \brief	create a table
	 * \param tot the num of data
	 */
	Table(int tot)
	{
		data.reserve(tot);
		weight.reserve(tot);
		value2id.reserve(tot);
	}
	~Table();
};
