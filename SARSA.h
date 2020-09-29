#ifndef SARSA_H
#define SARSA_H

class SARSA {

public:

	SARSA();
	void SARSALearn();

private:
	// private methods
	void writePolicy(int episode);
	void doEpisode();
	int getRandomAction();
	void takeAction();
	int getGreedyAction(int state);
	void readStates();
	void move(int action);
	void moveNormal(int action);
	void moveFromIce(int action);
	void moveRight();
	void moveUp();
	void moveLeft();
	void moveDown();

	// data members
	char S[100];
	int rewards[100];
	float Q[100][4];
	char policy[100];
	int currentState;


	double EPSILON;
	const double GAMMA = .9;


};

#endif