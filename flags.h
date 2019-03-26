struct argFlags {
    int dir_full_search;
    struct hash_flags hash_flags;
    int logfile;
    int outfile;
    char outfile_name[255]; //255 is, normally, the max file name lenght on UNIX
    char logfile_name[255];
};

struct hash_flags {
    int md5;
    int sha1;
    int sha256;
}