//
<<<<<<< HEAD
//  mesure_temps.h
//  Generation vecteur trié, inversement trié, aléatoire et semi-trié
//
//  Created by Alan Sottile, Calvin Graf, Lucas Hussain on 24.03.2023.
//	 HEIG-VD | ASD | Labo 3 | L3G???
=======
//  generation_vecteur.h
//  Generation de vecteur trié, inversement trié, aléatoire et semi-trié
//
//  Created by Alan Sottile, Calvin Graf, Lucas Hussain on 01.03.2023.
//	 Edited on 24.03.2023 for Labo 3 (L3G2)
//  HEIG-VD | ASD | Labo 1
>>>>>>> 2591415e1623f7ac57a0a12eb8931d6747c3dadb
//

#ifndef ASD_LABOS_2021_GENERATION_VECTEUR_H
#define ASD_LABOS_2021_GENERATION_VECTEUR_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

enum Type {
	CROISSANT = 1, DECROISSANT = 2, ALEATOIRE = 3, PRESQUE_TRIE = 4
};

/// Peuple un vecteur de valeurs croissantes
/// \tparam T Type du vecteur
/// \param vecteurGenere Vecteur à peupler
/// \param N Taille du vecteur
template<typename T>
void peuplementTableauCroissant(std::vector<T> &vecteurGenere, unsigned N) {
	for (unsigned i = 0; i < N; i++) {
		vecteurGenere.push_back(T(i));
	}
}

/// Génère un vecteur de 4 types différents
/// \tparam T Type du vecteur
/// \param N Taille du vecteur
/// \param seed Graine de génération aléatoire
/// \param type 1=Trié, 2=Inversement trié, 3=Aléatoire, 4=Semi trié
/// \return Vecteur généré
template<typename T>
std::vector<T> generationVecteur(unsigned N, int seed, unsigned type) {
	std::vector<T> vecteurGenere;

	switch (type) {
		case CROISSANT:
			peuplementTableauCroissant(vecteurGenere, N);
			break;
		case DECROISSANT:
			peuplementTableauCroissant(vecteurGenere, N);
			reverse(vecteurGenere.begin(), vecteurGenere.end());
			break;
		case ALEATOIRE:
			peuplementTableauCroissant(vecteurGenere, N);
			shuffle(vecteurGenere.begin(), vecteurGenere.end(),
					  std::default_random_engine(seed));
			break;
		case PRESQUE_TRIE:
		default:
			std::vector<T> vecteurAleatoire;
			peuplementTableauCroissant(vecteurGenere, N);
			peuplementTableauCroissant(vecteurAleatoire, N);
			shuffle(vecteurAleatoire.begin(),
					  vecteurAleatoire.end(),
					  std::default_random_engine(seed));

			for (auto i = 0; i < vecteurGenere.size(); i++) {
				T test = (vecteurGenere.at(i) * T(3) + vecteurAleatoire.at(i)) / T(2);
				vecteurGenere.at(i) = test;
			}
			break;
	}

	return vecteurGenere;
}

#endif //ASD_LABOS_2021_GENERATION_VECTEUR_H
