#pragma once

#ifndef BAG_H
#define BAG_H

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;
class Bag
{
	public:
		Bag();
		void fillBag(vector<char> bag);
		vector<char> updateBag(int quantity);
	private:
		vector<char> bag;
};
#endif // !BAG_H
#pragma once