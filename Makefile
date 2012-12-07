
LEX=flex 
YACC=bison
CC=gcc


objects=main_test.o jsonxml.o strTools.o libjson.so
JSON_objects=json.tab.o lex.yy.o json_types.o encode.o

main: main_test.o jsonxml.o strTools.o libjson.a
	$(CC) $^ -o main

src-build: json.tab.c json.tab.h lex.yy.c

debug:  CC += -DDEBUG -g
debug:  main


json.tab.c json.tab.h: json.y
	$(YACC) -d $^


lex.yy.c: json.l
	$(LEX) $^

json.tab.o: json.tab.c json.h
	gcc -Wall -fPIC -c json.tab.c

lex.yy.o: lex.yy.c 
	gcc -Wall -fPIC -c lex.yy.c

json_types.o: json_types.c json_types.h
	gcc -Wall -fPIC -c json_types.c

libjson.so: $(JSON_objects)
	gcc -shared -Wl,-soname,libjson.so -o libjson.so $(JSON_objects) -lc

libjson.a: $(JSON_objects)
	ar rcs libjson.a $?

pyjson.o: pyjson.c pyjson.h
	gcc -Wall -fPIC -I/usr/include/python3.2mu -c pyjson.c

cjson.so: pyjson.o libjson.a 
	gcc -shared $^ -o cjson.so -lpython3.2mu



clean:
	rm *.o
	rm *.so
	rm json.tab.c json.tab.h lex.yy.c
	rm main
