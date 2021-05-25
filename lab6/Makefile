objects = control.o input.o player.o cheat.o
lab6 :main.o gamecontrol.o gamebox.o cheat.o player.o gameinout.o
	g++ main.o gamecontrol.o gamebox.o cheat.o player.o gameinout.o -o lab6
main.o : main.cpp gamecontrol.h
	g++ -c main.cpp
gamecontrol.o :  gamecontrol.h gamecontrol.cpp cheat.h player.h gamebox.h
	g++ -c  gamecontrol.cpp
gamebox.o : gamebox.cpp gamebox.h
	g++ -c gamebox.cpp
cheat.o : cheat.cpp cheat.h
	g++ -c cheat.cpp
player.o : player.cpp player.h
	g++ -c player.cpp
gameinout.o :  gameinout.h gameinout.cpp
	g++ -c gameinout.cpp
clean:
	rm lab6 main.o gamebox.o gamecontrol.o gameinout.o player.o cheat.o 