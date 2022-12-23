#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char ** splitter(char * line){
    char * line_copy = line;
    size_t buffer_size = 1024;
    char **tokens = (char **)malloc(buffer_size*sizeof(char*));
    int index = 0;

    char * spc = "\\"; //all whitespace characters: ran into a bug when \n was not included as chdir("..\n") returns unsuccessfully

    char * token = strtok(line_copy, spc);

    while(token != NULL){
        tokens[index] = token;
        index++;
        token = strtok(NULL, spc);
    }

    tokens[index] = NULL;

    return tokens;
}

void help(){
    printf("\e[1;34msnail: \eusage: mkdir [-vp] [dirname]");
}

void checkstatus(int status){
    if (status != 0){
        perror("\e[1;34msnail: \e[0m");
        exit(-1);
    }
}

int main(int argc, char ** argv){
    //implementing flags -v, -p

    int vflag = 0, pflag = 0;

    char* flags = malloc(1024*sizeof(char));

    flags = strdup(argv[1]);
    if (strcmp(flags, "-v") == 0){
        vflag = 1;
    }
    else if (strcmp(flags, "-p") == 0){
        pflag = 1;
    }

    if (argc == 1){
        help();
        exit(-1);
    }
    else if (argc>3){
        help();
        exit(-1);
    }

    int i;

    if (vflag == 1|| pflag == 1) {
        i = 2;
    }
    else{
        i = 1;
    }

    if (vflag){printf("%s\n",argv[i]);}
    if (pflag){
        char ** folders = splitter(argv[i]);
        int n = sizeof(folders)/sizeof(folders[0]);

        for (int i = 0; i < n; i++){
            int status = mkdir(folders[i],0777);
            checkstatus(status);
        }

    }
    else{
        int status = mkdir(argv[i],0777);
        checkstatus(status);
    }


    return 0;
}
