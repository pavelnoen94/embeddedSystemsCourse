static char * TEXT[] = {
    "Seize all the means!",
    "Individual possessions are merely distractions from work.",
    "Oligarchies are such a beautiful concept!",
    "Everything is provided by the state."
};


char * stat_state_control(unsigned int degree){
    return TEXT[degree % 4];
}
