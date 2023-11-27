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

// uses the window lib to color the text
void color_char(char player); // by Fasih

// update the frame by clearing the screen and printing the grid
void update_frame(char **grid); // by Fasih

// validate a move in the specified column
bool validate_move(char **grid, int col); // by Fasih

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
