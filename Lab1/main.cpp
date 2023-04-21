#include"lab1.h"
#include <chrono>

int main()
{
    // 构建示例数据集
    auto start = std::chrono::high_resolution_clock::now();
   std::vector<std::unordered_set<int>>documents;
   int num_max =0;
   num_max = reader(documents,"E1_AOL-out.txt");

   printf("%d",num_max);
   for(int i =40;i<=100;i+=10)
   {
       run_experiment(documents,i,0.5,num_max);
   }
   auto end = std::chrono::high_resolution_clock::now();
   auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
   std::cout << "程序执行时间为 " << duration.count() << " 秒" << std::endl;
    return 0;
}