static char * TEXT[] = {
    "This regime is basically a tinderbox.",
    "The sheeple are dumb and happy. They will not revolt.",
    "Revolution? Uugh, again?",
    "Not with state operated mind control, you don't.",
    "Hey, I survived longer than my predecessor!",
    "This has been outlawed too."
};

char * stat_revolution(unsigned int degree){
    return TEXT[degree % 6];
}
