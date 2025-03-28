/*
 -----------------------------------------------------------------------------------
 Nom du fichier : evaluator.h
 Auteur(s)      : Alan Sottile, Calvin Graf, Lucas Hussain
 Date creation  : 04.05.2023

 Description    : /// TODO
 -----------------------------------------------------------------------------------
*/
#ifndef ASD1_LABS_2020_EVALUATOR_H
#define ASD1_LABS_2020_EVALUATOR_H

#include <string>

class bad_expression { };

/// Evalue une expression arithmétique écrite en notation infixée.
/// \param expression Expression arithmétique écrite en notation infixée
/// \return Résultat de l'expression
/// \throw bad_expression Si l'expression est mal formée
int evalue( std::string const& expression );

#endif //ASD1_LABS_2020_EVALUATOR_H
