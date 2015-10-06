#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
using namespace sf;
int num_x, num_y, coor_ceil_x, coor_ceil_y, coord_line, coor;
int address_cell[4], count, number, upgrade_white, upgrade_black;
int carved_white[12], carved_black[12], count_carv_black, count_carv_white, count_king_white, count_king_black;
int carved_king_white[12], carved_king_black[12], number_end;
bool white_move = true, move = false, king = false, draw;
struct pair{
	int one;
	int two;
};
pair coordinate(int line_x) {
	if (35 <= line_x)
		if (line_x < 123) {
			coord_line = 1;
			coor = 35;
		}
	if (123 <= line_x)
		if (line_x < 211) {
			coord_line = 2;
			coor = 123;
		}
	if (211 <= line_x)
		if (line_x < 299) {
			coord_line = 3;
			coor = 211;
		}
	if (299 <= line_x)
		if (line_x < 387) {
			coord_line = 4;
			coor = 299;
		}
	if (387 <= line_x)
		if (line_x < 475) {
			coord_line = 5;
			coor = 387;
		}
	if (475 <= line_x)
		if (line_x < 563) {
			coord_line = 6;
			coor = 475;
		}
	if (563 <= line_x)
		if (line_x < 651) {
			coord_line = 7;
			coor = 563;
		}
	if (651 <= line_x)
		if (line_x <= 739) {
			coord_line = 8;
			coor = 651;
		}
	pair result;
	result.one = coord_line;
	result.two = coor;
	return result;
}
int main() {
	RenderWindow window(sf::VideoMode(780, 780), "game");
	Texture whitetexture, blacktexture, mapstexture, king_whitetexture, king_blacktexture;
	whitetexture.loadFromFile("images/white.png");
	blacktexture.loadFromFile("images/black.png");
	mapstexture.loadFromFile("Images/checkers_780.png");
	king_whitetexture.loadFromFile("images/king_white.png");
	king_blacktexture.loadFromFile("images/king_black.png");
	Sprite mapssprite;
	mapssprite.setTexture(mapstexture);
	mapssprite.setPosition(0, 0);
	int mass[89];
	mass[11] = 2; mass[21] = 5; mass[31] = 2; mass[41] = 5; mass[51] = 2; mass[61] = 5; mass[71] = 2; mass[81] = 5;
	mass[12] = 5; mass[22] = 2; mass[32] = 5; mass[42] = 2; mass[52] = 5; mass[62] = 2; mass[72] = 5; mass[82] = 2;
	mass[13] = 2; mass[23] = 5; mass[33] = 2; mass[43] = 5; mass[53] = 2; mass[63] = 5; mass[73] = 2; mass[83] = 5;
	mass[14] = 5; mass[24] = 0; mass[34] = 5; mass[44] = 0; mass[54] = 5; mass[64] = 0; mass[74] = 5; mass[84] = 0;
	mass[15] = 0; mass[25] = 5; mass[35] = 0; mass[45] = 5; mass[55] = 0; mass[65] = 5; mass[75] = 0; mass[85] = 5;
	mass[16] = 5; mass[26] = 1; mass[36] = 5; mass[46] = 1; mass[56] = 5; mass[66] = 1; mass[76] = 5; mass[86] = 1;
	mass[17] = 1; mass[27] = 5; mass[37] = 1; mass[47] = 5; mass[57] = 1; mass[67] = 5; mass[77] = 1; mass[87] = 5;
	mass[18] = 5; mass[28] = 1; mass[38] = 5; mass[48] = 1; mass[58] = 5; mass[68] = 1; mass[77] = 5; mass[88] = 1;
	Sprite whitesprite[13], blacksprite[13], king_whitesprite[13], king_blacksprite[13];
	int coord_x = 35, coord_y = 35;
	int dX, dY;
	char num;
	bool isMove, cut;
	for (char i = 0; i < 12; i++) { // ���� ����������� ����� �����
		king_whitesprite[i].setTexture(king_whitetexture);
		king_whitesprite[i].setPosition(900, 900);
		carved_white[i] = 0;
		carved_black[i] = 0;
		whitesprite[i].setTexture(whitetexture);
		whitesprite[i].setPosition(coord_x, coord_y);
		coord_x += 176;
		if (coord_x == 739) {
			coord_x = 123;
			coord_y += 88;
		}
		if (coord_x == 827) {
			coord_x = 35;
			coord_y += 88;
		}
	}
	coord_x = 123; coord_y = 475;
	for (char i = 0; i < 12; i++) { // ���� ����������� ������ �����
		king_blacksprite[i].setTexture(king_blacktexture);
		king_blacksprite[i].setPosition(900, 900);
		blacksprite[i].setTexture(blacktexture);
		blacksprite[i].setPosition(coord_x, coord_y);
		coord_x += 176;
		if (coord_x == 739) {
			coord_x = 123;
			coord_y += 88;
		}
		if (coord_x == 827) {
			coord_x = 35;
			coord_y += 88;
		}
	}
	num = -1;
	for (char i = 0; i < 4; i++)
		address_cell[i] = 0;
	white_move = true;
	move = false;
	count_carv_white = 0;
	count_carv_black = 0;
	count_king_black = 0;
	count_king_white = 0;
	upgrade_white = 0; upgrade_black = 0;
	bool queen = false;
	while (window.isOpen()) {
		Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������
		Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
				if (event.key.code == Mouse::Left) {//� ������ �����
					if (white_move) {
						for (char i = 0; i < 12; i++) {
							if (whitesprite[i].getGlobalBounds().contains(pos.x, pos.y))//� ��� ���� ���������� ������� �������� � ������
							{
								coord_x = whitesprite[i].getPosition().x;
								coord_y = whitesprite[i].getPosition().y;
								dX = pos.x - whitesprite[i].getPosition().x;//������ �������� ����� �������� ������� � �������.��� ������������� �������
								dY = pos.y - whitesprite[i].getPosition().y;//���� ����� �� ������
								isMove = true;//����� ������� ������
								num = i;
								std::cout << "white ";
							}
							if (king_whitesprite[i].getGlobalBounds().contains(pos.x, pos.y))//� ��� ���� ���������� ������� �������� � ������
							{
								coord_x = king_whitesprite[i].getPosition().x;
								coord_y = king_whitesprite[i].getPosition().y;
								dX = pos.x - king_whitesprite[i].getPosition().x;//������ �������� ����� �������� ������� � �������.��� ������������� �������
								dY = pos.y - king_whitesprite[i].getPosition().y;//���� ����� �� ������
								isMove = true;//����� ������� ������
								num = i;
								queen = true;
								std::cout << "white king ";
							}
						}
					}
					else
						for (char i = 0; i < 12; i++) {
							if (blacksprite[i].getGlobalBounds().contains(pos.x, pos.y))//� ��� ���� ���������� ������� �������� � ������
							{
								coord_x = blacksprite[i].getPosition().x;
								coord_y = blacksprite[i].getPosition().y;
								dX = pos.x - blacksprite[i].getPosition().x;//������ �������� ����� �������� ������� � �������.��� ������������� �������
								dY = pos.y - blacksprite[i].getPosition().y;//���� ����� �� ������
								isMove = true;//����� ������� ������
								num = i;
								std::cout << "black ";
							}
							if (king_blacksprite[i].getGlobalBounds().contains(pos.x, pos.y))//� ��� ���� ���������� ������� �������� � ������
							{
								coord_x = king_blacksprite[i].getPosition().x;
								coord_y = king_blacksprite[i].getPosition().y;
								dX = pos.x - king_blacksprite[i].getPosition().x;//������ �������� ����� �������� ������� � �������.��� ������������� �������
								dY = pos.y - king_blacksprite[i].getPosition().y;//���� ����� �� ������
								isMove = true;//����� ������� ������
								num = i;
								queen = true;
								std::cout << "black king ";
							}
						}
					pair res;
					res = coordinate(pos.x);
					num_x = res.one; coor_ceil_x = res.two;
					res = coordinate(pos.y);
					num_y = res.one; coor_ceil_y = res.two;
					count = 0;
					cut = false;
					if (white_move) { //�������� �� ���������� ����
						if (queen) {
							if (num_y != 1) {
								if (num_x != 8) {
									if ((mass[(num_x + 1) * 10 + (num_y - 1)] == 1)||((mass[(num_x + 1) * 10 + (num_y - 1)] == 3)))
										if (num_y > 2)
											if (num_x < 7)
												if (mass[(num_x + 2) * 10 + (num_y - 2)] == 0) {
													address_cell[count] = (num_x + 2) * 10 + (num_y - 2);
													count += 1;
													cut = true;
												}
									if (cut == false)
										if (mass[(num_x + 1) * 10 + (num_y + 1)] == 0) {
											address_cell[count] = (num_x + 1) * 10 + (num_y - 1);
											count += 1;
										}
								}
								if (num_x != 1) {
									if ((mass[(num_x - 1) * 10 + (num_y - 1)] == 1)|| (mass[(num_x - 1) * 10 + (num_y - 1)] == 3)) {
										if (num_y > 2)
											if (num_x > 2)
												if (mass[(num_x - 2) * 10 + (num_y - 2)] == 0) {
													address_cell[count] = (num_x - 2) * 10 + (num_y - 2);
													count += 1;
													cut = true;
												}
									}
									if (cut == false)
										if (mass[(num_x - 1) * 10 + (num_y - 1)] == 0) {
											address_cell[count] = (num_x - 1) * 10 + (num_y - 1);
											count += 1;
										}

								}
							}
						}
						if (num_y != 8) {
							if (num_x != 8) {
								if ((mass[(num_x + 1) * 10 + (num_y + 1)] == 1)|| (mass[(num_x + 1) * 10 + (num_y + 1)] == 3))
									if (num_y < 7)
										if (num_x < 7)
											if (mass[(num_x + 2) * 10 + (num_y + 2)] == 0) {
												address_cell[count] = (num_x + 2) * 10 + (num_y + 2);
												count += 1;
												cut = true;
											}
								if (cut == false)
									if (mass[(num_x + 1) * 10 + (num_y + 1)] == 0) {
										address_cell[count] = (num_x + 1) * 10 + (num_y + 1);
										count += 1;
									}
							}
							if (num_x != 1) {
								if ((mass[(num_x - 1) * 10 + (num_y + 1)] == 1)|| (mass[(num_x - 1) * 10 + (num_y + 1)] == 3)) {
									if (num_y < 7)
										if (num_x > 2)
											if (mass[(num_x - 2) * 10 + (num_y + 2)] == 0) {
												address_cell[count] = (num_x - 2) * 10 + (num_y + 2);
												count += 1;
												cut = true;
											}
								}
								if (cut == false)
									if (mass[(num_x - 1) * 10 + (num_y + 1)] == 0) {
										address_cell[count] = (num_x - 1) * 10 + (num_y + 1);
										count += 1;
									}

							}
						}
					}
					else {
						if (queen) {
							if (num_y != 8) {
								if (num_x != 8) {
									if ((mass[(num_x + 1) * 10 + (num_y + 1)] == 2)|| (mass[(num_x + 1) * 10 + (num_y + 1)] == 4)) {
										if (num_y < 7)
											if (num_x < 7)
												if (mass[(num_x + 2) * 10 + (num_y + 2)] == 0) {
													address_cell[count] = (num_x + 2) * 10 + (num_y + 2);
													count += 1;
													cut = true;
												}
									}
									if (cut == false)
										if (mass[(num_x + 1) * 10 + (num_y + 1)] == 0) {
											address_cell[count] = (num_x + 1) * 10 + (num_y + 1);
											count += 1;
										}
								}
								if (num_x != 1) {
									if ((mass[(num_x - 1) * 10 + (num_y + 1)] == 2)|| (mass[(num_x - 1) * 10 + (num_y + 1)] == 4)) {
										if (num_y < 7)
											if (num_x > 2)
												if (mass[(num_x - 2) * 10 + (num_y + 2)] == 0) {
													address_cell[count] = (num_x - 2) * 10 + (num_y + 2);
													count += 1;
													cut = true;
												}
									}
									if (cut == false)
										if (mass[(num_x - 1) * 10 + (num_y + 1)] == 0) {
											address_cell[count] = (num_x - 1) * 10 + (num_y + 1);
											count += 1;
										}
								}
							}
						}
						if (num_y != 1) {
							if (num_x != 8) {
								if ((mass[(num_x + 1) * 10 + (num_y - 1)] == 2)|| (mass[(num_x + 1) * 10 + (num_y - 1)] == 4)) {
									if (num_y > 2)
										if (num_x < 7)
											if (mass[(num_x + 2) * 10 + (num_y - 2)] == 0) {
												address_cell[count] = (num_x + 2) * 10 + (num_y - 2);
												count += 1;
												cut = true;
											}
								}
								if (cut == false)
									if (mass[(num_x + 1) * 10 + (num_y - 1)] == 0) {
										address_cell[count] = (num_x + 1) * 10 + (num_y - 1);
										count += 1;
									}
							}
							if (num_x != 1) {
								if ((mass[(num_x - 1) * 10 + (num_y - 1)] == 2)|| (mass[(num_x - 1) * 10 + (num_y - 1)] == 4)) {
									if (num_y > 2)
										if (num_x > 2)
											if (mass[(num_x - 2) * 10 + (num_y - 2)] == 0) {
												address_cell[count] = (num_x - 2) * 10 + (num_y - 2);
												count += 1;
												cut = true;
											}
								}
								if (cut == false)
									if (mass[(num_x - 1) * 10 + (num_y - 1)] == 0) {
										address_cell[count] = (num_x - 1) * 10 + (num_y - 1);
										count += 1;
									}
							}
						}
					}
					for (char i = count; (i < 4); i++) {
						address_cell[count] = 0;
					}
					if (address_cell[0] != 0)
						move = true;
				}
			if (move) {
				if (event.type == Event::MouseButtonReleased)//���� ��������� �������
					if (event.key.code == Mouse::Left) {//� ������ �����
						isMove = false;
						move = false;
						pair res;
						res = coordinate(pos.x);
						num_x = res.one; coor_ceil_x = res.two;
						res = coordinate(pos.y);
						num_y = res.one; coor_ceil_y = res.two;
						number = num_x * 10 + num_y;
						number_end = number;
						for (char i = 0; i < 4; i++) {
							if ((num_x * 10 + num_y) == address_cell[i])
								move = true;
						}
						if (num != -1) {
							if (move) {
								if (white_move) {
									if ((coor_ceil_y >= 651) && (queen == false)) {
										upgrade_white += 1;
										whitesprite[num].setPosition(900, 900);
										carved_white[count_carv_white] = num;
										count_carv_white += 1;
										king_whitesprite[num].setPosition(coor_ceil_x, coor_ceil_y);
										mass[number] = 4;
									}
									else {
										if (queen) {
											king_whitesprite[num].setPosition(coor_ceil_x, coor_ceil_y);
											mass[number] = 4;
										}
										else {
											whitesprite[num].setPosition(coor_ceil_x, coor_ceil_y);
											mass[number] = 2;
										}
									}
									white_move = false;
									if (cut)
										for (char i = 0; i < 12; i++) {
											if (blacksprite[i].getGlobalBounds().contains(coord_x + ((coor_ceil_x - coord_x) / 2), coord_y + ((coor_ceil_y - coord_y) / 2))) {
												blacksprite[i].setPosition(900, 900);
												carved_black[count_carv_black] = i;
												count_carv_black += 1;
												res = coordinate(coord_x + ((coor_ceil_x - coord_x) / 2));
												num_x = res.one; coor_ceil_x = res.two;
												res = coordinate(coord_y + ((coor_ceil_y - coord_y) / 2));
												num_y = res.one; coor_ceil_y = res.two;
												mass[num_x * 10 + num_y] = 0;
											}
											if (king_blacksprite[i].getGlobalBounds().contains(coord_x + ((coor_ceil_x - coord_x) / 2), coord_y + ((coor_ceil_y - coord_y) / 2))) {
												king_blacksprite[i].setPosition(900, 900);
												carved_king_black[count_king_black] = i;
												count_king_black += 1;
												res = coordinate(coord_x + ((coor_ceil_x - coord_x) / 2));
												num_x = res.one; coor_ceil_x = res.two;
												res = coordinate(coord_y + ((coor_ceil_y - coord_y) / 2));
												num_y = res.one; coor_ceil_y = res.two;
												mass[num_x * 10 + num_y] = 0;
											}
										}
								}
								else {
									if ((coor_ceil_y < 122) && (queen == false)) {
										blacksprite[num].setPosition(900, 900);
										upgrade_black += 1;
										carved_black[count_carv_black] = num;
										count_carv_black += 1;
										king_blacksprite[num].setPosition(coor_ceil_x, coor_ceil_y);
										mass[number] = 3;
									}
									else {
										if (queen) {
											king_blacksprite[num].setPosition(coor_ceil_x, coor_ceil_y);
											mass[number] = 3;
										}
										else {
											blacksprite[num].setPosition(coor_ceil_x, coor_ceil_y);
											mass[number] = 1;
										}
									}
									white_move = true;
									if (cut)
										for (char i = 0; i < 12; i++) {
											if (whitesprite[i].getGlobalBounds().contains(coord_x + ((coor_ceil_x - coord_x) / 2), coord_y + ((coor_ceil_y - coord_y) / 2))) {
												whitesprite[i].setPosition(900, 900);
												carved_white[count_carv_white] = i;
												count_carv_white += 1;
												res = coordinate(coord_x + ((coor_ceil_x - coord_x) / 2));
												num_x = res.one; coor_ceil_x = res.two;
												res = coordinate(coord_y + ((coor_ceil_y - coord_y) / 2));
												num_y = res.one; coor_ceil_y = res.two;
												mass[num_x * 10 + num_y] = 0;
											}
											if (king_whitesprite[i].getGlobalBounds().contains(coord_x + ((coor_ceil_x - coord_x) / 2), coord_y + ((coor_ceil_y - coord_y) / 2))) {
												king_whitesprite[i].setPosition(900, 900);
												carved_king_white[count_king_white] = i;
												count_king_white += 1;
												res = coordinate(coord_x + ((coor_ceil_x - coord_x) / 2));
												num_x = res.one; coor_ceil_x = res.two;
												res = coordinate(coord_y + ((coor_ceil_y - coord_y) / 2));
												num_y = res.one; coor_ceil_y = res.two;
												mass[num_x * 10 + num_y] = 0;
											}
										}
								}
								res = coordinate(coord_x);
								num_x = res.one; coor_ceil_x = res.two;
								res = coordinate(coord_y);
								num_y = res.one; coor_ceil_y = res.two;
								mass[num_x * 10 + num_y] = 0;
								number = num_x * 10 + num_y;
								std::cout <<"move = "<< number<< "-" << number_end << "\n";
								std::cout << count_carv_white;
							}
							else
								if (white_move)
									whitesprite[num].setPosition(coord_x, coord_y);
								else
									blacksprite[num].setPosition(coord_x, coord_y);
						}
						move = false;
						queen = false;
					}
			}
			if (isMove) {
				if (white_move) {
					if (queen)
						king_whitesprite[num].setPosition(pos.x - dX, pos.y - dY);
					else
						whitesprite[num].setPosition(pos.x - dX, pos.y - dY);
				}
				else {
					if (queen)
						king_blacksprite[num].setPosition(pos.x - dX, pos.y - dY);
					else
						blacksprite[num].setPosition(pos.x - dX, pos.y - dY);
				}
			}
		}
		window.clear();
		window.draw(mapssprite);
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
			std::cout << "BLACK WIN";
			window.close();
		}
		if ((count_carv_black - upgrade_black + count_king_black) == 12) {
			std::cout << "WHITE WIN";
			window.close();
		}
		window.display();
	}
	return 0;
}