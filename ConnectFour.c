/*
 * Creators: Fasih Hasan, Syed Ukkashah, Muhammad Ali
 * Date (Last changed): 23/11/23
 * Desc: A game called connect 4. First player to create a sequence of 4 characters in a 6 by 7 grid will win
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define P1 'R'
#define P2 'B'
#define X '.'

// create a game grid
char **create_game_grid(); // by Ali, modification by Fasih

// uses the window lib to color the text
void color_char(char player); // by Fasih

// print the game grid
void print_grid(char **grid); // by Ali, modified by Fasih and Ukkashah

// update the frame by clearing the screen and printing the grid
void update_frame(char **grid); // by Fasih

// validate a move in the specified column
bool validate_move(char **grid, int col); // by Fasih

// displays relevant game end screen to player
void game_end_display(char **grid, int player, bool type); // by Ali

/*
		to-do:

- draw condition
- save wins and display them at the end
*/

int main()
{
	int player, col;
	bool valid = true, win = false;
	char player_char, **grid = create_game_grid();

	// default color scheme
	system("Color 0E");

	// game loop
	while (!win) {
		// for each player
		for (player = 0; player < 2; player++) {
			// loop until valid input
			do {
				update_frame(grid);
				if (!valid) printf("-- Enter appropriate column number --\n\n");
				col = user_input(player);
				valid = validate_move(grid, col);
			} while (!valid);

			// set to grid
			set_grid(grid, col, player);

			// check if win or draw
			win = game_win_status(grid, col, player);

			if (win) {
				break;
			}
		}
	}
	
	// display screen for WIN of player
	update_frame(grid);
	color_char((player) ? P1 : P2);
	printf(" WINS");

	// reset console color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	return 0; // end
} // end main()

char **create_game_grid()
{
	// creates double pointer for number of rows
	char **grid = (char **)malloc(sizeof(char *) * rows);

	// creates single pointers and sets them in all rows
	for (int i = 0; i < rows; i++) {
		grid[i] = (char *)malloc(sizeof(char) * cols);
	}

	// initializing as default
	for (int i = 0; i < rows; i++) {
		memset(grid[i], X, cols);
	}

	return grid;
} // end create_game_grid()

void color_char(char player)
{
	switch (player) {
        case P1: // Red color for P1
            // changing color using Window.h functions
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); 
            printf("%c", player); 
            break;
        case P2: // Blue color for P2
        	  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
            printf("%c", player); 
            break;
        default:
            printf("%c", player);
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // reset to default game color
} // end color_char()

void print_grid(char **grid)
{
	
	printf("%-4c", ' ');
	for (int i = 0; i < cols; i++) {
		printf("%-4d", i+1);
	}
	printf("\n");
	printf("%-2c|", ' ');
	for (int i = 2; i <= cols*4; i++) printf("%c", '-');
	printf("|");

	printf("\n");
	for (int i = 0; i < rows; i++) {
		printf("%d | ", i+1);
		for (int j = 0; j < cols; j++) {
			if (j == cols - 1) {
				color_char(grid[i][j]);
				printf(" |");
				break;
			}
			color_char(grid[i][j]);
			printf("%-3c", ' ');
		}
		if (i == rows - 1) continue;
		printf("\n");
		printf("%3c", '|');
		for (int i = 2; i < cols*4; i++) printf("%c", ' ');
		printf(" |\n");
	}
	printf("\n");
	printf("%-2c|", ' ');
	for (int i = 2; i <= cols*4; i++) printf("%c", '-');
	printf("|\n\n");
} // end print_grid(Player **)

void update_frame(char **grid)
{
	// clear screen and print grid
	system("cls");
	print_grid(grid);
} // end update_frame()


bool validate_move(char **grid, int col)
{
    // range check and overflow check
    return (col < cols && col >= 0) ? grid[0][col] == X : false;
} // end validate_move()
