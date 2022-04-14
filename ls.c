#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
int return_dirrectorycount(char* name){
    struct dirent *de;
    DIR *dr=opendir(name);
    int size=0;
    while((de=readdir(dr))!=NULL){
        if(de->d_name[0]=='.') continue;
        size++;
    }
    closedir(dr);
    return size;
}
static int myCompare(const void* a, const void* b)
{
  
    // setting up rules for comparison
    return strcmp(*(const char**)a, *(const char**)b);
}
  
// Function to sort the array
void sort(const char** arr, int n)
{
    // calling qsort function to sort the array
    // with the help of Comparator
    qsort(arr, n, sizeof(const char*), myCompare);
}
int main(int argc , char *argv[]){
    struct dirent *de;
    char* name;
    if(argc==1) name=".";
    else name=argv[1];
    DIR *dr=opendir(name);
    if(dr==NULL){
        printf("ls: cannot access '%s': No such file or directory",name);
    }
    int size=return_dirrectorycount(name);
    int i=0;
    const char** hold=malloc(size);
    while((de=readdir(dr))!=NULL){
        if(de->d_name[0]=='.') continue;
        hold[i]=de->d_name;i++;
    }i=0;
    sort(hold,size);
    while(i<size){
        printf("%s\n",hold[i]);i++;
    }
}