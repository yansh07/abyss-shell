#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[] = "apt-get install python3";
    char *args[10];

    int i = 0;
    char *token = strtok(input, " ");

    while(token != NULL) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    for (int j=0; args[j]!=NULL; j++) {
        printf("%s\n", args[j]);
    }
    
    return 0;
}