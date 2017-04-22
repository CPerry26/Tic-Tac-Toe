// Tic_Tac_Toe_Game.cpp : This source files defines the actual game loop.
// All logic will be defined else where and used here.
// Author: Cody Perry (CPerry26)

#include "stdafx.h"
#include "TicTacToeGame.h"
#include <string>
#include <iostream>


int main()
{
	// Receive keyboard input from console to handle game steps
	// Need to handle turns
	// TODO: Implement GUI

	bool play_again = false;

	do {
		print_intro();
		play_game();
		play_again = ask_to_play_again();
	} while (play_again);

    return 0;
}

void print_intro() {
	std::cout << "Welcome to a Tic-Tac-Toe console game!\n";
	std::cout << "Author: Cody Perry (CPerry26)\n\n";
}

void play_game() {
	std::cout << "How many players? (Currently only supports 2 player)";
	std::string response = "";
	std::getline(std::cin, response);
	int number_of_players = std::stoi(response);

	// Local game instance
	TicTacToeGame TTTGame(number_of_players);

	// Print initial state
	TTTGame.print_current_game_state();

	while (!TTTGame.is_game_won()) {
		std::cout << "Player " << TTTGame.get_current_turn() << ", please enter your x-coordinate: ";
		std::string x_value = "";
		std::string y_value = "";
		std::getline(std::cin, x_value);
		std::cout << "Player " << TTTGame.get_current_turn() << ", please enter your y-coordinate: ";
		std::getline(std::cin, y_value);

		bool valid_move = TTTGame.is_valid_move(std::stoi(x_value), std::stoi(y_value));
		if (!valid_move) {
			// handle incorrect move
		}
	}
}

/*
* This function asks the player whether they would like to play again.
* Arguments: None
* Returns:
*	=> bool play_again - true if they answered yes, false otherwise
*/
bool ask_to_play_again() {
	std::cout << "Would you like to play again? (y/n)\n";
	std::string response = "";
	std::getline(std::cin, response);
	return response[0] == 'Y' || response[0] == 'y';
}

