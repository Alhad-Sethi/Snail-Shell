#include<stdio.h>
#include<time.h>
#include<timeconv.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>

void normal_date(){
    struct tm *local;
    time_t t;

    t = time(NULL);
    local = localtime(&t);
    printf("IST: %s", asctime(local));
}

void flag_date(int op_r, int op_u, char * file){
    struct tm *local;
    time_t t;

    t = time(NULL);

    if (op_r == 1){
        struct stat attr;
        stat(file, &attr);
        if (attr.st_mtime!= 0){
            printf("Last modified time: %s", ctime(&attr.st_mtime));
        }
        else{
            printf("\e[1;34msnail: \e[0m file not found. usage: date [-r filename] [-u]\n");
        }

    }
    else if (op_u == 1 && file != NULL) {
        local = gmtime(&t);
        printf("UTC time and date: %s", asctime(local));
    }
    else{
        perror("\e[1;34msnail: \e[0mOption not available.");
    }

}

void help(){    
    printf("\e[1;34msnail: \e[0musage: date [-r filename] [-u]\n");
}

int main(int argc, char ** argv){
    if (argc == 1){
        normal_date();
    }
    //options supported: -r, -u
    else if(argc == 2 || argc == 3){
        if(strcmp(argv[1],"-u")==0||strcmp(argv[1], "-r")==0){
            int op_r = 0, op_u = 0;
            char *p = (char*)(argv[1] + 1);
            char *file;
            while(*p){
                if(*p == 'r') {
                    op_r = 1;
                    file = argv[2];
                }
                else if(*p == 'u') {
                    if (argc ==2) op_u = 1;
                    else{
                        help();
                        exit(EXIT_FAILURE);
                    }
                }

                p++;
            }
            flag_date(op_r, op_u, file);      
        }
        else{
            help();
            exit(EXIT_FAILURE);
        }
    }
    else{
        help();
    }

    return 0;
}

