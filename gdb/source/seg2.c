#include <stdio.h>

int array[200];

int main(){
	for(int i = 0; i < 240; i++){
		array[i] = i;
	}
	printf("Exit normally\n");
	return 0;
}
