 // Elleson Tran
// Roberts
// 8-Bit Painter
// allows the user to make 8 bit paintings in any size
// FINAL

#include "input.hpp"
#include "m/matrix.h"
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <vector>

using namespace std;

const string r = "🟥";
const string o = "🟧";
const string y = "🟨";
const string g = "🟩";
const string b = "🟦";
const string p = "🟪";
const string blk = "⬛️";
const string w = "⬜️";
const string br = "🟫";
const vector<string> colors = {r, o, y, g, b, p, blk, w, br};

// loads a vector with the names of files in a directory - the first two entries
// will be . and .., so meaningful content of vector is from index 2 on - so to
// display the file names, you should loop starting at index 2 to the end of the
// vector v back wherever you call this from - the vector will contain the FILE
// NAME and FILE EXTENSION only, so you will need to also specify the folder when
// you try to open the file
void read_directory(const std::string &name, vector<string> &v) {
	DIR *dirp = opendir(name.c_str());
	struct dirent *dp;
	while ((dp = readdir(dirp)) != NULL) {
		v.push_back(dp->d_name);
	}
	closedir(dirp);
}

// prints the board
void display(matrix<string> &board) {
	cout << endl;
	for (int row = 0; row < board.numRows(); row++) { // goes down each row
		for (int col = 0; col < board.numCols();
			 col++) { // goes through each column
			cout << board[row][col] << " ";
		}
		cout << endl;
	}
}

// prints the title
void title() {
	for (int x = 0; x < colors.size(); x++) {
		cout << colors[x] << " ";
	}
	cout << endl << "Welcome to 8-bit Drawing!" << endl;
	for (int x = 0; x < colors.size(); x++) {
		cout << colors[x] << " ";
	}
}

// asks the user for the size of the board
int ask(int &size) {
	cout << endl << "What size picture? (4-20sq): ";
	cin >> size;
	cin.ignore();

	if (size < 4) { // if the size is less than 4, makes it 4
		size = 4;
	}
	if (size > 20) { // same thing but if its greater than 20
		size = 20;
	}

	return size;
}

// restarts the board back to blanks
void restartBoard(matrix<string> &board) {
	for (int row = 0; row < board.numRows(); row++) { // goes down each row
		for (int col = 0; col < board.numCols();
			 col++) {					// goes through each column
			board[row][col] = "⬜️"; // makes the spot a blank
		}
	}
}

int main() {
	int size;
	title();
	ask(size);
	matrix<string> board(size, size);
	restartBoard(board);

	bool quit = false;
	int row = 0;
	int col = 0;
	int color = 0;

	// keeps going forever
	do {
		system("clear");
		board[row][col] = colors[color];
		display(board);

		// directions are a different because i do not have a full keyboard
		cout
			<< endl
			<< "Commands:" << endl
			<< "Move: | Left - A | Up - W | Right - D | Down - S | " << endl
			<< "Colors: | 🟥  - 1 | 🟧  - 2 | 🟨  - 3 | 🟩  - 4 | 🟦 "
			   " - 5 | 🟪  - 6 | ⬛️  - 7 | ⬜️  - 8 | 🟫  - 9 |  "
			<< endl
			<< "Other Options: Save - v | Open - n | New - f | Quit - x"
			<< endl;

		char c = 0;
		c = getch();
		c = tolower(c);

		// i do not have a full keyboard, so im using WASD instead of the number
		// keypad directions
		if (c == 'a') {		// going left
			if (col != 0) { // if we are NOT at the left edge
				col = col - 1;
			}
		}
		if (c == 'd') {			   // going right
			if (col != size - 1) { // if we are NOT the right edge
				col = col + 1;
			}
		}
		if (c == 'w') {		// going up
			if (row != 0) { // if we are NOT at the top edge
				row = row - 1;
			}
		}
		if (c == 's') {			   // going down
			if (row != size - 1) { // if we are NOT at the bottom edge
				row = row + 1;
			}
		}

		// i do not have a fullkeyboard, so im using numbers instead of letters
		// colors
		if (c == '1') { // red
			color =
				0; // spot in the colors vector changes, same thing for each one
		}
		if (c == '2') { // orange
			color = 1;
		}
		if (c == '3') { // yellow
			color = 2;
		}
		if (c == '4') { // green
			color = 3;
		}
		if (c == '5') { // blue
			color = 4;
		}
		if (c == '6') { // purple
			color = 5;
		}
		if (c == '7') { // black
			color = 6;
		}
		if (c == '8') { // white
			color = 7;
		}
		if (c == '9') { // brown
			color = 8;
		}

		const string folder = "pics/";

		// other options
		if (c == 'v') { // save
			string name;
			cout << endl << "Enter a name for this file: ";
			getline(cin, name);
			name = name + ".bit";

			ofstream outfile(folder + name); // makes a file in the pics folder
			if (outfile.fail()) {			 // if the path was wrong
				cout << endl << "File could not be opened!";
			} else {			 // if it wasnt
				outfile << size; // imports the size into the file to use later
				for (int row = 0; row < board.numRows(); row++) {
					for (int col = 0; col < board.numCols(); col++) {
						outfile << endl
								<< board[row][col]; // adds all the spots into
													// the file, as is
					}
				}
			}
			outfile.close(); // closes
		}
		if (c == 'n') { // open
			vector<string> dir;
			read_directory("pics", dir);

			int num = 0;
			for (int x = 2; x < dir.size(); x++) {
				cout << num << ") " << dir[x] << endl;
				num = num + 1;
			}

			int fileNum;
			cout << endl << "Which file?: ";
			cin >> fileNum;

			ifstream infile(
				folder + dir[fileNum + 2]); // opens the file the user wanted
			if (infile.fail()) {			// if the path was wrong
				cout << endl << "File could not be opened!";
			} else { // if it wasn't
				int size;
				infile >> size;

				matrix<string> newBoard(size, size);

				for (int row = 0; row < newBoard.numRows(); row++) {
					for (int col = 0; col < size; col++) {
						infile >>
							newBoard[row][col]; // put the block into each spot
					}
				}
				board = newBoard; // makes the current board, the saved board
				infile.close();   // closes
			}
		}
		if (c == 'f') { // new board
			system("clear");
			title();
			ask(size);
			matrix<string> newBoard(size, size); // creates a new board
			board = newBoard;	// makes the old board, the new one
			restartBoard(board); // clears everything

			// resets the placement on the board
			row = 0;
			col = 0;
		}
		if (c == 'x') { // quit
			quit = true;
		}

	} while (quit == false);

	system("clear");
	cout << "GOODBYE!";
}