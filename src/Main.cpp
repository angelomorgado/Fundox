#include <iostream>
#include <fstream>
#include "Game.h"

using namespace std;

vector<string> split(string str, char delim)
{
    vector<string> list;
    string aux;

    for (size_t x = 0; x <= str.length(); x++)
    {
        if (str[x] == delim) 
        {
            list.push_back(aux);
            aux.erase();
        }else
        {
            aux = aux + str[x];
        }

        if (x == (str.length() - 1))
        {
            list.push_back(aux);
        }
    }

    return list;
}


int main() { 
    //Get the initial values from the file
    ifstream myReadFile("files/CONFIG.TXT");
    
    //GET WINNER POINTS
    string line; // definir a variavel line do tipo string
    getline(myReadFile, line);
    int maxScore = stoi(split(line, ' ').at(2));

    //GET THE NAME OF THE FILE CONTAINING VALID WORDS
    getline(myReadFile, line);
    string validWordsFile = split(line, ' ').at(2);

    // Dummy line containing 'Letters:'
    getline(myReadFile, line);

    //Use a while loop to get the letters and numbers associated
    vector<string> splittedString;

    //Initiate the bag
    vector<char> letterList;

    while (getline(myReadFile, line))
    {
        if (line.empty() || line.size() < 2)
        {
            break;
        }

        // Put the letters in a map structure
        splittedString = split(line, ' ');

        int letterQuantity = stoi(splittedString.at(2));
        string letter = splittedString.at(0);
        
        for(int i=0; i < letterQuantity; i++)
        {
            letterList.push_back(letter[0]);
        }
    }

    //Close the file
    myReadFile.close();

    
    //Ask input from user
    int playerQuantity;
    cout << "How many players? (2-4 players)" << '\n';
    cin >> playerQuantity;

    int numLines;
    cout << "Board dimensions: lines" << '\n';
    cin >> numLines;
    
    int numCols;
    cout << "Board dimensions: columns" << '\n';
    cin >> numCols;

    //Create the game
    Game game(playerQuantity, maxScore, validWordsFile, letterList, numLines, numCols);

    // If you want to see the words
    //game.showValidWordList();

    //game.teste();

    while (!game.getGameFinish())
    {
        game.playRound();
    }

	return 0;
}