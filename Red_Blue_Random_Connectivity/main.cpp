#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

enum Color {
	RED, GREEN, BLACK
};

Color getColor(char c) {
	switch (c) {
	case 'R': return RED;
	case 'G': return GREEN;
	case 'B': return BLACK;
	default: throw 1;
	}
}

int main() {
	int nV, nE, s, f;
	Color initState; // R/G
	double p; // Probability of state changing
	ifstream textGr("graph.txt");

	char chState;
	textGr >> nV >> nE >> s >> f >> chState >> p;
	--s, --f;
	initState = getColor(chState);

	vector<vector<pair<int, Color>>> gr(nV);
	for (int i = 0; i < nE; ++i) {
		int from, to;
		textGr >> from >> to >> chState;
		gr[from-1].push_back(make_pair(to-1, getColor(chState)));
	}
	textGr.close();

	vector<double[2]> prob(nV);
	for (int i = 0; i < nV; ++i) {
		prob[i][RED] = prob[i][GREEN] = 0;
	}
	prob[f][RED] = prob[f][GREEN] = 1;

	for (int i = 1; i < nV; ++i) {
		for (int j = 0; j < nV; ++j) {
			for (auto edge : gr[j]) {
				int to = edge.first;
				Color col = edge.second;

				if (col == RED || col == BLACK) {
					prob[j][RED] = max(prob[to][RED] * (1 - p) + prob[to][GREEN] * p, prob[j][RED]);
				}
				if (col == GREEN || col == BLACK) {
					prob[j][GREEN] = max(prob[to][GREEN] * (1 - p) + prob[to][RED] * p, prob[j][GREEN]);
				}
			}
		}
	}

	ofstream out("out.txt");
	out << "Probability matrix:\n";
	for (int i = 0; i < nV; ++i) {
		out << i + 1 << ". Red: " << prob[i][RED] << ". Green: " << prob[i][GREEN] << ".\n";
	}
	out << "Resulting probability: " << prob[s][initState]<<"\n";
	out.close();

	return 0;
}