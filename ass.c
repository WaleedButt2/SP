#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include "color.h"
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
int main(int argc , char *argv[]){
    if(strcmp("./a.out",argv[0])==0) printf("Fuck you dio\n");
    else printf("Fuck you muqeet\n");
}