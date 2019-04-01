//Developers: Afonso Mendonça, João Araújo & Leonor Sousa
//Operative Systems

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>

#include "flags.h"
#include "funcs.h"
#include "utils.h"

int main(int argc, char* argv[])
{
    //get current time for logfile
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    s_start = spec.tv_sec;
    ms_start = spec.tv_nsec / 1.0e6; // Convert nanoseconds to milliseconds
    while(ms_start > 999) {
        s_start++;
        ms_start -= 1000;
    }

    struct argFlags arg_flags;

    if (argc < 2 || argc>8)
    {
        perror("To use the forensic tool, use the following syntax:\nforensic [-r] [-h [md5[,sha1[,sha256]]] [-o <outfile>] [-v] <file|dir>\n");      
        exit(1);
    }
    arg_flags=arg_parser(argc,argv);
    //arg_parser_test(arg_flags);
    
    //PERGUNTA:é suposto apagar o antigo?
    if (arg_flags.logfile){//empties previously existing file
        FILE* f=fopen(arg_flags.logfile_name, "w");
        fclose(f);
    }

    int fd_outfile;
    //checking for output file
    if (arg_flags.outfile)
    {
        printf("Data saved on file %s\n", arg_flags.outfile_name);
        printf("Execution records saved on file ...\n");
        fd_outfile=open(arg_flags.outfile_name, O_WRONLY | O_APPEND | O_CREAT);
        if (fd_outfile<0)
        {
            printf("Error on opening output file.\n");
            exit(10);
        }
        dup2(fd_outfile, STDOUT_FILENO);
    }

    if(arg_flags.dir_full_search==1 && is_dir(arg_flags.path)<=0)
        printf("Given path is not a folder.\n");

    treat_dir(argv[argc-1],arg_flags);

    exit(0);
}