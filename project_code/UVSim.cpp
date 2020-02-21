#include "UVSim.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>

//Globals
const int MAXNUM = 9999;
const int OPCODELEN = 4;

UVSim::UVSim()
{
	accumulator = 0;
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

std::vector<int> UVSim::retrieve_op()		// Can add feature to search through valid opcodes
{
	std::string input = "";
	std::cout << "Please enter opcode: (-99999 to stop and execute)" << std::endl;
	std::getline(std::cin, input);
	std::vector<int> ret;
	while (true)
	{
		if ((is_digits(input) && 0 <= std::stoi(input) && input.size() == OPCODELEN) || input == "-99999")
		{
			if (input == "")
			{
				ret.push_back(-99999);
				return ret;
			}
			if (input != "-99999")
			{
				std::string op = input.substr(0, 2);
				std::string param = input.substr(2, 2);
				ret.push_back(std::stoi(op));
				ret.push_back(std::stoi(param));
				return ret;
			}
			else
			{
				ret.push_back(-99999);
				return ret;
			}
		}

		std::cout << "Not a valid number. Please enter a valid four-digit op code" << ":" << std::endl;
		std::getline(std::cin, input);
	}
}

void UVSim::read(int param)
{
}

void UVSim::write(int param)
{
}

void UVSim::load(int param)
{
}

void UVSim::store(int param)
{
}

void UVSim::add(int param)
{
}

void UVSim::subtract(int param)
{
}

void UVSim::multiply(int param)
{
}

void UVSim::branch()
{
}

void UVSim::branchneg()
{
}

void UVSim::halt()
{
}

int UVSim::execute()
{
	std::string input = "";
	std::vector<int> opcode;
	int count = 0;
	while (input != "-99999" && count < 99)
	{
		opcode = retrieve_op();
		if (opcode[0] != -99999)
			input = std::to_string(opcode[0]) + std::to_string(opcode[1]);
		else
			input = std::to_string(opcode[0]);
		memory[count] = std::stoi(input);
		count++;
	}

	for (size_t i = 0; i < count; i++)
	{
		std::string op = std::to_string(memory[i]).substr(0, 2);
		std::string param = std::to_string(memory[i]).substr(2, 2);
		switch (std::stoi(op)) {
			//			case 10:											Example of opcode. Param is your parameter in string from.
			//				read(std::stoi(param));														pass in stoi if you want int.

		case 10:
		//read

		case 11: 
		//Write

		//Load and store operations

		case 20:
		//load

		case 21: 
		//store

		//Arithmetic Operations
		
		case 30: 
		//add

		case 31:
		//subtract

		case 32:
		//divide

		case 33:
		//multiply

		//Control operations

		case 40:
		//branch

		case 41:
		//branchneg

		case 42:
		//branchzero

		case 43:
		//halt

		default:
			std::cout << "Unknown opcode" << std::endl;
		}
	}
	return 0;
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


