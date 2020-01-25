static char * TEXT[] = {
    "There is no class struggle in the ONE state.",
    "Down with the bourgeoisie!",
    "Check your privilege!",
    "There is no I, only us.",
    "A carefully created hierarchy is the way to go.",
    "With these working hours, there can be no class struggle.",
    "Zamyatin says: Any cipher may use any other cipher...",
    "My subjects are worth equally little to me.",
    "Class struggle? Perennial serfdom, more like."
};


char * stat_class_struggle(unsigned int degree){
    return TEXT[degree % 9];
}
