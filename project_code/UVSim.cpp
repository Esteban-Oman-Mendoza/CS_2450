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
		if (input != "" && (is_digits(input) && 0 <= std::stoi(input) && input.size() == OPCODELEN) || input == "-99999")
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
	//Multiply the accumulator by number in memory location. 
	if (memory[param] == 0) //multiplying by zero. 
	{
		accumulator = 0;
		return;
	}
	else
	{ 
	std::string multiplyer = std::to_string(memory[param]).substr(2, 2); //Need to add a test for out of range erors. 
	accumulator = accumulator * std::stoi(multiplyer);
	//std::cout << accumulator << std::endl;  DEBUG LINE
	}
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
	//std::cout << accumulator << std::endl; DEBUG LINE
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

	for (size_t i = 0; i <= MEM_SIZE; i++)
	{
		if (memory[i] == -99999)
		{
			std::cout << "Invalid Opcode: " << -99999 << "Press enter to quit..." << std::endl;
			std::cin.get();
			exit(1);
		}
		try 
		{
			std::string op = std::to_string(memory[i]).substr(0, 2);
			std::string param = std::to_string(memory[i]).substr(2, 2);
		}
		catch (...)
		{
			std::cout << "tried to run non-opcode.\nPress enter to exit..." << std::endl;
			std::cin.get();
			exit(1);
		}
		std::string op = std::to_string(memory[i]).substr(0, 2);
		std::string param = std::to_string(memory[i]).substr(2, 2);
		switch (std::stoi(op)) {
			//			case 10:											Example of opcode. Param is your parameter in string from.
			//				read(std::stoi(param));														pass in stoi if you want int.

		case 10:
			break;
			//read

		case 11:
			//Write
			break;
			//Load and store operations

		case 20:
			//load
			break;
		case 21:
			//store
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
			multiply(std::stoi(param));
			break;
			//Control operations

		case 40:
			//branch
			i = std::stoi(param);
			std::cout << "Branching to " << param << std::endl;
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
			std::cout << "Invalid Opcode: " << (op + param) << "\tin memory " << i << "\nPress enter to quit..." <<  std::endl;
			std::cin.get();
			exit(1);
		}
	}
	std::cout << "Read access violation.\nPress enter to quit..." << std::endl;
	return 1;
}

void UVSim::memory_dump()
{
	std::cout << "---------Memory Dump----------" << std::endl << "\t";
	std::cout << accumulator; //FIXME debug line
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


