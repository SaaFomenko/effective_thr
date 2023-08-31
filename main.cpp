#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

const long sum_vec(const std::vector<int>& x, const std::vector<int>& y)
{
    long result = 0;

    for(int el : x)
    {
        result += el;
    }
    std::cout << "Summa x vector: " << result << '\n';
    
    for(int el : y)
    {
        result += el;
    }
    std::cout << "Summa x+y vectors: " << result << '\n';

    return result;
}

void vec_sum_v2(const std::vector<int>& x, long& result)
{
    for (int el : x)
    {
        result += el;
    }
}

int main()
{
    //const int thr_1[]{1, 2, 4, 8, 16};

    //const int mill = 1000000;
    const int mill = 1000000;
    const int thr = 2;

    std::cout << "mill = " << mill << '\n';

    std::vector<int> x;
    std::vector<int> y;
    std::vector<std::thread> V;

    for (int i = 0; i < mill; ++i)
    {
        x.push_back(i);
        y.push_back(i);
    }

    auto start = std::chrono::steady_clock::now();

    long result = sum_vec(x, y);

    auto end = std::chrono::steady_clock::now();

    auto delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    //double exec_time = static_cast<double>(delta.count() / 1000000.0);
    double exec_time = delta.count() / 1000000.0;

    std::cout.precision(12);
    std::cout << "Time sum 2 vectors[" << mill - 1 << "] = " << exec_time << " sec. \n";
    
    std::cout << "Last element vector[" << mill - 1 << "] = " << *--x.end() << '\n';

    std::cout << "Summa vectors x and y = " << result << '\n';
    std::cout << "Size result in byte: " << sizeof(result) << "\n\n\n";

    result = 0;

    start = std::chrono::steady_clock::now();
    
    for (int i = 0; i < thr; ++i)
    {
        bool isNull = i % 2 == 0;
        if (isNull)
            V.push_back(std::thread(vec_sum_v2, ref(x), std::ref(result)));
        else
            V.push_back(std::thread(vec_sum_v2, ref(y), std::ref(result)));
    }

    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "Result thr_sum_vec with 2 threads: " << result << '\n';
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}