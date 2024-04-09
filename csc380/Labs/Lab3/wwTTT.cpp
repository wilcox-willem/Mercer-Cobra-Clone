// WILLEM WILCOX, DR. DIGH, CSC380, MU

#include <iostream>
#include <string>
using namespace std;

enum Player {
	Human = -1,
	Blank = 0,
	Computer = 1
};

void printBoard(Player board[]);
// WW: My additions
bool isMoveValid(Player board[], int move); 
bool isWinner(Player board[], Player player); 
bool isDraw(Player board[]); 
void playGame(Player board[]);
int getComputerMove(Player board[]);

int main() {
	char play = 'Y';

	while(play == 'Y') {
		Player board[9] = {Blank,Blank,Blank,Blank,Blank,Blank,Blank,Blank,Blank};
		cout << "To play, use 1-9\n  1 | 2 | 3 \n-------------\n  4 | 5 | 6\n-------------\n  7 | 8 | 9 \n" << endl;
		printBoard(board);
		playGame(board);
		cout << "Do you want to play again? (Y/N) ";
		cin >> play;
		cout << endl;
	}
	return 0;
}

void printBoard(Player board[]) {
	
	for(int i = 0; i < 9; i++) {
		if((i == 2) || (i == 5) || (i == 8)) {
			if(board[i] == -1)
				cout << " X";
			else if (board[i] == 1)
				cout << " O";
			else
				cout << "  ";
		} else {
			if(board[i] == -1)
                                cout << "  X |";
                        else if (board[i] == 1)
                                cout << "  O |";
                        else
                                cout << "    |";
		}
		if(((i+1)%3 == 0) && (i != 8)) {
			cout << endl << "----|----|----" << endl;
		}
		if(i == 8)
			cout << endl;
	}

	cout << endl;

}

/*
 *
 *    In your playGame method, you will set up a loop like this :
 *    while (true)
 *    {
 *    		Human makes move & check for winner
 *    		Machine makes best move & check for winner
 *    		Exit when winner found
 *    }
 *
 *    When human selects, remember to input-- to be in range on your array.
 *
 *    HINT when human moves:
 *                    Player human = Human;
 *                    board[input] = human;
 *    HINT when computer moves:
 *                    Player computer = Computer;
 *                    board[input] = computer;
 *

 *
 * */

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

// isMoveValid() :: checks to see if move is not taken and in-bounds (1-9)
bool isMoveValid(Player board[], int move) {
	// in: current board, move being tried
	//out: true if valid
	return ((board[move] == Blank) && (10 > move && move > -1));
}

// isWinner() :: checks all possible win conditions
bool isWinner(Player board[], Player player) {
	// in: current board, player being checked
	//out: true if that player won
	// The board is
	// 0 | 1 | 2
	//-----------
	// 3 | 4 | 5
	//-----------
	// 6 | 7 | 8
	
	// check columns
    for (int i = 0; i < 3; i++) {
        if ((board[i] == player) && (board[i + 3] == player) && (board[i + 6] == player))
            return true;
    }

	// check rows
    for (int i = 0; i < 3; i++) {
        if ((board[i * 3] == player) && (board[i * 3 + 1] == player) && (board[i * 3 + 2] == player))
            return true;
    }

    // check diagonals
    if ((board[0] == player) && (board[4] == player) && (board[8] == player))
        return true;
    if ((board[2] == player) && (board[4] == player) && (board[6] == player))
        return true;

    return false;
}

// isDraw() :: checks if board is full
bool isDraw(Player board[]) {
	// in: current board
	//out: true if full and no winner
	for (int i = 0; i < 9; i++) {
		if (board[i] == Blank) {
			return false;
		}
	}

	// further verify no wins to determine draw
	if (isWinner(board, Computer)) return false;
	if (isWinner(board, Human)) return false;

	return true;
}

// getComputerMove() :: uses alg to determine what move to make
int getComputerMove(Player board[]) {
	// in: current board
	//out: board position to play, or -1 if error

	// 1st
	// start by checking if there is a winning move
	for (int i = 0; i < 9; i++) {
		if (isMoveValid(board, i)){
			board[i] = Computer;
			if (isWinner(board, Computer)) {
				board[i] = Blank; // reset move
				return i;
			}
			board[i] = Blank; // reset move
		}
	}

	// if no winning move, check to block any opponent winning moves
		for (int i = 0; i < 9; i++) {
		if (isMoveValid(board, i)){
			board[i] = Human;
			if (isWinner(board, Human)) {
				board[i] = Blank; // reset move
				return i;
			}
			board[i] = Blank; // reset move
		}
	}

	// 2nd
	// if a move to make two rows of two-in-a-row, take it
	// CURRENTLY, UNSURE HOW TO IMPLEMENT, MOVING ON,

	// 3rd
	// if center is free, play there (4)
	if (isMoveValid(board, 4)){
		return 4;
	}

	// 4th
	// if opponent played corner, play opposite if possible
	for (int i = 0; i < 5; i++) {
		if (i == 2) break;
		
		if ( (board[i*2] == Human) && (isMoveValid(board, (8 - i*2))) ) {
			return (8 - i*2); // opposite corner
		}
	}

	// 5th
	// if there is an empty corner, take it
	for (int i = 0; i < 5; i++) {
		if (i == 2) break;
		
		if (isMoveValid(board, i*2)) {
			return (i*2); // empty corner
		}
	}

	// 6th
	// if all else fails, play the first empty square
	for (int i = 0; i < 9; i++) {
		if (isMoveValid(board, i)) {
			return i;
		}
	}

	// okay, IF ALL ELSE FAILS, return -1
	return -1;

// end getComputerMove()
}

// playGame() :: starts game with empty board, man vs machine
void playGame(Player board[]) {
	// in: blank game board
	//out: plays game until win or draw
	while (true) {
		int user_move = -1;
		cout << "Where do you want to play? ";
		cin >> user_move;
		user_move -= 1; // To account for 1-9 grid displayed for user
		
		// handle invalid inputs
		while (!isMoveValid(board, user_move)) {
			cout << "Invalid move\nWhere do you want to play? ";
			cin >> user_move;
		}
		cout << endl;

		board[user_move] = Human;
		printBoard(board);
		if (isWinner(board, Human)) {
			cout << "Congrats on winning! " << endl;
			break;
		}

		if (isDraw(board)) {
			cout << "Draw, good game! " << endl;
			break;
		}

		// computers turn
		int computer_move = getComputerMove(board);
		board[computer_move] = Computer;
		printBoard(board);
		if (isWinner(board, Computer)) {
			cout << "Better luck next time! " << endl;
			break;
		}

	}
}