#include <iostream>
#include <SFML/Network.hpp>

#include "TicTacToe.h";

using namespace std;

void jouer(bool estServeur, unsigned short port);

void saisirPosition(int& ligne, int& colonne, char lettreJoueur);

int main()
{
	const unsigned short PORT = 54000;
	int choixOption;

	setlocale(LC_ALL, "");

	while (true) {
		cout << "TIC TAC TOE" << endl
			<< "===========" << endl << endl
			<< "Choisir une option: " << endl
			<< "1. Créer une partie" << endl
			<< "2. Joindre une partie" << endl << endl;

		do {
			cout << "Votre choix: ";
			cin >> choixOption;
		} while (choixOption != 1 && choixOption != 2);

		if (choixOption == 1) {
			jouer(true, PORT);
		}
		else {
			jouer(false, PORT);
		}
	}
}

void jouer(bool estServeur, unsigned short port) {
	sf::TcpListener listener;
	sf::TcpSocket socket;
	sf::Packet paquetEntrant, paquetSortant;
	string adresseServeur;

	char lettreJoueur;
	char tour = 'x';
	TicTacToe ticTacToe;

	int x, y;

	if (estServeur) {
		lettreJoueur = 'x';

		if (listener.listen(port) != sf::Socket::Done) {
			cout << "Une erreur est survenue lors de la création du listener." << endl;
			return;
		}

		cout << "En attente de l'autre joueur..." << endl;
		listener.accept(socket);
		cout << "L'autre joueur vient de se connecter." << endl << endl;
	}
	else {
		lettreJoueur = 'o';

		cout << "Entrer l'adresse du serveur: ";
		cin >> adresseServeur;
		
		if (socket.connect(adresseServeur, port)) {
			cout << "Une erreur est survenue lors de la connexion au serveur." << endl;
			return;
		}
	}

	while (ticTacToe.getGagnant() == ' ' && !ticTacToe.estMatchNul()) {
		cout << ticTacToe << endl;

		if (lettreJoueur == tour) {
			cout << "C'est votre tour." << endl;
			saisirPosition(x, y, lettreJoueur);
			paquetSortant << x << y;
			socket.send(paquetSortant);
		}
		else {
			cout << "C'est le tour de l'autre joueur." << endl;
			socket.receive(paquetEntrant);
			paquetEntrant >> x >> y;
			cout << "L'autre joueur a joué." << endl;
		}

		ticTacToe.jouer(x, y, tour);

		paquetSortant.clear();
	}

	if (ticTacToe.getGagnant() != ' ') {
		cout << ticTacToe.getGagnant() << " a gagné!" << endl;
	}
	else {
		cout << "Match nul!" << endl;
	}

	socket.disconnect();
}

void saisirPosition(int& x, int& y, char lettreJoueur) {
	char saisieX;
	int saisieY;

	do {
		cout << "Où voulez-vous placer votre " << lettreJoueur << "?" << endl
			<< "ligne colonne : ";
		cin >> saisieX >> saisieY;
	} while (saisieX < 'a' || saisieX > 'c' || saisieY < 1 || saisieY > 3);

	x = saisieX - 'a';
	x = saisieY - 1;
}
