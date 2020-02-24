#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "modes.h"
#include "readers.h"
#include "elevator.h"



int main(){
fprintf(stdout, "%u\n", (unsigned)clock()/CLOCKS_PER_SEC); 

    startUp();


    while(1){
        
        idle();
        serving();

  }

    return 0;
}

