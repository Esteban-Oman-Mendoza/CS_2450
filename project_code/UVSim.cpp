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

bool UVSim::is_digits(const std::string& str)	// Helper function, checks if string is all digits	
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

void UVSim::IO() {
	std::cout << "\ncurrent accumulator value: ";
	std::cout << accumulator;
}

void UVSim::read(int param)
{
	std::string input = "";
	int value = 0;
	std::cout << "Enter an integer: ";
	std::cin >> input;
	value = stoi(input);
	memory[param] = value;
}

void UVSim::write(int param)
{
}

void UVSim::load(int param)
{
	int memoryValue = memory[param];
	accumulator = memoryValue;
}

void UVSim::store(int param)
{
	//stores accumulator at the the indexed value of param in memory
	int memoryLocation = param;
	memory[memoryLocation] = accumulator;
}

void UVSim::add(int param)
{
	//adds the value at memory address param to accumulator and then stores in accumulator
	int addValue = memory[param];
	accumulator = accumulator + addValue;
	std::cout << accumulator << std::endl;
}

void UVSim::subtract(int param)
{
	//subtracts the value in memoery address param from accumulator and then stores in accumulator
	int subtractValue = memory[param];
	accumulator = accumulator - subtractValue;
	std::cout << accumulator << std::endl;
}

void UVSim::multiply(int param)
{
}

void UVSim::divide(int param)
{
	//memory_dump();
	//Divide word from specific  location in memory by the accumulator
	/*std::string dividend = std::to_string(memory[param]).substr(2, 2);
	accumulator = std::stoi(dividend) / accumulator;
	std::cout << accumulator << std::endl;*/

	//Divide accumulator by word from specific  location in memory
	std::string divisor = std::to_string(memory[param]).substr(2, 2);
	accumulator = accumulator / std::stoi(divisor);
	std::cout << accumulator << std::endl;
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
	accumulator = 0;//FIXME setting to manual value, waiting for load function.
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
		case 12:
			//crude implementation of a register 0 to console. I made this to better test my load function feel free to delete.
			IO();
			std::cout << std::endl;
			break;
		case 10:
			//read
			read(std::stoi(param));
			
			break;
		case 11:
			//Write
			break;
			//Load and store operations

		case 20:
			load(std::stoi(param));
			//load
			break;
		case 21:
			//I implemented this crude store function I dont know if it fits with our vision I just needed it to check my load function.
			store(std::stoi(param));
			//store
			break;
			//Arithmetic Operations

		case 30:
			//add
			add(std::stoi(param));
			break;
		case 31:
			//subtract
			subtract(std::stoi(param));
			break;
		case 32:
			//divide
				//divide a word from a sepcific location in memory by the word in the 
				//acumulator then leave results it acumulator
			divide(std::stoi(param));
			break;
		case 33:
			//multiply
			break;
			//Control operations

		case 40:
			//branch
			break;
		case 41:
			//branchneg
			break;
		case 42:
			//branchzero
			break;
		case 43:
			//halt
			break;
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