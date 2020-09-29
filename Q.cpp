#include "Q.h"

#include <fstream>
#include <iostream>
#include <ctime>

using namespace std; 

QLearning::QLearning() {
	srand(time(NULL));
	EPSILON = .9;
	readStates();

	for (int s = 0; s < 100; s++) {
		for (int a = 0; a < 4; a++) {
			if (S[s] == 'H')
				Q[s][a] = -50;
			else if (S[s] == 'G')
				Q[s][a] = 100;
			else 
				Q[s][a] = 0;
		}
	}
	currentState = 70;
}

void QLearning::qLearn() {
	int episode = 1;

	while (episode <= 2000) {
		if (episode % 100 == 0) {
			writePolicy(episode);
		}
		if (episode % 10 == 0) {
			EPSILON = .9 / (episode/10);
		}
		if (episode == 1000) {
			EPSILON = 0.0;
		}

		doEpisode();
		episode++;
	}
}

void QLearning::writePolicy(int episode) {
	ofstream outfile;
	outfile.open("QLearningPolicies.txt", ios_base::app);

	for (int s = 0; s < 100; s++) {
		int optAction = getGreedyAction(s);
		if (S[s] == 'H') policy[s] = 'H';
		else if (S[s] == 'G') policy[s] = 'G';
		else if (S[s] == 'S') policy[s] = 'S';
		else if (optAction == 0) policy[s] = 'U';
		else if (optAction == 1) policy[s] = 'D';
		else if (optAction == 2) policy[s] = 'L';
		else policy[s] = 'R';
	}

	outfile << "Episode: " << episode << endl << endl;
	for (int i = 0; i < 100; i++) {
	 	outfile << policy[i];
	 	if (i % 10 == 9)
	 		outfile << endl;
	}
	outfile << endl;
	outfile.close();
}

void QLearning::doEpisode() {
	int actionsTaken = 0;

	currentState = 70;

	while (currentState != 79 and actionsTaken < 1000) { 
		takeAction();
		actionsTaken++;
	}
}

void QLearning::takeAction() {
	int randProb = rand() % 100 + 1; // randprob between 1...100
	int action;
	if (randProb > (100 * EPSILON))
		action = getGreedyAction(currentState);
	else 
		action = getRandomAction();

	int sOriginal = currentState;

	move(action);

	int reward = rewards[currentState];

	Q[sOriginal][action] = reward + 
				(GAMMA * Q[currentState][getGreedyAction(currentState)]);

	if (S[currentState] == 'H') 
		currentState = sOriginal;
}

int QLearning::getGreedyAction(int state) {
  	int indexOfMax = 0;
  	for (int a = 0; a < 4; a++) {
  		if (Q[state][a] > Q[state][indexOfMax]) { 
  			indexOfMax = a;
  		}
  	}
  	return indexOfMax;
}

int QLearning::getRandomAction() {
	return rand() % 4;
}

void QLearning::readStates() {
	ifstream inFile;
	char c;
	inFile.open("IceWorld.txt");
	int numEndls = 0;

	for (int i = 0; i < 109; i++) {
		inFile.get(c);
		if (c != '\n') {
			S[i-numEndls] = c;
		}
		if (c == 'H')
			rewards[i-numEndls] = -50; 
		else if (c == 'O' or c == 'I' or c == 'S')
			rewards[i-numEndls] = -1;
		else if (c == 'G')
			rewards[i-numEndls] = 100;
		else if (c == '\n') {
			numEndls++;
			continue;
		}
	}
	inFile.close();
}

void QLearning::move(int action) {
	// normal movement
	if (S[currentState] != 'I') {
		moveNormal(action);
	} else
		moveFromIce(action);
}

void QLearning::moveNormal(int action) {
	// upward movement, if not in top row
	if (action == 0) {
		moveUp();
	// downward movement, if not in bottom row
	} else if (action == 1) {
		moveDown();
	// leftward movement, if not in left column of states
	} else if (action == 2) {
		moveLeft(); 
	// rightward movement, if not in right column of states
	} else if (action == 3) {
		moveRight();
	} else
		return;
}

void QLearning::moveUp() {
	if (currentState >= 10)
		currentState -= 10;
}

void QLearning::moveDown() {
	if (currentState < 90)
		currentState += 10;	
}

void QLearning::moveLeft() {
	if (currentState % 10 != 0)
		currentState -= 1; 
}

void QLearning::moveRight() {
	if (currentState % 10 != 9)
		currentState += 1;
}

void QLearning::moveFromIce(int action) {
	int randProb = rand() % 100 + 1; // randprob between 1...100
	if (randProb <= 80) {
		moveNormal(action);
	} else if (randProb > 80 and randProb <= 90) {
		if (action == 0) {
			moveUp();
			moveLeft();
		} else if (action == 1) {
			moveDown(); 
			moveRight();
		} else if (action == 2) {
			moveLeft();
			moveDown();
		} else {
			moveRight();
			moveUp();
		}
	} else {
		if (action == 0) {
			moveUp();
			moveRight();
		} else if (action == 1) {
			moveDown(); 
			moveLeft();
		} else if (action == 2) {
			moveLeft();
			moveUp();
		} else {
			moveRight();
			moveDown();
		}
	}
}