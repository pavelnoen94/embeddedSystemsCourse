#include <stdio.h>

int array[100];

void pointless_function(){
	int counter = 100;
	while(counter){
		counter--;
	}

	for(int i = 0; i < 100; i++){
		array[i] = i;
	}
}

int main(){
	for(int i = 0; i < 100; i++){
		array[i] = i;
	}

	pointless_function();

	return 0;
}
