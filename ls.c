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
int return_dirrectorycount(char* name){
    struct dirent *de;
    DIR *dr=opendir(name);
    int size=0;
    while((de=readdir(dr))!=NULL){
        size++;
    }
    closedir(dr);
    return size;
}
// Function to sort the array
int compare(char*x,char*y){
    int i=-1;
    while(1){
        i++;
        if(x[i]=='\0') return 1;
        if(y[i]=='\0') return 0;
        if(x[i]==y[i]) continue;
        if(x[i]<y[i]) return 1;
        else return 0;
    }
}
void sort(struct dirent **hold,int size)
{
    struct dirent* temp;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(compare(hold[i]->d_name,hold[j]->d_name)){
                temp=hold[i];
                hold[i]=hold[j];
                hold[j]=temp;
            }
        }
    }
}
char* remove_flags(char *argv[],int argc,int *ass){
    int i=1;
    while(i<argc&&argv[i][0]=='-'){
        if(strnlen(argv[i],256)>=256) {
            printf("Flag Name's too large\n");
            exit(1);
        }
        i++;
    } 
    i=1;
    int flag_count=0;
    while(i<argc){
        if(argv[i][0]=='-') flag_count++;
        i++;
    }
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
    return flag;
}
char** take_core(char *argv[],int argc,int flag_count){
    int i=1;
    int src=1;
    int count=argc-flag_count;
    char** newarray=malloc(count);
 //   printf("%d\n",count);
    for(int x=0;x<count;x++) newarray[x]=malloc(260);
    strncpy(newarray[0],argv[0],260);
    while(src<count){
        if(argv[i][0]!='-'){strncpy(newarray[src],argv[i],260);src++;}
        i++;
    } 
    return newarray; 
}
int search(char * flag,char x){
    for(int i=0;flag[i]!='\0';i++) if(x==flag[i]) return i;
    return -1;
}

void Print(char *s,char  type,int exe){
    if(type=='d') printf(ESC_FG_BLUE"%s  "ESC_RESET,s);
    else if(exe==1) printf(ESC_FG_CYAN"%s  "ESC_RESET,s);
    else
    printf("%s  ",s);
}
int con(int time){
    if(time>=24) time-=24;
    return time;
}
char typ(struct stat s){
    char type;
    if(s.st_mode&S_IFCHR)type='c';
    else if(s.st_mode&S_IFSOCK)type='s';
    else if(s.st_mode&S_IFBLK) type='b';
    else if(s.st_mode&S_IFIFO) type='p';
    else if(s.st_mode&S_IFLNK)type='l';
    else if(s.st_mode&S_IFDIR)type='d';
    else if(s.st_mode&S_IFREG) type='r';
    return type;
}
void spa_print(char ***array,int size){
    for(int i=0;i<size;i++){
        printf("%s %s %s %s %s\n",array[i][0],array[i][1],array[i][2],array[i][3],array[i][4]);
    }
}
void Handle_flags(struct dirent *hold,char *flag,struct stat s,char ***array,int loc){
    
   // printf("%s\n",flag);
    int index=0;
    int add=0;
    if((index=search(flag,'l'))>=0){
        if(index=search(flag,'a')>=0) add=1;
        if(add==0&&hold->d_name[0]=='.') return;
        char type=typ(s); 
        array[loc]=malloc(5);
        for(int i=0;i<5;i++) {
            array[loc][i]=malloc(40);
            if(!array[loc][i]) i--;
        }
        //itoa(s.st_size,array[3],10);
        struct tm dt = *(gmtime(&s.st_mtime));
        int month=dt.tm_mon;
        int year=dt.tm_year+1900;
        int day=dt.tm_mday;
        array[loc][4]=malloc(20);
        if(month==0)strcpy(array[loc][4],"Jan");
        else if(month==1) strcpy(array[loc][4],"Feb ");
        else if(month==2) strcpy(array[loc][4],"Mar ");
        else if(month==3) strcpy(array[loc][4],"Apr ");
        else if(month==4) strcpy(array[loc][4],"May ");
        else if(month==5) strcpy(array[loc][4],"Jun ");
        else if(month==6) strcpy(array[loc][4],"Jul ");
        else if(month==7) strcpy(array[loc][4],"Aug ");
        else if(month==8) strcpy(array[loc][4],"Sep ");
        else if(month==9) strcpy(array[loc][4],"Oct ");
        else if(month==10) strcpy(array[loc][4],"Nov ");
        else if(month==11) strcpy(array[loc][4],"Dec ");
        
        char string[5];
        sprintf(string,"%d",day);
        strcat(array[loc][4],string);
        int hr=con(dt.tm_hour+5);
        if(hr<10)strcat(array[loc][4]," 0");
        else strcat(array[loc][4]," ");
        sprintf(string,"%d",hr);
        strcat(array[loc][4],string);
        strcat(array[loc][4],":");
        sprintf(string,"%d",dt.tm_min);
        if(dt.tm_min<10)strcat(array[loc][4],"0");
        strcat(array[loc][4],string);
        printf("%s\n",array[loc][4]);
        if(s.st_mode&S_IRUSR)strcpy(array[loc][0],"r");
        else strcpy(array[loc][0],"-");
        if(s.st_mode&S_IWUSR)strcat(array[loc][0],"w");
        else strcat(array[loc][0],"-");
        if(s.st_mode&S_IXUSR)strcat(array[loc][0],"x");
        else strcat(array[loc][0],"-");
        if(s.st_mode&S_IRGRP)strcat(array[loc][0],"r");
        else strcat(array[loc][0],"-");
        if(s.st_mode&S_IWGRP)strcat(array[loc][0],"w");
        else strcat(array[loc][0],"-");
        if(s.st_mode&S_IXGRP)strcat(array[loc][0],"x");
        else strcat(array[loc][0],"-");
        if(s.st_mode&S_IROTH)strcat(array[loc][0],"r");
        else strcat(array[loc][0],"-");
        if(s.st_mode&S_IWOTH)strcat(array[loc][0],"w");
        else strcat(array[loc][0],"-");
        if(s.st_mode&S_IXOTH)strcat(array[loc][0],"x");
        else strcat(array[loc][0],"-");
        struct passwd *pw = getpwuid(s.st_uid);
        struct group  *gr = getgrgid(s.st_gid);  
        if(pw!=0) strcpy(array[loc][1],pw->pw_name);
        else strcpy(array[loc][1],"0");
        if(gr!=0) strcpy(array[loc][2],gr->gr_name);
        else strcpy(array[loc][2],"0");
        sprintf(array[loc][3],"%ld",s.st_size);
        printf("%s\n",array[loc][4]);
      // printf("%s %s %s %s\n",array[loc][0],array[loc][1],array[loc][2],array[loc][3]);

       
       // printf("%s %s %s %s %s\n",array[loc][0],array[loc][1],array[loc][2],array[loc][3],array[loc][4]);
        //Print(hold->d_name,type,s.st_mode&1);
    }
    if((index=search(flag,'a'))>=0){
        int i=0;
        printf(ESC_FG_GREEN"%s  ",hold->d_name);    printf("\n");
        i++;     
    }

}
int main(int argc , char *argv[]){
    struct dirent *de;
    char* name;int flag_count;int cnt;
    char*flag=remove_flags(argv,argc,&flag_count);cnt=argc-flag_count;
    char** soruce=take_core(argv,argc,flag_count);
    
    name=".";
    int current=1;
    //printf("%d\n",cnt);
    while(current<cnt||current==1){
        if(cnt>1) name=soruce[current];
        DIR *dr=opendir(name);
        printf("%s\n",name);
        if(dr==NULL){
            printf("ls: cannot access '%s': No such directory\n",name);return 0;
        }
        if(cnt>2)printf("%s:\n",name); 
        int size=return_dirrectorycount(name);
        int i=0;
        
        struct dirent **hold=malloc(sizeof(struct dirent*)*size);
        while((de=readdir(dr))!=NULL){
            hold[i]=de;
            i++;
        }
        i=0;
        sort(hold,size);char*** array=malloc(size);
        struct stat s;
        if(flag_count!=0){
            
            while(i<size){
                name=realpath(hold[i]->d_name,NULL);
                if(name==NULL) name=soruce[current];
                if(stat(name,&s)!=0){
                    printf("Could not access %s Stats\n",name);
                }
                Handle_flags(hold[i],flag,s,array,i);
                
                i++;
            }
        }
        else{
            while(i<size){
                if(hold[i]->d_name[0]!='.'){
                    name=realpath(hold[i]->d_name,NULL);
                    if(name==NULL) name=soruce[current];
                    if(stat(name,&s)!=0){
                       printf("Could not access %s Stats\n",name);
                    }
                    Print(hold[i]->d_name,typ(s),s.st_mode&1);
                }i++;
            }
        }
       // if(flag_count!=0) spa_print(array,size);
        printf("\n");
        closedir(dr);
        current++;
    }
}
//gcc ls.c -fsanitize=address -fno-omit-frame-pointer -ggdb