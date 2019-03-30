#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

#include "flags.h"
#include "utils.h"

// TO-DO: mais tarde mudar esta função (e outras) para outro ficheiro com respetivo header
//adicionar também verificação de argumentos válidos
struct argFlags arg_parser(int argc, char** argv) {
    struct argFlags arg_flags = {0};
    char *token;
    
    for(int i=1; i<argc; i++) {
        if(strcmp(argv[i],"-r")==0) {
            arg_flags.dir_full_search=1;
        }

        if(strcmp(argv[i],"-h")==0) {
            arg_flags.hash_calc=1;
            i++;
            token = strtok(argv[i],",");
            while(token!=NULL) {
                if(strcmp(token,"md5")==0)
                    arg_flags.hash_flags.md5=1;
                else if(strcmp(token,"sha1")==0)
                    arg_flags.hash_flags.sha1=1;
                else if(strcmp(token,"sha256")==0)
                    arg_flags.hash_flags.sha256=1;
                token = strtok(NULL,",");
            }
        }

        if(strcmp(argv[i],"-o")==0) {
            arg_flags.outfile=1;
            i++;
            strcpy(arg_flags.outfile_name,argv[i]);
        }
        if(strcmp(argv[i],"-v")==0) {
            if(getenv("LOGFILENAME")!=NULL ) {
                strcpy(arg_flags.logfile_name,getenv("LOGFILENAME")); 
                arg_flags.logfile=1;
            }
            else printf("Environment variable not set. -v argument will be ignored\n\n\n");
        }
        strcpy(arg_flags.path,argv[argc-1]);
    }
    return arg_flags;
}

//falta adicionar verificação de file_type mas como será usando "file",
//invés da "stat", fica para depois
void print_file_data(const char* path, struct argFlags arg_flags) {
    struct stat fs; //fs: file_stat
    stat(path,&fs);
    //prints file name
    printf("%s,",path);
    //prints file size in bytes
    printf("%ld,",fs.st_size);
    //prints file permissions/access
    printf( (fs.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fs.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fs.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fs.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fs.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fs.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fs.st_mode & S_IROTH) ? "r" : "-");
    printf( (fs.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fs.st_mode & S_IXOTH) ? "x" : "-");
    //running hash calculations
    if(arg_flags.hash_calc) {
        char hash[300];
        if(arg_flags.hash_flags.md5) {
            printf(",");
            char *md5cmd = malloc(strlen("md5sum ")+strlen(path)+1);
            strcpy(md5cmd,"md5sum ");
            strcat(md5cmd,path);
            char hash[300];
            FILE *cmd_out = popen(md5cmd,"r");
            fscanf(cmd_out,"%s",hash);
            printf("%s",hash);
        }
        if(arg_flags.hash_flags.sha1) {
            printf(",");
            char *sha1cmd = malloc(strlen("sha1sum ")+strlen(path)+1);
            strcpy(sha1cmd,"sha1sum ");
            strcat(sha1cmd,path);
            FILE *cmd_out = popen(sha1cmd,"r");
            fscanf(cmd_out,"%s",hash);
            printf("%s",hash);  
        }
        if(arg_flags.hash_flags.sha256) {
            printf(",");
            char *sha256cmd = malloc(strlen("sha256sum ")+strlen(path)+1);
            strcpy(sha256cmd,"sha256sum ");
            strcat(sha256cmd,path);
            FILE *cmd_out = popen(sha256cmd,"r");
            fscanf(cmd_out,"%s",hash);
            printf("%s",hash);  
        }
    }
    return;
}