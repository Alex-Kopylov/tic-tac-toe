#pragma once
#include <vector>
#include <algorithm>
#include <random> 
#include <ctime>
#include <fstream>
class Game
{
public:
	Game();
	void next_turn();
	void make_play(int index);
	bool is_this_cell_empty(int index);
	std::vector<unsigned int> get_game_board() const;
	bool is_game_over();
	void start_new_game(unsigned int game_number);
	void auto_step();
	unsigned int get_player_turn() const;
	unsigned short* get_game_stat();
	~Game();
private:
	unsigned short int game_number_;
	static  std::ofstream file_;
	unsigned short int player_turn_ = 1;
	std::vector<unsigned int> gameboard_ =  std::vector<unsigned int>(9,0);
	std::vector<unsigned short int> win_conditions = { 0,1,2, //24 elements
						3,4,5,
						6,7,8,
						0,3,6,
						1,4,7,
						2,5,8,
						0,4,8,
						2,4,6, };
	unsigned short int game_stat_[3] = { 0,0,0 };
	void keep_game_board_and_start_thread(const unsigned short int winner) const;
	void random_step();
	std::mt19937 gen_{ std::random_device()() };
	static DWORD WINAPI write_data_in_file(void * lpvoid);
	typedef struct buffer;
};

