#include <iostream>
#include <vector>

using namespace std;

vector<vector<vector<int>>> generate_boards(vector<vector<int>> board, int player) {
	vector<vector<vector<int>>> boards = {};
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			if (board[i][j] != 2)
			{
				continue;
			}
			vector<vector<int>> board1 = board;
			board1[i][j] = player;
			boards.push_back(board1);
		}
	}
	return boards;
}

int has_won(vector<vector<int>> board_state, int player) {
	for (int i = 0; i < board_state.size(); i++)
	{
		if (board_state[i][0] == board_state[i][1] && board_state[i][0] == board_state[i][2])
		{
			if (board_state[i][0] == player)
			{
				return 10;
			}
			else if (board_state[i][0] != 2)
			{
				return -10;
			}
		}
	}

	for (int i = 0; i < board_state[0].size(); i++)
	{
		if (board_state[0][i] == board_state[1][i] && board_state[0][i] == board_state[2][i])
		{
			if (board_state[0][i] == player) {
				return 10;
			}
			else if (board_state[0][i] != 2) {
				return -10;
			}
		}
	}

	if (board_state[0][0] == board_state[1][1] && board_state[0][0] == board_state[2][2]) {
		if (board_state[0][0] == player)
		{
			return 10;
		}
		else if (board_state[0][0] != 2) {
			return -10;
		}
	}

	if (board_state[0][2] == board_state[1][1] && board_state[0][2] == board_state[2][0]) {
		if (board_state[0][2] == player)
		{
			return 10;
		}
		else if (board_state[0][2] != 2) {
			return -10;
		}
	}

	return 0;
}


int minimax(vector<vector<int>> board_state, int player, int depth) {
	if (has_won(board_state, player) != 0) {
		return has_won(board_state, player) - depth;
	}
	vector<vector<vector<int>>> generated_possibilities = generate_boards(board_state, player);

	if (generated_possibilities.size() == 0) {
		return -depth;
	}

	int min_opponent = INFINITY;
	vector<vector<int>> best_board = generated_possibilities[0];

	for (vector<vector<int>> board_config : generated_possibilities) {
		if (minimax(board_config, (player + 1) % 2, depth + 1) < min_opponent)
		{
			min_opponent = minimax(board_config, (player + 1) % 2, depth + 1);
			best_board = board_config;
		}
	}

	return has_won(best_board, player) - depth;

}

vector<vector<int>> get_best_move(vector<vector<int>> board_state, int player) {
	vector<vector<vector<int>>> possibilities = generate_boards(board_state, player);

	int max_minimax = -INFINITY;
	vector<vector<int>> best_board = possibilities[0];

	for (vector<vector<int>> board_config : possibilities) {
		if (minimax(board_config, player, 0) > max_minimax)
		{
			max_minimax = minimax(board_config, player, 0) > max_minimax;
			best_board = board_config;
		}
	}

	return best_board;

}

int is_full(vector<vector<int>> board_state) {
	if (generate_boards(board_state, 0).size() == 0) {
		return 1;
	}
	return 0;
}

char convert(int oznaka) {
	if (oznaka == 1)
	{
		return 'o';
	}
	if (oznaka == 0)
	{
		return 'x';
	}
	return ' ';
}

void print_big_vector(vector<vector<int>> big_vector) {
	cout << "\n";
	cout << convert(big_vector[0][0]) << " | " << convert(big_vector[0][1]) << " | " << convert(big_vector[0][2]);
	cout << "\n_________\n";
	cout << convert(big_vector[1][0]) << " | " << convert(big_vector[1][1]) << " | " << convert(big_vector[1][2]);
	cout << "\n_________\n";
	cout << convert(big_vector[2][0]) << " | " << convert(big_vector[2][1]) << " | " << convert(big_vector[2][2]);
	cout << "\n\n";
}

vector<vector<int>> ask_player_input(vector<vector<int>> board_state) {
	while (true) {
		int potez = 0;
		cout << "odaberi svoj potez >> ";
		scanf_s("%d", &potez);
		potez -= 1;
		if (board_state[(int)potez / board_state.size()][potez % board_state[0].size()] == 2)
		{
			board_state[(int)potez / board_state.size()][potez % board_state[0].size()] = 0;
			return board_state;
		}
		cout << "\nTaj potez je zauzet, pokusaj ponovo...\n";
	}
}

int main(void) {
	vector<vector<int>> board_state = {
		{2, 2, 2},
		{2, 2, 2},
		{2, 2, 2}
	};

	print_big_vector(board_state);

	while (is_full(board_state) == 0) {
		cout << "razmisljam...\n";
		board_state = get_best_move(board_state, 1);
		print_big_vector(board_state);
		if (is_full(board_state) == 1) {
			break;
		}
		board_state = ask_player_input(board_state);
		print_big_vector(board_state);
	}
	cout << "\n";
	if (has_won(board_state, 0) == 10)
	{
		cout << "pobijedio si!!";
	}
	else if (has_won(board_state, 0) == -10) {
		cout << "izgubio si :(";
	}
	else {
		cout << "nerijeseno!";
	}
	while (1);
}
