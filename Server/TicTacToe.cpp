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
	_gagnant = ' ';
	_estMatchNul = false;
}

void TicTacToe::_verifierGagnant() {
	int x, o;
	int lignes = 3, colonnes = 3, diagonales = 2;

	// Vérifier les lignes
	for (int i = 0; i < 3; i++) {
		x = o = 0;
		for (int j = 0; j < 3; j++) {
			if (_grille[i][j] == 'x') {
				x++;
			}
			if (_grille[i][j] == 'o') {
				o++;
			}
		}
		if (x == 3) {
			_gagnant = 'x';
		}
		else if (o == 3) {
			_gagnant = 'o';
		}
		else if (x > 0 && o > 0) {
			lignes--;
		}
	}
	// Vérifier les colonnes
	for (int j = 0; j < 3; j++) {
		x = o = 0;
		for (int i = 0; i < 3; i++) {
			if (_grille[i][j] == 'x') {
				x++;
			}
			if (_grille[i][j] == 'o') {
				o++;
			}
		}
		if (x == 3) {
			_gagnant = 'x';
		}
		else if (o == 3) {
			_gagnant = 'o';
		}
		else if (x > 0 && o > 0) {
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
	if (x == 3) {
		_gagnant = 'x';
	}
	else if (o == 3) {
		_gagnant = 'o';
	}
	else if (x > 0 && o > 0) {
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
	if (x == 3) {
		_gagnant = 'x';
	}
	else if (o == 3) {
		_gagnant = 'o';
	}
	else if (x > 0 && o > 0) {
		diagonales--;
	}
	// Détecter un match nul
	_estMatchNul = (lignes == 0 && colonnes == 0 && diagonales == 0);
}

bool TicTacToe::jouer(int x, int y, char lettre) {
	assert(x >= 0 && x <= 3 && y >= 0 && y <= 3);
	assert(lettre == 'x' || lettre == 'o');

	if (_grille[x][y] == ' ' && _gagnant == ' ' && !_estMatchNul) {
		_grille[x][y] = lettre;
		_verifierGagnant();
		return true;
	}
	return false;
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

char TicTacToe::getGagnant() const {
	return _gagnant;
}

bool TicTacToe::estMatchNul() const {
	return _estMatchNul;
}

sf::Packet& TicTacToe::ecrirePaquet(sf::Packet& paquet) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			paquet << _grille[i][j];
		}
	}
	return paquet;
}

sf::Packet& TicTacToe::lirePaquet(sf::Packet& paquet) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			paquet >> _grille[i][j];
		}
	}
	return paquet;
}

ostream& operator<<(ostream& sortie, TicTacToe& const ticTacToe) {
	ticTacToe.afficher(sortie);
	return sortie;
}
