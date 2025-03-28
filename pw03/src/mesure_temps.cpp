//
//  mesure_temps.cpp
//  Comparaison des tris efficaces (tri rapide, tri par base)
//
//  Created by Alan Sottile, Calvin Graf, Lucas Hussain on 24.03.2023.
//  HEIG-VD | ASD | Labo 3 | L3G2
//

#include <vector>
#include <chrono>
#include "generation_vecteur.h"
#include "exporter_csv.h"
#include "tri_rapide.h"
#include "tri_par_base.h"

using namespace std;
using iterateur = vector<int>::iterator;

/// Mesure le temps d'execution d'un tri donné
/// \tparam Fn Type de fonction
/// \param f Fonction de tri
/// \return Vecteur 2 dimensions des mesures faites
template<typename Fn>
vector<vector<double>> mesure_temps(Fn f) {
	int seed = rand();

	vector<vector<double>> mesures;

	vector<double> temps;

	for (unsigned i = 10; i <= 1000000; i *= 10) {
		vector<int> v = generationVecteur<int>(i, seed, 3);

		auto t1 = std::chrono::high_resolution_clock::now();
		f(v.begin(), v.end());
		auto t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> time_ms = t2 - t1;

		temps.push_back(time_ms.count());
	}

	mesures.push_back(temps);

	return mesures;
}

int main() {
	// Tri rapide
	exporter_csv("../../rapport/csv/rapide.csv",
					 mesure_temps(tri_rapide<iterateur>));

	// Tri par base

	//exporter_csv("../../rapport/csv/base.csv",
	//				 mesure_temps(tri_par_base<iterateur, size_t>));

	return 0;
}