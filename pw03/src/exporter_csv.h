//
//  exporter_csv.h
//  Exportation d'un fichier CSV des mesures de temps sur un tri
//
//  Created by Alan Sottile, Calvin Graf, Lucas Hussain on 01.03.2023.
//	 Edited on 24.03.2023 for Labo 3 (L3G2)
//  HEIG-VD | ASD | Labo 1
//

#ifndef ASD_LABOS_2021_EXPORTER_CSV_H
#define ASD_LABOS_2021_EXPORTER_CSV_H

#include <iostream>
#include <fstream>
#include <vector>
#include <random>

/// Exporte les mesures dans un fichier csv
/// \tparam T Type des mesures
/// \param filename Chemin du fichier
/// \param mesures Tableau de mesures
template<typename T>
void exporter_csv(std::string const &filename,
						std::vector<std::vector<T>>const &mesures){

	std::vector<int> n_values = {10, 100, 1000, 10000, 100000, 1000000};

	std::ofstream out(filename);

	if (not out.is_open()) {
		std::cerr << "Pas pu ouvrir le fichier en écriture" << std::endl;
		return;
	}

	out << "n";
	for (int n: n_values) out << "," << n;
	out << std::endl;

	for (size_t i: {0u, 1u, 2u, 3u, 4u, 5u}) {
		out << "mesure " << i;
		for (auto a: mesures[i])
			out << "," << a;
		out << std::endl;
	}
}

#endif //ASD_LABOS_2021_EXPORTER_CSV_H
