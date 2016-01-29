/**
*  @author Jimmy Lindsey
*  @date 1/29/2016
*  @version 1.1
*  @file main.cpp
*/
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;


#include "sudoku.h"

int main()
{
	bool run = true;
	cout << "Welcome to Jimmy Lindsey's Sudoku Solver" << endl;
	while (run)
	{
		cout << "Enter 1 through 5 to solve a Sudoku of that difficulty," << endl;
		cout << "enter 6 to try an unsolvable sudoku, enter 7 to try your own sudoku," << endl; 
		cout << "or enter 0 to quit." << endl;
		int num;
		cin >> num;
		cout << endl;
		Sudoku s;
		if (num == 1)
			s.open("1star.txt");
		else if (num == 2)
			s.open("2star.txt");
		else if (num == 3)
			s.open("3star.txt");
		else if (num == 4)
			s.open("4star.txt");
		else if (num == 5)
			s.open("5star.txt");
		else if (num == 6)
			s.open("impossible.txt");
		else if (num == 7)
		{
			cout << "Type in pathway to the file. If you have added the file to this folder, then just type in the file's name" << endl;
			string sudoku;
			cin >> sudoku;
			s.open(sudoku);
		}
		else if (num == 0)
		{
			cout << "Closing Jimmy Lindsey's Sudoku Solver. Have a nice day!" << endl;
			break;
		}
		else
			cout << "Invalid entry. Please try again" << endl;
		if (s.getFailState())
		{
			cout << "File failed to open. Make sure you entered the corret pathway." << endl;
			break;
		}
		else
			cout << "Opening " << s.getFilename() << endl << endl;
		s.print();
		cout << endl;
		cout << "Solving using backtracking" << endl << endl;
		if (s.backtrack())
		{
			s.print();
		}
		else
		{
			cout << "The Sudoku entered cannot be solved." << endl << endl;
		}
	}


	return 0;
}