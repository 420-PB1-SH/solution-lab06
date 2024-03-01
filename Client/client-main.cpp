#include <iostream>
#include <conio.h>
#include <SFML/Network.hpp>

using namespace std;

int main()
{
    sf::TcpSocket socket;
    sf::SocketSelector selecteur;
    sf::IpAddress adresseServeur = "127.0.0.1";
    unsigned short portServeur = 54000;
    sf::Packet paquetEntrant, paquetSortant;

    string code, nomUtilisateur, ancienNom, nouveauNom, nomExpediteur, message;
    char actionClavier;

    setlocale(LC_ALL, "");

    cout << "SUPER CHAT" << endl;
    cout << "================" << endl << endl;

    if (socket.connect(adresseServeur, portServeur) != sf::Socket::Done)
    {
        cout << "Impossible de se connecter au serveur " << adresseServeur << " sur le port " << portServeur << "." << endl;
        return 1;
    }

    selecteur.add(socket);

    cout << "Connecté au serveur " << adresseServeur << " sur le port " << portServeur << "." << endl << endl;

    cout << "Commandes disponibles : " << endl
        << "M - Envoyer un message" << endl
        << "N - Changer de nom d'utilisateur" << endl << endl;

    while (true) {
        if (selecteur.wait(sf::milliseconds(10))) {
            socket.receive(paquetEntrant);
            paquetEntrant >> code;

            if (code == "USER_ENTER") {
                paquetEntrant >> nomUtilisateur;
                cout << nomUtilisateur << " a joint le clavardage." << endl;
            }
            else if (code == "USER_LEAVE") {
                paquetEntrant >> nomUtilisateur;
                cout << nomUtilisateur << " a quitté le clavardage." << endl;
            }
            else if (code == "USER_CHANGE_NAME") {
                paquetEntrant >> ancienNom >> nouveauNom;
                cout << ancienNom << " a changé son nom pour " << nouveauNom << "." << endl;
            }
            else if (code == "MESSAGE") {
                paquetEntrant >> nomExpediteur >> message;
                cout << "[" << nomExpediteur << "] " << message << endl;
            }
            else if (code == "YOUR_NAME") {
                paquetEntrant >> nomUtilisateur;
                cout << "Votre nom d'utilisateur est " << nomUtilisateur << "." << endl;
            }
            else if (code == "NAME_TAKEN") {
                cout << "Ce nom d'utilisateur est déjà pris." << endl;
            }
            else if (code == "INVALID_ACTION") {
                cout << "Action invalide." << endl;
            }
        }

        if (_kbhit()) {
            switch (tolower(_getch())) {
            case 'm':
                cout << "Entrez votre message : ";
                getline(cin, message);

                paquetSortant << "SEND_MESSAGE" << message;
                socket.send(paquetSortant);

                break;
            case 'n':
                cout << "Entrez votre nom d'utilisateur : ";
                getline(cin, nomUtilisateur);

                paquetSortant << "CHANGE_NAME" << nomUtilisateur;
                socket.send(paquetSortant);

                break;
            }
        }

        paquetSortant.clear();
    }

    system("pause");
}
