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

string convert(int player) {
	if (player == 1) {
		return "\033[1;31mX\033[0m";
	}
	else if (player == 0) {
		return "\033[1;0mO\033[0m";
	}
	return " ";
}

void print_board(vector<vector<int>> board) {
	cout << "\n\n     |     |     \n";
	cout << "  " + convert(board[0][0]) + "  |  " + convert(board[0][1]) + "  |  " + convert(board[0][2]) + "  \n";
	cout << "_____|_____|_____\n";
	cout << "     |     |     \n";
	cout << "  " + convert(board[1][0]) + "  |  " + convert(board[1][1]) + "  |  " + convert(board[1][2]) + "  \n";
	cout << "_____|_____|_____\n";
	cout << "     |     |     \n";
	cout << "  " + convert(board[2][0]) + "  |  " + convert(board[2][1]) + "  |  " + convert(board[2][2]) + "  \n";
	cout << "     |     |     \n\n\n";
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



vector<vector<int>> ask_player_input(vector<vector<int>> board_state, int player = 1) {
	while (true) {
		int pos;
		cout << "Unesi broj polja >>> ";
		scanf_s("%d", &pos);

		int coords[2] = { (int)(pos - 1) / (int)board_state.size(), (pos - 1) % board_state[0].size() };

		if (board_state[coords[0]][coords[1]] != 2) {
			cout << "polje zauzeto, unosi drugo...\n";
		}
		else {
			board_state[coords[0]][coords[1]] = player;
			return board_state;
		}
	}
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

vector<vector<int>> get_best_move(vector<vector<int>> board) {
	int max_minimax = -2;

	vector<vector<vector<int>>> generated_possibilities = generate_possibilities(board, 1);

	for (int i = 0; i < generated_possibilities.size(); i++) {
		vector<vector<int>> board_ = generated_possibilities[i];
		int this_minimax = minimax(board_, 1);
		if (this_minimax > max_minimax) {
			max_minimax = this_minimax;
			board = board_;
		}
		cout << "\n" << ((float)(i + 1) / (float)generated_possibilities.size()) * 100 << "%";
	}

	cout << "\n";

	return board;
}

void print_board_old(vector<vector<int>> board) {
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

int main(void) {

	vector<vector<int>> board = {
	{2, 2, 2},
	{2, 2, 2},
	{2, 2, 2}
	};

	string dec;

	cout << "zelis li ici prvi (da/ne)? ";
	cin >> dec;

	if (dec == "da") {
		while (true) {
			print_board(board);
			if (evaluate_board(board, 1) != 0 || is_full(board) == 1) {
				if (evaluate_board(board, 1) == 1) {
					cout << "Pobijedio sam\n";
				}
				else {
					cout << "Nerijeseno\n";
				}
				break;
			}
			board = ask_player_input(board, 0);
			print_board(board);
			if (evaluate_board(board, 1) != 0 || is_full(board) == 1) {
				if (evaluate_board(board, 1) == 1) {
					cout << "Pobijedio sam\n";
				}
				else {
					cout << "Nerijeseno\n";
				}
				break;
			}
			board = get_best_move(board);
		}
	}
	else {
		while (true) {
			print_board(board);
			if (evaluate_board(board, 1) != 0 || is_full(board) == 1) {
				if (evaluate_board(board, 1) == 1) {
					cout << "Pobijedio sam\n";
				}
				else {
					cout << "Nerijeseno\n";
				}
				break;
			}
			board = get_best_move(board);
			print_board(board);
			if (evaluate_board(board, 1) != 0 || is_full(board) == 1) {
				if (evaluate_board(board, 1) == 1) {
					cout << "Pobijedio sam\n";
				}
				else {
					cout << "Nerijeseno\n";
				}
				break;
			}
			board = ask_player_input(board, 0);
		}
	}

	string decision;
	cout << "opet (da/ne)? ";
	cin >> decision;

	if (decision == "da") {
		cout << "ok, jos jednom...\n\n\n\n\n";
		main();
	}
	else{
		cout << "ok, bok...\n";
		return 0;
	}
}
