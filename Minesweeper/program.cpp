#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

#define FIELD_WIDTH 9
#define FIELD_HEIGHT 9

int mine[FIELD_HEIGHT][FIELD_WIDTH];
int field[FIELD_HEIGHT][FIELD_WIDTH];
int field_count_mine[FIELD_HEIGHT][FIELD_WIDTH];
int cursorX, cursorY;
int mine_bomb;

void check_mine(int x_, int y_)
{
	if (mine[y_][x_]) {
		mine_bomb = 1;
	}
	else {
		field[y_][x_] = 0;
	}
}

int main()
{
	int mine_count = 0;

	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		int y_mine = rand() % FIELD_HEIGHT;
		int x_mine = rand() % FIELD_WIDTH;
		mine[y_mine][x_mine] = 1;
	}
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			field[y][x] = 1;
		}
	}

	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					int y2 = y + i;
					int x2 = x + j;
					if (y2 < 0 || x2 < 0 || y2 >= FIELD_HEIGHT || x2 >= FIELD_WIDTH)continue;
					else if(mine[y2][x2]) mine_count++;
				}
			}
			field_count_mine[y][x] = mine_count;
			mine_count = 0;
		}
	}

	while (1) {
		system("cls");
		if (!mine_bomb) {
			for (int y = 0; y < FIELD_HEIGHT; y++) {
				for (int x = 0; x < FIELD_WIDTH; x++) {
					if ((x == cursorX) && (y == cursorY)) {
						printf("ü");
					}
					else if (field[y][x]) {
						printf("¡");
					}
					else {
						printf(" %d", field_count_mine[y][x]);
					}
				}
				printf("\n");
			}
		}
		else {
			for (int y = 0; y < FIELD_HEIGHT; y++) {
				for (int x = 0; x < FIELD_WIDTH; x++) {
					if (mine[y][x]) {
						printf("~");
					}
					else {
						printf(" %d", field_count_mine[y][x]);
					}
				}
				printf("\n");
			}
			printf("game over\n");
			_getch();
			return 1;
		}
		switch (_getch()) {
		case 'w': cursorY--; break;
		case 'a': cursorX--; break;
		case 's': cursorY++; break;
		case 'd': cursorX++; break;
		case ' ': check_mine(cursorX, cursorY); break;
		case 'q':return 1;
		}
	}
	return 0;
}