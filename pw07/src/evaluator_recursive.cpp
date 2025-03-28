/*
 -----------------------------------------------------------------------------------
 Nom du fichier : evaluator_recursive.cpp
 Auteur(s)      : Alan Sottile, Calvin Graf, Lucas Hussain
 Date creation  : 04.05.2023

 Description    : /// TODO
 -----------------------------------------------------------------------------------
*/
#include "evaluator.h"
#include <string> // std::string

// a compléter avec une définition récursive de la fonction evalue
// qui n'utilise pas de pile

/// Vérifie si un caractère est un opérateur simple (+, -, *, /, %)
/// \param c Le caractère à vérifier
/// \return true si c'est un opérateur, false sinon
bool estUnOperateur(char c);

int evalue(std::string const &expression) {

    size_t parenthesesOuvertes = 0;
    size_t positionOperateur = 0;
    size_t posApresOperateur = 1;

    for (size_t i = 0; i < expression.size(); ++i) {
        if (expression[i] == '(') {
            ++parenthesesOuvertes;
        } else if (expression[i] == ')') {
            --parenthesesOuvertes;
            if (expression[i + 1] == ' ') {
                ++posApresOperateur; // permet d'eviter de prendre un espace dans l'expression
            }
        } else if (parenthesesOuvertes == 0 && estUnOperateur(expression[i])) {
            if (estUnOperateur(expression[i + 1]) || estUnOperateur(expression[0])) {
                // evite les cas ou deux opérateurs se suivent ou si l'expression commence par un opérateur
                throw bad_expression();
            }
            positionOperateur = i;
            if (expression[i - 2] == ' ') {
                ++posApresOperateur;
            }
            break;
        }
    }

    if (positionOperateur) {
        int lhs = evalue(expression.substr(0, positionOperateur));
        int rhs = evalue(expression.substr(
                positionOperateur + posApresOperateur)); // permet d'éviter de prendre les/l'espace(s) après l'operateur

        switch (expression[positionOperateur]) {
            case '+':return lhs + rhs;
            case '-':return lhs - rhs;
            case '*':return lhs * rhs;
            case '/':return lhs / rhs;
            case '%':return lhs % rhs;
            default:throw bad_expression();
        }
    }

    size_t positionParentheseOuvrante = expression.find_first_of('(');
    size_t positionParentheseFermante = expression.find_last_of(')');

    if (positionParentheseOuvrante < std::string::npos && positionParentheseFermante < std::string::npos) {
        //si le parenthèsage est effectué corrèctement
        return evalue(expression.substr(++positionParentheseOuvrante, --positionParentheseFermante));
    } else if (positionParentheseOuvrante != std::string::npos && positionParentheseFermante == std::string::npos) {
        //evite le cas d'une parenthèse non-fermantes
        throw bad_expression();
    }
    return stoi(expression);
}

bool estUnOperateur(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}