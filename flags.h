struct hash_flags {
    int md5;
    int sha1;
    int sha256;
};

struct argFlags {
    int dir_full_search;
    int hash_calc;
    struct hash_flags hash_flags;
    int logfile;
    int outfile;
    char logfile_name[255];
    char outfile_name[255]; //255 is, normally, the max file name lenght on UNIX
};
/*struct argFlags arg_handler(int argc, char** argv) {
    struct argFlags arg_flags = {0};

    for(int i=1; i<argc; i++) {
        if(strcmp(argv[i],"-r")==0) {
            arg_flags.dir_full_search=1;
        }

        if(strcmp(argv[i],"-h")==0) {
            while(strcmp(argv[i],"md5")==0 || strcmp(argv[i],"sha1")==0 || strcmp(argv[i],"sha256")==0) {

                if(strcmp(argv[i],"md5")==0) 
                    arg_flags.hash_flags.md5==1;

                else if(strcmp(argv[i],"sha1")==0) 
                    arg_flags.hash_flags.sha1==1;
                
                else 
                    arg_flags.hash_flags.sha256==1;

                i++;
            }

        }
        //talvez mudar isto para abrir diretamente o ficheiro e guardar na struct 
        //num membro do tipo FILE* ???
        if(strcmp(argv[i],"-o")==0) {
            strcpy(argv[i],arg_flags.outfile_name);
        }

        if(strcmp(argv[i],"-v")==0) {
            strcpy(getenv("LOGFILENAME"),arg_flags.logfile_name);
        }
    }
    return arg_flags;
}*/