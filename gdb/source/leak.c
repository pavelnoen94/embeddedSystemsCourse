#include <stdio.h>
#include <stdlib.h>

int * create_array(int elements){
	int *array = (int *)malloc(sizeof(int) * elements);

	array[0] = 0;
	array[1] = 1;
	for(int i = 2; i < elements; i++){
		array[i] = array[i - 2] + array[i - 1];
	}

	return array;
}

int main(int argc, char ** argv){
	if(argc < 2){
		printf("Usage: %s <num>\n", argv[0]);
		exit(1);
	}

	int elements = atoi(argv[1]);
	int *array = create_array(elements);
	for(int i = 0; i < elements; i++){
		printf("Fibonacci(%d): %d\n", i, array[i]);
	}

	return 0;
}
