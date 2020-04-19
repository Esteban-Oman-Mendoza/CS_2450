#include <iostream>
#include <stdexcept>
#include "UVSim.h"

/*	Program: UVSim
	Creators: Tyler Aldous, Colby Gardiner, Esteban Mendoza, Kolton <Last Name>, Steven Anderson.
	Project Description: UVSim will simulates machine code for students to learn machine language and architecture. */



int main()
{
	try
	{
		UVSim logic;
		logic.execute();
		logic.memory_dump();
		std::cin.get();
		return 0;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

}