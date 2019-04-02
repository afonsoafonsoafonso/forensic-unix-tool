make:
	gcc -o forensic forensic.c funcs.c utils.c flags.h
clean:
	rm log.txt
var:
	export LOGFILENAME="log.txt"