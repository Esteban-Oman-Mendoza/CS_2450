#include "UVSim.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stdexcept>

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
				if (input == "4300")
				{
					while (input != "-99999")
					{
						
					}
				}
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
	//read() gets keyboard input of an integer and converts it to an int and places it in memory[param]
	
	int value = 0;
	std::cout << "Enter an integer: ";
	std::cin >> value;
	if(!std::cin)
	{
		throw std::runtime_error("Your input was not an integer. Please restart the program.");
	}
	//value = stoi(input);
	memory[param] = value;
	
}

void UVSim::write(int param)
{
	//write will print to console the contets of memory location 'param'
	std::cout << memory[param] << std::endl;
}

void UVSim::load(int param)
{
}

void UVSim::store(int param)
{
	memory[param] = accumulator;
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
	memory_dump();
	return;
}

int UVSim::execute()
{
	accumulator = 80;//FIXME setting to manual value, waiting for load function.
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
			//accepts user input of integer into memory location 'param'
			read(std::stoi(param));
			break;
		//read

		case 11: 
		//Write
			//prints to console whatever is in the memory location of operand
			write(std::stoi(param));
			break;
		//Load and store operations

		case 20:
		//load
			break;
		case 21: 
		//store
			//Stores accumulator in designated memory location
			store(std::stoi(param));
			break;

		//Arithmetic Operations
		
		case 30: 
		//add
			break;
		case 31:
		//subtract
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
			halt();
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
			std::cout << (i / 10) << "\t";
		}
		std::cout << memory[i] << "\t";
		if (i % 10 == 9)
		{

			std::cout << std::endl;
		}
	}
}


