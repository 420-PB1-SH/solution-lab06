#pragma once

#include <iostream>
#include <SFML/Network.hpp>

using namespace std;

class TicTacToe {
private:
	char _grille[3][3];
	char _gagnant;
	bool _estMatchNul;

	void _verifierGagnant();
public:
	TicTacToe();
	~TicTacToe();
	void reinitialiser();
	bool jouer(int ligne, int colonne, char lettre);

	char getGagnant()const;
	bool estMatchNul()const;

	void afficher(ostream& sortie) const;
};

ostream& operator<<(ostream& sortie, TicTacToe& const ticTacToe);