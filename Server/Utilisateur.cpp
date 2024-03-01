#include "Utilisateur.h"

using namespace std;

Utilisateur::Utilisateur(string nom) : _nom(nom) {}

void Utilisateur::setNom(const string& nom)
{
    _nom = nom;
}

const string& Utilisateur::getNom() const
{
    return _nom;
}

sf::TcpSocket& Utilisateur::getSocket()
{
    return _socket;
}
