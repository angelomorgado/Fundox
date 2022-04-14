#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "../include/Bag.h"

using namespace std;
// The vect here is a copy of vect in main()

Bag::Bag()
{
	
}

void Bag::fillBag(vector<char> bag) {
	this->bag = bag;
}

vector<char> Bag::updateBag(int quantity) {
	int randNum;
	vector<char> aux;
	for (int i = 0; i < quantity; i++){
		//Find the random element to put in the rack
		randNum = rand() % (bag.size()-1);

		//Add that element to an auxiliary list
		aux.push_back(bag.at(randNum));

		//Eliminate it from the bag
		bag.erase(bag.begin() + randNum);
	}
	
	return aux;
}

