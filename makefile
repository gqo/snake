make:
	g++ -c snake.cpp
	g++ snake.o -o snake-app -lsfml-graphics -lsfml-window -lsfml-system
