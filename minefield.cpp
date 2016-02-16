#include <fstream>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <string>
#include "minefield.h"


const size_t Minefield::MIN_ROW_COUNT = 1;
const size_t Minefield::MAX_ROW_COUNT = 100;
const size_t Minefield::MIN_COL_COUNT = 1;
const size_t Minefield::MAX_COL_COUNT = 100;


Minefield::Minefield(size_t rowCount, size_t colCount) :
	m_rowCount(rowCount),
	m_colCount(colCount),
	m_data(NULL)
{
	// validate row count
	if(m_rowCount < MIN_ROW_COUNT || m_rowCount > MAX_ROW_COUNT)
		throw std::range_error("row count is out of range");
	
	// validate column count
	if(m_colCount < MIN_COL_COUNT || m_colCount > MAX_COL_COUNT)
		throw std::range_error("column count is out of range");
	
	// allocate and initialize data array
	size_t dataSize = m_rowCount * m_colCount;
	m_data = new bool[dataSize];
	for(size_t i = 0; i < dataSize; ++i)
		m_data[i] = false;
}


Minefield::~Minefield()
{
	// deallocate data array
	delete[] m_data;
}


void Minefield::validateCellPosition(size_t row, size_t col) const
{
	if(row > m_rowCount)
		throw std::range_error("row index is out of range");
	if(col > m_colCount)
		throw std::range_error("column index is out of range");
}


size_t Minefield::getCountOfMinesAroundCell(size_t row, size_t col) const
{
	// check whether given cell position is valid
	validateCellPosition(row, col);
	
	// determine whether this cell has rows in the both vertical directions
	bool hasTop = row > 0;
	bool hasBottom = row < m_rowCount - 1;

	// determine whether this cell has columns in the both horizontal directions
	bool hasLeft = col > 0;
	bool hasRight = col < m_colCount - 1;
	
	// count mines around
	size_t result = 0;
	if(hasTop && getCell(row-1, col)) ++result; 
	if(hasTop && hasRight && getCell(row-1, col + 1)) ++result; 
	if(hasRight && getCell(row, col+1)) ++result; 
	if(hasBottom && hasRight && getCell(row+1, col+1)) ++result; 
	if(hasBottom && getCell(row+1, col)) ++result; 
	if(hasBottom && hasLeft && getCell(row+1, col-1)) ++result; 
	if(hasLeft && getCell(row, col-1)) ++result; 
	if(hasTop && hasLeft && getCell(row-1, col-1)) ++result;
	
	return result;
}


void Minefield::printMinesMap(std::ostream& os) const
{
	for(size_t row = 0; row < m_rowCount; ++row)
	{
		for(size_t col = 0; col < m_colCount; ++col)
		{
			if(getCell(row, col))
				os << '*';
			else
				os << getCountOfMinesAroundCell(row, col);
		}
		os << std::endl;
	}
}


Minefield* Minefield::loadFromFile(const char* fileName)
{
	// object error message composition 
	std::ostringstream err;
	
	// open input file
	std::ifstream ifs(fileName);
	if(!ifs.is_open())
	{
		err << "failed to open input file '" << fileName << "'." << std::endl;
		throw std::runtime_error(err.str());
	}
	
	// initialize variables
	size_t lineNumber = 0, rowNumber = 0;
	size_t rowCount = 0, colCount = 0;
	std::string line;
	std::auto_ptr<Minefield> field;
	
	// read contents of an input file
	do {
		// increment current line number
		++lineNumber;
		
		// read subsequent line from the input file
		if(!std::getline(ifs, line)) 
		{
			if(lineNumber == 1)
				err << "failed to read header line from file '"<< fileName << "'";
			else
				err << "failed to read row #" << (lineNumber - 1) << " from file '" << fileName << "'";
			throw std::runtime_error(err.str());
		}

		// Mitigate text file line endings issue
		if (!line.empty() && line[line.length() - 1] == 0xD)
			line = line.substr(0, line.length() - 1);
		
		// parse header line
		if(lineNumber == 1)
		{
			std::istringstream iss(line);

			// read row count
			if(!(iss >> rowCount))
			{
				err << "failed to read row count from header line of the file '" << fileName << "'";
				throw std::runtime_error(err.str());
			}
			
			// read column count
			if(!(iss >> colCount))
			{
				err << "failed to read column count from header line of the file '"<< fileName << "'";
				throw std::runtime_error(err.str());
			}
			
			// create minefield object - sizes will be validated in constructor
			field.reset(new Minefield(rowCount, colCount));
			
			// continue to next input line
			continue;
		}
		
		// validate input line length
		size_t cellCount = line.length();
		if(cellCount != colCount)
		{
			err << fileName << "(" << lineNumber << "): Invalid cell count: " 
				<< cellCount << " (expecting " << colCount << ")"; 	
			throw std::runtime_error(err.str());
		}
		
		// parse input line contents
		for(size_t i = 0; i < cellCount; ++i)
		{
			char c = line[i];
			switch(c)
			{
				case '*':
				{
					field->setCell(rowNumber, i, true);
					break;
				}
				
				case '.':
				{
					field->setCell(rowNumber, i, false);
					break;
				}
				
				// otherwise report error and stop
				default:
				{
					err << fileName << "(" << lineNumber << ", " << (i + 1) 
						<< "): Illegal character '" << c << "' (only '.' and '*' are allowed here)";
					throw std::runtime_error(err.str());
				}
			}
		}
			
		++rowNumber;
		
	} while(rowNumber < rowCount);
	
	// close file
	ifs.close();

	// return object
	return field.release();
}

