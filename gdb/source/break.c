#include <stdio.h>
#include "break2.h"

void local_call(){
	printf("Call from same file\n");
}

int main(){
	int alloc;

	alloc = 6;

	for(int i = 0; i < 100; i++){
		alloc = i;
	}

	library_call();

	return 0;
}
