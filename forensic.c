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
#include <flags.h>

int main(int argc, char** argv)
{
    struct argFlags arg_flags;

    if (argc < 2)
    {
        printf("To use the forensic tool, use the following syntax:\nforensic [-r] [-h [md5[,sha1[,sha256]]] [-o <outfile>] [-v] <file|dir>\n");      
        exit(1);
    }

    exit(0);
}

// TO-DO: mais tarde mudar esta função (e outras) para outro ficheiro com respetivo header
int arg_handler(int argc, char** argv, struct argFlags arg_flags) {
    for(int i=1; i<=argc; i++) {

        if(argv[i]=="-r") {
            arg_flags.dir_full_search=1;
        }

        else if(argv[i]=="-h") {
            while(argv[i]=="md5" || argv[i]=="sha1" || argv[i]=="sha256") {

                if(argv[i]=="md5") 
                    arg_flags.hash_flags.md5==1;

                else if(argv[i]=="sha1") 
                    arg_flags.hash_flags.sha1==1;
                
                else 
                    arg_flags.hash_flags.sha256==1;

                i++;
            }

        }
        //talvez mudar isto para abrir diretamente o ficheiro e guardar na struct 
        //num membro do tipo FILE* ???
        else if(argv[i]=="-o") {
            i++;
            strcpy(argv[i],arg_flags.outfile_name);
        }

        else if(argv[i]=="-v") {
            i++;
            strcpy(getenv("LOGFILENAME"),arg_flags.logfile_name);
        }
    }
}