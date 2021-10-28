#include <iostream>
#include <vector>

using namespace std;

int evaluate_board(vector<vector<int>> board, int player) {
	//redci
	for (vector<int> row : board) {
		if (row[0] == row[1] && row[1] == row[2]) {
			if (row[1] == 2) {
				continue;
			}
			if (row[1] == player) {
				return 1;
			}
			return -1;
		}
	}

	//stupci
	for (int i = 0; i < board[0].size(); i++) {
		vector<int> column = {board[0][i], board[1][i], board[2][i]};
		if (column[0] == column[1] && column[1] == column[2]) {
			if (column[1] == 2) {
				continue;
			}
			if (column[1] == player) {
				return 1;
			}
			return -1;
		}
	}

	//linije ukoso
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
		if (board[1][1] != 2) {
			if (board[1][1] == player) {
				return 1;
			}
			return -1;
		}
	}

	if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
		if (board[1][1] != 2) {
			if (board[1][1] == player) {
				return 1;
			}
			return -1;
		}
	}

	return 0;

}

void print_board(vector<vector<int>> board) {
	for (vector<int> row : board) {
		for (int element : row) {
			if (element == 2) {
				cout << "/ ";
				continue;
			}
			cout << element << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

vector<vector<vector<int>>> generate_possibilities(vector<vector<int>> board, int player) {
	vector<vector<vector<int>>> possibilities = {};

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j] != 2) {
				continue;
			}

			vector<vector<int>> board_copy = board;
			board_copy[i][j] = player;
			possibilities.push_back(board_copy);

		}
	}

	return possibilities;

}

int is_full(vector<vector<int>> board) {
	if (generate_possibilities(board, 0).size() == 0) {
		return 1;
	}
	return 0;
}

int max(vector<int> list) {
	int max_element = list[0];

	for (int element : list) {
		if (element > max_element) {
			max_element = element;
		}
	}

	return max_element;

}

int min(vector<int> list) {
	int min_element = list[0];

	for (int element : list) {
		if (element < min_element) {
			min_element = element;
		}
	}

	return min_element;

}

int minimax(vector<vector<int>> board, int is_maximizing) {
	if (evaluate_board(board, 1) != 0 || is_full(board) == 1) {
		return evaluate_board(board, 1);
	}

	vector<vector<vector<int>>> generated_boards = generate_possibilities(board, (is_maximizing + 1) % 2);
	vector<int> scores = {};

	for (vector<vector<int>> board_state : generated_boards) {
		scores.push_back(minimax(board_state, (is_maximizing + 1) % 2));
	}

	if (is_maximizing == 0) {
		return max(scores);
	}

	return min(scores);

}

int main(void) {

	vector<vector<int>> board = {
		{1, 0, 2},
		{2, 0, 2},
		{0, 1, 2}
	};

	for (vector<vector<int>> board_ : generate_possibilities(board, 1)){
		cout << minimax(board_, 1);
		cout << "\n";
		print_board(board_);
	}

}
