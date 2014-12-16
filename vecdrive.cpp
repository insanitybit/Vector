#include <iostream>
#include "Vector.h"
#include <vector>
#include <chrono>

using namespace std;

int main()
{

	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;

	start = std::chrono::steady_clock::now();

	Vector<size_t> vec;

	for (size_t i = 0; i < (10 * 10 * 100000); ++i)
	{
		vec.push_back(i);
	}

	// std::vector<size_t> vec;


	// for (size_t i = 0; i < (10 * 10 * 100000); ++i)
	// {
	// 	vec.push_back(i);
	// }


	end = std::chrono::steady_clock::now();
	elapsed_seconds = end-start;
	cout << "10k push_back::  " << elapsed_seconds.count() * 1000 << "ms" << endl;


	return 0;
}