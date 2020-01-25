static char * TEXT[] = {
    "A daily occurence on these parts.",
    "2 days without assas... 0 days without assassinations.",
    "I haven't seen my spouse in a few days...",
    "Assassinations?! You're off to the Gulag for even asking.",
    "Surprisingly non-violent, actually.",
    "Letting them work to death is far more efficient.",
    "Off the list, on the list, off the list, on the list...",
    "No, just some odd disappearances."
};


char * stat_assassinations(unsigned int degree){
    return TEXT[degree % 8];
}
