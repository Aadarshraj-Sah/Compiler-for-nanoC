output.txt: a.out A4_30.nc
	./a.out < A4_30.nc > output.txt

a.out: lex.yy.o y.tab.o A4_30.o
	cc lex.yy.o y.tab.o A4_30.o -lfl

lex.yy.o: lex.yy.c
	cc -c lex.yy.c

y.tab.o: y.tab.c
	cc -c y.tab.c

A4_30.o: A4_30.c
	cc -c A4_30.c

lex.yy.c: A4_30.l y.tab.h 
	flex A4_30.l

y.tab.c: A4_30.y
	bison -dty A4_30.y

y.tab.h: A4_30.y
	bison -dty A4_30.y

A4_30.c:
	touch A4_30.c

clean:
	rm output.txt a.out lex.yy.* y.tab.* A4_30.o