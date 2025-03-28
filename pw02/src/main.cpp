/*
Alan Sottile, Calvin Graf, Lucas Hussain - L2G12
17.03.2023
HEIG-VD | ASD | Labo 2
Ce programme permet de trouver toutes les solutions d'un puzzle qui contient les
pièces contenu dans "pieces.h" et "pieces.cpp"
*/

#include <iostream>
#include <vector>
#include "pieces.h"

using namespace std;
using numeros = vector<int>;

void permuter(const Pieces &P, Pieces piecesEnJeu, numeros numPieces,
              const string &solution);

bool compatible(Piece pieceTest, Pieces piecesEnJeu);

string pieceEnLettre(size_t position, size_t rotation);

vector<string> solutions;

int main() {
    Pieces piecesEnJeu;
    const numeros NUM_PIECES{1, 2, 3, 4, 5, 6, 7, 8, 9};

    permuter(PIECES, piecesEnJeu, NUM_PIECES, "");

    for (const string &s: solutions) {
        cout << s << endl;
    }
}

void permuter(const Pieces &P, Pieces piecesEnJeu, numeros numPieces,
              const string &solution) {
    Pieces piecesRestantes = P;
    numeros numPiecesRestantes = numPieces;
    string solutionEnCours = solution;

    for (size_t i = 0; i < P.size(); ++i) {
        Piece pieceTest = piecesRestantes[i];
        for (size_t j = 0; j < 4; ++j) {
            // Évite de faire des rotations inutiles si l'arrosoir inversé est
				// testée au milieu
            if (pieceTest == PIECES.at(8) && piecesEnJeu.size() == 4) {
                j = 4;
            } else {
                if (compatible(pieceTest, piecesEnJeu)) {

                    // Indique que la pièce a été posée
                    piecesEnJeu.push_back(pieceTest);

                    // Supprime la pièce des pièces restantes
                    piecesRestantes.erase(piecesRestantes.begin() + i);
                    numPiecesRestantes.erase(numPiecesRestantes.begin() + i);

                    solutionEnCours += pieceEnLettre(numPieces.at(i), j);

                    if (piecesEnJeu.size() == 9)
                        solutions.push_back(solutionEnCours); // Solution complète
                    else {
							  permuter(piecesRestantes, piecesEnJeu, numPiecesRestantes,
										  solutionEnCours);
						  }

                    // Revient en arrière quand aucune solution n'est possible
                    piecesRestantes = P;
                    numPiecesRestantes = numPieces;
                    piecesEnJeu.pop_back();
                    solutionEnCours = solution;
                }
                rotation(pieceTest);
            }
        }
    }
}

bool compatible(Piece pieceTest, Pieces piecesEnJeu) {
    size_t pos = piecesEnJeu.size();
    AttachementType symboleVoisinGauche;
    AttachementType symboleVoisinHaut;

    for (int i = 0; i < 4; ++i) {
        switch (piecesEnJeu.size()) {
            case 0:
                return true;
            case 1:
            case 2:
                symboleVoisinGauche = piecesEnJeu[pos - 1][1];
                if (symboleVoisinGauche % 2 == 0)
                    return pieceTest[3] == symboleVoisinGauche + 1;
                else
                    return pieceTest[3] == symboleVoisinGauche - 1;
            case 3:
            case 6:
                symboleVoisinHaut = piecesEnJeu[pos - 3][2];
                if (symboleVoisinHaut % 2 == 0)
                    return pieceTest[0] == symboleVoisinHaut + 1;
                else
                    return pieceTest[0] == symboleVoisinHaut - 1;
            default:
                symboleVoisinGauche = piecesEnJeu[pos - 1][1];
                symboleVoisinHaut = piecesEnJeu[pos - 3][2];
                if (symboleVoisinGauche % 2 == 0 and symboleVoisinHaut % 2 == 0)
                    return pieceTest[3] == symboleVoisinGauche + 1 and
                           pieceTest[0] == symboleVoisinHaut + 1;
                else if (symboleVoisinGauche % 2 == 0 and symboleVoisinHaut % 2 == 1)
                    return pieceTest[3] == symboleVoisinGauche + 1 and
                           pieceTest[0] == symboleVoisinHaut - 1;
                else if (symboleVoisinGauche % 2 == 1 and symboleVoisinHaut % 2 == 0)
                    return pieceTest[3] == symboleVoisinGauche - 1 and
                           pieceTest[0] == symboleVoisinHaut + 1;
                else if (symboleVoisinGauche % 2 == 1 and symboleVoisinHaut % 2 == 1)
                    return pieceTest[3] == symboleVoisinGauche - 1 and
                           pieceTest[0] == symboleVoisinHaut - 1;
                break;
        }
        // Tourne la pièce dans le sens suivant jusqu'à avoir essayé les 4 sens
        rotation(pieceTest);
    }

    return false;
}

string pieceEnLettre(size_t position, size_t rotation) {
    const char VALEUR_ROTATION[] = {'a', 'b', 'c', 'd'};
    return to_string(position) + VALEUR_ROTATION[rotation] + " ";
}
