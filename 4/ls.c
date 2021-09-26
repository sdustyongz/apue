#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>


char * permession_mode(struct stat * sbuf , char * permode,int length);

char file_type(struct stat * st){
    char  ptr; 
   if (S_ISREG(st->st_mode)){
        ptr = '-';
   }else if(S_ISDIR(st->st_mode)){
        ptr = 'd';
   }else if(S_ISCHR(st->st_mode)){
       ptr = 'c';
   }else if(S_ISBLK(st->st_mode)){
       ptr = 'B';
   }else if(S_ISFIFO(st->st_mode)){
       ptr = 'f';
   }else if(S_ISLNK(st->st_mode)){
       ptr = 'L';
   }else if(S_ISSOCK(st->st_mode)){
       ptr = 's';

   } else 
       ptr = '-';
    return ptr;
}
void dir_file(char * file,struct stat * sbuf){
    char ft = file_type(sbuf);
    char mode[9];
    permession_mode(sbuf,mode,10);
    mode[9] = '\0';
    printf("%s  %s\n",file,mode);
}

void dir_dir(char * dir_path){
    DIR * dir;
    if((dir = opendir(dir_path)) == NULL){
        perror("opendir fail:");
        return;
    }
    struct dirent * drientp;
    while((drientp = readdir(dir)) !=NULL){
        struct stat sbuf;
        char *  nname = malloc(NAME_MAX);
        strcat(nname,dir_path);
        strcat(nname,drientp->d_name);
        lstat(nname,&sbuf);
        dir_file(drientp->d_name,&sbuf);
        free(nname);
    }
}

char * permession_mode(struct stat * sbuf , char * permode,int length){
    if(length<9){
        printf("permession length not enough\n");
        exit(1);
    }
    memset(permode,'-',length); 
    if(sbuf->st_mode & S_IRUSR){
        permode[0]='r';
    }
    if(sbuf->st_mode & S_IWUSR){
        permode[1]='w';
    }
    if(sbuf->st_mode & S_IXUSR){
        permode[2]='x';
    }
    if(sbuf->st_mode & S_ISUID){
        permode[2]='s';
    }
    if(sbuf->st_mode & S_IRGRP){
        permode[3]='r';
    }
    if(sbuf->st_mode & S_IWGRP){
        permode[4]='w';
    }
    if(sbuf->st_mode & S_IXGRP){
        permode[5]='x';
    }
    if(sbuf->st_mode & S_ISGID){
        permode[5]='s';
    }
    if(sbuf->st_mode & S_IROTH){
        permode[6]='r';
    }
    if(sbuf->st_mode & S_IWOTH){
        permode[7]='r';
    }

    if(sbuf->st_mode & S_IXOTH){
        permode[8]='x';
    }
    
}

int main(int ac ,char * av[]){
    if(ac < 2){
        printf("useage error\n");
        return 0;
    }
    struct stat sbuf;
    if(stat(av[1],&sbuf) <0){

    }

    if(S_ISDIR(sbuf.st_mode)){
        dir_dir(av[1]);
    }else{
        dir_file(av[1],&sbuf);
    }

}


