objects = control.o input.o player.o cheat.o gameinout.o log.o bonus.o
lab7 :main.o gamecontrol.o gamebox.o cheat.o player.o gameinout.o log.o bonus.o
	g++ main.o gamecontrol.o gamebox.o cheat.o player.o gameinout.o log.o bonus.o -o lab7
main.o : main.cpp gamecontrol.h
	g++ -c main.cpp
gamecontrol.o :  gamecontrol.h gamecontrol.cpp cheat.h player.h gamebox.h bonus.h
	g++ -c  gamecontrol.cpp
gamebox.o : gamebox.cpp gamebox.h
	g++ -c gamebox.cpp
cheat.o : cheat.cpp cheat.h
	g++ -c cheat.cpp
player.o : player.cpp player.h
	g++ -c player.cpp
gameinout.o :  gameinout.h gameinout.cpp
	g++ -c gameinout.cpp
log.o: log.h log.cpp
	g++ -c log.cpp
bonus.o: bonus.h bonus.cpp
	g++ -c bonus.cpp
clean:
	rm lab6 main.o gamebox.o gamecontrol.o gameinout.o player.o cheat.o log.o bonus.o