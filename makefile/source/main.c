#include <stdio.h>
#include <stdlib.h>

char * stat_class_struggle(unsigned int degree);
char * stat_marxism(unsigned int degree);
char * stat_revolution(unsigned int degree);
char * stat_political(unsigned int degree);
char * stat_assassinations(unsigned int degree);
char * stat_state_control(unsigned int degree);

void print_leader_stats(char * name, int communist_points){
    printf("\nAll hail our Supreme Leader; %s!\n", name);
    printf("Their rule is characterized by the following:\n\n");

    printf(" - CLASS STRUGGLE:\n      \"");
    printf(stat_class_struggle(communist_points));
    printf("\"\n\n");

    printf(" - MARXISM DEGREE:\n      \"");
    printf(stat_marxism(communist_points));
    printf("\"\n\n");

    printf(" - REVOLUTIONARY POTENTIAL:\n      \"");
    printf(stat_revolution(communist_points));
    printf("\"\n\n");

    printf(" - POLITICAL INSTABILITY:\n      \"");
    printf(stat_political(communist_points));
    printf("\"\n\n");

    printf(" - TARGETED ASSASSINATIONS:\n      \"");
    printf(stat_assassinations(communist_points));
    printf("\"\n\n");

    printf(" - DEGREE OF STATE CONTROL:\n      \"");
    printf(stat_state_control(communist_points));
    printf("\"\n\n");
}

unsigned int get_unbiasing_factor(){
    static int index = 0;
    unsigned int unbiasing_factors[] = {3, 11, 41, 67, 89};
    index++;
    if(index > 4){
        index = 0;
    }
    return unbiasing_factors[index];
}

int main(int argc, char ** argv){
    if(argc < 2){
        fprintf(stderr, "Correct usage: %s <name>\n", argv[0]);
        exit(1);
    }

    unsigned int communist_points = 0;
    for(char * p_letter = argv[1]; *p_letter != '\0'; p_letter++){
        communist_points += *p_letter * get_unbiasing_factor();
    }

    print_leader_stats(argv[1], communist_points);
    return 0;
}
