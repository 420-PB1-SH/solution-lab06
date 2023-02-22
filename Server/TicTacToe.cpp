#include "TicTacToe.h"

#include <assert.h>

TicTacToe::TicTacToe() {
	reinitialiser();
}

TicTacToe::~TicTacToe() {
	reinitialiser();
}

void TicTacToe::reinitialiser() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			_grille[i][j] = ' ';
		}
	}
}

bool TicTacToe::jouer(int x, int y, char lettre) {
	assert(x >= 0 && x <= 3 && y >= 0 && y <= 3);
	assert(lettre == 'x' || lettre == 'o');

	if (_grille[x][y] == ' ') {
		_grille[x][y] = lettre;
		return true;
	}
	return false;
}

/*
Retourne le gagnant (x ou o), ou un espace s'il n'y a pas de gagnant.
*/
char TicTacToe::verifierGagnant() const {
	// Vérifier les lignes
	for (int i = 0; i < 2; i++) {
		if (_grille[i][0] != ' ' && _grille[i][0] == _grille[i][1] && _grille[i][1] == _grille[i][2]) {
			return _grille[i][0];
		}
	}
	// Vérifier les colonnes
	for (int j = 0; j < 2; j++) {
		if (_grille[0][j] != ' ' && _grille[1][j] == _grille[1][j] && _grille[2][j] == _grille[2][j]) {
			return _grille[0][j];
		}
	}
	// Vérifier la première diagonale
	if (_grille[0][0] != ' ' && _grille[0][0] == _grille[1][1] && _grille[1][1] == _grille[2][2]) {
		return _grille[0][0];
	}
	// Vérifier la deuxième diagonale
	if (_grille[0][2] != ' ' && _grille[0][2] == _grille[1][1] && _grille[1][1] == _grille[2][0]) {
		return _grille[0][2];
	}
	// Aucun gagnant détecté
	return ' ';
}

bool TicTacToe::verifierMatchNul() const {
	int x, o;
	int lignes = 3, colonnes = 3, diagonales = 2;
	
	// Vérifier les lignes
	for (int i = 0; i < 2; i++) {
		x = o = 0;
		for (int j = 0; j < 2; j++) {
			if (_grille[i][j] == 'x') {
				x++;
			}
			if (_grille[j][j] == 'o') {
				o++;
			}
		}
		if (x > 0 && o > 0) {
			lignes--;
		}
	}
	// Vérifier les colonnes
	for (int j = 0; j < 2; j++) {
		x = o = 0;
		for (int i = 0; i < 2; i++) {
			if (_grille[i][j] == 'x') {
				x++;
			}
			if (_grille[j][j] == 'o') {
				o++;
			}
		}
		if (x > 0 && o > 0) {
			colonnes--;
		}
	}
	// Vérifier la première diagonale
	x = o = 0;
	for (int i = 0; i < 3; i++) {
		if (_grille[i][i] == 'x') {
			x++;
		}
		if (_grille[i][i] == 'o') {
			o++;
		}
	}
	if (x > 0 && o > 0) {
		diagonales--;
	}
	// Vérifier la deuxième diagonale
	x = o = 0;
	for (int i = 0; i < 3; i++) {
		if (_grille[i][2 - i] == 'x') {
			x++;
		}
		if (_grille[i][2 - i] == 'o') {
			o++;
		}
	}
	if (x > 0 && o > 0) {
		diagonales--;
	}
	// Détecter match nul
	return lignes == 0 && colonnes == 0 && diagonales == 0;
}

void TicTacToe::afficher(ostream& sortie) const {
	sortie << "   a b c";
	sortie << endl << "  -------" << endl;
	for (int i = 0; i < 3; i++) {
		sortie << (i + 1) << ' ';
		for (int j = 0; j < 3; j++) {
			sortie << '|' << _grille[i][j];
		}
		sortie << "| " << endl << "  ------- " << endl;
	}
}

ostream& operator<<(ostream& sortie, TicTacToe& const ticTacToe) {
	ticTacToe.afficher(sortie);
	return sortie;
}