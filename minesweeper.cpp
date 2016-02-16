#include <iostream>
#include <stdexcept>
#include <memory>
#include "minefield.h"

int main(int argc, char** argv)
{
	std::auto_ptr<Minefield> field;
	
	try 
	{
		// check for required number of the command line arguments
		if(argc < 2) throw std::runtime_error("missing input file name");
		
		// load data from file
		field.reset(Minefield::loadFromFile(argv[1]));
	
		// process data
		field->printMinesMap(std::cout);
	}
	catch(std::exception& ex)
	{
		std::cerr << "Error: " << ex.what() << '.' << std::endl;
		return 1;
	}
	
	return 0;
}
