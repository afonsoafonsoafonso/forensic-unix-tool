#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

#include "flags.h"

int is_dir(const char* path) {
    struct stat buf;
    stat(path,&buf);
    return S_ISDIR(buf.st_mode);
}

void arg_parser_test(struct argFlags arg_handler) {
    printf("-r:%d\n ; -h:%d\n ; -v:%d - %s\n ; -o:%d - %s\n",arg_handler.dir_full_search,arg_handler.hash_calc,arg_handler.logfile,arg_handler.logfile_name,arg_handler.outfile,arg_handler.outfile_name);

    printf("md5:%d ; sha1:%d ; sha256:%d\n",arg_handler.hash_flags.md5,arg_handler.hash_flags.sha1,arg_handler.hash_flags.sha256);
}