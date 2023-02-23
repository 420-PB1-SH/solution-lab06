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

		cout << endl;
		system("pause");
		system("cls");
	}
}

void jouer(bool estServeur, unsigned short port) {
	sf::TcpListener listener;
	sf::TcpSocket socket;
	sf::Packet paquetEntrant, paquetSortant;
	sf::Socket::Status etatSocket;
	string adresseServeur;

	TicTacToe ticTacToe;
	char lettreJoueur;
	char tour = 'x';
	bool coupValide;

	int ligne, colonne;

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
		cout << endl << ticTacToe << endl;

		if (lettreJoueur == tour) {
			cout << "C'est votre tour." << endl;
			do {
				saisirPosition(ligne, colonne, lettreJoueur);

				coupValide = ticTacToe.jouer(ligne, colonne, tour);
				if (!coupValide) {
					cout << "Vous ne pouvez pas placer votre " << tour << " là." << endl;
				}
			} while (!coupValide);

			paquetSortant << ligne << colonne;
			etatSocket = socket.send(paquetSortant);

			if (etatSocket == sf::Socket::Disconnected) {
				cout << "L'autre joueur s'est déconnecté.";
				return;
			}
		}
		else {
			cout << "C'est le tour de l'autre joueur." << endl;
			etatSocket = socket.receive(paquetEntrant);

			if (etatSocket == sf::Socket::Disconnected) {
				cout << "L'autre joueur s'est déconnecté.";
				return;
			}

			paquetEntrant >> ligne >> colonne;
			ticTacToe.jouer(ligne, colonne, tour);
			cout << "L'autre joueur a joué." << endl;
		}

		if (tour == 'x') {
			tour = 'o';
		}
		else {
			tour = 'x';
		}
		paquetSortant.clear();
	}

	cout << endl << ticTacToe << endl;
	if (ticTacToe.getGagnant() != ' ') {
		cout << endl << "Le joueur " << '"' << ticTacToe.getGagnant() << "\" a gagné!" << endl;
	}
	else {
		cout << endl << "Match nul!" << endl;
	}

	socket.disconnect();
}

void saisirPosition(int& x, int& y, char lettreJoueur) {
	char saisieLigne;
	int saisieColonne;

	do {
		cout << "Où voulez-vous placer votre " << lettreJoueur << "?" << endl
			<< "ligne colonne : ";
		cin >> saisieLigne >> saisieColonne;
	} while (saisieLigne < 'a' || saisieLigne > 'c' || saisieColonne < 1 || saisieColonne > 3);

	x = saisieLigne - 'a';
	y = saisieColonne - 1;
}
