#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>  
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <sys/wait.h>
#define MAXLENGTH 1124
char* PROMPT;
void Global(){
    PROMPT=malloc(64);
    strncpy(PROMPT,"Butt_Sahab:- ",15);
}
void Print(char **argv,int argc){
    for(int i=0;i<=argc;i++){
        printf("argv[%d] = %s\n",i,argv[i]);
    }
    printf("\n");
}
void Printc(char **argv,int argc){
    for(int i=0;i<argc;i++){
        int j=0;
        while(argv[i][j]!='\0') {printf("%d ",argv[i][j]);j++;}
    }
    printf("\n");
}
void Printca(char *argv,int argc){
    int j=0;
    while(argv[j]!='\0') {printf("%d ",argv[j]);j++;}
    printf("\n");
}
char * copy(int start,int end,char*s){
    char * new_string=malloc(end-start+2);
    int x=0;
    for(int i=0;i<(end-start+2);i++){
        new_string[i]='\0';
    }
    for(int i=start;i<end;i++,x++){
        new_string[x]=s[i];
    }
  //  printf("%s\n",new_string);
   // Printca(new_string,end-start+2);
    return new_string;
}
char** restruct(char *s,int* len){
    int argc=0;
    int i=0;        
    while(s[i]==' '&&s[i]!='\0'){
        i++;
    }
    while(i<*len&&s[i]!='\0'){
        argc++;
        while(s[i]!=' '&&s[i]!='\0'){
            i++;
        }
        while(s[i]==' '&&s[i]!='\0'){
            i++;
        }
    }
    char ** argv= malloc((argc+1)*sizeof(char*));
    int x=0;i=0;int prev=0;
    while(s[i]==' '&&s[i]!='\0'){
        i++;
    }
    while(i<*len&&s[i]!='\0'){
        prev=i;
        while(s[i]!=' '&&s[i]!='\0'){
            i++;
        }
        char *as=copy(prev,i,s);
        argv[x]=as;
        x++;
        while(s[i]==' '&&s[i]!='\0'){
            i++;
        }
    }
 //  Print(argv,argc);
    *len=argc;
    return argv;
}
char* red(FILE* f){
    printf("%s",PROMPT);
    char *s= malloc(MAXLENGTH);
    for(int i=0;i<MAXLENGTH;i++) s[i]='\0';
    int x=getc(f);
    int i=0;
    while(x!=EOF){
        if(x=='\n') break;
        s[i]=x;i++;
        x=getc(f);
    }
    s[i]='\0';
    return s;
}
void redirect(char** argv,int *argc){
    int output_redirect=STDOUT_FILENO;bool o=false;
    int input_redirect=STDIN_FILENO;bool in=false;
    int error_redirect=STDERR_FILENO;bool err=false;
    int found=0;
    for(int i=0;i<*argc;i++){
        if((strcmp(argv[i],"\0")==0)||argv[i]==NULL) break;
        if((strcmp(argv[i],"<")==0)||(strcmp(argv[i],">")==0)||(strcmp(argv[i],"2>")==0)||(strcmp(argv[i],"1>")==0)||(strcmp(argv[i],"0<")==0)){
            if(argv[i+1]!=NULL&&(strcmp(argv[i+1],"\0")!=0))found++;
            i++;
            found++;
          //  printf("%d\n",found);
        }
    }
    if(found==0) return;
   //printf("%d\n",found);
    for(int i=0;i<*argc;i++){
        if((strcmp(argv[i],"1>")==0)||(strcmp(argv[i],">")==0)){
            if(argv[i+1]!=NULL||strcmp(argv[i+1],"\0")==0){
                output_redirect= i+1;
                o=true;
            }
            else{
                printf("Error with redirection\n");exit(0);
            }
        }
        if((strcmp(argv[i],"0<")==0)||(strcmp(argv[i],"<")==0)){
            if(argv[i+1]!=NULL||strcmp(argv[i+1],"\0")==0){
                input_redirect= i+1;in=true;
            }
            else{
                printf("Error with redirection\n");exit(0);
            }
        }
        if((strcmp(argv[i],"2>")==0)){
            if(argv[i+1]!=NULL||strcmp(argv[i+1],"\0")==0){
                error_redirect= i+1;err=true;
            }
            else{
                printf("Error with redirection\n");exit(0);
            }
        }
    }
    
    char* filename;
    int f;
    filename=argv[input_redirect];
    if(fopen(filename,"r")==NULL){
        printf("%s file does not exist\n",filename);exit(0);
    }
    //printf("input = %s\noutput = %s\nerror = %s\n",argv[input_redirect],argv[output_redirect],argv[error_redirect]);
    if(in){
        f=open(filename,O_RDONLY);
        dup2(f,STDIN_FILENO);
    }
    filename=argv[output_redirect];
    printf("%s\n",filename);
    if(o){
        f=open(filename,O_CREAT||O_RDWR||O_APPEND);
        if(f==-1){
            printf("Error in opening/accessing file\n");exit(0);
        }
        dup2(f,STDOUT_FILENO);
    }
    filename=argv[error_redirect];
    if(err){
        f=open(filename,O_CREAT||O_RDWR||O_APPEND);
        dup2(f,STDERR_FILENO);
    }
    //printf("%d\n",f);
    //changing argc and removing redirections from argv
    char** new_argv =malloc(*argc-found+1);
    printf("%d\n",*argc-found+1);
    int x=0;
    for(int i=0;i<*argc;i++){
        if((strcmp(argv[i],"\0")==0)||argv[i]==NULL) break;
        if((strcmp(argv[i],"<")==0)||(strcmp(argv[i],">")==0)||(strcmp(argv[i],"2>")==0)||(strcmp(argv[i],"1>")==0)||(strcmp(argv[i],"0<")==0)){
            free(argv[i]);
            if((strcmp(argv[i+1],"\0")!=0)||argv[i+1]!=NULL)free(argv[i+1]);
            i++;
        }
        else{
            new_argv[x]=argv[i];x++;
        }
    }
    *argc=*argc-found;
    new_argv[*argc]=malloc(2);
    new_argv[*argc]=NULL;
    argv=new_argv;
  //  printf("%d\n",*argc);
   // Print(argv,*argc);
}
int main(){
    Global();
    char* s=red(stdin);
    while(s!=NULL){
        int argc=256;
        char** argv=restruct(s,&argc);
        argv[argc]=malloc(1);
        argv[argc]=NULL;
        int status;
        int pid=fork();
        if(pid==0){
            redirect(argv,&argc);
            //printf("%d\n",argc);
           // Print(argv,argc);
            if(execvp(argv[0],argv)==-1) printf("poop\n");
            for(int i=0;i<=argc;i++) free(argv[i]);
            free(argv);
            free(s);
            return 0;
        }
        wait(&status);
        for(int i=0;i<=argc;i++) free(argv[i]);
        free(argv);
        free(s);
        s=red(stdin);
    }
    free(s);
    return 1;
}
//-fsanitize=address -fno-omit-frame-pointer -ggdb