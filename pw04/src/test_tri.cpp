//
// Created by lucas on 23/03/2023.
// ALL RIGHT RESERVED, YOU KNOW WHAT IM SAYING MY
//

#include <iostream>
#include <vector>
#include <iterator>
#include <type_traits>
#include "tri_par_base.h"
#include "tri_rapide.h"

using namespace std;

int main() {
	// vecteur de 20 int placé aléatoirement entre 0 et 20
	vector<int> v(20);
	for (int& i : v) i = rand() % 20;

	cout << "Vecteur non trie : " << endl;
	for (int i : v) cout << i << " ";
	cout << endl;

	tri_rapide(v.begin(), v.end());

	cout << endl << "Vecteur trie : " << endl;
	for (int i : v) cout << i << " ";
	cout << endl;

	return 0;
}