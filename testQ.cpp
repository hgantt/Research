#include "Q.h"
#include <iostream>
#include <cmath>

using namespace std;

void testGetRandomAction(QLearning &q); // working


void testCon(QLearning &q);
void testGreedy(QLearning &q);
void testEpisode(QLearning &q);


int main() {

	QLearning q;
	testGetRandomAction(q);
	testCon(q);
	testGreedy(q);
	testEpisode(q);

}



void testGetRandomAction(QLearning &q) {

	int count = 0;
	char c;

	while (count < 10) {
		c = q.getRandomAction();
		cout << c << " ";
		count++;
	}

	cout << endl;
}

void testCon(QLearning &q) {

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << q.valueFunction[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << q.rewards[i][j] << "  ";
		}
		cout << endl;
	}

	cout << endl;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << q.S[i][j] << "  ";
		}
		cout << endl;
	}


	cout << "epsilon is: " << q.epsilon << endl;
}

void testGreedy(QLearning &q) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			q.valueFunction[i][j] = i / j;
		}
	}

cout << endl;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << q.valueFunction[i][j] << " ";
		}
		cout << endl;
	}

cout << endl;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			q.currentState[0] = i;
			q.currentState[1] = j;
			cout << q.getGreedyAction() << " ";
		}
		cout << endl;
	}

	q.currentState[0] = 9;
	q.currentState[1] = 3;
	cout << q.getGreedyAction() << endl;
	for (int i = 0; i < 3; i++)
		cout << q.actionsArray[i] << " ";

	cout << endl;
	
}

void testEpisode(QLearning &q) {
	q.doEpisode();
}

	// QLearning();


	// void writePolicy(int episode);
	// void doEpisode();
	// void takeAction();
	// void qLearn();