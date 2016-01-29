/**
@file sudoku.h
@author Jimmy Lindsey
@version 1/29/2014
Declarations for Sudoku Solver
*/

#ifndef SUDOKU_H_
#define SUDOKU_H_
#include <vector>
#include <string>

class Sudoku
{
public:
	//default constructor
	Sudoku();

	/**
	 * constructor, does the same thing as open()
	 * if the Sudoku is constructed this way
	 */
	Sudoku(std::string file);

	/**
	 * returns the name of the file associated with the sudoku
	 * @return the filename
	 */
	std::string getFilename() const;

	/**
	 * @return the bool value of whether the file could be opened
	 */
	bool Sudoku::getFailState() const;

	/**
	 * Opens the file and fills in the numbers in grid
	 * Also sets the failstate to true if the file doesn't open
	 * @param file the file to be opened
	 */
	void open(std::string file);

	/**
	 * Prints the sudoku
	 */
	void Sudoku::print() const;

	/**
	* Uses backtracking to solve the sudoku
	* @return true if the sudoku can be solved
	* also modifies grid, the 2D vector that
	* holds the Sudoku. If backtrack returns
	* true, then grid is modified so that it
	* has the answer to the sudoku puzzle
	*/
	bool Sudoku::backtrack();

private:
	//data members
	vector<vector<int>> grid;
	std::string filename;
	bool failstate = false;
	/**
	 * helper functions
	 * to see commments about what each one does
	 * view sudoku.cpp
	 */
	vector<Sudoku> successor();
	bool reject();
	bool accept();
	bool test3x3(const int& row, const int& col);
	bool testCol(const int& col);
	bool testRow(const int& row);
	bool checkUnique(const vector<int>& a);

};

#endif