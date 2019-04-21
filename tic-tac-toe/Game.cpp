#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	file_.open("output_file.txt", std::ios::app);
}

void Game::next_turn()
{
	player_turn_ = (player_turn_ == 1) ? 2 : 1;

}

void Game::make_play(const int index)
{
	gameboard_[index] = player_turn_;
	next_turn();
}

bool Game::is_this_cell_empty(const int index)
{
	return gameboard_[index] == 0;
}

std::vector<unsigned int> Game::get_game_board() const
{
	return gameboard_;
}

bool Game::is_game_over()
{
	for (auto i = 0; i < 24; i += 3) {
		if (gameboard_[win_conditions[i]] != 0 &&
			gameboard_[win_conditions[i]] == gameboard_[win_conditions[1 + i]] &&
			gameboard_[win_conditions[i]] == gameboard_[win_conditions[2 + i]]) {
			keep_game_board_and_start_thread(gameboard_[win_conditions[i]]);
			//game_stat_[gameboard_[win_conditions[i]]-1]++; //winner
			return true;
		}
	}
	for (auto i = 0; i < 9; i++) {
		if (gameboard_[i] == 0) {
			return false; //no winner
		}
	}
	//game_stat_[2]++;
	keep_game_board_and_start_thread(2);
	return true; //draw
}

void Game::start_new_game(const unsigned int game_number) 
{
	this->game_number_ = game_number;
	player_turn_ = 1;
	std::fill(gameboard_.begin(), gameboard_.end(), 0);
}

void Game::auto_step()
{
	for (auto i = 0; i < 24; i += 3) {
		std::vector<unsigned int> win_condition = { gameboard_[win_conditions[i]], gameboard_[win_conditions[i + 1]], gameboard_[win_conditions[i + 2]] };
		if (std::count(win_condition.begin(), win_condition.end(), 0) < 2)
		{
			//Try to not to fail
			if (win_condition[0] == 0)
				if (win_condition[1] == win_condition[2] && win_condition[1] != get_player_turn()) {
					make_play(win_conditions[i]);
					return;
				}
			if (win_condition[1] == 0)
				if (win_condition[0] == win_condition[2] && win_condition[0] != get_player_turn()) {
					make_play(win_conditions[i + 1]);
					return;
				}
			if (win_condition[2] == 0)
				if (win_condition[0] == win_condition[1] && win_condition[0] != get_player_turn()) {
					make_play(win_conditions[i + 2]);
					return;
				}
		}
	}
	random_step();
}

void Game::keep_game_board_and_start_thread(const unsigned short int winner) const
{
	typedef struct buffer {
		std::vector<unsigned int> gameboard_ = this->gameboard_;
		unsigned short int buffer_winner_= 1;
	} buffer;

	static buffer params;

	auto thread = CreateThread(NULL, 0, write_data_in_file, (void*)&params, 0, NULL);
}

void Game::random_step() {
	std::vector<int> empty_cells;
	for (auto i = 0; i < 9; i++) {
		if (gameboard_[i] == 0) {
			empty_cells.push_back(i);
		}
	}	
	if (empty_cells.empty())
		return;
	const std::uniform_int_distribution<int> uid(0, empty_cells.size()-1);
	const auto random_empty_cell = empty_cells[uid(gen_)];
	make_play(random_empty_cell);
}
unsigned int Game::get_player_turn() const
{
	return player_turn_;
}

unsigned short* Game::get_game_stat()
{
	return game_stat_;
}

DWORD WINAPI Game::write_data_in_file(void * param) {
	buffer * ptr = (buffer*)param;

	file_ << "Game № " << ptr->gameboard_crre+1;
	switch (buffer_winner_) {
	case (1): 
		file_ << " [O win]";
		break;
	case (2):
		file_ << " [X win]";
		break;
	case (3):
		file_ << " [Draw]";
		break;
	default: ;
	}
	file_ << std::endl;
	for (auto i = 0; i < 9; i++) {
		switch (buffer_gameboard_[i]) {
		case 0:
			file_ << " ";
			break;
		case 1:
			file_ << "O";
			break;
		case 2:
			file_ << "X";
			break;
		default: ;
		}
		
		if(i==2||i==5||i==8)
			file_ << std::endl;
	}
	/*    ___
	   |   |
	   |   |
	   |XOO|
		‾‾‾*/
	return 0;
}
Game::~Game()
{
	file_.close();
}