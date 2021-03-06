#pragma once

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>

#include "flags.h"
#include "utils.h"

extern long ms_start;
extern int s_start;
extern struct argFlags arg_flags;

void sigusr1_handler(int signo);
void sigusr2_handler(int signo);
//struct argFlags 
void arg_parser(int argc, char** argv);
void treat_dir(char path[]);//, struct argFlags arg_flags);
void print_file_data(const char *file);//, struct argFlags arg_flags);
void print_logfile(const char* act,const char* act2);//, struct argFlags arg_flags);