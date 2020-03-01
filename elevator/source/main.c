#include "headers/elevator.h"
#include <unistd.h>

int main(){
    // release the terminal
    if(fork() == 0){
        modeSelector();
    }
    return 0;

}