all :
	make part2
	make bot

part2 : part2.c snakeAPI.c clientAPI.c arena.c ai.c
	gcc -o part2 part2.c snakeAPI.c clientAPI.c arena.c ai.c

bot : main.c snakeAPI.c clientAPI.c arena.c ai.c snake.c
	gcc -o bot main.c snakeAPI.c clientAPI.c arena.c ai.c snake.c
	

run :
	make bot
	./bot

clean : 
	rm -f part2
	rm -f bot