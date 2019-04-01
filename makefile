make:
	gcc -o forensic forensic.c funcs.c utils.c flags.h
remove:
	rm log.txt