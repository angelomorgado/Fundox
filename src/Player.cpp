#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Player.h"

using namespace std;
// The vect here is a copy of vect in main()

//==================================================
// Default constructor of the class 'Player' 
Player::Player()
{
	name = "Undefined";
	score = 0;
	//int playerNum = 0;
	giveUp = false;
	this->color = numToColor();
}
//==================================================
 //Complete constructor of the class 'Player'
Player::Player(const string name, int score, const int playerNum)
{
	this->name = name;
	this->score = score;
	this->playerNum = playerNum;
	this->giveUp = false;
	this->color = numToColor();
}
//----------------------------------------------------
// MEMBER FUNCTIONS DEFINITION
//----------------------------------------------------

// Change the name of the player
void Player::setName(const std::string& name) {
	this->name = name;
}
//==================================================
//Change the score of the player
void Player::setScore(unsigned int score) {
	this->score = score;
}
//==================================================
void Player::setPlayerNum(const int& playerNum) {
	this->playerNum = playerNum;
}
//==================================================
//setGiveUp
void Player::setGiveUp(bool giveUp) {
	this->giveUp = giveUp; //mesma coisa do passTurn
}
//==================================================
//Return the name of the player
std::string Player::getName() const {
	return name;
} // getName
//==================================================
// Return the text color of the player
int Player::getColor() const {
	return color;
}
//==================================================
// Return score of the player
int Player::getScore() const {
	return score;
} // 
//==================================================
//Return the Player ID (number)
int Player::getPlayerNum() const {
	return playerNum; // ou return this->passTurn;
}// 
//==================================================
// Return giveUP 
bool Player::getGiveUp() {
	return giveUp;
}
//==================================================
// Update the Player's score
void Player::updateScore() {
	score++;
}
//==================================================
// Update the Player's score
int Player::numToColor() {
	switch (playerNum)
	{
	case 1:
		return 31;
	case 2:
		return 34;
	case 3:
		return 32;
	case 4:
		return 35;
	//In case of error, shouldn't happen
	default:
		return 93;
	}
}