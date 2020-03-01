

# Hellevator

Hellevator is a simple elevator software.
It can carry orders like a normal elevator.

## How to get started

```bash
git clone https://github.com/pavelnoen94/EmbeddedSystemsCourse
cd EmbeddedSystemsCourse/elevator
make
./elevator
```

## How the software works
This software has predefined states at which the elevator can be in. The modes are `RUNNING`, `IDLE`, `SERVING`, `STOP`, and `UNKNOWN`. Each mode pulls necessary sensors and calls required functions to do the decisions. Each mode continuously checks when their state are no longer valid and returns to a state picker or a mode selector if you'd like. The modes are stored in `modes.c` file and the mode selector are stored in `modeSelector.c`.

All modes don't have to check all the sensors. If the elevator is idle there is no need in checking floor sensors because they are not necessary. Thats why different modes check different sensors. All the logic are to be found in `interface.c`. It contains mainly two things. Sensor reading functions that collect sensor data and stores them in a variable. And some logic. The logic part finds e.g. the correct direction for the elevator.

Everything is dependent on the drivers. Function declaration can be found in `hardware.h`

## Deployment
If you for some reason want to run this program forever and not have a terminal window open you could use the program like this:

```c
#include <unistd.h>
#include "elevator.h"

int main(){
    // start process as a child
    if(fork() == 0){
        start();
    }

    return 0;
}
```
This way it will execute the elevator application as a new process. You don't have to leave a terminal window open. If you use gdb for debugging then it will automatically follow child process unless you for some reason overwrote `~/.gdbinit`.  
Note that program uses stdout to print to console info, warning and error messages when they occur.

## Tips
For faster development use autoBuild.sh script. It watches for changes in source folder and builds automatically new binaries.
To use it you will need inotify installed. `sudo apt install inotify-tools`







