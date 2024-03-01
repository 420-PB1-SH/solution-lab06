#pragma once

#include <string>
#include <SFML/Network.hpp>

class Utilisateur {
private:
    std::string _nom;
    sf::TcpSocket _socket;
public:
    Utilisateur(std::string nom);

    void setNom(const std::string& nom);
    const std::string& getNom() const;

    sf::TcpSocket& getSocket();
};
