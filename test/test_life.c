#include <stdio.h>
#include <stdlib.h>

#include "life.h"

void test_func(int (*func)(void), char* err_string) {
	if (func()) {
		printf(".");
		fflush(stdout);
		return;
	}
	printf("x\n%s\n", err_string);
	return;
}

int test_initialise_grid_never_null() {
	char* grid;
	for (int i = 0; i < 10; i++) {
		grid = initialise_grid(10,10);
		if (grid == NULL) return 0;
		free(grid);
	}
	return 1;
}

int test_initialise_grid_zeroed() {
	char* grid;
	for (int i = 0; i < 10; i++) {
		grid = initialise_grid(10,10);
		for (int i = 0; i < 10*10+1; i++) {
			if (grid[i] != '\0') {
				free(grid);
				return 0;
			}
		}
		free(grid);
	}
	return 1;
}

int main() {
	test_func(
		test_initialise_grid_never_null,
		"malloc failed to allocate in 'initialise_grid()'"
	);
	test_func(
		test_initialise_grid_zeroed,
		"grid produced by 'initialise_grid()' wasn't zeroed"
	);
	printf("\n");
	return 0;
}
