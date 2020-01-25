static char * TEXT[] = {
    "Marx didn't go far enough!",
    "Even my bedroom is red!",
    "Marx was too influenced by Hegel to be trusted.",
    "We adhere to a more... Frankfurt school approach here.",
    "Better dead than red.",
    "We outlawed the color blue on day one; purple too!",
    "Actually, we're a constitutional monarchy.",
    "A one-party democracy is still a democracy."
};

char * stat_marxism(unsigned int degree){
    return TEXT[degree % 8];
}
