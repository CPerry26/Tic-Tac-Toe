#pragma once

// Class representation of game. Handles all game related logic.
class TicTacToeGame {

public:
	// Default object constructor.
	TicTacToeGame(int number_of_players);

	// Print the current game state.
	void print_current_game_state();

	// Get and return the current game turn (specifically their player ID).
	int get_current_turn();

	// Place the current turn player ID's move at (x,y).
	void move(int x, int y);

	// Check if the game has been won.
	bool is_game_won();

	// Check if the move is valid. Always called before move(x,y).
	bool is_valid_move(int x, int y);

private:
	// Private representation of the game board.
	char tic_tac_toe_game[3][3];

	// Private player count. Set in constructor.
	int player_count;

	// The player ID associated with the current turn.
	int current_turn;

	// The winning player's ID.
	int winning_player;

	// Private boolean declaring a game over state.
	bool is_game_over;
	
	// Method to handle and print game over material.
	void game_over(int winning_player_id);

	// Method to reset the game board to it's initialized state.
	void reset();

	// Method for checking win conditions.
	bool check_for_win_helper(char current_char, int x, int y);

	// Method for checking if no player can win (resulting in a tie).
	bool check_for_fail();

	// Method for checking if a win has occured. check_for_win_helper() is called from this method.
	void check_for_win();
};
