#pragma once

#include "TicTacToeGame.h"
#include <string>
#include <iostream>

/*
* This is the game constructor. It sets up the number of players and game board.
* Arguments:
*	=> int number_of_players - Number of players for the game. If 1, then use AI.
*							   Else, use simple console interaction.
* Returns: None
*/
TicTacToeGame::TicTacToeGame(int number_of_players) {
	player_count = number_of_players;
	is_game_over = false;
	current_turn = 1;
	reset();
}

/*
* This function checks if the game is won. It also sets the winning player's ID.
* Arguments: None
* Returns: None
*/
void TicTacToeGame::check_for_win() {

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			bool current_win_check = check_for_win_helper(tic_tac_toe_game[i][j], i, j);
			
			// We don't want to continue checking if someone already won, so we
			// just set game over and return.
			if (current_win_check == true) {
				is_game_over = true;
				return;
			}
		}
	}
}

/*
* This function is a getter for the current game state.
* It will speedup the program so we do not need to check win conditions
* in a while loop inside of main.cpp.
* Arguments: None
* Returns:
*	=> bool is_game_over - true if game is over, false otherwise.
*/
bool TicTacToeGame::is_game_won() {
	return is_game_over;
}

void TicTacToeGame::move(int x, int y) {
	bool is_game_over = is_game_won();
	
	if (!is_game_over) {
		if (current_turn == 1) {
			tic_tac_toe_game[x][y] = 'X';
			current_turn = 2;
		}
		else {
			tic_tac_toe_game[x][y] = 'O';
			current_turn = 1;
		}

		check_for_win();
		bool current_game_state = is_game_won();
		if (!current_game_state) {
			bool is_game_tied = check_for_fail();

			if (is_game_tied) {
				is_game_over = true;
				std::cout << "Game is tied!\n";
				return;
			}
		}
		print_current_game_state();
	}
	else {
		// Game is over. Report winner.
		game_over(winning_player);
	}
}

/*
* This function checks if it is the current player's turn before making a move.
* If the game has a single player, we can just return true since the player
* could only make a move if the computer has already made their turn. Otherwise,
* we need to check who's current turn it is.
*
* Arguments: None
* Returns:
*	=> bool turn - true if it is their turn, false otherwise
*/
int TicTacToeGame::get_current_turn() {
	return current_turn;
}

/*
* This function prints the current state of the game.
* Arguments: None
* Returns: None
* TODO: Refactor this logic. It seems too cumbersome.
*/
void TicTacToeGame::print_current_game_state() {
	// Setup separator of game board, then print it.
	std::string row_separator = "+-----+-----+-----+\n";
	std::cout << row_separator;

	for (int i = 0; i < 3; i++) {
		// Print beginning of row. Every row is 3 separaters long and 5 spaces wide.
		std::cout << "|     |     |     |\n";

		// Print column values.
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				std::cout << "|  " << tic_tac_toe_game[i][j] << "  |";
			}
			else if (j == 1) {
				std::cout << "  " << tic_tac_toe_game[i][j] << "  |";
			}
			else {
				std::cout << "  " << tic_tac_toe_game[i][j] << "  |\n";
			}
		}

		// Print end of row.
		std::cout << "|     |     |     |\n";

		// Print row separator.
		std::cout << row_separator;
	}
}

/*
* This function checks if a given move is valid.
* Arguments:
*	=> int x - x-coordinate of move
*	=> int y - y-coordinate of move
*
* Returns:
*	=> bool valid_move - true if valid move, false otherwise
*/
bool TicTacToeGame::is_valid_move(int x, int y) {
	// Assume move is valid until proven otherwise.
	bool valid_move = true;

	// Make sure player didn't enter a move which will break the code.
	if (x > 2 || y > 2 || x < 0 || y < 0) {
		valid_move = false;
	}
	else if (tic_tac_toe_game[x][y] != 'e') {
		valid_move = false;
	}

	return valid_move;
}

/*
* This function is used to set and reset the initial game state.
* Arguments: None
* Returns: None
*/
void TicTacToeGame::reset() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			// 'e' signifies empty, or no move yet.
			tic_tac_toe_game[i][j] = '\0';
		}
	}
}

/*
* This function reports that the game is over. It also prints the winning player's
* ID.
* Arguments:
*	=> int winning_player_id - ID of winning player.
* Returns: None
*/
void TicTacToeGame::game_over(int winning_player_id) {
	std::cout << "*** GAME OVER ***\nPlayer " << winning_player_id << " wins!\n";
}

/*
* This function checks if all spots are taken and no one has won.
* Arguments: None
* Returns:
*	=> bool game_tie - true if game is tied, false otherwise.
*/
bool TicTacToeGame::check_for_fail() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (tic_tac_toe_game[i][j] == '\0') {
				return false;
			}
		}
	}

	return true;
}

/*
* This function takes a current character, a row and column and checks possible
* win scenarios. Should it find one, it sets the winning player and returns that
* someone won.
* Arguments:
*	=> char current_char - char currently being examined.
*	=> int x - row index
*	=> int y - column index
* Returns:
*	=> bool won - true if player won, false otherwise.
*/
bool TicTacToeGame::check_for_win_helper(char current_char, int x, int y) {
	if (x == 0) {
		if (y == 0) {
			// X = 0, Y = 0
			// Checking row
			if (tic_tac_toe_game[x][y + 1] == current_char && tic_tac_toe_game[x][y + 2] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
			// X = 0, Y = 0
			// Checking column
			else if (tic_tac_toe_game[x + 1][y] == current_char && tic_tac_toe_game[x + 2][y] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
			// X = 0, Y = 0
			// Checking diagonal
			else if (tic_tac_toe_game[x + 1][y + 1] == current_char && tic_tac_toe_game[x + 2][y + 2] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
		}
		else if (y == 1) {
			// X = 0, Y = 1
			// Checking row
			if (tic_tac_toe_game[x][y - 1] == current_char && tic_tac_toe_game[x][y + 1] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
			// X = 0, Y = 1
			// Checking column
			else if (tic_tac_toe_game[x + 1][y] == current_char && tic_tac_toe_game[x + 2][y] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
		}
		else {
			// X = 0, Y = 2
			// Checking row
			if (tic_tac_toe_game[x][y - 1] == current_char && tic_tac_toe_game[x][y - 2] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
			// X = 0, Y = 2
			// Checking column
			else if (tic_tac_toe_game[x + 1][y] == current_char && tic_tac_toe_game[x + 2][y] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
			// X = 0, Y = 2
			// Checking diagonal
			else if (tic_tac_toe_game[x + 1][y - 1] == current_char && tic_tac_toe_game[x + 2][y - 2] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
		}
	}
	else if (x == 1) {
		if (y == 0) {
			// X = 1, Y = 0
			// Checking row
			if (tic_tac_toe_game[x][y + 1] == current_char && tic_tac_toe_game[x][y + 2] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
			// X = 1, Y = 0
			// Checking column
			else if (tic_tac_toe_game[x - 1][y] == current_char && tic_tac_toe_game[x + 1][y] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
		}
		else if (y == 1) {
			// X = 1, Y = 1
			// Checking row
			if (tic_tac_toe_game[x][y - 1] == current_char && tic_tac_toe_game[x][y + 1] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
			// X = 1, Y = 1
			// Checking column
			else if (tic_tac_toe_game[x - 1][y] == current_char && tic_tac_toe_game[x + 1][y] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
			// X = 1, Y = 1
			// Checking diagonal
			else if (tic_tac_toe_game[x + 1][y - 1] == current_char && tic_tac_toe_game[x - 1][y + 1] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
		}
		else {
			// X = 1, Y = 2
			// Checking row
			if (tic_tac_toe_game[x][y - 1] == current_char && tic_tac_toe_game[x][y - 2] == current_char) {
				 if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
			// X = 1, Y = 2
			// Checking column
			else if (tic_tac_toe_game[x - 1][y] == current_char && tic_tac_toe_game[x + 1][y] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
		}
	}
	else {
		// X = 2
		if (y == 0) {
			// X = 2, Y = 0
			// Checking row
			if (tic_tac_toe_game[x][y + 1] == current_char && tic_tac_toe_game[x][y + 2] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
			// X = 2, Y = 0
			// Checking column
			else if (tic_tac_toe_game[x - 1][y] == current_char && tic_tac_toe_game[x - 2][y] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
			// X = 2, Y = 0
			// Checking diagonal
			else if (tic_tac_toe_game[x - 1][y + 1] == current_char && tic_tac_toe_game[x - 2][y + 2] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
		}
		else if (y == 1) {
			// X = 2, Y = 1
			// Checking row
			if (tic_tac_toe_game[x][y - 1] == current_char && tic_tac_toe_game[x][y + 1] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
			// X = 2, Y = 1
			// Checking column
			else if (tic_tac_toe_game[x - 1][y] == current_char && tic_tac_toe_game[x - 2][y] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
		}
		else {
			// X = 2, Y = 2
			// Checking row
			if (tic_tac_toe_game[x][y - 1] == current_char && tic_tac_toe_game[x][y - 2] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
			// X = 2, Y = 2
			// Checking column
			else if (tic_tac_toe_game[x - 1][y] == current_char && tic_tac_toe_game[x - 2][y] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
			// X = 2, Y = 2
			// Checking diagonal
			else if (tic_tac_toe_game[x - 1][y - 1] == current_char && tic_tac_toe_game[x - 2][y - 2] == current_char) {
				if (current_char == 'X') {
					winning_player = 1;
					return true;
				}
				else {
					winning_player = 2;
					return true;
				}
			}
		} // close else for X = 2, Y = 2
	} // close else for X = 2

	// If we haven't returned before this, no winner yet so return false.
	return false;
} // close function "check_for_win_helper"