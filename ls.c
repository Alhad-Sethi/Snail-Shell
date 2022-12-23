
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

void snail_ls(int op_a,int op_1)
{
	struct dirent *d;
	DIR *dh = opendir(".");
	if (!dh)
	{
		if (errno == ENOENT)
		{
			perror("\e[1;34msnail\e[0m: Directory doesn't exist");
		}
		else
		{
			perror("\e[1;34msnail: \e[0mUnable to read directory");
		}
		exit(-1);
	}
	while ((d = readdir(dh)) != NULL)
	{
		if (!op_a && d->d_name[0] == '.'){continue;}
		printf("%s  ", d->d_name);
		if(op_1) printf("\n");
	}
	if(!op_1) printf("\n");
}
int main(int argc, const char *argv[])
{
	int op_a = 0, op_1 = 0;
	if (argc == 1)
	{
		snail_ls(op_a,op_1);
	}
	else if (argc == 2)
	{
		if (argv[1][0] == '-')
		{
			char *p = (char*)(argv[1] + 1);
			while(*p){
				if(*p == 'a') op_a = 1;
				else if(*p == '1') op_1 = 1;
				else{
					perror("\e[1;34msnail: \e[0mOption not available");
					exit(EXIT_FAILURE);
				}
				p++;
			}
			snail_ls(op_a,op_1);
		}
	}
	return 0;
}
