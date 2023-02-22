#include <iostream>
#include <SFML/Network.hpp>

#include "TicTacToe.h";

using namespace std;

int main()
{
	TicTacToe ticTacToe;

	cout << ticTacToe;

	cout << "Gagnant: " << ticTacToe.getGagnant() << endl;
	cout << "Match nul: " << ticTacToe.estMatchNul() << endl;

	ticTacToe.jouer(0, 0, 'x');

	cout << ticTacToe;

	cout << "Gagnant: " << ticTacToe.getGagnant() << endl;
	cout << "Match nul: " << ticTacToe.estMatchNul() << endl;

	ticTacToe.jouer(0, 0, 'o');

	cout << ticTacToe;

	cout << "Gagnant: " << ticTacToe.getGagnant() << endl;
	cout << "Match nul: " << ticTacToe.estMatchNul() << endl;

	ticTacToe.jouer(0, 1, 'x');

	cout << ticTacToe;

	cout << "Gagnant: " << ticTacToe.getGagnant() << endl;
	cout << "Match nul: " << ticTacToe.estMatchNul() << endl;

	ticTacToe.jouer(0, 2, 'x');

	cout << ticTacToe;

	cout << "Gagnant: " << ticTacToe.getGagnant() << endl;
	cout << "Match nul: " << ticTacToe.estMatchNul() << endl;

	system("pause");
}
