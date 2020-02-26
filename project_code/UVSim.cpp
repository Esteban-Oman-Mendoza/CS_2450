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

std::vector<std::string> UVSim::retrieve_op()		// Can add feature to search through valid opcodes
{
	std::string input = "";
	std::cout << "Please enter opcode: (-99999 to stop and execute)" << std::endl;
	std::getline(std::cin, input);
	std::vector<std::string> ret;
	while (true)
	{
		if (input != "" && (is_digits(input) && 0 <= std::stoi(input) && input.size() == OPCODELEN) || input == "-99999")
		{
			if (input == "")
			{
				ret.push_back("-99999");
				return ret;
			}
			if (input != "-99999")
			{
				std::string op = input.substr(0, 2);
				std::string param = input.substr(2, 2);
				ret.push_back(op);
				ret.push_back(param);
				return ret;
			}
			else
			{
				ret.push_back("-99999");
				return ret;
			}
		}

		std::cout << "Not a valid number. Please enter a valid four-digit op code" << ":" << std::endl;
		std::getline(std::cin, input);
	}
}

void UVSim::flags(int checker)
{
	if (checker < 0)
		neg_flag = -1;
	else if (checker == 0)
		checker = 0;
	else
		neg_flag = 1;
}

int UVSim::flags()
{
	return neg_flag;
}


void UVSim::read(int param)
{
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
}

void UVSim::add(int param)
{
	int addValue = memory[param];
	accumulator = accumulator + addValue;
	std::cout << accumulator << std::endl;
}

void UVSim::addDirect(int param) {
	int addValueDirect = param;
	accumulator = accumulator + addValueDirect;
}

void UVSim::subtract(int param)
{
	int subtractValue = memory[param];
	accumulator = accumulator - subtractValue;
	std::cout << accumulator << std::endl;
}

void UVSim::subtractDirect(int param) {
	int subtractValueDirect = param;
	accumulator = accumulator - param;
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
	flags(accumulator);
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
	flags(accumulator);
	//std::cout << accumulator << std::endl; DEBUG LINE
}

void UVSim::branch(size_t* place, int param)
{
	*place = param - 1;
}

void UVSim::branchneg(size_t* place, int param)
{
	if (neg_flag == -1)
		branch(place, param);
}

void UVSim::branchzero(size_t* place, int param)
{
	if (neg_flag == 0)
		branch(place, param);
}

void UVSim::halt()
{
}

int UVSim::execute()
{
	accumulator = 0;//FIXME setting to manual value, waiting for load function.
	std::string input = "";
	std::vector<std::string> opcode;
	int count = 0;
	while (input != "-99999" && count < 99)
	{
		opcode = retrieve_op();
		if (opcode[0] != "-99999")
			input = opcode[0] + opcode[1];
		else
		{
			input = opcode[0];
			continue;
		}
		memory[count] = std::stoi(input);
		count++;
	}

	for (size_t i = 0; i <= MEM_SIZE; i++)
	{

		try
		{
			std::string op = std::to_string(memory[i]).substr(0, 2);
			std::string param = std::to_string(memory[i]).substr(2, 2);
		}
		catch (...)
		{
			std::cout << "tried to run non-opcode.\nPress enter to exit..." << std::endl;
			memory_dump();
			std::cin.get();
			exit(1);
		}
		std::string op = std::to_string(memory[i]).substr(0, 2);
		std::string param = std::to_string(memory[i]).substr(2, 2);
		switch (std::stoi(op)) {
			//			case 10:											Example of opcode. Param is your parameter in string form.
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
			load(std::stoi(param));
			break;
		case 21:
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
			multiply(std::stoi(param));
			break;
			//Control operations

		case 40:
			branch(&i, std::stoi(param));
		case 41:
			branchneg(&i, std::stoi(param));
			break;
		case 42:
			branchzero(&i, std::stoi(param));
			break;
		case 43:
			//halt
			memory_dump();
			return 0;
			break;
		case 50:
			//direct add
			addDirect(std::stoi(param));
			break;
		case 51:
			//direct subtract
			subtractDirect(std::stoi(param));
			break;
		default:
			std::cout << "Invalid Opcode: " << (op + param) << "\tin memory " << i << "\nPress enter to quit..." << std::endl;
			memory_dump();
			std::cin.get();
			exit(1);
		}
	}
	std::cout << "Read access violation.\nPress enter to quit..." << std::endl;
	return 1;
}

void UVSim::memory_dump()
{
	std::cout << "---------Memory Dump----------" << std::endl;
	std::cout << "value in accumulator: ";
	std::cout << accumulator;
	std::cout << std::endl;//FIXME debug line
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