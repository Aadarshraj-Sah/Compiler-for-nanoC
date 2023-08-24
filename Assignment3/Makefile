#declare variable
CC=gcc
FC=flex

#Commmands
output.txt: a.out A3_30.nc
	./a.out < A3_30.nc > output.txt

a.out: lex.yy.c A3_30.c 
	$(CC) A3_30.c

lex.yy.c: A3_30.l
	$(FC) A3_30.l 

clean:
	rm output.txt lex.yy.c a.out 