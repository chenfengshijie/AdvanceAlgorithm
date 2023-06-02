#include"lab5.h"

#include<iostream>
#include<fstream>
#include<filesystem>
#include <vector>

int main() 
{
    namespace  fs = std::filesystem;
    const std::string data_dir = R"(C:\Users\FrozeWorld\source\repos\AdvanceAlgorithm\Lab5\data)";
    std::vector<std::string>files;
    for(const auto&file:fs::directory_iterator(data_dir))
    {
	    if(file.is_regular_file()&&file.path().extension()==".txt")
			files.push_back(file.path().string());
    }
    
    return 0;
}
