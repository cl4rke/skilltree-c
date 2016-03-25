#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define string char*

string read_string(FILE* source) {
    string s = malloc(100);

    fscanf(source, "%[^1234567890]", s);

    int length = strlen(s);

    // to remove that extra space.
    if (s[length-1] == ' ') {
        s[length-1] = '\0';
    }

    return s;
}

string read_string_until_pipe(FILE* source) {
    string s = malloc(100);

    fscanf(source, "%[^|]", s);

    int length = strlen(s);

    // to remove that extra space.
    if (s[length-1] == ' ') {
        s[length-1] = '\0';
    }

    return s;
}

int read_int(FILE* source) {
    int x;

    fscanf(source, "%d", &x);

    return x;
}

void clean_new_line(FILE* source) {
    fscanf(source, "\n");
}

void clean_pipe(FILE* source) {
    fscanf(source, "| ");
}

