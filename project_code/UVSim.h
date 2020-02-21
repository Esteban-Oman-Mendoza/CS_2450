#pragma once
#include <string>
#include <vector>

const int MEM_SIZE = 100;

class UVSim
{
private:
	int memory[MEM_SIZE] = {};
	int accumulator;

public:
	UVSim();
	~UVSim();
	// Helper functions
	bool is_digits(const std::string &str);
	int retrieve_int();
	std::vector<int> retrieve_op();

	// Opcodes
	void read(int param);
	void write(int param);
	void load(int param);
	void store(int param);
	void add(int param);
	void subtract(int param);
	void multiply(int param);
	void branch();
	void branchneg();
	void halt();


	// Function for Main
	int execute();
	void memory_dump();
};


