#include <iostream>
#include <SFML/Network.hpp>

#include "TicTacToe.h";

using namespace std;

int jouerServeur(unsigned short port);
int jouerClient(unsigned short port);

int main()
{
	const unsigned short PORT = 54000;

	TicTacToe ticTacToe;
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
		return jouerServeur(PORT);
	}
	else {
		return jouerClient(PORT);
	}
}

int jouerServeur(unsigned short port) {
	sf::TcpListener listener;
	sf::TcpSocket client;
	sf::Socket::Status etatClient;

	sf::Packet paquetEntrant;
	sf::Packet paquetSortant;

	if (listener.listen(port) != sf::Socket::Done) {
		cout << "Une erreur est survenue lors de la création du listener." << endl;
		return 1;
	}

	cout << "En attente de l'autre joueur..." << endl;
	listener.accept(client);

	system("pause");

	return 0;
}

int jouerClient(unsigned short port) {
	string adresseServeur;
	sf::TcpSocket serveur;
	
	cout << "Entrer l'adresse du serveur: ";
	cin >> adresseServeur;

	if (serveur.connect(adresseServeur, port)) {
		cout << "Une erreur est survenue lors de la connexion au serveur." << endl;
		return 1;
	}

	system("pause");

	return 0;
}
