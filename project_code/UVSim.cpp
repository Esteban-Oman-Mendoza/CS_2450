#include "UVSim.h"
#include <string>
#include <algorithm>
#include <iostream>

//Globals
const int MAXNUM = 9999;
const int OPCODELEN = 4;

UVSim::UVSim()
{
}


UVSim::~UVSim()
{
}

bool UVSim::is_digits(const std::string & str)	// Helper function, checks if string is all digits	
{
	return all_of(str.begin(), str.end(), ::isdigit);
}

int UVSim::retrieve_int()	// Get's number from keyboard and makes sure it's a valid input
{
	std::string input = "";
	std::getline(std::cin, input);
	while (true)
	{
		if (is_digits(input) && 0 <= std::stoi(input) && input.size() <= MAXNUM)
				return std::stoi(input);
		std::cout << "Not a valid number. Please enter a non-negative integer less than " << MAXNUM + 1 << ":" << std::endl;
		std::getline(std::cin, input);
	}
}

std::string UVSim::retrieve_op()		// Can add feature to search through valid opcodes
{
	std::string input = "";
	std::getline(std::cin, input);
	while (true)
	{
		if (is_digits(input) && 0 <= std::stoi(input) && input.size() == OPCODELEN)
			return input;
		std::cout << "Not a valid number. Please enter a valid four-digit op code" << ":" << std::endl;
		std::getline(std::cin, input);
	}
	return input;
}

void UVSim::memory_dump()
{
	std::cout << "---------Memory Dump----------" << std::endl << "\t"; 
	for (size_t i = 0; i < 10; i++)
	{
		std::cout << i << "\t";
	}
	std::cout << std::endl << std::endl;
	for (size_t i = 0; i < MEM_SIZE; i++)
	{
		if (i % 10 == 0)
		{
			std::cout << (i / 10) + 1 << "\t";
		}
		std::cout << memory[i] << "\t";
		if (i % 10 == 9)
		{

			std::cout << std::endl;
		}
	}
}


