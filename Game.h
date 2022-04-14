#pragma once

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "Player.h"
#include "Bag.h"
#include "Board.h"
#include "Rack.h"

using namespace std;
class Game
{
	private:
		int playerQuantity;
		int maxScore;
		vector<string> validWordsList;
		vector<Player> playerList;
		Board *board; //Para aceder as funcoes da board tem que se utilizar a '->' em vez do '.'
		Rack rack;
		Bag bag;
		bool gameFinished;
		int currentRound;
		int currentPlayer;
		vector<char> letterlist;
		int numLines;
		int numCols;
		void showScoreboard();
		string stringToUpper(string s);
		bool checkWordExistence(string word);
		bool checkpositions(int line, int col);
		string stringToLower(string s);
		int numberOfPasses;
		int numberOfGivenUpRounds;
		bool allPlayersGivenUp();

	public:
		Game();
		Game(int playerQuantity, int maxScore, string validWordsFileName, vector<char> letterList, int numLines, int numCols);
		vector<string> getValidWordsFromFile(string fileName);
		void showValidWordList();
		vector<Player> getPlayerList(int playerQuantity);
		void playRound();
		bool getGameFinish();
		void teste();
		void getWinner();
	};
#endif // !GAME_H
#pragma once