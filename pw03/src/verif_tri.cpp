//
//  test_tri.cpp
//  Vérification des fonctions tri_rapide.h et tri_par_base.h
//
//  Created by Alan Sottile, Calvin Graf, Lucas Hussain on 24.03.2023.
//  HEIG-VD | ASD | Labo 3 | L3G2
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include "generation_vecteur.h"
#include "tri_par_base.h"
#include "tri_rapide.h"

using namespace std;

int main() {
	int seed = rand();
	const vector<unsigned> TAILLE = {10, 100, 1000, 10000, 100000, 1000000};

	cout << "Tri rapide :" << endl;

	for (size_t n: TAILLE) {
		vector<unsigned> v = generationVecteur<unsigned>(n, seed, 3);

		tri_rapide(v.begin(), v.end() + 1);

		cout << "Taille " << left << setw(7) << n << " | ";
		if (is_sorted(v.begin(), v.end())) cout << "ok" << endl;
		else cout << "KO" << endl;
	}

	cout << endl << "Tri par base :" << endl;
	string p = "| 1 bit   | 2 bits  | 4 bits  | 8 bits  | 16 bits |";
	cout << setw(66) << right << p << endl;
	for (size_t n: TAILLE) {
		cout << "Taille " << left << setw(7) << n << " ";
		for (int base = 1; base <= 16; base *= 2) {
			vector<unsigned> v = generationVecteur<unsigned>(n, seed, 3);
			tri_par_base<vector<unsigned>::iterator, 1>(v.begin(), v.end());
			if (is_sorted(v.begin(), v.end())) cout << setw(10) << "| ok ";
			else cout << "KO" << endl;

		}
		cout << "|" << endl;
	}

	return 0;
}