#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int global_value = 0;

void myst_func_1(int);
void myst_func_2(int);
void myst_func_3(int);
void myst_func_4(int);

int bad_rand_range(int lower, int upper){
	int interval = upper - lower + 1;
	double rand = (double)random();
	rand = (rand / RAND_MAX) * interval;
	return lower + ((int)(rand));
}

void myst_func_1(int level){
	if(level == 0){
		global_value = 1;
	}
	else{
		int next_call = bad_rand_range(1, 4);
		switch(next_call){
			case 1:
				myst_func_1(level - 1);
				break;
			case 2:
				myst_func_2(level - 1);
				break;
			case 3:
				myst_func_3(level - 1);
				break;
			case 4:
				myst_func_4(level - 1);
				break;
		}
	}
}

void myst_func_2(int level){
	if(level == 0){
		global_value = 1;
	}
	else{
		int next_call = bad_rand_range(1, 4);
		switch(next_call){
			case 1:
				myst_func_1(level - 1);
				break;
			case 2:
				myst_func_2(level - 1);
				break;
			case 3:
				myst_func_3(level - 1);
				break;
			case 4:
				myst_func_4(level - 1);
				break;
		}
	}
}

void myst_func_3(int level){
	if(level == 0){
		global_value = 1;
	}
	else{
		int next_call = bad_rand_range(1, 4);
		switch(next_call){
			case 1:
				myst_func_1(level - 1);
				break;
			case 2:
				myst_func_2(level - 1);
				break;
			case 3:
				myst_func_3(level - 1);
				break;
			case 4:
				myst_func_4(level - 1);
				break;
		}
	}
}

void myst_func_4(int level){
	if(level == 0){
		global_value = 1;
	}
	else{
		int next_call = bad_rand_range(1, 4);
		switch(next_call){
			case 1:
				myst_func_1(level - 1);
				break;
			case 2:
				myst_func_2(level - 1);
				break;
			case 3:
				myst_func_3(level - 1);
				break;
			case 4:
				myst_func_4(level - 1);
				break;
		}
	}
}

int main(){
	srandom(time(NULL));
	myst_func_1(10);
	return 0;
}
