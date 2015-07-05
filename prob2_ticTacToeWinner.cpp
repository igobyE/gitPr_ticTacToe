/************************************************
*	9 | 8 | 7	Represent tic tac toe board with an int value. Each player will
*	---------	have his/her board. Every move must be verified against the other
*	6 | 5 | 4	player's board to make sure it the move is not overlapping.
*	---------	Since the board is represented by int, bitwise operations can be
*	3 | 2 | 1	used for verifications (valid move or winning).
*				If a bit position is 0, the position is available. 1 = occupied.
************************************************/

#include <iostream>
#include <string>
#include <sstream>

bool isOpen (const int& board, const int& pos) {
	int tmp = 0;
	tmp = 1<<pos;
	if ((board & tmp) == 0)
		return true;
	return false;
}

bool canMove (const int& pos) {
	if (pos < 1 || pos > 9) {
		return false;
	}
	return true;
}

/************************************************
*	Winning combinations are based on the position numbers:
*	(1, 2, 3) = ...000000111 = 7(10), 	(1, 4, 7) = ...001001001 = 73(10)
*	(1, 5, 9) = ...100010001 = 273(10),	(2, 5, 8) = ...010010010 = 146(10)
*	(3, 5, 7) = ...001010100 = 84(10),	(3, 6, 9) = ...100100100 = 292(10)
*	(4, 5, 6) = ...000111000 = 56(10),	(7, 8, 9) = ...111000000 = 448(10)
************************************************/
bool isWinner (const int& board) {
	if ((board & 7) == 7) {
		return true;
	}
	else if ((board & 73) == 73) {
		return true;
	}
	else if ((board & 273) == 273) {
		return true;
	}
	else if ((board & 146) == 146) {
		return true;
	}
	else if ((board & 84) == 84) {
		return true;
	}
	else if ((board & 292) == 292) {
		return true;
	}
	else if ((board & 56) == 56) {
		return true;
	}
	else if ((board & 448) == 448) {
		return true;
	}
	return false;
}

void showBoard (const int& board1, const int& board2) {
	for (int i=8; i>=0; --i) {
		if ((board1 & (1<<i)) > 0) {
			std::cout << " x ";
		}
		else if ((board2 & (1<<i)) > 0) {
			std::cout << " o ";
		}
		else {
			std::cout << "   ";
		}

		if (i == 6 || i == 3) {
			std::cout << std::endl;
			std::cout << "-----------\n";
		}
		else if (i == 0){
			std::cout << std::endl;
		}
		else {
			std::cout << "|";
		}
	}
	std::cout << std::endl;
}

void printDefaultBoard () {
	for (int i=8; i>=0; --i) {
		std::cout << ' ' << i+1 << ' ';

		if (i == 6 || i == 3) {
			std::cout << std::endl;
			std::cout << "-----------\n";
		}
		else if (i == 0){
			std::cout << std::endl;
		}
		else {
			std::cout << "|";
		}
	}
	std::cout << std::endl;
}

int getInput (const int& player) {
	int myNumber = 0;
	bool term = false;
	while (!term) {
		std::string input = "";
		std::cout << "Player: " << player << "\n\tPlease enter your move (1-9): ";
		getline(std::cin, input);

		// This code converts from string to number safely.
		std::stringstream myStream(input);
		if (myStream >> myNumber) {
			term = true;
		}

		if (!canMove (myNumber)) {
			std::cout << "Invalid input!\n";
			term = false;
		}
	 }

	return myNumber;
}

int main () {
	int board1 = 0;
	int board2 = 0;
	bool term = false;
	int cntMvs = 0;
	// showBoard (board1, board2);

	do {
		for (int plr=1; plr<=2; ++plr) {
			std::cout << "Move count: " << cntMvs << std::endl;
			showBoard (board1, board2);
			int pos = getInput (plr)-1;

			int boardPlr = 0;
			int boardOpp = 0;
			if (plr == 1) {
				boardOpp = board2;
				boardPlr = board1;
			}
			else {
				boardOpp = board1;
				boardPlr = board2;
			}

			if (!isOpen (boardOpp, pos)) {
				std::cout << "\tThe position is occupied by the other player!\n";
				plr -= 1;
				continue;
			}

			if (!isOpen (boardPlr, pos)) {
				std::cout << "\tYou already moved there!\n";
				plr -= 1;
				continue;
			}

			boardPlr = boardPlr | (1<<pos);
			if (plr == 1) {
				board1 = boardPlr;
			}
			else {
				board2 = boardPlr;
			}

			if (isWinner (boardPlr)) {
				showBoard (board1, board2);
				std::cout << "\tThe WINNER is player " << plr << "!\n";
				term = true;
				break;
			}

			cntMvs += 1;
			if (cntMvs > 8) {
				showBoard (board1, board2);
				std::cout << "\tThe game tied!\n";
				term = true;
				break;
			}
		}

		if (term == true) {
			std::cout << "Do you want to play again? (y/n)\n";
			std::string tmp = "n";
			getline(std::cin, tmp);
			if (tmp.compare("y") == 0) {
				term = false;
				board1 = 0;
				board2 = 0;
				cntMvs = 0;
			}
		}
	} while (term != true);

	return 0;
}