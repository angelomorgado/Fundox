#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include "Rack.h"

using namespace std;

Rack::Rack()
{

}

void Rack::showRack() 
{
	for (size_t i = 0; i < rack.size(); i++)
	{
		cout << rack.at(i) << " ";
	}
	cout << endl;
}

//Deletes the used letters
void Rack::updateRack(vector<char> usedLetters)
{
	for (size_t i = 0; i < usedLetters.size(); i++)
	{
		for (size_t f = 0; f < rack.size(); f++)
		{
			if (rack.at(f) == usedLetters.at(i))
			{
				rack.erase(rack.begin() + f);
				break;
			}
		}
	}
}

vector<char> Rack::getRack()
{
	return rack;
}

void Rack::cloneRack(Rack r)
{
	rack = r.getRack();
}

int Rack::getSize()
{
	return rack.size();
}

//Letter exists?
bool Rack::checkLetter(char c)
{
	for (size_t i = 0; i < rack.size(); i++)
	{
		if (c == rack.at(i))
		{
			return true;
		}
	}
	return false;
}


//Fills/Refills the rack
void Rack::fillRack(vector<char> newLetters)
{
	if (newLetters.size() <= 7 && newLetters.size() >= 0)
	{
		//Concatenate the newLetters vector into the rack vector
		rack.insert(rack.end(), newLetters.begin(), newLetters.end());

		//Sort rack
		sort(rack.begin(),rack.end());
	}
}