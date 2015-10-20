#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

using namespace sf;

void arrangement_map(Sprite mapsprite[8][8], Texture & maptexture, float cord_x, float cord_y) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			mapsprite[i][j].setTexture(maptexture);
			mapsprite[i][j].setPosition(cord_x, cord_y);
			cord_x += 88;
			if (cord_x == 739) {
				cord_x = 35;
				cord_y += 88;
			}
		}
	}
}
// функци€ расстановки шашек
void arrangement_of_checkers(Sprite king_checker[13], Texture & king_texture, Sprite checker[13], Texture & ch_texture, float cord_x, float cord_y) {
	for (int i = 0; i < 12; i++) {
		king_checker[i].setTexture(king_texture);
		king_checker[i].setPosition(900, 900);
		checker[i].setTexture(ch_texture);
		checker[i].setPosition(cord_x, cord_y);
		cord_x += 176;
		if (cord_x == 739) {
			cord_x = 123;
			cord_y += 88;
		}
		if (cord_x == 827) {
			cord_x = 35;
			cord_y += 88;
		}
	}
}

struct pair {
	int one;
	int two;
};
//функци€ определени€ €чейки
pair coordinate(float line_x) {
	int coord_line = -1;
	int coor = 900;
	int const_coord[10] = { 35, 123, 211, 299, 387, 475, 563, 651, 739 };
	if ((const_coord[0] <= line_x) && (line_x < const_coord[1])) {
		coord_line = 0;
		coor = 35;
	}
	if ((const_coord[1] <= line_x) && (line_x < const_coord[2])) {
		coord_line = 1;
		coor = 123;
	}
	if ((const_coord[2] <= line_x) && (line_x < const_coord[3])) {
		coord_line = 2;
		coor = 211;
	}
	if ((const_coord[3] <= line_x) && (line_x < const_coord[4])) {
		coord_line = 3;
		coor = 299;
	}
	if ((const_coord[4] <= line_x) && (line_x < const_coord[5])) {
		coord_line = 4;
		coor = 387;
	}
	if ((const_coord[5] <= line_x) && (line_x < const_coord[6])) {
		coord_line = 5;
		coor = 475;
	}
	if ((const_coord[6] <= line_x) && (line_x < const_coord[7])) {
		coord_line = 6;
		coor = 563;
	}
	if ((const_coord[7] <= line_x) && (line_x < const_coord[8])) {
		coord_line = 7;
		coor = 651;
	}
	pair result;
	result.one = coord_line;
	result.two = coor;
	return result;
}
struct motion {
	int start_x, start_y, mov_x, mov_y, num_spr;
	bool isMov;
};
motion move_object(Sprite obje[13], int position_x, int position_y) {
	motion result;
	bool ch_bol = false;
	for (char i = 0; i < 12; i++)
		if (obje[i].getGlobalBounds().contains(position_x, position_y))//и при этом координата курсора попадает в спрайт
		{
			result.start_x = obje[i].getPosition().x;
			result.start_y = obje[i].getPosition().y;
			result.mov_x = position_x - obje[i].getPosition().x;//делаем разность между позицией курсора и спрайта.дл€ корректировки нажати€
			result.mov_y = position_y - obje[i].getPosition().y;//тоже самое по игреку
			result.isMov = true;//можем двигать спрайт
			result.num_spr = i;
			ch_bol = true;
		}
	if (ch_bol == false) {
		result.start_x = -1;
		result.start_y = -1;
		result.mov_x = -1;
		result.mov_y = -1;
		result.isMov = false;
		result.num_spr = -1;
	}
	return result;
}
bool check_safe_move(int num_x, int num_y, int chess_board[8][8]) {
	int const_checker[3];
	bool safe = false;
	const_checker[0] = 1;
	const_checker[1] = 3;
	if ((chess_board[num_y - 1][num_x + 1] != const_checker[0]) && (chess_board[num_y - 1][num_x + 1] != const_checker[1]) &&
		(chess_board[num_y - 1][num_x - 1] != const_checker[0]) && (chess_board[num_y - 1][num_x - 1] != const_checker[1]))
		safe = true;
	return safe;
}
struct ret_check {
	bool one;
	int two[5][3];
};
ret_check check_move(bool & white_move, bool & queen, int num_x, int num_y, int chess_board[8][8]) {
	int const_checker[3];
	int count = 0;
	int address_move[5][3]; 
	bool cut = false;
	bool check_up = false, check_down = false;
	if (white_move) {
		const_checker[0] = 1;
		const_checker[1] = 3;
		check_down = true;
	}
	else {
		const_checker[0] = 2;
		const_checker[1] = 4;
		check_up = true;
	}
	if (queen) {
		check_down = true;
		check_up = true;
	}
	if ((num_y != 0) && (num_x != 7) && check_up) {
		if (((chess_board[num_y - 1][num_x + 1] == const_checker[0]) || (chess_board[num_y - 1][num_x + 1] == const_checker[1])) && (num_y > 1) && (num_x < 6)) {
			if (chess_board[num_y - 2][num_x + 2] == 0) {
				if (cut == false)
					count = 0;
				address_move[count][0] = num_y - 2;
				address_move[count][1] = num_x + 2;
				count += 1;
				cut = true;
			}
		}
		if ((chess_board[num_y - 1][num_x + 1] == 0) && (cut == false)) {
			address_move[count][0] = num_y - 1;
			address_move[count][1] = num_x + 1;
			count += 1;
		}
	}
	if ((num_y != 0) && (num_x != 0) && check_up) {
		if (((chess_board[num_y - 1][num_x - 1] == const_checker[0]) || (chess_board[num_y - 1][num_x - 1] == const_checker[1])) && (num_y > 1) && (num_x > 1)) {
			if (chess_board[num_y - 2][num_x - 2] == 0) {
				if (cut == false)
					count = 0;
				address_move[count][0] = num_y - 2;
				address_move[count][1] = num_x - 2;
				count += 1;
				cut = true;
			}
		}
		if ((chess_board[num_y - 1][num_x - 1] == 0) && (cut == false)) {
			address_move[count][0] = num_y - 1;
			address_move[count][1] = num_x - 1;
			count += 1;
		}
	}
	if ((num_y != 7) && (num_x != 7) && check_down) {
		if (((chess_board[num_y + 1][num_x + 1] == const_checker[0]) || (chess_board[num_y + 1][num_x + 1] == const_checker[1])) && (num_y < 6) && (num_x < 6)) {
			if (chess_board[num_y + 2][num_x + 2] == 0) {
				if (cut == false)
					count = 0;
				address_move[count][0] = num_y + 2;
				address_move[count][1] = num_x + 2;
				count += 1;
				cut = true;
			}
		}
		if ((chess_board[num_y + 1][num_x + 1] == 0) && (cut == false)) {
			address_move[count][0] = num_y + 1;
			address_move[count][1] = num_x + 1;


			count += 1;
		}
	}
	if ((num_y != 7) && (num_x != 0) && check_down) {
		if (((chess_board[num_y + 1][num_x - 1] == const_checker[0]) || (chess_board[num_y + 1][num_x - 1] == const_checker[1])) && (num_y < 6) && (num_x > 1)) {
			if (chess_board[num_y + 2][num_x - 2] == 0) {
				if (cut == false)
					count = 0;
				address_move[count][0] = num_y + 2;
				address_move[count][1] = num_x - 2;
				count += 1;
				cut = true;
			}
		}
		if ((chess_board[num_y + 1][num_x - 1] == 0) && (cut == false)) {
			address_move[count][0] = num_y + 1;
			address_move[count][1] = num_x - 1;
			count += 1;
		}
	}
	for (char i = count; (i < 4); i++) {
		address_move[i][0] = -1;
		address_move[i][1] = -1;
	}
	ret_check result;
	result.one = cut;
	for (char i = 0; i < 4; i++) {
		result.two[i][0] = address_move[i][0];
		result.two[i][1] = address_move[i][1];
	}
	result.two[4][0] = -1;
	result.two[4][1] = -1;
	return result;
}

int main() {
	Font font;//шрифт 
	font.loadFromFile("images/CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 40);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пиксел€х);//сам объект текст (не строка)
	text.setColor(Color::Blue);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	pair ret;
	ret_check res;
	motion answer;
	//bool safely = false;
	int che_num, cut_move[13][5], number_el;
	int bot_move[13][3], moved_bot[24][5];
	int num_x_start, num_y_start, num_x_end, num_y_end;
	int const_coords[10] = { 35, 123, 211, 299, 387, 475, 563, 651, 739 };
	int const_pos[3];
	//bool mov_cut = false;
	//int address_move[5][3];
	int num_x, num_y, coor_ceil_x, coor_ceil_y;
	int address_cell[5][3], count, number, upgrade_white, upgrade_black;
	int carved_white[13], carved_black[13], count_carv_black, count_carv_white, count_king_white, count_king_black;
	int carved_king_white[13], carved_king_black[13], number_end;
	bool white_move = true, move = false, king = false, draw;
	int dX, dY;
	char num;
	bool isMove = false, cut, safe, cut_mode = false;
	bool queen = false;
	int count_res, count_bot_move, count_cut, mass_cut[6][3];
	int coord_x = 35, coord_y = 35; // 35? 35
	RenderWindow window(sf::VideoMode(780, 780), "game");
	Texture whitetexture, blacktexture, king_whitetexture, king_blacktexture, maptexture, maptexture_wall;
	whitetexture.loadFromFile("images/white.png");
	blacktexture.loadFromFile("images/black.png");
	maptexture.loadFromFile("images/mapp.png");
	maptexture_wall.loadFromFile("images/checkers_780.png");
	king_whitetexture.loadFromFile("images/king_white.png");
	king_blacktexture.loadFromFile("images/king_black.png");
	int chess_board[8][8] =
	{
		{ 2, 5, 2, 5, 2, 5, 2, 5 },
		{ 5, 2, 5, 2, 5, 2, 5, 2 },
		{ 2, 5, 2, 5, 2, 5, 2, 5 },
		{ 5, 0, 5, 0, 5, 0, 5, 0 },
		{ 0, 5, 0, 5, 0, 5, 0, 5 },
		{ 5, 1, 5, 1, 5, 1, 5, 1 },
		{ 1, 5, 1, 5, 1, 5, 1, 5 },
		{ 5, 1, 5, 1, 5, 1, 5, 1 }
	};
	Sprite whitesprite[13], blacksprite[13], king_whitesprite[13], king_blacksprite[13], mapsprite[8][8], mapsprite_wall;
	mapsprite_wall.setTexture(maptexture_wall);
	mapsprite_wall.setPosition(0, 0);
	arrangement_map(mapsprite, maptexture, coord_x, coord_y);
	coord_x = 35; coord_y = 35;
	arrangement_of_checkers(king_whitesprite, king_whitetexture, whitesprite, whitetexture, coord_x, coord_y);
	coord_x = 123; coord_y = 475; // 123? 475
	arrangement_of_checkers(king_blacksprite, king_blacktexture, blacksprite, blacktexture, coord_x, coord_y);
	num = -1;
	white_move = true;
	count_carv_white = 0;
	count_carv_black = 0;
	count_king_black = 0;
	count_king_white = 0;
	upgrade_white = 0; upgrade_black = 0;
	while (window.isOpen()) {
		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (white_move) {
				const_pos[0] = 2;
				const_pos[1] = 4;
			}
			else {
				const_pos[0] = 1;
				const_pos[1] = 3;
			}
			move = false;
			if (isMove == false) {
				count_bot_move = 0;
				count_cut = 0;
				cut_mode = false;
				for (int i = 0; i < 8; i++)
					for (int j = 0; j < 8; j++) {
						if ((chess_board[i][j] == const_pos[0]) || (chess_board[i][j] == const_pos[1])) {
							if (white_move == false) {
								bot_move[count_bot_move][0] = j; bot_move[count_bot_move][1] = i;
								count_bot_move += 1;
							}
							else {
								res = check_move(white_move, queen, j, i, chess_board);
								cut = res.one;
								if (cut) {
									cut_mode = true;
									mass_cut[count_cut][0] = j; mass_cut[count_cut][1] = i;
									count_cut += 1;
								}
								count_res = 0;
								while ((res.two[count_res][0] != -1) && (res.two[count_res][1] != -1)) {
									mapsprite[res.two[count_res][0]][res.two[count_res][1]].setColor(Color::Red);
									count_res += 1;
								}
							}
						}
					}
			}
			if (cut_mode) {
				for (char i = 0; i < 8; i++)
					for (char j = 0; j < 8; j++)
						mapsprite[i][j].setColor(Color::White);
				for (int i = 0; i < count_cut;i++) {
					res = check_move(white_move, queen, mass_cut[i][0], mass_cut[i][1], chess_board);
					count_res = 0;
					while ((res.two[count_res][0] != -1) && (res.two[count_res][1] != -1)) {
						mapsprite[res.two[count_res][0]][res.two[count_res][1]].setColor(Color::Red);
						count_res += 1;
					}
				}
			}
			if (white_move == false) {
				std::cout << "BLACK";
				count = 0;
				bool safe_mode = false;
				for (int i = 0; i < count_bot_move; i++) {
					if (chess_board[bot_move[i][1]][bot_move[i][0]] == const_pos[1])
						queen = true;
					else
						queen = false;
					res = check_move(white_move, queen, bot_move[i][0], bot_move[i][1], chess_board);
					if (res.one) {
						moved_bot[0][4] = 2;
						moved_bot[0][0] = bot_move[i][0]; moved_bot[0][1] = bot_move[i][1];
						moved_bot[0][2] = res.two[0][1]; moved_bot[0][3] = res.two[0][0];
						count += 1;
					}
					count_res = 0;
					while ((res.two[count_res][0] != -1) && (res.two[count_res][1] != -1)) {
						safe = check_safe_move(res.two[count_res][0], res.two[count_res][1], chess_board);
						if (safe) {
							moved_bot[count][4] = 1;
							moved_bot[count][0] = bot_move[i][0]; moved_bot[count][1] = bot_move[i][1];
							moved_bot[count][2] = res.two[count_res][1]; moved_bot[count][3] = res.two[count_res][0];
							count += 1;
						}
						else {
							moved_bot[count][4] = -1;
							moved_bot[count][0] = bot_move[i][0]; moved_bot[count][1] = bot_move[i][1];
							moved_bot[count][2] = res.two[count_res][1]; moved_bot[count][3] = res.two[count_res][0];
							count += 1;
						}
						count_res += 1;
					}
				}
				if (moved_bot[0][4] == 2) {
					num_x_start = moved_bot[0][0]; num_y_start = moved_bot[0][1];
					num_x_end = moved_bot[0][2]; num_y_end = moved_bot[0][3];
					if (chess_board[num_y_start][num_x_start] == const_pos[0]) {
						answer = move_object(blacksprite, const_coords[num_x_start], const_coords[num_y_start]);
						if (const_coords[num_y_end] < 123) {
							carved_black[count_carv_black] = answer.num_spr;
							count_carv_black += 1;
							king_blacksprite[answer.num_spr].setPosition(const_coords[num_x_end], const_coords[num_y_end]);
							blacksprite[answer.num_spr].setPosition(900, 900);
							chess_board[num_y_end][num_x_end] = 3;
						}
						else {
							blacksprite[answer.num_spr].setPosition(const_coords[num_x_end], const_coords[num_y_end]);
							chess_board[num_y_end][num_x_end] = 1;
							queen = false;
						}
					}
					else {
						answer = move_object(king_blacksprite, const_coords[num_x_start], const_coords[num_y_start]);
						king_blacksprite[answer.num_spr].setPosition(const_coords[num_x_end], const_coords[num_y_end]);
						chess_board[num_y_end][num_x_end] = 3;
						queen = true;
					}
					chess_board[num_y_start][num_x_start] = 0;
					che_num = chess_board[num_y_start + (num_y_end - num_y_start) / 2][num_x_start + (num_x_end - num_x_start) / 2];
					chess_board[num_y_start + (num_y_end - num_y_start) / 2][num_x_start + (num_x_end - num_x_start) / 2] = 0;
					std::cout << "cutsss" << num_y_start + (num_y_end - num_y_start) / 2 << num_x_start + (num_x_end - num_x_start) / 2 << "vot";
					if (che_num == 2) {
						answer = move_object(whitesprite, const_coords[num_x_start + (num_x_end - num_x_start) / 2], const_coords[num_y_start + (num_y_end - num_y_start) / 2]);
						carved_white[count_carv_white] = answer.num_spr;
						whitesprite[answer.num_spr].setPosition(900, 900);
						count_carv_white += 1;
					}
					if (che_num == 4) {
						answer = move_object(king_whitesprite, const_coords[num_x_start + (num_x_end - num_x_start) / 2], const_coords[num_y_start + (num_y_end - num_y_start) / 2]);
						carved_king_white[count_king_white] = answer.num_spr;
						king_whitesprite[answer.num_spr].setPosition(900, 900);
						count_king_white += 1;
					}
					res = check_move(white_move, queen, num_x_end, num_y_end, chess_board);
					if (res.one)
						white_move = false;
					else
						white_move = true;
				}
				else {
					number = 0;
					while ((moved_bot[number][4] != 1) && (number <= count)) {
						number += 1;
					}
					num_x_start = moved_bot[number][0]; num_y_start = moved_bot[number][1];
					num_x_end = moved_bot[number][2]; num_y_end = moved_bot[number][3];
					if (chess_board[num_y_start][num_x_start] == const_pos[0]) {
						answer = move_object(blacksprite, const_coords[num_x_start], const_coords[num_y_start]);
						if (const_coords[num_y_end] < 123) {
							carved_black[count_carv_black] = answer.num_spr;
							count_carv_black += 1;
							king_blacksprite[answer.num_spr].setPosition(const_coords[num_x_end], const_coords[num_y_end]);
							blacksprite[answer.num_spr].setPosition(900, 900);
							chess_board[num_y_end][num_x_end] = 3;
						}
						else {
							blacksprite[answer.num_spr].setPosition(const_coords[num_x_end], const_coords[num_y_end]);
							chess_board[num_y_end][num_x_end] = 1;
						}
					}
					else {
						answer = move_object(king_blacksprite, const_coords[num_x_start], const_coords[num_y_start]);
						king_blacksprite[answer.num_spr].setPosition(const_coords[num_x_end], const_coords[num_y_end]);
						chess_board[num_y_end][num_x_end] = 3;
					}
					chess_board[num_y_start][num_x_start] = 0;
					white_move = true;
				}
			}
			if ((event.type == Event::MouseButtonPressed) && (event.key.code == Mouse::Left)) {//если нажата клавиша мыши//а именно лева€
				for (char i = 0; i < 8; i++)
					for (char j = 0; j < 8; j++)
						mapsprite[i][j].setColor(Color::White);
				isMove = false;
				if (white_move) {
					answer = move_object(whitesprite, pos.x, pos.y);
					isMove = answer.isMov;
					if (isMove != true) {
						answer = move_object(king_whitesprite, pos.x, pos.y);
						isMove = answer.isMov;
						if (isMove == true) {
							coord_x = answer.start_x; coord_y = answer.start_y;
							dX = answer.mov_x; dY = answer.mov_y;
							num = answer.num_spr;
							queen = true;
						}
					}
					else {
						coord_x = answer.start_x; coord_y = answer.start_y;
						dX = answer.mov_x; dY = answer.mov_y;
						num = answer.num_spr;
						queen = false;
					}
				}
				ret = coordinate(coord_x);
				num_x_start = ret.one;
				ret = coordinate(coord_y);
				num_y_start = ret.one;
				if (cut_mode) {
					count = 0;
					isMove = false;
					for (int i = 0; i < count_cut;i++) {
						if ((mass_cut[i][0] == num_x_start) && (mass_cut[i][1] == num_y_start))
							isMove = true;
					}
				}
				if (isMove) {
					res = check_move(white_move, queen, num_x_start, num_y_start, chess_board);
					count_res = 0;
					while ((res.two[count_res][0] != -1) && (res.two[count_res][1] != -1)) {
						mapsprite[res.two[count_res][0]][res.two[count_res][1]].setColor(Color::Red);
						count_res += 1;
					}
				}
			}
			if ((event.type == Event::MouseButtonReleased) && (isMove) && (event.key.code == Mouse::Left)) {//если отпустили клавишу//а именно левую
				isMove = false;
				std::cout << "WHITE";
				move = false;
				count_res = 0;
				while ((res.two[count_res][0] != -1) && (res.two[count_res][1] != -1)) {
					mapsprite[res.two[count_res][0]][res.two[count_res][1]].setColor(Color::White);
					count_res += 1;
				}
				ret = coordinate(coord_x);
				num_x_start = ret.one;
				ret = coordinate(coord_y);
				num_y_start = ret.one;
				res = check_move(white_move, queen, num_x_start, num_y_start, chess_board);
				cut = res.one;
				ret = coordinate(pos.x);
				num_x_end = ret.one; coor_ceil_x = ret.two;
				ret = coordinate(pos.y);
				num_y_end = ret.one; coor_ceil_y = ret.two;
				for (char l = 0; l < 4; l++)
					if ((res.two[l][0] == num_y_end) && (res.two[l][1] == num_x_end)) {
						move = true;
					}
				if (move) {
					if (queen == false) {
						if (coor_ceil_y >= 651) {
							chess_board[num_y_end][num_x_end] = 4;
							carved_white[count_carv_white] = num;
							whitesprite[num].setPosition(900, 900);
							king_whitesprite[num].setPosition(coor_ceil_x, coor_ceil_y);
							count_carv_white += 1;
						}
						else {
							whitesprite[num].setPosition(coor_ceil_x, coor_ceil_y);
							chess_board[num_y_end][num_x_end] = 2;
						}
						chess_board[num_y_start][num_x_start] = 0;
						if (cut) {
							std::cout << "cutsss" << num_y_start + (num_y_end - num_y_start) / 2 << num_x_start + (num_x_end - num_x_start) / 2 << "vot";
							che_num = chess_board[num_y_start + (num_y_end - num_y_start) / 2][num_x_start + (num_x_end - num_x_start) / 2];
							chess_board[num_y_start + (num_y_end - num_y_start) / 2][num_x_start + (num_x_end - num_x_start) / 2] = 0;
							if (che_num == 1) {
								answer = move_object(blacksprite, coord_x + (coor_ceil_x - coord_x) / 2, coord_y + (coor_ceil_y - coord_y) / 2);
								carved_black[count_carv_black] = answer.num_spr;
								count_carv_black += 1;
								blacksprite[answer.num_spr].setPosition(900, 900);
							}
							if (che_num == 3) {
								answer = move_object(king_blacksprite, coord_x + (coor_ceil_x - coord_x) / 2, coord_y + (coor_ceil_y - coord_y) / 2);
								carved_king_black[count_king_black] = answer.num_spr;
								count_king_black += 1;
								king_blacksprite[answer.num_spr].setPosition(900, 900);
							}
							res = check_move(white_move, queen, num_x_end, num_y_end, chess_board);
							cut_mode = false;
							if (res.one) {
								number_el = num;
							}
							else
								white_move = false;
						}
						else
							white_move = false;
					}
					else {
						king_whitesprite[num].setPosition(coor_ceil_x, coor_ceil_y);
						chess_board[num_y_start][num_x_start] = 0;
						chess_board[num_y_end][num_x_end] = 4;
						if (cut) {
							che_num = chess_board[num_y_start + (num_y_end - num_y_start) / 2][num_x_start + (num_x_end - num_x_start) / 2];
							chess_board[num_y_start + (num_y_end - num_y_start) / 2][num_x_start + (num_x_end - num_x_start) / 2] = 0;
							if (che_num == 1) {
								answer = move_object(blacksprite, coord_x + (coor_ceil_x - coord_x) / 2, coord_y + (coor_ceil_y - coord_y) / 2);
								carved_black[count_carv_black] = answer.num_spr;
								count_carv_black += 1;
								blacksprite[answer.num_spr].setPosition(900, 900);
							}
							if (che_num == 3) {
								answer = move_object(king_blacksprite, coord_x + (coor_ceil_x - coord_x) / 2, coord_y + (coor_ceil_y - coord_y) / 2);
								carved_king_black[count_king_black] = answer.num_spr;
								count_king_black += 1;
								king_blacksprite[answer.num_spr].setPosition(900, 900);
							}
							res = check_move(white_move, queen, coor_ceil_x, coor_ceil_y, chess_board);
							if (res.one) {
								//cut_mode = true;
								number_el = num;
							}
							else
								white_move = false;
						}
						else
							white_move = false;
					}
				}
				else {
					if (white_move) {
						if (queen)
							king_whitesprite[num].setPosition(coord_x, coord_y);
						else
							whitesprite[num].setPosition(coord_x, coord_y);
					}
				}
				move = false;
				num = -1;
			}
			if ((isMove) && (white_move)) {
				if (queen)
					king_whitesprite[num].setPosition(pos.x - dX, pos.y - dY);
				else
					whitesprite[num].setPosition(pos.x - dX, pos.y - dY);
			}
		}		
		window.clear();
		window.draw(mapsprite_wall);
		for (char i = 0; i < 8; i++)
			for (char j = 0; j < 8; j++) {
				if ((i % 2 == 0) && (j % 2 == 0))
					window.draw(mapsprite[i][j]);
				if ((i % 2 != 0) && (j % 2 != 0))
					window.draw(mapsprite[i][j]);
			}
		for (char i = 0; i < 12; i++) {
			draw = true;
			for (char j = 0; j < count_king_white; j++) {
				if (carved_king_white[j] == i)
					draw = false;
			}
			if (draw)
				window.draw(king_whitesprite[i]);
			draw = true;
			for (char j = 0; j < count_king_black; j++) {
				if (carved_king_black[j] == i)
					draw = false;
			}
			if (draw)
				window.draw(king_blacksprite[i]);
			draw = true;
			for (char j = 0; j < count_carv_white; j++) {
				if (carved_white[j] == i)
					draw = false;
			}
			if (draw)
				window.draw(whitesprite[i]);
			draw = true;
			for (char j = 0; j < count_carv_black; j++) {
				if (carved_black[j] == i)
					draw = false;
			}
			if (draw)
				window.draw(blacksprite[i]);
		}
		if ((count_carv_white - upgrade_white + count_king_white) == 12) {
			text.setPosition(300, 350);//задаем позицию текста, центр камеры
			text.setString("BOT WIN");//задает строку тексту
			window.draw(text);//рисую этот текст
		}
		if ((count_carv_black - upgrade_black + count_king_black) == 12) {
			text.setPosition(300, 350);//задаем позицию текста, центр камеры
			text.setString("Player WIN");//задает строку тексту
			window.draw(text);//рисую этот текст
		}
		window.display();
	}
	return 0;
}