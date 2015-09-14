#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int board[3][3];

int check_win() {
	
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

int board_full() {
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
		printf("\nYour turn!\nEnter position to play: ");
		scanf("%d", &pos);
	}while(!(valid = valid_move(pos, 1)));
}

void computer_move() {
	int pos;
	srand((unsigned int)time(NULL));
	printf("\nComputer's turn!\nEnter position to play: ");
	do {
		pos = rand() % 9 + 1;
	}while(!valid_move(pos, -1));
	printf("%d\n", pos);
}

play_game() {
	printf("X: Computer\nO: User\nThe Computer always plays first!\n\n");
	while(!board_full() && !check_win()) {
		computer_move();
		printf("Computer just made a move...\n");
		print_board();
		if(board_full() || check_win()) {
			break;
		}
		player_move();
		printf("You just made a move...\n");
		print_board();
	}

	printf("\n\n------------------------------\n\n");
	if(check_win() == 0) {
		printf("It's a DRAW!\n");
	}
	else if(check_win() == 1) {
		printf("YOU WON!\n");
	}
	else {
		printf("COMPUTER WON!\n");
	}
	printf("\n------------------------------\n");
}

int main() {
	reset_board();
	print_board();
	play_game();
	return 0;
}