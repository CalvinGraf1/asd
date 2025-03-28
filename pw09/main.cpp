//
// Created by lucas on 15/06/2023.
//
#include <iostream>
#include <string>
#include <map>
#include <queue>

using namespace std;

vector<string> getNeighbors(string v) {
	size_t lastPosition;

	vector<string> res;
	size_t pos = v.find('0');
	if (pos % 3 != 2) { // 0 échangé avec la droite
		res.push_back(v);
		lastPosition = res.size() - 1;
		swap(res[lastPosition][pos], res[lastPosition][pos + 1]);
	}
	if (pos <= 5) { // 0 échangé avec le bas
		res.push_back(v);
		lastPosition = res.size() - 1;
		swap(res[lastPosition][pos], res[lastPosition][pos + 3]);
	}
	if ((pos % 3) - 2 != 1) { // 0 échangé avec la gauche
		res.push_back(v);
		lastPosition = res.size() - 1;
		swap(res[lastPosition][pos], res[lastPosition][pos - 1]);
	}
	if (pos >= 3) { // 0 échangé avec le haut
		res.push_back(v);
		lastPosition = res.size() - 1;
		swap(res[lastPosition][pos], res[lastPosition][pos - 3]);
	}
	return res;
}

map<string, string> breadthFirstSearch(string start) {
	map<string, string> parents = {{start, ""}}; // <child, parent>
	queue<string> q;
	q.push(start);
	parents[start] = start;
	while (!q.empty()) {
		string v = q.front();
		q.pop();
		vector<string> neighbors = getNeighbors(v);
		for (const string& neighbor : neighbors) {
			if (parents.find(neighbor) == parents.end()) {
				parents[neighbor] = v;
				q.push(neighbor);
				if (neighbor == "012345678") { // Solution trouvée
					break;
				}
			}
		}
	}
	return parents;
}

int main() {
	cout << "\nEntrez une grille (ex: 0 1 2 3 4 5 6 7 8) : " << endl;
	string grid;
	getline(cin, grid);

	map<string, string> parents;

	parents = breadthFirstSearch(grid);

	return 0;
}