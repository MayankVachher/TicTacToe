#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int board[3][3];

int check_win(int board[3][3]) {
	
	int i;
	for(i = 0; i < 3; i++) {
		if(board[i][0] && board[i][1] == board[i][2] && board[i][2] == board[i][0]) {
			return board[i][0];
		}
		if(board[0][i] && board[1][i] == board[2][i] && board[2][i] == board[0][i]) {
			return board[0][i];
		}
	}

	if(!board[1][1])
		return 0;
	if(board[1][1] == board[0][0] && board[2][2] == board[1][1]) {
		return board[1][1];
	}
	if(board[1][1] == board[0][2] && board[1][1] == board[2][0]) {
		return board[1][1];
	}

	return 0;
}


void reset_board() {
	int i, j;
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			board[i][j] = 0;
		}
	}
}


void print_board() {
	int i, j;
	char *move = "X O";
	printf(" ___  ___  ___ \n");
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			printf("| %c |", move[board[i][j] + 1]);
		}
		printf("\n|___||___||___|\n");
	}
	printf("\n");
}

void print_board_start() {
	int i, j;
	char *move = "X O";
	printf(" ___  ___  ___ \n");
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			printf("| %d |", i*3 + j + 1);
		}
		printf("\n|___||___||___|\n");
	}
	printf("\n");
}

int board_full(int board[3][3]) {
	int i, j;
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			if(board[i][j] == 0) {
				return 0;
			}
		}
	}
	return 1;
}

int valid_move(int pos, int player) {
	if(pos > 9 || pos < 1) {
		printf("Invalid move! Try Again.\n");
		return 0;
	}
	int play_i, play_j;
	play_i = pos/3;
	play_j = pos%3;
	if(play_j == 0) {
		play_i--;
		play_j = 2;
	}
	else {
		play_j--;
	}
	if(board[play_i][play_j] != 0) {
		return 0;
	}
	else {
		board[play_i][play_j] = player;
		return player;
	}
}

void player_move() {
	int pos, valid = 1;
	do {
		if(!valid){
			printf("Invalid move! Try Again.\n");
		}
		printf("\n\nEnter position you want to play: ");
		scanf("%d", &pos);
	}while(!(valid = valid_move(pos, 1)));
}

void populate(int a[3][3], int b[3][3]) {
	int i, j;
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			a[i][j] = b[i][j];
		}
	}
}

void computer_move() {
	int pos = -26;
	int i, j, best_i = 1, best_j = 1;
	int points = 25, move_points = 0;

	printf("\n\nZ3TA plays position: ");
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			if(!board[i][j]) {
				board[i][j] = -1;
				move_points = minimax(board, 1);
				//printf("%d\n", move_points); the magic happens here!
				if(points > move_points) {
					points = move_points;
					pos = i*3 + j + 1;
					best_i = i;
					best_j = j;
				}
				board[i][j] = 0;
			}
		}
	}

	board[best_i][best_j] = -1;
	printf("%d\n", pos);
}

int minimax(int b[3][3], int player) {
	
	int val = check_win(b);
	int i, j;
	int points = 25, move_points = 0;
	if(player == 1) points = -points;

	if(val || board_full(b)) {
		return val;
	}
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			
			if(!b[i][j]) {
				
				if(player == -1) {
					b[i][j] = -1;
					move_points = minimax(b, 1);
					if(points > move_points) {
						points = move_points;
					}
				}
				
				else {
					b[i][j] = 1;
					move_points = minimax(b, -1);
					if(points < move_points) {
						points = move_points;
					}
				}

				b[i][j] = 0;
			}
		}
	}

	return points;
}

void play_game() {
	char name[50];
	printf("Hi!\n\nI am Z3TA.\n\nWhat's your name: ");
	scanf("%s", name);
	int play_first = 0;
	printf("\n\nDo you want to play first? 1 - Yes, 0 - No:  ");
	scanf("%d", &play_first);
	printf("\n\n\nX: Z3TA\nO: %s\n\n\n",name);
	if(!play_first) {
			while(!board_full(board) && !check_win(board)) {
			computer_move();
			printf("Z3TA just made a move...\n");
			print_board();
			if(board_full(board) || check_win(board)) {
				break;
			}
			player_move();
			printf("%s just made a move...\n", name);
			print_board();
		}
	}

	else {
			while(!board_full(board) && !check_win(board)) {
			player_move();
			printf("%s just made a move...\n", name);
			print_board();
			if(board_full(board) || check_win(board)) {
				break;
			}
			computer_move();
			printf("Z3TA just made a move...\n");
			print_board();
		}
	}

	printf("\n\n------------------------------\n\n");
	if(check_win(board) == 0) {
		printf("It's a DRAW!\n");
	}
	else if(check_win(board) == 1) {
		printf("%s WON!\n", name);
	}
	else {
		printf("Z3TA WON!\n");
	}
	printf("\n------------------------------\n");
}

int main() {
	reset_board();
	print_board_start();
	play_game();
	return 0;
}