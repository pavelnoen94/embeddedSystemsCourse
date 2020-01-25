#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int legs;
	int can_fly;
} horse;

int main(){
	int stat_array[] = {1, 2, 3, 4, 5};

	int * dyn_array = (int *)malloc(5 * sizeof(int));
	for(int i = 0; i < 5; i++){
		dyn_array[i] = i + 1;
	}

	horse sleipner = {8, 1};

	int some_number = 1;

	return 0;
}
