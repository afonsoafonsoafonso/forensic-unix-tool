#pragma once

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

struct argFlags arg_parser(int argc, char** argv);
void print_file_data(const char *file, struct argFlags arg_flags);