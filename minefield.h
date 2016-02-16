#ifndef MINEFIELD_H
#define MINEFIELD_H


#include <cstddef>
#include <ostream>


class Minefield 
{
public:
	
	static Minefield* loadFromFile(const char* filename);
	
	Minefield(size_t rowCount, size_t colCount);
	
	~Minefield();
	
	size_t getRowCount() const { return m_rowCount; }

	size_t getColCount() const { return m_colCount; }
	
	bool getCell(size_t row, size_t col) const { return m_data[getCellDataIndex(row, col)]; }
	
	void setCell(size_t row, size_t col, bool value) { m_data[getCellDataIndex(row, col)] = value; }
	
	size_t getCountOfMinesAroundCell(size_t row, size_t col) const;
	
	void printMinesMap(std::ostream& os) const;
		
private:
	void validateCellPosition(size_t row, size_t col) const;
	
	size_t getCellDataIndex(size_t row, size_t col) const
	{
		validateCellPosition(row, col);
		return row*m_colCount + col;
	}
		
	size_t m_rowCount;
	size_t m_colCount;
	bool* m_data;
	
	// disallow copying & assignment 
	// by declaring copy constructor and assignment operator as private member functions
	Minefield(const Minefield&);
	Minefield& operator=(const Minefield&);

	// field size limitation constants
	static const size_t MIN_ROW_COUNT;
	static const size_t MAX_ROW_COUNT;
	static const size_t MIN_COL_COUNT;
	static const size_t MAX_COL_COUNT;
};


#endif
