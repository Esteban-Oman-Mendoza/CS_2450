#pragma once
#include <string>

const int MEM_SIZE = 100;

 class UVSim
{
private:
	int memory[MEM_SIZE] = {};

public:
	UVSim();
	~UVSim();
	// Helper functions
	bool is_digits(const std::string &str);
	int retrieve_int();
	std::string retrieve_op();

	// Opcodes

	// Function for Main
	void memory_dump();
};


