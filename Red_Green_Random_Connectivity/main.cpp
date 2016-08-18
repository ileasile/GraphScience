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
	const double eps = 1e-4;
	int nV, nE, s, f;
	Color initState; // R/G
	double p; // Probability of state changing
	ifstream textGr("in.txt");

	// Reading graph from file
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

	// initializing dynamic table
	vector<double[2]> prob(nV);
	for (int i = 0; i < nV; ++i) {
		prob[i][RED] = prob[i][GREEN] = 0;
	}
	prob[f][RED] = prob[f][GREEN] = 1;

	// Bellman-Ford algorithm modification 
	int times = nV - 1;
	double ores = 2, res;
	while (true) {
		for (int i = times; i > 0; --i) {
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
		res = prob[s][initState];
		if (abs(res - ores) < eps) break;
		ores = res;
		times *= 2;
	}

	// output the result
	ofstream out("out.txt");
	out << "Probability matrix:\n";
	for (int i = 0; i < nV; ++i) {
		out << i + 1 << ". Red: " << prob[i][RED] << ". Green: " << prob[i][GREEN] << ".\n";
	}
	out << "Resulting probability: " << res <<"\n";
	out.close();

	return 0;
}