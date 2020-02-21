all: cgol.c dynCGOL.c
	gcc -ansi -Wall -o cgol cgol.c
	gcc -ansi -Wall -o dynCGOL dynCGOL.c
cgol: cgol.c
	gcc -ansi -Wall -o cgol cgol.c
dynCGOL: dynCGOL.c
	gcc -ansi -Wall -o dynCGOL dynCGOL.c
clean:
	rm cgol dynCGOL
