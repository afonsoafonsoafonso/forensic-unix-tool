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

void sigint_handler(int signo) {  
    printf("In SIGINT handler ...\n");
    arg_flags.end=1;
    print_logfile("Signal ","SIGINT");
} 

int main(int argc, char* argv[])
{
    struct sigaction ctrl_c;
    ctrl_c.sa_handler=sigint_handler;
    ctrl_c.sa_flags=SA_RESTART;
    sigemptyset(&ctrl_c.sa_mask);
    if (sigaction(SIGINT,&ctrl_c,NULL) < 0)   {
        fprintf(stderr,"Unable to install SIGINT handler\n");     
        exit(1);   }   
    struct sigaction SIGDIR;
    SIGDIR.sa_handler=sigusr1_handler;
    SIGDIR.sa_flags=SA_RESTART;
    sigemptyset(&SIGDIR.sa_mask);
    if (sigaction(SIGUSR1,&SIGDIR,NULL) < 0)   {
        fprintf(stderr,"Unable to install SIGUSR1 handler\n");     
        exit(1);   }  
    struct sigaction SIGFILE;
    SIGFILE.sa_handler=sigusr2_handler;
    SIGFILE.sa_flags=SA_RESTART;
    sigemptyset(&SIGFILE.sa_mask);
    if (sigaction(SIGUSR2,&SIGFILE,NULL) < 0)   {
        fprintf(stderr,"Unable to install SIGUSR2 handler\n");     
        exit(1);   }  
    //get current time for logfile
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    s_start = spec.tv_sec;
    ms_start = spec.tv_nsec; // 1.0e6; // Convert nanoseconds to milliseconds


    if (argc < 2 || argc>8)
    {
        perror("To use the forensic tool, use the following syntax:\nforensic [-r] [-h [md5[,sha1[,sha256]]] [-o <outfile>] [-v] <file|dir>\n");      
        exit(1);
    }
    //arg_flags=
    arg_parser(argc,argv);
    //arg_parser_test(arg_flags);
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
    treat_dir(argv[argc-1]);//,arg_flags);
    if (arg_flags.logfile){fclose(arg_flags.f);}
    exit(0);
}