#ifndef MAP_H
#define MAP_H

#include <string>
#include <iomanip>
#include <fstream>
#include "Vec.h"

using namespace std;

class Map {
	int size;
    char** grid;

public:
	Map() {
		this->size = 5;
		fstream reader;
		string word;
		
		grid = new char*[size];
		for (int i = 0; i < size; i++) {
			grid[i] = new char[size];
			for (int j = 0; j < size; j++) {
				grid[i][j] = 'p';
			}
		}
		
		reader.open("../includes/map.txt", ios::in);
		if (reader.is_open()) {
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					reader >> word;
					grid[i][j] = word[0];
				}
			}
		}
		else cout << "ERROR: MAP NOT FOUND" << endl;
		
		reader.close();
	}

	Map(const string file) {
		fstream reader;
		string word;
		
		reader.open(file, ios::in);
		if (reader.is_open()) {
			reader >> size;
			
			grid = new char*[size];
			for (int i = 0; i < size; i++) {
				grid[i] = new char[size];
				for (int j = 0; j < size; j++) {
					grid[i][j] = 'p';
				}
			}
			
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					reader >> word;
					grid[i][j] = word[0];
				}
			}
		}
		else cout << "ERROR: MAP NOT FOUND" << endl;
	
		reader.close();
	}

	~Map() {
		for (int i = 0; i < size; i++) {
			delete[] grid[i];
		} 
		delete[] grid;
	}
/*
    void loadMap(string file, int size);
	void storeMap();
*/	
	char** getMap() const {
		return grid;
	}
	char* getRow(int i) const {
		return *(grid + i);
	}
	int getSize() const {
		return size;
	}
	
	bool isValid() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (grid[i][j] == '@') {
					return true;
				}
			}
		}
		return false;
	}
	
	Vec<int> getPos() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (grid[i][j] == '@') {
					return Vec<int>(i,j);
				}
			}
		}
		cout << "error in getPos()" << endl;
		return Vec<int>(-1,-1);
	}
	
	bool movePos( Vec<int> &pos, Vec<int> move ) {
		Vec<int> test = pos;
		test.add(move);
		
		if (grid[test.getX()][test.getY()] == '*') {
			grid[pos.getX()][pos.getY()] = '0';
			grid[test.getX()][test.getY()] = '@';
			pos.add(move);
			return true;
		}
		
		if (grid[test.getX()][test.getY()] != '#') {
			grid[pos.getX()][pos.getY()] = '0';
			grid[test.getX()][test.getY()] = '@';
			pos.add(move);
		}
		return false;
	}
	
	// DEBUG
	void print() {
		cout << "map size: " << size << endl;
		
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << grid[i][j] << " ";
			}
			cout << endl;
		}
	}
};

#endif