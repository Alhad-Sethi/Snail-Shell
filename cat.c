
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

const int bufferSize = 4096;

void help(){
    printf("\e[1;34msnail: \e[0musage: cat [-ben] [filename1] [filename2] .. [filename 4]");
}

int main(int argc, char **argv) {

    int bflag = 0, nflag = 0;

    char* flags = malloc(1024*sizeof(char));

    flags = strdup(argv[1]);
    if (strcmp(flags, "-b") == 0){
        bflag = 1;
    }
    else if (strcmp(flags, "-n") == 0){
        nflag = 1;
    }

    if (argc == 1){
        printf("\e[1;34msnail: \e[0m arguments expected.");
        help();
    }

    int i;

    if (bflag == 1|| nflag == 1) {
        i = 2;
    }
    else{
        i = 1;
    }

    while (i<=argc){
        FILE *file;
        char buffer[bufferSize];
        
        file = fopen(argv[i],"r");

        char *line = malloc(4096*sizeof(char));
        int counter = 1;
        
        while(fgets(line, 4096, file)){

        if (bflag){
            if (strcmp(line, "\n")==0){
                counter++;
            }
            else{
                printf("%s", line);
                counter++;
            }
        }
        else if (nflag){
            printf("%d. %s", counter, line);
            counter++;
        }
        else{
            printf("%s", line);
        }
        }
        i++;
        fclose(file);
    }

    return 0;
}
