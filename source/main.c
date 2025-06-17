#include <stdio.h>
#include "life.h"

int main() {
	int coords[][2] = {
		{10,11},
		{10,12},
		{10,13},
		{9,12},
		{11,13}
	};
	int count = sizeof(coords) / (2*sizeof(int));
	life(coords, count);
	return 0;
}
