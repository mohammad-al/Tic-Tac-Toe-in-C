#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define GAMEOVER 1
#define NAME_LEN_MAX 12

void clearInputBuff();
void printGame(char map[3][3]);
char getGameMode(void);
void setPlayersNames(char *player1, char *player2);
void setSinglePlayerName(char *player);
bool getPlayerName(char *player);
void initMap(char map[3][3]);
bool getPlayerMove(char map[3][3], char *playerName, char letter);
bool doCompMove(char map[3][3], char letter);
bool isTie(char map[3][3]);
bool isWinner(char map[3][3]);
void enterMultiplayerMode(char map[3][3]);
void multiplayerLoopPlayer1StartFirst(
	char map[3][3],
	char *player1,
	char *player2
);
void multiplayerLoopPlayer2StartFirst(
	char map[3][3],
	char *player1,
	char *player2
);
void enterSingleplayerMode(char map[3][3]);
void singlePlayerLoopXStartFirst(char map[3][3], char *player);
void singlePlayerLoopXStartSecond(char map[3][3], char *player);
void singlePlayerLoopOStartFirst(char map[3][3], char *player);
void singlePlayerLoopOStartSecond(char map[3][3], char *player);

int main(int argc, char **argv) {

	printf("Welcome to my tic-tac-toe game!\n\n\n");
	char map[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
	printGame(map);
	initMap(map);
	printf("\n\n");

	char mode = getGameMode();
	char *player1 = malloc(sizeof(char) * (NAME_LEN_MAX + 1));

	if (mode == 'm') {
		enterMultiplayerMode(map);
	} else {
		enterSingleplayerMode(map);
	}
	
	return 0;
}

void enterSingleplayerMode(char map[3][3]) {
		srand(74612);
		char *player = malloc(sizeof(char) * (NAME_LEN_MAX + 1));

		printf("Welcome to single-player mode!\n\n\n");
	 	setSinglePlayerName(player);

		char isX;

		printf("Do you want to be X's? (y/n): ");
		while ((isX = tolower(getchar())) != 'y'
			&& isX != 'n') {
			printf("Do you want to be X's? (y/n): ");
	 		clearInputBuff();
		}
	 	clearInputBuff();

		char startFirst;
		printf("Do you want %s to start first? (y/n): ", player);
		while ((startFirst = tolower(getchar())) != 'y'
			&& startFirst != 'n') {
			printf("Do you want %s to start first? (y/n): ", player);
	 		clearInputBuff();
		}
	 	clearInputBuff();

		printf("Game is starting!!!\n");
		if (isX == 'y' && startFirst == 'y') {
			printGame(map);
	 		singlePlayerLoopXStartFirst(map, player);
		} else if (isX == 'y' && startFirst == 'n') {
			printGame(map);
	 		singlePlayerLoopXStartSecond(map, player);
		} else if (isX == 'n' && startFirst == 'y') {
			printGame(map);
	 		singlePlayerLoopOStartFirst(map, player);
		} else {
			printGame(map);
	 		singlePlayerLoopOStartSecond(map, player);
		}
			
}

void singlePlayerLoopXStartFirst(char map[3][3], char *player) {

	while (true) {

		while (!getPlayerMove(map, player, 'X')) {
			;
		}
		printGame(map);
		if (isTie(map)) {
			printf("This game has ended in a draw!\n");
			return;
		}

		if (isWinner(map)) {
			printf("Hey %s. You won!\n", player);
			return;
		} else {
			printf("Computers turn\n");
			while (!doCompMove(map, 'O')) {
				printf("Comuter searching for a position\n");
			}
			printGame(map);

			if (isWinner(map)) {
				printf("Unlucky, the computer won!\n");
				return;
			}
		}
	}
	
}

void singlePlayerLoopXStartSecond(char map[3][3], char *player) {

	while (!isTie(map)) {

		printf("Computers turn\n");
		while (!doCompMove(map, 'O')) {
			printf("Comuter searching for a position\n");
		}
		printGame(map);
		if (isTie(map)) {
			printf("This game has ended in a draw!\n");
			return;
		}

		if (isWinner(map)) {
			printf("Unlucky, the computer won!\n");
			return;
		} else {
			
			while (!getPlayerMove(map, player, 'X')) {
				;
			}
			printGame(map);

			if (isWinner(map)) {
				printf("Hey %s. You won!\n", player);
				return;
			}
		}
	}
	printf("This game has ended in a draw!\n");
	
}
void singlePlayerLoopOStartFirst(char map[3][3], char *player) {
	

	while (!isTie(map)) {

		while (!getPlayerMove(map, player, 'O')) {
			;
		}
		printGame(map);
		if (isTie(map)) {
			printf("This game has ended in a draw!\n");
			return;
		}

		if (isWinner(map)) {
			printf("Hey %s. You won!\n", player);
			return;
		} else {
			
			printf("Computers turn\n");
			while (!doCompMove(map, 'O')) {
				printf("Comuter searching for a position\n");
			}
			printGame(map);

			if (isWinner(map)) {
				printf("Unlucky, the computer won!\n");
				return;
			}
		}
	}
	printf("This game has ended in a draw!\n");
	
}

void singlePlayerLoopOStartSecond(char map[3][3], char *player) {
	

	while (!isTie(map)) {

		printf("Computers turn\n");
		while (!doCompMove(map, 'O')) {
			printf("Comuter searching for a position\n");
		}
		printGame(map);
		if (isTie(map)) {
			printf("This game has ended in a draw!\n");
			return;
		}

		if (isWinner(map)) {
			printf("Unlucky, the computer won!\n");
			return;
		} else {
			
			while (!getPlayerMove(map, player, 'O')) {
				;
			}
			printGame(map);

			if (isWinner(map)) {
				printf("Hey %s. You won!\n", player);
				return;
			}
		}
	}
	printf("This game has ended in a draw!\n");
	
}
void enterMultiplayerMode(char map[3][3]) {

		char *player1 = malloc(sizeof(char) * (NAME_LEN_MAX + 1));
		char *player2 = malloc(sizeof(char) * (NAME_LEN_MAX + 1));

		printf("Welcome to multiplayer mode!\n\n\n");
		setPlayersNames(player1, player2);

		char player1StartFirst;

		printf("Do you want %s to start first? (y/n): ", player1);
		while ((player1StartFirst = tolower(getchar())) != 'y'
			&& player1StartFirst != 'n') {
			printf("Do you want %s to start first? (y/n): ", player1);
	 		clearInputBuff();
		}
	 	clearInputBuff();

		if (player1StartFirst == 'y') {
			printf("Game is starting!!!\n");
			printGame(map);
			multiplayerLoopPlayer1StartFirst(map, player1, player2);
		} else {
			printGame(map);
			multiplayerLoopPlayer2StartFirst(map, player1, player2);
		}
}
void multiplayerLoopPlayer1StartFirst(
	char map[3][3],
	char *player1,
	char *player2
) {
	while (!isTie(map)) {

		while (!getPlayerMove(map, player1, 'X')) {
			;
		}
		printGame(map);
		if (isTie(map)) {
			printf("This game has ended in a draw!\n");
			return;
		}

		if (isWinner(map)) {
			printf("Hey %s. You won!\n", player1);
			return;
		} else {

			while (!getPlayerMove(map, player2, 'O')) {
				;
			}
			printGame(map);
			if (isWinner(map)) {
				printf("Hey %s. You won!\n", player2);
				return;
			}
		}
	}
	printf("This game has ended in a draw!\n");
}

void multiplayerLoopPlayer2StartFirst(
	char map[3][3],
	char *player1,
	char *player2
) {

	while (!isTie(map)) {

		while (!getPlayerMove(map, player2, 'O')) {
			;
		}
		printGame(map);
		if (isTie(map)) {
			printf("This game has ended in a draw!\n");
			return;
		}

		if (isWinner(map)) {
			printf("Hey %s. You won!\n", player2);
			return;
		} else {

			while (!getPlayerMove(map, player1, 'X')) {
				;
			}
			printGame(map);
			if (isWinner(map)) {
				printf("Hey %s. You won!\n", player1);
				return;
			}
		}
	}
}

bool isWinner(char map[3][3]) {
	if (map[0][0] == 'X' && map[1][0] == 'X' && map[2][0] == 'X') {
		return true;
	} else if (map[0][1] == 'X' && map[1][1] == 'X' && map[2][1] == 'X') {
		return true;
	} else if (map[0][2] == 'X' && map[1][2] == 'X' && map[2][2] == 'X') {
		return true;
	} else if (map[0][0] == 'X' && map[0][1] == 'X' && map[0][2] == 'X') {
		return true;
	} else if (map[1][0] == 'X' && map[1][1] == 'X' && map[1][2] == 'X') {
		return true;
	} else if (map[2][0] == 'X' && map[2][1] == 'X' && map[2][2] == 'X') {
		return true;
	} else if (map[0][0] == 'X' && map[1][1] == 'X' && map[2][2] == 'X') {
		return true;
	} else if (map[0][2] == 'X' && map[1][1] == 'X' && map[2][0] == 'X') {
		return true;
	} else if (map[0][0] == 'O' && map[1][0] == 'O' && map[2][0] == 'O') {
		return true;
	} else if (map[0][1] == 'O' && map[1][1] == 'O' && map[2][1] == 'O') {
		return true;
	} else if (map[0][2] == 'O' && map[1][2] == 'O' && map[2][2] == 'O') {
		return true;
	} else if (map[0][0] == 'O' && map[0][1] == 'O' && map[0][2] == 'O') {
		return true;
	} else if (map[1][0] == 'O' && map[1][1] == 'O' && map[1][2] == 'O') {
		return true;
	} else if (map[2][0] == 'O' && map[2][1] == 'O' && map[2][2] == 'O') {
		return true;
	} else if (map[0][0] == 'O' && map[1][1] == 'O' && map[2][2] == 'O') {
		return true;
	} else if (map[0][2] == 'O' && map[1][1] == 'O' && map[2][0] == 'O') {
		return true;
	} else {
		return false;
	}
}

bool isTie(char map[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (map[i][j] == ' ') {
				return false;
			}
		}
	}
	return true;
}

bool doCompMove(char map[3][3], char letter) {
	int compPos = rand();
	compPos = (compPos % 9) + 1;
	switch (compPos) {
		case 1:
			if (map[0][0] == ' ') { map[0][0] = letter; return true;}
		case 2:
			if (map[0][1] == ' ') { map[0][1] = letter; return true;}
		case 3:
			if (map[0][2] == ' ') { map[0][2] = letter; return true;}
		case 4:
			if (map[1][0] == ' ') { map[1][0] = letter; return true;}
		case 5:
			if (map[1][1] == ' ') { map[1][1] = letter; return true;}
		case 6:
			if (map[1][2] == ' ') { map[1][2] = letter; return true;}
		case 7:
			if (map[2][0] == ' ') { map[2][0] = letter; return true;}
		case 8:
			if (map[2][1] == ' ') { map[2][1] = letter; return true;}
		case 9: 
			if (map[2][2] == ' ') { map[2][2] = letter; return true;}
	}
	return false;
}
bool getPlayerMove(char map[3][3], char *playerName, char letter) {
	printf("Hey %s, its your turn. Please enter a position: ", playerName);
	int pos = getchar();
	clearInputBuff();
	switch (pos) {
		case '1':
			if (map[0][0] == ' ') { map[0][0] = letter; return true;}
		case '2':
			if (map[0][1] == ' ') {map[0][1] = letter; return true;}
		case '3':
			if (map[0][2] == ' ') {map[0][2] = letter; return true;}
		case '4':
			if (map[1][0] == ' ') {map[1][0] = letter; return true;}
		case '5':
			if (map[1][1] == ' ') {map[1][1] = letter; return true;}
		case '6':
			if (map[1][2] == ' ') {map[1][2] = letter; return true;}
		case '7':
			if (map[2][0] == ' ') {map[2][0] = letter; return true;}
		case '8':
			if (map[2][1] == ' ') {map[2][1] = letter; return true;}
		case '9': 
			if (map[2][2] == ' ') {map[2][2] = letter; return true;}
	}
	return false;
}

void setPlayersNames(char *player1, char *player2) {

	printf("Please enter player 1's name (Will be X's): ");
	while (!getPlayerName(player1)) {
		printf("Please try again, your player name can have a maximum length of 12 "
			"characters\n");
	}
	printf("Please enter player 2's name (Will be O's): ");
	while (!getPlayerName(player2)) {
		printf("Please try again, your player name can have a maximum length of 12 "
			"characters\n");
	}
}

void setSinglePlayerName(char *player) {
	printf("Please enter your name: ");
	while (!getPlayerName(player)) {
		printf("Please try again, your player name can have a maximum length of 12 "
			"characters\n");
	}
}

bool getPlayerName(char *player) {
	for (int i = 0; i < NAME_LEN_MAX + 1; i++) {
		player[i] = 0;
	}
	int c;
	int i;
	for (i = 0; i < (NAME_LEN_MAX + 1) && (c = getchar()) != '\n'; i++) {
		player[i] = c;
	}
	if (i == NAME_LEN_MAX + 1 && player[NAME_LEN_MAX] != '\0') {
		clearInputBuff();
		return false;
	}
	return true;
}

char getGameMode(void) {
	int mode;
	do {
		printf("Enter 'S' for single player and 'M' for multiplayer: \n");
		mode = getchar();
		mode = tolower(mode);
		while (getchar() != '\n')
			;
	} while (mode != 's' && mode != 'm'); 
	return mode;
}

void printGame(char map[3][3]) {
	printf("____________________________\n");
	for (int row = 0; row < 3; row++) {
		for (int i = 0; i < 4; i++) {
			printf("|");
			for (int col = 0; col < 3; col++) {
				if (i == 2) {
					printf("   %c    |", map[row][col]);
				} else  {
					printf("        |");
				}
			}
			printf("\n");
		}
		printf("|________|________|________|\n");
	}
	printf("\n");
}

void clearInputBuff() {

	while (getchar() != '\n')
		;
}

void initMap(char map[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			map[i][j] = ' ';
		}
	}
}
