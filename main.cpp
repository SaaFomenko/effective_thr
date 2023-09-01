#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>
//#include <mutex>


//static std::mutex barrier;

void sum_vec(
    std::atomic<long>& result, 
    const std::vector<int>& x, 
    const std::vector<int>& y, 
    const int l, 
    const int r
    )
{
    long part_sum = 0;

    for (int i = l; i < r; ++i)
        part_sum += x.at(i) + y.at(i);

   // std::lock_guard<std::mutex> block_threads_until_finish_this_job(barrier);

    result += part_sum;
}

std::vector<int> bounds(const int thr, const int num_elem)
{
    std::vector<int> bnd;
    int delta = num_elem / thr;
    int reminder = num_elem % thr;
    int n1 = 0;
    int n2 = 0;

    bnd.push_back(n1);

    for (int i = 0; i < thr; ++i)
    {
        n2 = n1 + delta;

        if (i == thr - 1)
            n2 += reminder;

        bnd.push_back(n2);
        n1 = n2;
    }

    return bnd;
}

void print_thr_test(const int num_elem, const int thr)
{
    std::vector<int> x;
    std::vector<int> y;
    std::vector<std::thread> V;
    std::atomic<long> result(0);
    std::vector<int> bnd(bounds(thr, num_elem));
    
    for (int k = 0; k < num_elem; ++k)
    {
        x.push_back(k);
        y.push_back(k);
    }
    
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < thr; ++i)
    {
        V.push_back(std::thread(
            sum_vec, 
            std::ref(result), 
            std::ref(x), 
            std::ref(y), 
            bnd.at(i), 
            bnd.at(i + 1)
        ));
    }
    
    for(auto &el : V)
    {
        if (el.joinable())
            el.join();
    }
    
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    
    std::cout << '\t' << elapsed_seconds.count() << 's';
}

int main()
{
    const int num_elem[] = {1000, 10000, 100000, 1000000};
    const int thr[] = {1, 2, 4, 8, 16};
    const int thr_size = sizeof(thr) / sizeof(thr[0]);
    const int num_size = sizeof(num_elem) / sizeof(num_elem[0]);

    std::cout << "CPU logical cores: " << std::thread::hardware_concurrency() << "\n\n\t";

    for (int i = 0; i < num_size; ++i)
    {
        std::cout << '\t' << num_elem[i] << '\t';
    }
    std::cout << '\n';
   
    for (int i = 0; i < thr_size; ++i)
    {
        std::cout << thr[i] << " threads";
        for (int j = 0; j < num_size; ++j)
        {
            print_thr_test(num_elem[j], thr[i]);
        }
        std::cout << '\n';
    }

    return 0;
}