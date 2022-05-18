#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#define PAGELENGTH 24
#define LINELENGTH 100
int main(int argc , char *argv[]){
    if(argc==1) exit(0);
    for(int i=1;i<argc;i++){
        FILE *f=fopen(argv[i],"r");
        struct termios t;
        tcgetattr(STDIN_FILENO,&t);
        t.c_lflag &= ~(ECHO|ICANON);
        tcsetattr(STDERR_FILENO,TCSAFLUSH,&t);
        char buffer[100];int x;
        if(i>=2) {
            printf("\n");
            goto Here;
        }
        x=0;//if int x is written here go to causes error
        while(fgets(buffer,LINELENGTH,f)){
            printf("%s",buffer);x++;
            if(x==23) break;
        }x=0;
        printf("\033[7m(--more--)\033[m");
        char c;
        Here:
        while(f){
            c=getchar();printf("\033[2k\033[G");
            if(c=='\n'){
                fgets(buffer,LINELENGTH,f);
                printf("%s",buffer);
            }
            else if(c==' '){
                x=0;
                while(fgets(buffer,LINELENGTH,f)){
                    printf("%s",buffer);x++;
                    if(x==PAGELENGTH-1) break;
                }
            }
            else if(c=='q') return 0;
            printf("\n\033[7m(--more--)\033[m");
        }
    }
}