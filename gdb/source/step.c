#include <stdio.h>

int multiply(int a, int b){
	int result = a * b;
	return result;
}

int main(){
	int prod1 = multiply(2, 6);
	int prod2 = multiply(5, 3);
	int prod3 = multiply(7, 2);

	printf("Some numbers: %d, %d, %d\n", prod1, prod2, prod3);
	return 0;
}
