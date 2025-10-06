#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

void count_chars(char *fname) {
    FILE *fp = fopen(fname, "r");
    if (!fp) { printf("File not found!\n"); return; }
    int c = 0;
    while (fgetc(fp) != EOF) c++;
    fclose(fp);
    printf("Number of characters: %d\n", c);
}

void count_words(char *fname) {
    FILE *fp = fopen(fname, "r");
    if (!fp) { printf("File not found!\n"); return; }
    int words = 0;
    char ch, prev = ' ';
    while ((ch = fgetc(fp)) != EOF) {
        if (!isspace(ch) && isspace(prev)) words++;
        prev = ch;
    }
    fclose(fp);
    printf("Number of words: %d\n", words);
}

int main() {
    char input[100], *arg[5];

    while (1) {
        printf("myshell$ ");
        if (!fgets(input, sizeof(input), stdin)) break;

        int i = 0;
        arg[i] = strtok(input, " \t\n");
        if (!arg[i]) continue;
        while ((arg[++i] = strtok(NULL, " \t\n")));

        if (!strcmp(arg[0], "exit")) break;

        else if (!strcmp(arg[0], "count") && arg[1] && arg[2]) {
            if (arg[1][0] == 'c') count_chars(arg[2]);
            else if (arg[1][0] == 'w') count_words(arg[2]);
            else printf("Invalid option for count\n");
        }

        else {
            if (fork() == 0) {
                execvp(arg[0], arg);
                perror("Command failed");
                exit(1);
            } else wait(NULL);
        }
    }
    return 0;
}
