#include <iostream>
#include <SFML/Network.hpp>

#include "TicTacToe.h";

using namespace std;

//int jouerServeur(unsigned short port);
//int jouerClient(unsigned short port);

int jouer(bool estServeur, unsigned short port);

int main()
{
	const unsigned short PORT = 54000;
	int choixOption;

	setlocale(LC_ALL, "");

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
		return jouer(true, PORT);
	}
	else {
		return jouer(false, PORT);
	}
}

int jouer(bool estServeur, unsigned short port) {
	sf::TcpListener listener;
	sf::TcpSocket socket;
	sf::Packet paquetEntrant, paquetSortant;
	string adresseServeur;

	char lettreJoueur;
	char tour = 'x';
	TicTacToe ticTacToe;

	char saisieLigne;
	int saisieColonne;

	if (estServeur) {
		lettreJoueur = 'x';

		if (listener.listen(port) != sf::Socket::Done) {
			cout << "Une erreur est survenue lors de la création du listener." << endl;
			return 1;
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
			return 1;
		}
	}

	while (ticTacToe.getGagnant() == ' ' && !ticTacToe.estMatchNul()) {
		cout << ticTacToe << endl;
		if (lettreJoueur == tour) {
			cout << "C'est votre tour." << endl
				<< "Où voulez-vous placer votre " << lettreJoueur << "?" << endl
				<< "ligne colonne : ";
			cin >> saisieLigne >> saisieColonne;
		}
		else {
			cout << "C'est le tour de l'autre joueur." << endl;
			socket.receive(paquetEntrant);
		}
	}

	system("pause");
}

//int jouerServeur(unsigned short port) {
//	sf::TcpListener listener;
//	sf::TcpSocket socket;
//	sf::Socket::Status etatSocket;
//
//	sf::Packet paquetEntrant;
//	sf::Packet paquetSortant;
//
//	TicTacToe ticTacToe;
//
//	char saisieLigne;
//	int saisieColonne, ligne, colonne;
//
//	if (listener.listen(port) != sf::Socket::Done) {
//		cout << "Une erreur est survenue lors de la création du listener." << endl;
//		return 1;
//	}
//
//	cout << "En attente de l'autre joueur..." << endl;
//	listener.accept(socket);
//	cout << "L'autre joueur vient de se connecter." << endl << endl;
//
//	cout << ticTacToe;
//
//	cout << endl << "C'est votre tour. Vous jouez les X." << endl;
//	do {
//		cout << "Où voulez-vous placer votre x? (ligne colonne) ";
//		cin >> saisieLigne >> saisieColonne;
//	} while (saisieLigne < 'a' || saisieLigne > 'c' || saisieColonne < 1 || saisieColonne > 3);
//	ligne = saisieLigne - 'a';
//	colonne = saisieColonne - 1;
//	ticTacToe.jouer(ligne, colonne, 'x');
//
//	paquetSortant << ligne << colonne;
//	socket.send(paquetSortant);
//
//	cout << endl << ticTacToe << endl << endl
//		<< "En attente du tour de l'autre joueur..." << endl;
//
//	system("pause");
//
//	return 0;
//}
//
//int jouerClient(unsigned short port) {
//	string adresseServeur;
//	sf::TcpSocket socket;
//
//	sf::Packet paquetEntrant;
//	sf::Packet paquetSortant;
//
//	TicTacToe ticTacToe;
//
//	char saisieLigne;
//	int saisieColonne, ligne, colonne;
//	
//	cout << "Entrer l'adresse du serveur: ";
//	cin >> adresseServeur;
//
//	if (socket.connect(adresseServeur, port)) {
//		cout << "Une erreur est survenue lors de la connexion au serveur." << endl;
//		return 1;
//	}
//
//	cout << ticTacToe;
//
//	cout << endl << "En attente du tour de l'autre joueur..." << endl;
//	socket.receive(paquetEntrant);
//
//	paquetEntrant >> ligne >> colonne;
//
//	ticTacToe.jouer(ligne, colonne, 'x');
//
//	cout << endl << ticTacToe << endl << endl;
//
//	system("pause");
//
//	return 0;
//}
