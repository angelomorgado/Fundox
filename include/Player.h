#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;
class Player
{
	private:
		string name;
		int score;
		int color;
		int playerNum;
		bool giveUp;

	public:
		Player();
		Player(const string name, int score, const int playerNum);
		void setName(const std::string& name);
		void setScore(unsigned int score); // ver questão do & e do unsigned 
		void setPlayerNum(const int& playerNum);
		void setGiveUp(bool giveUp);
		string getName() const;
		int getScore() const;
		int getPlayerNum() const;
		bool getGiveUp();
		void updateScore();
		int numToColor();
		int getColor() const;
};
#endif // !PLAYER_H
#pragma once