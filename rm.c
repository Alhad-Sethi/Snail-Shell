#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void help(){
    printf("\e[1;34msnail: \eusage: rm [-vi] [file]..");
}

void checkstatus(int status){
    if (status != 0){
        perror("\e[1;34msnail: \e[0m");
        exit(-1);
    }
}

int main(int argc, char ** argv){
    //implementing flags -v, -i

    int vflag = 0, iflag = 0;

    char* flags = malloc(1024*sizeof(char));

    flags = strdup(argv[1]);
    if (strcmp(flags, "-v") == 0){
        vflag = 1;
    }
    else if (strcmp(flags, "-i") == 0){
        iflag = 1;
    }

    if (argc == 1){
        printf("\e[1;34msnail: \e[0m arguments expected.");
        help();
    }

    int i;

    if (vflag == 1|| iflag == 1) {
        i = 2;
    }
    else{
        i = 1;
    }

    while(i<argc){
        if (vflag){printf("%s",argv[i]);}
        if (iflag){
            printf("\e[1;34msnail: \e[0m Are you sure? (1/0)");
            int c;
            scanf("%d",&c);
            if (c == 1){
                int status = remove(argv[i]);
                checkstatus(status);
            }
        }
        else{
            int status = remove(argv[i]);
            checkstatus(status);
        }
        i++;
        printf("\n");
    }

    return 0;
}
