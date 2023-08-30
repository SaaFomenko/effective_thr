#include <iostream>
//#include <thread>
#include <chrono>
#include <vector>

const long sum_vec(const std::vector<int>& x, const std::vector<int>& y)
{
    long result = 0;

    for(int el : x)
    {
        result += el;
    }
    
    for(int el : y)
    {
        result += el;
    }

    return result;
}

int main()
{
    //const int thr_1[]{1, 2, 4, 8, 16};

    const int mill = 1000000;

    std::cout << "mill = " << mill << '\n';

    std::vector<int> x;
    std::vector<int> y;

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < mill; ++i)
    {
        x.push_back(i);
        y.push_back(i);
    }

    auto end = std::chrono::steady_clock::now();

    auto delta = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    std::cout << "Time init vector[" << mill - 1 << "] = " << delta.count() << '\n';
    
    std::cout << "Last element vector[" << mill - 1 << "] = " << *--x.end() << '\n';

    std::cout << "Summa vectors x and y = " << sum_vec(x, y) << '\n'

    return 0;
}