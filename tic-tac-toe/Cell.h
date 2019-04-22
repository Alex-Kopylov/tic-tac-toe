#pragma once
class Cell
{
public:
	Cell();
	static int get_cell_number_from_point(int x_pos, int y_pos, RECT board_rect);
	~Cell();
	RECT * get_cell_rectangle(int index, RECT board_rect);
	HICON getIcon(int player_turn);
	void delete_brushes() const;
	void mark_the_cell(HDC hdc, int player_turn, int x_left, int y_top);

private:
	HICON x_icon_, o_icon_;
};

