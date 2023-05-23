#pragma once
#include <unordered_map>
#include <vector>
class Table;
class DataBase;
void read_data(const char* file_name, Table& table);

class Table
{

public:
	std::vector<int> weight;
	std::vector<std::pair<int, int>> data;
	std::unordered_multimap<int, int>value2id;

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
class DataBase
{
public:
	std::vector<Table> database;
	int n;

	DataBase(int num_table, const char** file_name) :n(num_table)
	{
		database.reserve(num_table);
		for (int i = 0; i < num_table; i++)
		{
			database.emplace_back(Table(1000));
			read_data(*(file_name + i), database[i]);
		}
		exact_weight(database);
	}
	~DataBase() = default;

	std::vector<int> sample();
private:
	/**
	 * \brief use dynamic programming to compute the exact weight
	 * \param database the chain database 
	 */
	static void exact_weight(std::vector<Table>& database);
	/**
	 * \brief olken use max frequency to assign the weight
	 * \param database the chain database to be compute 
	 */
	static void olken_weight(std::vector<Table>& database);
	static void random_walk(std::vector<Table>& database);
};
