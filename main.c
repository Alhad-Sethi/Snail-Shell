#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<pthread.h>

void shell_init(){
    printf("x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n");
    printf("                                    \033[34;1m(SLOW) SNAIL SHELL!\033[0m\n");
    printf("x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n");
}

char initial_address[1024];

void set_initial_address(){
    getcwd(initial_address, 1024);
}

char* getting_line(){
    //using getline()
    char *buffer;
    size_t buffer_size = 1024;
    size_t characters;

    buffer = (char *)malloc(buffer_size*sizeof(char));
    if (buffer == NULL){
        //error handling
        perror("Buffer allocation error.");
        exit(1);
    }
    characters = getline(&buffer, &buffer_size, stdin);

    return buffer;
}

char ** splitter(char * line){
    char * line_copy = line;
    size_t buffer_size = 1024;
    char **tokens = (char **)malloc(buffer_size*sizeof(char*));
    int index = 0;

    char * spc = " \t\r\n\v\f"; //all whitespace characters: ran into a bug when \n was not included as chdir("..\n") returns unsuccessfully

    char * token = strtok(line_copy, spc);

    while(token != NULL){
        tokens[index] = token;
        index++;
        token = strtok(NULL, spc);
    }

    tokens[index] = NULL;

    return tokens;
}

int snail_cd(char** arguments){
    if (arguments[1]==NULL){
        printf("\e[1;34msnail: \e[0mExpected arguments. \n");
    }
    else if(strcmp(arguments[1],"~")==0){
        chdir(initial_address);
    }
    else if(strcmp(arguments[1],"-h")==0){
        printf("\e[1;34msnail: \e[0musage: cd [dir|~ for home directory] \n");
    }
    else{
        if (chdir(arguments[1]) != 0){
            perror("\e[1;34msnail\e[0m");
        }
    }

    return 1;
}

int snail_cat(char** arguments){
    char cat_path[1024];

    strcpy(cat_path, initial_address);
    strcat(cat_path, "/cat");

    pid_t pid = fork();
    
    if (pid<0){
        perror("\e[1;34msnail: \e[0m fork failed.");
    }
    else if (pid == 0){
        execl(cat_path, cat_path, arguments[1], arguments[2], arguments[3], arguments[4], arguments[5]);
    }

    wait(NULL);

    return 1;

}

int snail_date(char ** arguments){
    char date_path[1024];

    strcpy(date_path, initial_address);
    strcat(date_path, "/date");

    pid_t pid = fork();
    
    if (pid<0){
        perror("\e[1;34msnail: \e[0m fork failed.");
    }
    else if (pid == 0){
        execl(date_path, date_path, arguments[1], arguments[2], arguments[3]);
    }

    wait(NULL);

    return 1;
}

int snail_rm(char ** arguments){
    char rm_path[1024];

    strcpy(rm_path, initial_address);
    strcat(rm_path, "/rm");

    pid_t pid = fork();
    
    if (pid<0){
        perror("\e[1;34msnail: \e[0m fork failed.");
    }
    else if (pid == 0){
        execl(rm_path, rm_path, arguments[1], arguments[2], arguments[3]);
    }

    wait(NULL);

    return 1;
}

int snail_mkdir(char ** arguments){
    char mkdir_path[1024];

    strcpy(mkdir_path, initial_address);
    strcat(mkdir_path, "/mkdir");

    pid_t pid = fork();
    
    if (pid<0){
        perror("\e[1;34msnail: \e[0m fork failed.");
    }
    else if (pid == 0){
        execl(mkdir_path, mkdir_path, arguments[1], arguments[2], arguments[3]);
    }

    wait(NULL);

    return 1;
}

int snail_echo(char **arguments){
    //implemented -n
    int nwordpass = 0;
    for (int i = 1; arguments[i] != NULL; i++){
        if (strcmp(arguments[i], "-n")!=0 && strcmp(arguments[i], "-h")!=0){
            printf("%s ", arguments[i]);
        }
        else if(strcmp(arguments[i], "-h")==0){
            printf("\e[1;34msnail: \eusage: echo [-hn] [string]");
            return 1;
        }
        else{
            nwordpass = 1;
        }
    }

    if (nwordpass != 1){
        printf("\n");
    }

    return 1;
}

int snail_ls(char**arguments){
    char ls_path[1024];

    strcpy(ls_path, initial_address);
    strcat(ls_path, "/ls");

    pid_t pid = fork();
    
    if (pid<0){
        perror("\e[1;34msnail: \e[0m fork failed.");
    }
    else if (pid == 0){
        execl(ls_path, ls_path, arguments[1], arguments[2], arguments[3]);
    }

    wait(NULL);

    return 1;
}

int snail_pwd(char ** arguments){
    char pwd[1024];
    if (getcwd(pwd, 1024)==NULL){
        perror("\e[1;34msnail\e[0m");
    }
    printf("%s \n", pwd);
    return 1;
}

void * threader(void * arg){
    char * aargh = (char *) arg;
    system(aargh);

    return NULL;
}

int threader_execution_engine(char ** arguments){
    char * args_new = malloc(4096*sizeof(char));
    strcat(args_new, initial_address);
    strcat(args_new, "/");
    strcat(args_new, arguments[0]);
    for (int i = 2; arguments[i]!= NULL; i++){
        strcat(args_new, " ");
        strcat(args_new, arguments[i]);
    }

    pthread_t new;

    pthread_create(&new, NULL, threader, args_new);
    pthread_join(new, NULL);

    return 1;
}

int execution_engine(char ** arguments){
    if (arguments[0]==NULL){
        return 1;
    }
    else if (strcmp(arguments[0],"exit")==0){
        exit(0);
    }
    else if (arguments[1]!= NULL && strcmp(arguments[1], "&t")==0){
        threader_execution_engine(arguments);
    }

    else if (strcmp(arguments[0],"cd")==0){
        return snail_cd(arguments);
    }
    else if (strcmp(arguments[0],"echo")==0){
        return snail_echo(arguments);
    }
    else if(strcmp(arguments[0],"clear") == 0){
        printf("\e[1;1H\e[2J");
    }
    else if(strcmp(arguments[0],"pwd") == 0){
        return snail_pwd(arguments);
    }
    else if(strcmp(arguments[0],"ls") == 0){
        return snail_ls(arguments);
    }
    else if(strcmp(arguments[0],"cat")==0){
        return snail_cat(arguments);
    }
    else if(strcmp(arguments[0],"rm")==0){
        return snail_rm(arguments);
    }
    else if(strcmp(arguments[0],"mkdir")==0){
        return snail_mkdir(arguments);
    }
    else if(strcmp(arguments[0],"date")==0){
        return snail_date(arguments);
    }
    else if (strcmp(arguments[0],"man")==0){
        return snail_date(arguments);
    }

    return 1;
}

void snail_loop(){
    char *line;
    char **arguments;
    int status;

    do {
        //printf("snail: ");
        printf ("\e[1;34msnail: \e[0m");
        line = getting_line();
        arguments = splitter(line);
        status = execution_engine(arguments);

        free(line);
        free(arguments);

    }while(status);

}

int main(int argc, char ** argv){
    set_initial_address();
    shell_init();
    snail_loop();

    return 0;
}
