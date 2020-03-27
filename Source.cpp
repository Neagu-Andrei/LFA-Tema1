// Tema1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct edge {
	char cost;
	int next;
};

struct cond {
	edge* vect;
	int nrleg = -1;
	bool final = false;
};


bool acceptare(int startState, string word, cond* automata) {
	if (word == "")
		if (automata[startState].final)
			return true;
		else
			return false;
	else {
		for (int i = 0; i < automata[startState].nrleg+1; i++) {
			if (automata[startState].vect[i].cost == word.at(0)) {
				//std::cout << word << " " << startState << "\n";
				//string s = word.erase(0, 1);
				word.erase(0, 1);
				return acceptare(automata[startState].vect[i].next, word , automata);
			}
		}
		return false;
	}
	/*
	while (word != "") {
		for (int i = 0; i < automata[startState].nrleg; i++){
			if (automata[startState].vect[i].cost == word.at(0)){
				word.erase(0, 1);
				acceptare(automata[startState].vect[i].next);
			}
		}
	}
	*/
}

int main() {
	ifstream f("Input.txt");
	int startState, numberOfFinishStates, numberOfStates, numberOfEdges;
	f >> startState >> numberOfFinishStates >> numberOfStates >> numberOfEdges;
	cond* automata = new cond[numberOfStates];
	for (int i = 0; i < numberOfStates; i++)
		automata[i].vect = new edge[numberOfEdges];
	for (int i = 0; i < numberOfFinishStates; i++) {
		int finishState;
		f >> finishState;
		automata[finishState].final = true;
	}
	for (int i = 0; i < numberOfEdges; i++) {
		int start, finish;
		char c;
		f >> start >> finish >> c;
		automata[start].nrleg++;
		automata[start].vect[automata[start].nrleg].next = finish;
		automata[start].vect[automata[start].nrleg].cost = c;
	}
	string str;
	std::cout << "Citeste cuvantul: ";
	getline(std::cin, str);
	if (acceptare(startState, str, automata) or str == "lambda")
		std::cout << "Cuvant acceptat";
	else
		std::cout << "Cuvant neacceptat";
	f.close();
	return 0;
}