#pragma once

class TicTacToeGame {

public:
	TicTacToeGame(int number_of_players);
	void print_current_game_state();
	int get_current_turn();
	void move(int x, int y);
	bool is_game_won();
	bool is_valid_move(int x, int y);

private:
	char tic_tac_toe_game[3][3];
	int player_count;
	int current_turn;
	int winning_player;
	bool is_game_over;
	
	void game_over(int winning_player_id);
	void reset();
	bool check_for_win_helper(char current_char, int x, int y);
	bool check_for_fail();
	void check_for_win();
};
