#pragma once

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;
class Board
{
	public:
		Board();
		Board(int numLines, int numCols, char value);
		void show();
		void setBoardTile(int posx, int posy, char c, int color);
		char getBoardTile(int posx, int posy);
		int getLineCoordinate(char posx);
		int getColumnCoordinate(char posy);
		vector<vector<int>> getColorBoard();
		vector<vector<char>> getBoard(); 
		void cloneBoard(Board b);
		vector<int> getScores();

	private:
		int numLines;
		int numCols;
		vector<vector<char>> board; //numCols = board.at(1).size()
		vector<vector<int>> colorBoard;
};
#endif // !BOARD_H
#pragma once