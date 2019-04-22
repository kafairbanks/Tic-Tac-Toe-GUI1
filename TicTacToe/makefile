all: play

play: main.o board.o ui.o gameengine.o score.o Computer.o Node.o MinimaxTree.o
	g++ --std=c++11 -o play main.o board.o score.o ui.o gameengine.o Computer.o Node.o MinimaxTree.o -lmenu -lpanel -lform -lutil -lncurses
Computer.o: Computer.cpp
	g++ --std=c++11 -c Computer.cpp -lmenu -lpanel -lform -lutil -lncurses
Node.o: Node.cpp
	g++ --std=c++11 -c Node.cpp -lmenu -lpanel -lform -lutil -lncurses
MinimaxTree.o: MinimaxTree.cpp
	g++ --std=c++11 -c MinimaxTree.cpp -lmenu -lpanel -lform -lutil -lncurses
score.o: score.cpp
	g++ --std=c++11 -c score.cpp -lmenu -lpanel -lform -lutil -lncurses
ui.o: ui.cpp gameengine.h
	g++ --std=c++11 -c ui.cpp -lmenu -lpanel -lform -lutil -lncurses
board.o: board.cpp gameengine.h
	g++ --std=c++11 -c board.cpp -lmenu -lpanel -lform -lutil -lncurses
gameengine.o: gameengine.cpp gameengine.h
	g++ --std=c++11 -c gameengine.cpp -lmenu -lpanel -lform -lutil -lncurses
main.o : main.cpp gameengine.h board.h ui.h
	g++ --std=c++11 -c main.cpp -lmenu -lpanel -lform -lutil -lncurses
clean:
	rm *.o play
