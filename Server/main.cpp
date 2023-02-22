#include <iostream>
#include <SFML/Network.hpp>

#include "TicTacToe.h";

using namespace std;

int main()
{
	TicTacToe ticTacToe;

	cout << ticTacToe;

	ticTacToe.jouer(0, 0, 'x');
	ticTacToe.jouer(1, 1, 'o');
	ticTacToe.jouer(2, 2, 'x');

	cout << ticTacToe;

	system("pause");
}
