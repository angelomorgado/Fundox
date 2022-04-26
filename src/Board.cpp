#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Board.h"

using namespace std;
// The vect here is a copy of vect in main()

Board::Board()
{
}

Board::Board(int numLines, int numCols, char value)
{
	this->numLines = numLines;
	this->numCols = numCols;
	board = vector<vector<char>>(this->numLines, vector<char>(this->numCols, value));
	colorBoard = vector<vector<int>>(this->numLines, vector<int>(this->numCols, -1));
}
// returns the number of the line
int Board::getLineCoordinate(char posx)
{
	// 'a' ASCII code = 97
	return ((int)(posx)-97 + 1);
}
int Board::getColumnCoordinate(char posy)
{
	// 'A' ASCII code = 65
	return ((int)(posy)-97 + 1);
}
void Board::setBoardTile(int posx,int posy, char c, int color)
{
	board.at(posy).at(posx) = c;
	colorBoard.at(posy).at(posx) = color;
}
char Board::getBoardTile(int posx, int posy)
{
	return  board.at(posx).at(posy);
}

vector<int> Board::getScores()
{
	vector<int> vect{ 0, 0, 0, 0 };

	for (int i = 0; i < numLines; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			switch (colorBoard.at(i).at(j))
			{
				case 31:
					vect[0]++;
					continue;
				case 34:
					vect[1]++;
					continue;
				case 32:
					vect[2]++;
					continue;
				case 35:
					vect[3]++;
					continue;
			}
		}
	}

	return vect;
}

vector<vector<char>> Board::getBoard()
{
	return board;
}

void Board::cloneBoard(Board b)
{
	board = b.getBoard();
	colorBoard = b.getColorBoard();
}

void Board::show()
{
	//Initial space to make it look like a table
	cout << "  ";

	char letterlin = 'A';

	//Draw the columns
	for (int i = 0; i < numCols; i++)
		cout << (char)('a' + i) << "  ";
	cout << endl;

	//Draw the lines
	for (int i = 0; i < numLines; i++)
	{
		cout << letterlin++ << ' ';
		for (int j = 0; j < numCols; j++)
		{
			cout << "\033[" << colorBoard.at(i).at(j) << "m" << board.at(i).at(j) << ' ' << "\033[0m" << " ";
		}
		cout << endl;
	}
	cout << endl;
}

vector<vector<int>> Board::getColorBoard()
{
	return colorBoard;
}