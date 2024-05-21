all :
	make part2
	make part3

part2 : part2.c snakeAPI.c clientAPI.c arena.c ai.c
	gcc -o part2 part2.c snakeAPI.c clientAPI.c arena.c ai.c

part3 : partie2.c snakeAPI.c clientAPI.c arena.c ai.c
	gcc -o part3 partie2.c snakeAPI.c clientAPI.c arena.c ai.c

run :
	make
	./p1vsbot

clean : 
	rm -f part2
	rm -f part3