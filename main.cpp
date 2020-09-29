#include <iostream>

using namespace std;

#include <iostream>

#include "Q.h"
#include "SARSA.h"

int main(int argc, char * argv[]) {

	QLearning q;
	q.qLearn();

	SARSA s;
	s.SARSALearn();

	return 0;

}