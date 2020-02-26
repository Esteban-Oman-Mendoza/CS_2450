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
	*place = param -1;
}

void UVSim::branchneg(size_t* place, int param)
{
	if (neg_flag == -1)
		branch(place, param);
}

void UVSim::branchzero(size_t * place, int param)
{
	if (neg_flag == 0)
		branch(place, param);
}

void UVSim::halt()
{
	memory_dump();
	system("pause");
	exit(0);
}

int UVSim::execute()
{
	accumulator = 80;//FIXME setting to manual value, waiting for load function.
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
			halt();

			break;
		default:
			std::cout << "Invalid Opcode: " << (op + param) << "\tin memory " << i << "\nPress enter to quit..." <<  std::endl;
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
			std::cout << (i / 10) << "\t";
		}
		std::cout << memory[i] << "\t";
		if (i % 10 == 9)
		{

			std::cout << std::endl;
		}
	}
}


