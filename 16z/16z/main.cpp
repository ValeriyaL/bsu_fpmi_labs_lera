#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <atomic>
#include <mutex>
#include <vector> 

std::mutex mutex;
std::atomic<unsigned long long> sum(0);
unsigned long long array[1000];
std::atomic<int> index(0);


void summ_func(unsigned long long interval, unsigned long long number)
{
	while (index<1000)
		{
			unsigned long long beg = array[index++];
			for (unsigned long long i = beg+1; i <= beg + interval; i++)
			{
				std::unique_lock<std::mutex> lock(mutex);
				if (!(number%i))
					sum += i;
				lock.unlock();
			}
		}
}

int main()
{
	int threads;
	std::cout << "Please input number of threads: ";
	std::cin >> threads;
	unsigned long long number;
	std::cout << "Please input your number: ";
	std::cin >> number;
	std::vector<std::thread> vect1;
	unsigned long long interval = number/2 / 1000;
	unsigned long long begin = 0;
	for (int j = 0; j < threads; j++)
	{
		array[j] = begin;
		begin += interval+1;
	}
	auto start_time = std::chrono::system_clock::now();
	for (int j = 0; j < threads; j++)
	{
		vect1.push_back(std::thread(summ_func, interval, number));
	}
	for (int j = 0; j < threads; j++)
		vect1[j].join();
	auto end_time = std::chrono::system_clock::now();
	auto dif = end_time - start_time;
	if (number == sum)
		std::cout << "Your number is perfect" << std::endl;
	else
		std::cout << "Your number isn't perfect" << std::endl;
	std::cout << "Duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(dif).count() << std::endl;
	//	std::cout << "Sum " << sum << std::endl;
	return 0;
}