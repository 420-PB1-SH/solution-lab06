#pragma once

#include <iostream>

using namespace std;

class TicTacToe {
private:
	char _grille[3][3];
public:
	TicTacToe();
	~TicTacToe();
	void reinitialiser();
	bool jouer(int x, int y, char lettre);

	// Retourne le gagnant (x ou o), ou un espace s'il n'y a pas de gagnant.
	char verifierGagnant() const;

	bool verifierMatchNul() const;

	void afficher(ostream& sortie) const;
};

ostream& operator<<(ostream& sortie, TicTacToe& const ticTacToe);