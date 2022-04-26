#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "Game.h"

using namespace std;

Game::Game()
{

}

Game::Game(int playerQuantity, int maxScore, string validWordsFileName, vector<char> letterList, int numLines, int numCols)
{
	this->playerQuantity = playerQuantity;
	this->maxScore = maxScore;
	this->validWordsList = getValidWordsFromFile(validWordsFileName);
	this->playerList = getPlayerList(playerQuantity);
	this->board = new Board(numLines, numCols, ' ');
	this->gameFinished = false;
	this->currentRound = 0;
	this->currentPlayer = 0;
	this->numLines = numLines;
	this->numCols = numCols;
	this->letterlist = letterList;
	bag.fillBag(letterList);
	rack.fillRack(bag.updateBag(7 - rack.getSize()));
	numberOfPasses = 0;
	numberOfGivenUpRounds = 0;
}

vector<string> Game::getValidWordsFromFile(string fileName)
{

	fileName.erase(std::remove(fileName.begin(), fileName.end(), '\n'), fileName.end());
	fileName.erase(fileName.size() - 1);
	fileName = "files/" + fileName;

	vector<string> validWordsList;
	string line;
	ifstream wordsFile;

	//"WORDS_EN.TXT"
	wordsFile.open(fileName, ios::in);

	cout << fileName << endl;

	if(fileName == "WORDS_EN.TXT")
	{
		cout << "São iguais wtf\n";
	}

	if(!wordsFile)
    {
        cout << "Error opening file\n";
    } 

	while (getline(wordsFile, line))
	{
		if (line.empty() || line.size() < 2)
        {
            break;
        }

		line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
		line.erase(line.size() - 1);
		validWordsList.push_back(line);
	}

	return validWordsList;
}

vector<Player> Game::getPlayerList(int playerQuantity)
{
	vector<Player> playerList;

	for (int i = 1; i <= playerQuantity; i++)
	{
		string s = "Player" + to_string(i);
		Player player(s, 0, i);
		playerList.push_back(player);
	}

	return playerList;
}


void Game::showValidWordList()
{
	for(uint8_t i=0; i < validWordsList.size(); i++)
	{
		cout << validWordsList.at(i) << endl;
	}
}

bool Game::checkWordExistence(string word)
{
	for (size_t i = 0; i < validWordsList.size(); i++)
	{
		if (word.compare(validWordsList.at(i)) == 0)
		{
			return true;
		}
	}
	return false;
}

bool Game::checkpositions(int line, int col)
{
	if (line <= numLines && line >= 0 && col <= numCols && col >= 0)
	{
		return true;
	}

	return false;
}

void Game::teste()
{
	cout << "Lista de jogadores\n";
	for (size_t i = 0; i < playerList.size(); i++)
	{
		cout << "Nome: " << playerList.at(i).getName() << endl;
	}

	cout << "Board:\n";

	board->show();

	rack.fillRack(bag.updateBag(7 - rack.getSize()));

	rack.showRack();
}

string Game::stringToUpper(string s)
{
	for (size_t i = 0; i < s.size(); i++)
	{
		s.at(i) = toupper(s.at(i));
	}
	return s;
}

string Game::stringToLower(string s)
{
	for (size_t i = 0; i < s.size(); i++)
	{
		s.at(i) = tolower(s.at(i));
	}
	return s;
}

void Game::showScoreboard()
{
	cout << "Scoreboard:\n";
	
	for (int i = 0; i < playerQuantity; i++)
	{
		//colocar cor
		cout << playerList.at(i).getName() << ": " + to_string(playerList.at(i).getScore());

		if (playerList.at(i).getGiveUp())
		{
			cout << " (gave up)";
		}

		cout << endl;
	}

}

bool Game::getGameFinish()
{
	return gameFinished;
}

bool Game::allPlayersGivenUp()
{
	int counter = 0;
	for (int i = 0; i < playerQuantity; i++)
	{
		if (playerList.at(i).getGiveUp())
		{
			counter++;
		}
	}

	if (counter == playerQuantity)
	{
		return true;
	}

	return false;
}

void Game::getWinner()
{
	vector<int>playerScores = board->getScores();

	int winner = max_element(playerScores.begin(), playerScores.end()) - playerScores.begin();

	cout << "The winner is " << playerList.at(winner).getName() << " with " << to_string(playerList.at(winner).getScore()) << "points!\n";
}


//Displays the current round
void Game::playRound()
{
	//Control variable to check if the play is valid
	bool validPlay = true;

	//Control variable that will count how many times it intercepts with another word
	int interceptCounter = 0;

	//Unused letters vector
	vector<char> usedLetters;

	//Stores the initial rack so it can be updated later
	Rack auxRack;
	auxRack.cloneRack(rack);

	//Checks if the current player has given up, if yes, then pass to the next
	if (playerList.at(currentPlayer).getGiveUp() == true)
	{
		currentPlayer++;
		
		//When the first player plays again
		if (currentPlayer >= playerQuantity)
		{
			currentPlayer = 0;
			numberOfPasses = 0;
		}

		//If all players give up
		if (allPlayersGivenUp())
		{
			gameFinished = true;
			getWinner();
		}

		return;
	}

	cout << "\n\n\n===================================================================================\n";
	
	//Information screen
	cout << "Round " + to_string(currentRound) << endl;
	cout << endl;
	showScoreboard();
	cout << endl;
	cout << "Current player -> " << playerList.at(currentPlayer).getName() << endl << endl;
	board->show();
	cout << endl;

	//Show rack
	cout << "Rack:\n";
	rack.showRack();
	cout << endl;


	//Ask for information
	string word;
	char lineAux;
	char colAux;
	int line;
	int col;
	char orientation;

	cout << "Insert the word (Pass: press 'p' | Give up: press 'q'): ";
	cin >> word;

	//word.erase(std::remove(word.begin(), word.end(), '\n'), word.end());

	//If the player passes
	if (word.compare("p") == 0)
	{
		//Updates the current player
		currentPlayer++;

		//When the first player plays again
		if (currentPlayer >= playerQuantity)
		{
			currentPlayer = 0;
			numberOfPasses = 0;
		}

		//Updates the current round
		currentRound++;

		numberOfPasses++;

		if (numberOfPasses == playerQuantity)
		{
			//Empty the rack and reffils it
			rack.updateRack(auxRack.getRack());
			rack.fillRack(bag.updateBag(7 - rack.getSize()));
			currentPlayer = 0;
			numberOfPasses = 0;
			numberOfGivenUpRounds++;
		}

		//If 3 consecutive rounds are skipped
		if (numberOfGivenUpRounds == 3)
		{
			gameFinished = true;
			getWinner();
		}

		return;
	}

	if (word.compare("q") == 0)
	{
		playerList.at(currentPlayer).setGiveUp(true);
		return;
	}

	word = stringToUpper(word);

	cout << "Line? (A - " << (char)('A' + numLines - 1) << "): ";
	cin >> lineAux;
	//Ascii code of the letter
	line =  lineAux - 65;

	cout << "Column? (a - " << (char)('a' + numCols - 1) << "): ";
	cin >> colAux;
	//Ascii code of the letter
	col = colAux - 97;

	//check if the position is invalid
	if (!checkpositions(line, col))
	{
		cout << "\n---------------------------\n";
		cout << "Error! Invalid positions!\n";
		cout << "---------------------------";
		return;
	}

	cout << "Orientation? (V/H): ";
	cin >> orientation;

	//Creates an auxiliary board
	Board *auxBoard = new Board();
	auxBoard->cloneBoard(*board);


	if (orientation == 'V' || orientation == 'v')
	{
		for (uint8_t i = 0; i < word.size(); i++)
		{
			if (line + i >= numLines)
			{
				cout << "\n---------------------------\n";
				cout << "Error! Word doesn't fit!\n";
				cout << "---------------------------";
				rack.cloneRack(auxRack);
				return;
			}

			//Check if letter is invalid
			if (!rack.checkLetter(word.at(i)) && auxBoard->getBoardTile(line + i, col) != word.at(i))
			{
				validPlay = false;
			}

			if (auxBoard->getBoardTile(line+i, col) == word.at(i))
			{
				interceptCounter++;
			}
			else
			{
				usedLetters.push_back(word.at(i));
				rack.updateRack(usedLetters);
			}

			//Update the word and color matrix
			auxBoard->setBoardTile(col, i + line, word.at(i), playerList.at(currentPlayer).getColor());
		}

	}
	else if (orientation == 'H' || orientation == 'h')
	{
		for (uint8_t i = 0; i < word.size(); i++)
		{
			if (col + i >= numCols)
			{
				cout << "\n---------------------------\n";
				cout << "Error! Word doesn't fit!\n";
				cout << "---------------------------";
				rack.cloneRack(auxRack);
				return;
			}

			//Check if letter is invalid
			if (!rack.checkLetter(word.at(i)) && auxBoard->getBoardTile(line, col + i) != word.at(i))
			{
				validPlay = false;
			}

			if (auxBoard->getBoardTile(line,col + i) == word.at(i))
			{
				interceptCounter++;
			}
			else
			{
				usedLetters.push_back(word.at(i));
				rack.updateRack(usedLetters);
			}

			//Update the word and color matrix
			auxBoard->setBoardTile(i + col, line, word.at(i), playerList.at(currentPlayer).getColor());
		}
	}

	//Check if the word doesn't exist in the file
	if (!checkWordExistence(stringToLower(word)))
	{
		cout << "\n---------------------------\n";
		cout << "Error! Word is invalid!\n";
		cout << "---------------------------";
		rack.cloneRack(auxRack);
		return;
	}

	//Check if it is connected to another word
	if (interceptCounter == 0 && currentRound > 0)
	{
		cout << "\n---------------------------\n";
		cout << "Error! Word must be connected to another word!\n";
		cout << "---------------------------";
		rack.cloneRack(auxRack);
		return;
	}

	//check if the letter is in the rack or coinciding with another already on the board
	if (!validPlay)
	{
		cout << "\n---------------------------\n";
		cout << "Error! Letter not in the rack or intercepting\n";
		cout << "---------------------------";
		rack.cloneRack(auxRack);
		return;
	}




	//=================== In case of valid play =======================

	//Update the board
	board->cloneBoard(*auxBoard);

	//Update rack
	rack.cloneRack(auxRack);
	rack.updateRack(usedLetters);
	rack.fillRack(bag.updateBag(7 - rack.getSize()));

	//Reset the number of given up rounds
	numberOfGivenUpRounds = 0;

	//Update scores
	vector<int>playerScores = board->getScores();

	for (size_t i = 0; i < playerList.size(); i++)
	{
		playerList.at(i).setScore(playerScores.at(i));
	}

	//Game ending conditions
	if (playerList.at(currentPlayer).getScore() >= maxScore)
	{
		getWinner();
		gameFinished = true;
		return;
	}

	//Update the player
	currentPlayer++;
	
	//When the first player plays again
	if (currentPlayer >= playerQuantity)
	{
		currentPlayer = 0;
		numberOfPasses = 0;
	}

	//Updates the current round
	currentRound++;
}
