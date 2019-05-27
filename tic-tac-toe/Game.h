#pragma once
#include <vector>
#include <algorithm>
#include <random> 
#include <ctime>
#include <fstream>
#include <cstdlib>
class Game
{
public:
	struct buffer_struct;
	Game();
	void next_turn();
	void make_play(int index);
	bool is_this_cell_empty(int index);
	std::vector<unsigned int> get_game_board() const;
	bool is_game_over();
	void start_new_game();
	void auto_step();
	unsigned int get_player_turn() const;
	unsigned short* get_game_stat();
	short int get_winner() const;
	buffer_struct* keep_game_board_in_struct();
	~Game();
private:
	unsigned short int game_number = 1;
	unsigned short int player_turn_ = 1;
	std::vector<unsigned int> gameboard_ =  std::vector<unsigned int>(9,0);
	std::vector<unsigned short int> win_conditions_ = { 0,1,2, //24 elements
						3,4,5,
						6,7,8,
						0,3,6,
						1,4,7,
						2,5,8,
						0,4,8,
						2,4,6, };
	unsigned short int game_stat_[3] = { 0,0,0 }; //0-DRAW; 1-X; 2 - O; 
	void random_step();
	std::mt19937 gen_{ std::random_device()() };
	short int winner = -1;;
	struct buffer_struct {
		std::vector<unsigned int> gameboard_;
		unsigned short int buffer_winner{};
		unsigned short int game_number_{};
		
	} ;
};

