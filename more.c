#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
int LINELEN =179;
int size =11;
struct termios orig_termios;
void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);
  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO|ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
void do_more(FILE *fp){
    char buffer[LINELEN];
    char c;
    int x=0;
    while(x<size&&fgets(buffer, LINELEN, fp)){
        x++;
        fputs(buffer, stdout);
    }
     printf("\033[7m--More--(%%)\033[m");
    while(fgets(buffer, LINELEN, fp)){
        c=getchar();
        printf("\33[2K\33[0G");
        if(c=='\n'){
         //   exit(0);
        // printf("\33[1T");
        write(STDOUT_FILENO,buffer, LINELEN);
        if(strchr(buffer,'\n')==NULL) printf("\n");
        printf("\033[7m--More--(%%)\033[m");
        }
        else if(c==' '){
            x=1;
            while(x<size&&fgets(buffer, LINELEN, fp)){
                x++;
                write(STDOUT_FILENO,buffer, LINELEN);
            }if(strchr(buffer,'\n')==NULL) printf("\n");
            printf("\033[7m--More--(%%)\033[m");
        }
    }
}
int main(int argc , char *argv[]){
    enableRawMode();
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    LINELEN=w.ws_col;
    size=w.ws_row;
    size--;
    //printf ("lines %d\n", w.ws_row);
  //  printf ("columns %d\n", w.ws_col);
   if (argc == 1){
       printf("more: bad usage\nTry 'more --help' for more information.\n");
       exit (0);
   }
   FILE * fp;
   fp = fopen(argv[1] , "r");
   if(fp == NULL){
       perror("more: stat of jojo failed: No such file or directory");
       exit(1);
   }
   do_more(fp);
   fclose(fp); 
   printf("\n");
   //disableRawMode();
   return 0;
}

