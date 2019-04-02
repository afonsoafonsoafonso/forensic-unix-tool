forensic: forensic.c funcs.c utils.c flags.h
	gcc -o forensic forensic.c funcs.c utils.c flags.h
debug: forensic forensic.c funcs.c utils.c flags.h
	gcc -g -o forensic forensic.c funcs.c utils.c flags.h
clean:
	rm -f log.txt forensic
var:
	export LOGFILENAME="log.txt"
