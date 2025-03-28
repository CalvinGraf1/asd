/*
 -----------------------------------------------------------------------------------
 Nom du fichier : evaluator.cpp
 Auteur(s)      : Alan Sottile, Calvin Graf, Lucas Hussain
 Date creation  : 04.05.2023

 Description    : /// TODO
 -----------------------------------------------------------------------------------
*/
#include "evaluator.h"
#include <stack> // std::stack
#include <cctype> // std::isdigit
#include <string> // std::string

// a compléter avec une définition de la fonction evalue qui met en
// oeuvre l'algorithme à 2 piles

/// Vérifie si un caractère est un opérateur simple (+, -, *, /, %)
/// \param c Le caractère à vérifier
/// \return true si c'est un opérateur, false sinon
bool estUnOperateur(char c);

int evalue( std::string const& expression ) {
	std::stack<char> pileOp;
	std::stack<int> pileVal;

	for(size_t i = 0; i < expression.size(); ++i) {

		if(expression[i] == ' ' or expression[i] == '(') continue;
		else if (std::isdigit(expression[i])) {
			std::string val;
			// Récupère tous les digits suivant si c'est une dizaine, centaine, etc.
			while(i < expression.size() and std::isdigit(expression[i]))  {
				val += expression[i];
				++i;
			}
			--i;
			try { pileVal.push(std::stoi(val)); }
			// Si la conversion échoue, bad_expression pour éviter un crash
			catch(...) { throw bad_expression(); }
		}
		else if (estUnOperateur(expression[i]))
			pileOp.push(expression[i]);
		else if (expression[i] == ')') {
			// S'il n'y a pas assez d'opérande ou opérateur -> bad_expression
			if(pileVal.size() < 2 or pileOp.empty())
				throw bad_expression();

			// Parenthèse fermante = on calcule
			int v2 = pileVal.top();
			pileVal.pop();
			int v1 = pileVal.top();
			pileVal.pop();
			char op = pileOp.top();
			pileOp.pop();
			int resultat;
			switch(op) {
				case '+': resultat = v1 + v2; break;
				case '-': resultat = v1 - v2; break;
				case '*': resultat = v1 * v2; break;
				case '/': resultat = v1 / v2; break;
				case '%': resultat = v1 % v2; break;
				default: throw bad_expression();
			}
			pileVal.push(resultat);
		}
	}

	if(not(pileOp.empty()) or pileVal.size() != 1)
		throw bad_expression();

	return pileVal.top();

}

bool estUnOperateur(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}