#include <iostream>
#include <vector>
#include <SFML/Network.hpp>

#include "Utilisateur.h"

using namespace std;

void envoyerATous(sf::Packet& paquetSortant, vector<Utilisateur*>& utilisateurs);
void envoyerMessage(Utilisateur* utilisateur, sf::Packet paquetEntrant, vector<Utilisateur*>& utilisateurs);
void changerNom(Utilisateur* utilisateur, sf::Packet paquetEntrant, vector<Utilisateur*>& utilisateurs);

int main()
{
    sf::TcpListener listener;
    sf::SocketSelector selecteur;
    unsigned short port = 54000;

    vector<Utilisateur*> utilisateurs;
    Utilisateur* nouvelUtilisateur;

    sf::Packet paquetEntrant, paquetSortant;
    string code;

    int idAnonyme = 1;

    setlocale(LC_ALL, "");

    if (listener.listen(port) != sf::Socket::Done)
    {
        cout << "Erreur lors de l'�coute sur le port " << port << endl;
        return 1;
    }
    selecteur.add(listener);

    cout << "Le serveur �coute sur le port " << port << "." << endl;

    while (true) {
        selecteur.wait();

        if (selecteur.isReady(listener)) {
            nouvelUtilisateur = new Utilisateur("Anonyme" + to_string(idAnonyme));
            idAnonyme++;

            listener.accept(nouvelUtilisateur->getSocket());

            cout << nouvelUtilisateur->getNom() << " ("
                << nouvelUtilisateur->getSocket().getRemoteAddress()
                << ":"
                << nouvelUtilisateur->getSocket().getRemotePort()
                << ") s'est connect�." << endl;

            paquetSortant << "YOUR_NAME" << nouvelUtilisateur->getNom();
            nouvelUtilisateur->getSocket().send(paquetSortant);
            paquetSortant.clear();

            paquetSortant << "USER_ENTER" << nouvelUtilisateur->getNom();
            envoyerATous(paquetSortant, utilisateurs);

            selecteur.add(nouvelUtilisateur->getSocket());
            utilisateurs.push_back(nouvelUtilisateur);
        }

        for (int i = 0; i < utilisateurs.size(); i++) {
            if (selecteur.isReady(utilisateurs[i]->getSocket())) {
                if (utilisateurs[i]->getSocket().receive(paquetEntrant) == sf::Socket::Disconnected) {
                    cout << utilisateurs[i]->getNom() << " s'est d�connect�." << endl;
                    
                    paquetSortant << "USER_LEAVE" << utilisateurs[i]->getNom();
                    envoyerATous(paquetSortant, utilisateurs);

                    selecteur.remove(utilisateurs[i]->getSocket());
                    delete utilisateurs[i];
                    utilisateurs[i] = nullptr;
                    utilisateurs.erase(utilisateurs.begin() + i);
                }
                else {
                    paquetEntrant >> code;

                    cout << "Action re�ue de "
                        << utilisateurs[i]->getSocket().getRemoteAddress()
                        << ":"
                        << utilisateurs[i]->getSocket().getRemotePort()
                        << " : " << code
                        << endl;

                    if (code == "SEND_MESSAGE") {
                        envoyerMessage(utilisateurs[i], paquetEntrant, utilisateurs);
                    }
                    else if (code == "CHANGE_NAME") {
                        changerNom(utilisateurs[i], paquetEntrant, utilisateurs);
                    }
                }
            }
        }
    }
}

void envoyerATous(sf::Packet& paquetSortant, vector<Utilisateur*>& utilisateurs) {
    for (int i = 0; i < utilisateurs.size(); i++) {
        utilisateurs[i]->getSocket().send(paquetSortant);
    }
    paquetSortant.clear();
}

void envoyerMessage(Utilisateur* utilisateur, sf::Packet paquetEntrant, vector<Utilisateur*>& utilisateurs)
{
    string message;
    sf::Packet paquetSortant;

    paquetEntrant >> message;

    paquetSortant << "MESSAGE" << utilisateur->getNom() << message;
    envoyerATous(paquetSortant, utilisateurs);
}

void changerNom(Utilisateur* utilisateur, sf::Packet paquetEntrant, vector<Utilisateur*>& utilisateurs)
{
    string ancienNom, nouveauNom;
    sf::Packet paquetSortant;

    paquetEntrant >> nouveauNom;

    for (int i = 0; i < utilisateurs.size(); i++) {
        if (utilisateurs[i]->getNom() == nouveauNom) {
            sf::Packet paquetSortant;
            paquetSortant << "NAME_TAKEN" << nouveauNom;
            utilisateur->getSocket().send(paquetSortant);
            return;
        }
    }

    ancienNom = utilisateur->getNom();
    utilisateur->setNom(nouveauNom);

    paquetSortant << "USER_CHANGE_NAME" << ancienNom << nouveauNom;
    envoyerATous(paquetSortant, utilisateurs);
}
