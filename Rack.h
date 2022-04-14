#pragma once

#ifndef RACK_H
#define RACK_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
class Rack
{
	public:
		Rack();
		void fillRack(vector<char> newLetters);
		void showRack();
		void updateRack(vector<char> usedLetters);
		int getSize();
		bool checkLetter(char c);
		void cloneRack(Rack r);
		vector<char> getRack();
	private:
		vector<char> rack;
};
#endif // !RACK_H
#pragma once