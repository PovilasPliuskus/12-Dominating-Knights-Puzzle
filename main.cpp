#include"algorithm.h"
#include<ctime>

int main()
{
    time_t t = clock();
    algorithm();
    t = clock() - t;
    double timeTaken = ((double)t)/CLOCKS_PER_SEC;
    std::cout << "Time taken: " << timeTaken << std::endl;
}