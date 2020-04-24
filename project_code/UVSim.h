
#include <string>
#include <vector>

const int MEM_SIZE = 1000;

class UVSim
{
private:
	int memory[MEM_SIZE] = {};
	int accumulator;
	int neg_flag = 0;
	int opCounter;

	bool debug = false;

public:
	UVSim();
	~UVSim();
	// Helper functions
	bool is_digits(const std::string& str);
	int retrieve_int();
	std::vector<std::string> retrieve_op();
	void flags(int checker);
	int flags();

	// Opcodes
	void read(int param);
	void write(int param);
	void load(int param);
	void store(int param);
	void add(int param);
	void addDirect(int param);
	void subtract(int param);

	void subtractDirect(int param);
	void multiply(int param);
	void divide(int param);
	void branch(size_t* place, int param);
	void branchneg(size_t* place, int param);
	void branchzero(size_t* place, int param);
	void halt();


	// Function for Main
	int execute();
	void memory_dump();
};