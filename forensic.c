//Developers: Afonso Mendonça, João Araújo & Leonor Sousa
//Operative Systems

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

//
#include "flags.h"

struct argFlags arg_parser(int argc, char** argv);
void arg_handler_test(struct argFlags arg_flags);

int main(int argc, char** argv)
{
    struct argFlags arg_flags;

    if (argc < 2)
    {
        printf("To use the forensic tool, use the following syntax:\nforensic [-r] [-h [md5[,sha1[,sha256]]] [-o <outfile>] [-v] <file|dir>\n");      
        exit(1);
    }

    printf("argc: %d\n", argc);
    arg_flags=arg_parser(argc,argv);
    arg_handler_test(arg_flags);

    exit(0);
}

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
            arg_flags.logfile=1;
            i++;
            strcpy(arg_flags.logfile_name,argv[i]);
        }
    }

    return arg_flags;
}

void arg_handler_test(struct argFlags arg_handler) {
    printf("-r:%d\n ; -h:%d\n ; -v:%d - %s\n ; -o:%d - %s\n",arg_handler.dir_full_search,arg_handler.hash_calc,arg_handler.logfile,arg_handler.logfile_name,arg_handler.outfile,arg_handler.outfile_name);

    printf("md5:%d ; sha1:%d ; sha256:%d\n",arg_handler.hash_flags.md5,arg_handler.hash_flags.sha1,arg_handler.hash_flags.sha256);
}