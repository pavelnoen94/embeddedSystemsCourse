static char * TEXT[] = {
    "I keep finding horse heads in my bed. Might not be a good sign.",
    "The Supreme Leader is very well liked. Everything is fine.",
    "Not with state supplied opiates for the masses.",
    "Too much misinformation for anyone to point at me.",
    "Curfews, lockdowns, isolation. I think we are good.",
    "This is like Vietnam times all over again..."
};


char * stat_political(unsigned int degree){
    return TEXT[degree % 6];
}
