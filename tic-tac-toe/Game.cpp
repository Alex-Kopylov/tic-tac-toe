#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	
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
		if (gameboard_[win_conditions_[i]] != 0 &&
			gameboard_[win_conditions_[i]] == gameboard_[win_conditions_[i + 1]] &&
			gameboard_[win_conditions_[i]] == gameboard_[win_conditions_[i + 2]]) {
			winner = gameboard_[win_conditions_[i]];
			return true;
		}
	}
	for (auto i = 0; i < 9; i++) {
		if (gameboard_[i] == 0) {
			return false; //no winner
		}
	}

	winner = 0;
	return true; //draw
}

void Game::start_new_game()
{
	winner = -1;
	player_turn_ = 1;
	std::fill(gameboard_.begin(), gameboard_.end(), 0);
}

void Game::auto_step()
{
	for (auto i = 0; i < 24; i += 3) {
		std::vector<unsigned int> win_condition = { gameboard_[win_conditions_[i]], gameboard_[win_conditions_[i + 1]], gameboard_[win_conditions_[2 + i]] };
		if (std::count(win_condition.begin(), win_condition.end(), 0) < 2)
		{
			//Try to not to fail
			if (win_condition[0] == 0)
				if (win_condition[1] == win_condition[2] && win_condition[1] != get_player_turn()) {
					make_play(win_conditions_[i]);
					return;
				}
			if (win_condition[1] == 0)
				if (win_condition[0] == win_condition[2] && win_condition[0] != get_player_turn()) {
					make_play(win_conditions_[i + 1]);
					return;
				}
			if (win_condition[2] == 0)
				if (win_condition[0] == win_condition[1] && win_condition[0] != get_player_turn()) {
					make_play(win_conditions_[i + 2]);
					return;
				}
		}
	}
	random_step();
}

void Game::keep_game_board_in_struct()
{
	my_buffer_struct.game_number_ = this->game_number;
	my_buffer_struct.gameboard_ = gameboard_;
	my_buffer_struct.buffer_winner = winner;
	game_stat_[winner]++;
	game_number++;
}
Game::buffer_struct& Game::get_buffer_struct()
{
	return my_buffer_struct;
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

short int Game::get_winner() const
{
	return winner;
}

Game::~Game()
{
}
