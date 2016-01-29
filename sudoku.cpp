#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "sudoku.h"



Sudoku::Sudoku()
{
	vector<vector<int>> sudoku(9, vector<int>(9));
	grid = sudoku;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			grid[i][j] = 0;
		}

	}
}


Sudoku::Sudoku(string file)
{
	filename = file;
	vector<vector<int>> sudoku(9, vector<int>(9));
	grid = sudoku;
	ifstream puzzle;
	puzzle.open(filename);
	if (puzzle.fail())
	{
		failstate = true;;
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			puzzle >> grid[i][j];
		}
	}
}


std::string Sudoku::getFilename() const
{
	return filename;
}

bool Sudoku::getFailState() const
{
	return failstate;
}

void Sudoku::open(string file)
{
	filename = file;
	ifstream puzzle;
	puzzle.open(file);
	if (puzzle.fail())
	{
		failstate = true;;
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			puzzle >> grid[i][j];
		}
	}
}


void Sudoku::print() const
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (grid[i][j] == 0)
				cout << " ";
			else
				cout << grid[i][j];
			if (j != 2 && j != 5)
				cout << " ";
			if (j == 2 || j == 5)
				cout << "|";
		}
		cout << endl;
		if (i == 2 || i == 5)
		{
			cout << "-----+-----+-----" << endl;
		}
	}
	cout << endl;
}

/**
 * Checks the created vector (of a Sudoku unit)
 * to see if there any numbers that are the same
 * Note: no 0's are passed to this function
 * @param the vector of the unit
 * @return true if there is a match, false if there isn't
 */
bool Sudoku::checkUnique(const vector<int>& a)
{
	int size = a.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i != j && a[i] == a[j])
				return true;
		}
	}
	return false;
}

/**
 * Tests a sudoku row
 * @param the row to test
 * @return true if an error in the sudoku is found
 */
bool Sudoku::testRow(const int& row)
{
	vector<int> test;
	for (int x = 0; x < 9; x++)
	{
		if (grid[row][x] != 0)
		{
			test.push_back(grid[row][x]);
		}
	}
	return checkUnique(test);

}

/**
 * Tests a sudoku column
 * @param the column to test
 * @return true if an error in the sudoku is found
 */
bool Sudoku::testCol(const int& col)
{
	vector<int> test;
	for (int y = 0; y < 9; y++)
	{
		if (grid[y][col] != 0)
		{
			test.push_back(grid[y][col]);
		}
	}
	return checkUnique(test);
}


/**
 * Tests a sudoku 3x3 square
 * Note: only works with the numbers 0, 3, 6
 * @param the row to test
 * @param the column to test
 * @return true if an error in the sudoku is found
 */
bool Sudoku::test3x3(const int& row, const int& col)
{
	vector<int> test;
	for (int i = row; i <= row + 2; i++)
	{
		for (int j = col; j <= col + 2; j++)
		{
			if (grid[i][j] != 0)
			{
				test.push_back(grid[i][j]);
			}
		}
	}
	return checkUnique(test);
}

/**
 * Checks to see if the Sudoku has broken any rules
 * And therefore, if it should be rejected
 * @return true if an error in the sudoku is found
 */
bool Sudoku::reject()
{
	for (int i = 0; i < 9; i++)
	{
		if (testRow(i))
			return true;
		if (testCol(i))
			return true;
	}
	vector<int> test = {0, 3, 6};
	for (int e : test)
	{
		for (int f : test)
		{
			if (test3x3(e, f))
				return true;
		}
	}
	return false;
}

/**
 * Tests to see if a sudoku is complete
 * @return true if the sudoku is complete
 */
bool Sudoku::accept()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (grid[i][j] == 0)
				return false;
		}
	}
	return true;
}

/**
 * Creates the possible successor states of the sudoku
 * These sudokus are similar to each other, but in one
 * [row][column] the number is 1-9, one for each sudoku
 * @return a vector of 9 sudokus
 */
vector<Sudoku> Sudoku::successor()
{
	vector<Sudoku> successor;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (grid[i][j] == 0)
			{
				for (int x = 1; x < 10; x++)
				{
					grid[i][j] = x;
					successor.push_back(*this);
				}
				return successor;
			}
		}
	}
	return successor;
}


bool Sudoku::backtrack()
{
	if (reject())
		return false;
	if (accept())
		return true;
	vector<Sudoku> next = successor();
	for (Sudoku s : next)
	{
		bool res = s.backtrack();
		if (res)
		{
			grid = s.grid;
			return res;
		}
	}

	return false;
}