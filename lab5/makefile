
cc = g++
prom = game
deps = $(shell find ./ -name "*.h")
src = $(shell find ./ -name "*.cpp")
obj = $(src:%.c=%.o) 

game:player.cpp gamebox.cpp gamecontrol.cpp main.cpp
	g++ player.cpp gamecontrol.cpp gamebox.cpp  main.cpp -o lab6
