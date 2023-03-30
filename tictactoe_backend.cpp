#include<iostream>
#include<pybind11/pybind11.h>

namespace py = pybind11;

//Enum that helps identifying player turn.
namespace PlayerTurn
{
	enum PlayerTurn
	{
		PLAYER1=1,
		PLAYER2,
	};
}

//Enum that helps identifying the result of the game.
namespace Result
{
	enum Result
	{
		CONTINUE,
		PLAYER1,
		PLAYER2,
		DRAW
	};
}

//Class that controls everything of the game except taking inputs from the players.
class TicTacToe
{
private:
	//Space where the game is played.
	static int matrix[3][3];

protected:
	//Function that decides the winner.
	static bool check(int row, int column)
	{
		//Checking if the row has identical elements.
		if(matrix[row][0] == matrix[row][1] and matrix[row][1] == matrix[row][2] and matrix[row][0] != -1)
			return true;

		//Checking if the column has identical elements.
		if(matrix[0][column] == matrix[1][column] and matrix[1][column] == matrix[2][column] and matrix[0][column] != -1)
			return true;

		//Checks if the left diagonal has identical elements.
		if(row == column)
			if(matrix[0][0] == matrix[1][1] and matrix[1][1] == matrix[2][2] and matrix[1][1] != -1)
				return true;

		//Checks if the right diagonal has identical elements.
		if(row == (2-column))
			if(matrix[0][2] == matrix[1][1] and matrix[1][1] == matrix[2][0] and matrix[1][1] != -1)
				return true;

		//Tells that winner cannot be declared for now.
		return false;
	}

	//Identifies if the move is valid and makes the required changes.
	static bool makeChanges(int input, int row, int column)
	{
		if(matrix[row][column] != -1)
			return false;
		else
		{
			matrix[row][column] = input;
			return true;
		}
	}

public:
	//Sets the values of each space to -1 which later helps in identifying if the space is being filled for the first time.
	static void setup_board()
	{
		for(int i = 0; i<3; i++)
			for(int j = 0; j<3; j++)
				matrix[i][j] = -1;
	}

public:
	//Checks if the TicTacToe is full.
	static bool isFull();
	//Prints TicTacToe.
	static void getMatrix();
};

//Player1 class. Controls the moves of the player1.
class Player : public TicTacToe
{
public:
	//who's turn to play?
	static PlayerTurn::PlayerTurn turn_to_play;

	//Gets input form the player.
	static bool getInput(int input, int row, int column)
	{
		bool success = makeChanges(input, row, column);
		return success;
	}

	//Checks if the any player has won the game.
	static bool getResult(int row, int column)
	{
		bool result = check(row, column);
		return result;
	}
};

//Forward declaration of the class variables.
int TicTacToe::matrix[3][3];
PlayerTurn::PlayerTurn Player::turn_to_play;

bool TicTacToe::isFull()
{
	bool value = 1;

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(TicTacToe::matrix[i][j] == -1)
				value = 0;
			if(value == 0) break;
		}
		if(value == 0) break;
	}
	return value;
}

void TicTacToe::getMatrix()
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
			std::cout<<matrix[i][j]<<" ";
		std::cout<<"\n";
	}
}

void setup() {
	//init board to -1.
	TicTacToe::setup_board();

	//start with player 1.
	Player::turn_to_play = PlayerTurn::PLAYER1;
}

int play_once(int row, int column) {
	bool success = Player::getInput(Player::turn_to_play, row, column);
	TicTacToe::getMatrix();
	if(success == 0) return -1; //invalide play.

	bool result = Player::getResult(row, column);
	if(result) {
		if (Player::turn_to_play == PlayerTurn::PLAYER1) return Result::PLAYER1;
		else return Result::PLAYER2;
	} else if(TicTacToe::isFull()) return Result::DRAW;
		
	if(Player::turn_to_play == PlayerTurn::PLAYER1) 
		Player::turn_to_play = PlayerTurn::PLAYER2;
	else if(Player::turn_to_play == PlayerTurn::PLAYER2) 
		Player::turn_to_play = PlayerTurn::PLAYER1;

	return Result::CONTINUE; //continue play.
}

PYBIND11_MODULE(tictactoe, handle) {
	handle.def("setup", &setup);
	handle.def("play_once", &play_once);
}