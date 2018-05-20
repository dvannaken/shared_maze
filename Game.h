#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include "Map.h"
#include "Vec.h"
#include "Rect.h"

class Game {
    Map *map;
	Vec<int> hero;
	std::vector < std::vector < Rect* > > board;
	float resolution;
	bool win;
public:
	Game() {
		win = 0;
		map = new Map();
		
		if (map->isValid()) {
			std::cout << "valid map" << std::endl;
			hero = map->getPos();
		}
		else {
			hero = Vec<int>(-1,-1);
			std::cout << "invalid map" << std::endl;
		}
		
		int res = 200 / map->getSize();
		resolution = (float)res / 100;
		
		Rect *m;
		int inci = 0;
		unsigned count = 0;
		for (float j = 1; j > -1; j-=resolution) {
			int incj = 0;
			for (float i = -1; i < 1; i+=resolution) {
				char **p = map->getMap();
				if (p[inci][incj] == '#') {
					m = new Rect(count, i, j, resolution, resolution, 0, 0, 1);
				}
				else if (p[inci][incj] == '0') {
					m = new Rect(count, i, j, resolution, resolution, 1, 1, 1);
				}
				else if (p[inci][incj] == '@') {
					m = new Rect(count, i, j, resolution, resolution, 1, 0, 0);
				}
				else {
					m = new Rect(i, j, resolution, resolution);
					std::cout << "map error: invalid tile" << std::endl;
				}
				board.at(inci).push_back(m);
				incj++;
				count++;
			}
			inci++;
		}
	}
	Game(const string file) {
		win = 0;
		map = new Map(file);
		
		if (map->isValid()) {
			std::cout << "valid map" << std::endl;
			hero = map->getPos();
		}
		else {
			hero = Vec<int>(-1,-1);
			std::cout << "invalid map" << std::endl;
		}
		
		board.resize( map->getSize() );
		for ( auto &it : board ) {
			it.resize( map->getSize() );
		}
		
		int res = 200 / map->getSize();
		resolution = (float)res / 100;
		
		Rect *m;
		int inci = 0;
		unsigned count = 0;
		for (float j = 1; j > -0.99; j-=resolution) {
			int incj = 0;
			for (float i = -1; i < 0.99; i+=resolution) {
				char **p = map->getMap();
				if (p[inci][incj] == '#') {
					m = new Rect(count, i, j, resolution, resolution, 0, 0, 1);
				}
				else if (p[inci][incj] == '0') {
					m = new Rect(count, i, j, resolution, resolution, 1, 1, 1);
				}
				else if (p[inci][incj] == '@') {
					m = new Rect(count, i, j, resolution, resolution, 1, 0, 0);
				}
				else {
					m = new Rect(i, j, resolution, resolution);
				}
				
				board[inci][incj] = m;
				incj++;
				count++;
			}
			inci++;
		}
	}
	~Game() {
		delete map;
		for (unsigned i = 0; i < board.size(); i++) {
			for (unsigned j = 0; j < board.at(i).size(); j++)
				delete[] board[i][j];
		}
	}
	
	float getResolution() const {
		return resolution;
	}
	int getSize() const {
		return map->getSize();
	}
	bool isWon() const {
		return win;
	}

//	board
	float getBoardX(int x, int y) const {
		return board[x][y]->getX();
	}
	float getBoardY(int x, int y) const {
		return board[x][y]->getY();
	}
	float getBoardWidth(int x, int y) const {
		return board[x][y]->getWidth();
	}
	float getBoardHeight(int x, int y) const {
		return board[x][y]->getHeight();9;
	}
	float getBoardRed(int x, int y) const {
		return board[x][y]->getRed();
	}
	float getBoardGreen(int x, int y) const {
		return board[x][y]->getGreen();
	}
	float getBoardBlue(int x, int y) const {
		return board[x][y]->getBlue();
	}
	int getBoardSize() const {
		return board.size();
	}
	int getBoardSize(int i) const {
		return board.at(i).size();
	}
	int getBoardTotalSize() const {
		int sum = 0;
		for (unsigned i = 0; i < board.size(); i++) {
			sum += board.at(i).size();
		}
		return sum;
	}
	
	void refresh() {
		for (int i = 0; i < map->getSize(); i++) {
			for (int j = 0; j < map->getSize(); j++) {
				char **p = map->getMap();
				if (p[i][j] == '#') {
					board[i][j]->setRed(0.0);
					board[i][j]->setGreen(0.0);
					board[i][j]->setBlue(1.0);
				}
				else if (p[i][j] == '0') {
					board[i][j]->setRed(1.0);
					board[i][j]->setGreen(1.0);
					board[i][j]->setBlue(1.0);
				}
				else if (p[i][j] == '@') {
					board[i][j]->setRed(1.0);
					board[i][j]->setGreen(0.0);
					board[i][j]->setBlue(0.0);
				}
				else if (p[i][j] == '*') {
					board[i][j]->setRed(1.0);
					board[i][j]->setGreen(1.0);
					board[i][j]->setBlue(0.0);
				}
				else {
					std::cout << "map error, can't refresh" << std::endl;
					break;
				}
			}
		}
	}
	
	void onClick(float mx, float my) {}
	void onPress(unsigned char key) {
		if (map->isValid()) {
			switch (key) {
			case 'w':
				win = map->movePos( hero, Vec<int>(-1,0) );
				break;
			case 'a':
				win = map->movePos( hero, Vec<int>(0,-1) );
				break;
			case 's':
				win = map->movePos( hero, Vec<int>(1,0) );
				break;
			case 'd':
				win = map->movePos( hero, Vec<int>(0,1) );
				break;
			}
		} else std::cout << "error: no hero" << std::endl;
	}
	
	
//  DEBUG
	void print() {
		std::cout << "board size: " << board.size() << std::endl;
		map->print();
	}
	void printBoard() {
		for (int i = 0; i < map->getSize(); i++) {
			for (int j = 0; j < map->getSize(); j++) {
				if (board[i][j]) {
					std::cout << board[i][j]->getID() << std::endl;
				}
				else {
					std::cout << "map error" << std::endl;
				}
			}
		}
	}
};

#endif