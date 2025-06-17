#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GRID_WIDTH 100
#define GRID_HEIGHT 20
#define ALIVE_CHAR 'o'
#define DEAD_CHAR '.'

// you must free this pointer
char* initialise_grid(int height, int width) {
	char *mem;
	do {
		mem = (char*)malloc(sizeof(char)*height*width+1);
	} while(mem == NULL);
	memset(mem, 0, sizeof(char)*height*width + 1);
	return mem;
}

void print_grid(const char* const grid, int height, int width) {
	char* buffer = initialise_grid(height, width+1);
	char* buff_p = buffer;
	const char *grid_dupe = grid;

	for(int i = 0; i < height*width; i++) {
		*buff_p = *grid_dupe;
		buff_p++; grid_dupe++;

		if ((i+1) % width == 0) {
			*buff_p = '\n';
			buff_p++;
		}
	}
	printf("%s", buffer);
	free(buffer);

	return;
}

// height and width are of the grid, grid_pos is 0-indexed
int calc_num_alive_neighbours(const char* const grid, int height, int width, int grid_pos) {
	//printf("DEBUG: pos %d\n", grid_pos);
	int count = 0;
	// top left
	if (grid_pos-width > 0 && grid_pos%width != 0 && grid[grid_pos-width-1] == ALIVE_CHAR) {
		//printf("top-left\n");
		count++;
	}
	// top middle
	if (grid_pos-width > 0 && grid[grid_pos-width] == ALIVE_CHAR) {
		//printf("top-middle\n");
		count++;
	}
	// top right
	if (grid_pos-width > 0 && (grid_pos+1)%width != 0 && grid[grid_pos-width+1] == ALIVE_CHAR) {
		//printf("top-right\n");
		count++;
	}
	// middle left
	if (grid_pos%width != 0 && grid[grid_pos-1] == ALIVE_CHAR) {
		//printf("middle-left\n");
		count++;
	}
	// middle right
	if ((grid_pos+1)%width != 0 && grid[grid_pos+1] == ALIVE_CHAR) {
		//printf("middle-right\n");
		count++;
	}
	// bottom left
	if (grid_pos+width < height*width && grid_pos%width != 0 && grid[grid_pos+width-1] == ALIVE_CHAR) {
		//printf("bottom-left\n");
		count++;
	}
	// bottom middle
	if (grid_pos+width < height*width && grid[grid_pos+width] == ALIVE_CHAR) {
		//printf("bottom-middle\n");
		count++;
	}
	// bottom right
	if (grid_pos+width < height*width && (grid_pos+1)%width != 0 && grid[grid_pos+width+1] == ALIVE_CHAR) {
		//printf("bottom-right\n");
		count++;
	}
	return count;
}

// you must free this pointer
char* calc_next_grid_state(const char* const grid, int height, int width){
	char* next_grid = initialise_grid(height, width);
	for(int i = 0; i < height*width; i++) {
		// 4. any dead cells with three neighbours becomes a live cell
		if (grid[i] == DEAD_CHAR) {
			if (calc_num_alive_neighbours(grid, height, width, i) == 3)
				next_grid[i] = ALIVE_CHAR;
			else
				next_grid[i] = DEAD_CHAR;
			continue;
		}

		// cell 'i' is alive
		switch(calc_num_alive_neighbours(grid, height, width, i)) {
			case 0: ;
			case 1: ;
			case 4: ;
			case 5: ;
			case 6: ;
			case 7: ;
			case 8: next_grid[i] = DEAD_CHAR;break;
			case 2: ;
			case 3: next_grid[i] = ALIVE_CHAR;break;
			default: printf("wtf\n");break;
		}
		// 1. any live cells with fewer than two neighbours die
		// 2. any live cells with two or three neighbours survive
		// 3. any live cells with more than three neighbours die
	}
	return next_grid;
}

// we can't move the pointer, but we can change its contents
void rules_of_life(char* const grid, int height, int width){
	char* new_grid = calc_next_grid_state(grid, height, width);
	strncpy(grid, new_grid, sizeof(char)*height*width+1);
	free(new_grid);
	return;
}

int life(int coords[][2], int count) {
	// this is where we store the representation
	char* grid = initialise_grid(GRID_HEIGHT, GRID_WIDTH);
	for(int i = 0; i < GRID_HEIGHT*GRID_WIDTH; i++) {
		grid[i] = DEAD_CHAR;
	}

	for(int i = 0; i < count; i++) {
		int xcoord = coords[i][1];
		int ycoord = coords[i][0];
		grid[(ycoord-1)*GRID_WIDTH + xcoord - 1] = ALIVE_CHAR;
	}

	while(1) {
		system("clear");
		print_grid(grid, GRID_HEIGHT, GRID_WIDTH);
		usleep(0.02*1000000);
		rules_of_life(grid, GRID_HEIGHT, GRID_WIDTH);
	}

	return 0;
}
