/**
 * @file
 * @brief The main file of the application
 */
#include <stdio.h>
#include <stdlib.h>
#include "memory_library.h"

void print_buffer(int * p_buffer, int size){
    printf("[");
    for(int i = 0; i < size - 1; i++){
        printf("%d, ", p_buffer[i]);
    }
    printf("%d]\n\n", p_buffer[size - 1]);
}

int main(){
    int normal_buffer[] = {1, 2, 3, 4, 5, 6};

    int * reverse_buffer = (int *)malloc(6 * sizeof(int));
    memory_reverse_copy(normal_buffer, reverse_buffer, 6);

    printf("Normal buffer: ");
    print_buffer(normal_buffer, 6);

    printf("Reverse buffer: ");
    print_buffer(reverse_buffer, 6);

    printf("* Multiply reverse buffer with 12 *\n");
    memory_multiply_elements(reverse_buffer, 12, 6);
    printf("Reverse buffer: ");
    print_buffer(reverse_buffer, 6);

    free(reverse_buffer);

    return 0;
}
