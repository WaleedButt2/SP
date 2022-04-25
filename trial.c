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
char** take_core(char *argv[],int count){
    int i=1;
    int src=1;
    char** newarray=malloc(count);
    for(int x=0;x<count;x++) newarray[x]=malloc(260);
   // printf("%d\n",count);
    strncpy(newarray[0],argv[0],260);
    while(src<count){
        if(argv[i][0]!='-'){strncpy(newarray[src],argv[i],260);src++;}
        i++;
    } 
    return newarray; 
}
char* remove_flags(char *argv[],int argc,int *f){
    int i=1;
    while(i<argc&&argv[i][0]=='-'){
        if(strnlen(argv[i],256)>=256) {
            printf("Flag Name's too large\n");
            exit(1);
        }
        i++;
    } 
    int flag_count=0;
    i=1;
    while(i<argc){
        //printf("%d\n",flag_count);
        if(argv[i][0]=='-') flag_count++;
        i++;
    }
    //printf("%d\n",flag_count);
    char *flag=malloc(flag_count*256);
    i=1;
    int first=1;
    while(i<argc){
        if(argv[i][0]=='-'){
            if(first){
                first=0;
                strncpy(flag,&argv[i][1],256);
            }
            else strncat(flag,&argv[i][1],256);
        } 
        i++;
    }
    *f=flag_count;
    //printf("%s \n%d\n",flag,flag_count);
    return flag;
}
int main(int argc , char *argv[]){
    struct dirent *de;
    char* name;int flag_count=0;int cnt;char *flag;
    flag=remove_flags(argv,argc,&flag_count);cnt=argc-flag_count;
    char** soruce=take_core(argv,cnt);
    free(flag);
    fro(soruce,cnt);
}
//gcc trial.c -fsanitize=address -fno-omit-frame-pointer -ggdb