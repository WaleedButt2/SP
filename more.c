#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
//have not checked with large file name
// fix vim addition
int LINELEN =179;
int size =11;
int No_of_char;
char* name;
struct winsize w;
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
void Set_size(){
    LINELEN=w.ws_col;
    size=w.ws_row;
    size--;
}
void get_No_char(FILE *fp){
    No_of_char=0;
    while(getc(fp)!=EOF){
        No_of_char++;
    }
    fseek(fp,0,0);
}
int char_in(char* s){
    int i=0;
    int con=0;
    while(s[i]!='\0'){con++;i++;}
    return con;
}
//does not include \n or ' ' in more percentage
void do_more(FILE *fp,char *argv[],int argc,int i){
    char c='\0';
    int x=0;
    char* buffer = malloc(LINELEN);
  //  printf("char= %d\nLIne = %d\n",No_of_char,LINELEN);
    int consumed=0;
    Set_size();
    int flag=0;
    size-=3;
    if(i>1){c=getchar();printf("\33[2K\33[0G");}
    if(argc>1){
           printf("::::::::::::::\n%s\n::::::::::::::\n",argv[i]);
    }
    if(i==1){
    while(x<size&&fgets(buffer, LINELEN, fp)){
        x++;
        consumed+=strlen(buffer);
        fputs(buffer, stdout);
    }
     printf("\033[7mBUTT(%d%%)\033[m",(int)(consumed/(double)No_of_char*100));
    }
    while(fgets(buffer, LINELEN, fp)){
        //if(strcmp(argv[1],argv[i])!=0)
        LABEL:
        if(flag!=0)c=getchar();
        flag=1;
        if(c=='\n'){if(flag!=0)printf("\33[2K\33[0G");
         //   exit(0);
        // printf("\33[1T");
        fputs(buffer,stdout);
        if(strchr(buffer,'\n')==NULL) printf("\n");
        consumed+=strlen(buffer);
        printf("\033[7mBUTT(%d%%)\033[m",(int)(consumed/(double)No_of_char*100));
        //printf("%d\n",consumed);
        }
        else if(c==' '){if(flag!=0)printf("\33[2K\33[0G");
            ioctl(0, TIOCGWINSZ, &w);
            Set_size();
            x=0;
            while(x<size&&fgets(buffer, LINELEN, fp)){
                x++;
                consumed+=strlen(buffer);
                fputs(buffer,stdout);
            }if(strchr(buffer,'\n')==NULL) printf("\n");
            x--;
           printf("\033[7mBUTT(%d%%)\033[m",(int)(consumed/(double)No_of_char*100)); 
           //printf("%d\n",consumed);
        }
        else if(c=='v'){if(flag!=0)printf("\33[2K\33[0G");
            if(fork()==0){
                char * path[]={" /usr/bin/vi",argv[i],NULL};
                execv(" /usr/bin/vi",path);
            }
            else
            wait(NULL);
        }
        else goto LABEL;
    }
    printf("\33[2K\33[0G");
}
int main(int argc , char *argv[]){
    enableRawMode();
    //printf ("lines %d\n", w.ws_row);
  //  printf ("columns %d\n", w.ws_col);
  
   if (argc == 1){
       printf("more: bad usage\nTry 'more --help' for more information.\n");
       exit (0);
   }int i=1;
   
   while(1){
   FILE * fp;
   fp = fopen(argv[i] , "r");
   get_No_char(fp);
   if(fp == NULL){
       printf("more: stat of %s failed: No such file or directory",argv[i]);
       exit(1);
   }
    ioctl(0, TIOCGWINSZ, &w);
   do_more(fp,argv,argc,i);
   fclose(fp);i++; if(i>=argc) break;
   printf("\n");
   if(i<argc) printf("\033[7mBUTT(Next file: test.txt)\033[m");
   }
   //disableRawMode();
   return 0;
}

