/**
 * @file
 * @brief Implementation file for memory library
 */
#include "memory_library.h"
#include <stdlib.h>

int memory_reverse_copy(const int * p_from, int * p_to, int size){
    if(p_from == NULL || p_to == NULL)
        return 1;

    for(int i = 0; i < size; i++){
        p_to[size - i - 1] = p_from[i];
    }
    return 0;
}

void memory_multiply_elements(int * p_buffer, int factor, int size){
    if(p_buffer == NULL)
        exit(1);

    for(int i = 0; i < size; i++){
        p_buffer[i] *= factor;
    }
}
