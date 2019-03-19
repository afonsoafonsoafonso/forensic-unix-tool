//Developers: Afonso Mendonça, João Araújo & Leonor Sousa
//Operative Systems

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("To use the forensic tool, use the following syntax:\nforensic [-r] [-h [md5[,sha1[,sha256]]] [-o <outfile>] [-v] <file|dir>\n");      
        exit(1);
    }
    exit(0);
}