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
	unsigned long long sum2 = 0;
	while (index<1000)
		{
			unsigned long long beg = array[index++];
			if (beg == 0) break;
			for (unsigned long long i = beg; i <= beg + interval; i++)
			{
				if (!(number%i))
					sum2 += i;
			}
		}
	std::unique_lock<std::mutex> lock(mutex);
	sum += sum2;
	lock.unlock();
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
	unsigned long long interval;
	if (number < 2000)
	{
		interval = 0;
		for (int j = 0; j < (number/2)+1; j++)
		{
			array[j] = j+1;
		}
	}
	else
	{
		interval = number / 2 / 1000;
		unsigned long long begin = 0;
		for (int j = 0; j < 1000; j++)
		{
			array[j] = begin+1;
			begin += interval + 1;
		}
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