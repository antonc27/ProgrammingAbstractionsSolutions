#include "simpio.h"
#include <iostream>
#include <fstream>
#include "vector.h"
#include "map.h"
#include "random.h"

void readFile(ifstream &file) {
	while (true)
	{
		cout << "Please enter filename containing source text: ";
		string s = GetLine();
		file.open(s.c_str());
		if (!file.fail()) break;
		cout << "Bad file name, enter again!" << endl;
		file.clear();
	}
}

int getOrder() {
	int order;
	while (true) {
		cout << "What order of analysis? (a number from 1 to 10): ";
		order = GetInteger();
		if (1 <= order && order <= 10) break;
		cout << "Try again!" << endl;
	}
	return order;
}

void fillModel(int order, ifstream &file, Map<Vector<char>> &model) {
	string sequence;
	for (int i=0; i<order; i++) {
		sequence += file.get();
	}

	int nextInt;
	char nextChar;
	while ((nextInt = file.get()) != EOF) {
		nextChar = (char)nextInt;
		
		model[sequence].add(nextChar);

		sequence += nextChar;
		sequence = sequence.substr(1);
	}
	file.close();
}

string getInitialSeed(Map<Vector<char>> &model) {
	string seed;
	int maxFreq = 0;
	Map<Vector<char>>::Iterator itr = model.iterator();
	while (itr.hasNext()) {
		string key = itr.next();
		Vector<char> value = model[key];
		if (value.size() > maxFreq) {
			maxFreq = value.size();
			seed = key;
		}
	}
	return seed;
}

void print(string key, Vector<char> value) {
	cout << key << " - " << value.size() << endl;
}

void randomWriter() {
	ifstream file;
	readFile(file);
	
	int order = getOrder();

	Map<Vector<char>> model;
	fillModel(order, file, model);

	string seed = getInitialSeed(model);
	
	cout << seed;
	int outputCount = seed.length();
	while (outputCount < 2000) {
		Vector<char> freq = model[seed];
		if (freq.isEmpty()) break;
		char nextChar = freq.getAt(RandomInteger(0, freq.size() - 1));

		cout << nextChar;
		outputCount++;

		seed += nextChar;
		seed = seed.substr(1);
	}

	cout << endl;
}