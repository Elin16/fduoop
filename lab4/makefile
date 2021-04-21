
cc = g++
prom = game
deps = $(shell find ./ -name "*.h")
src = $(shell find ./ -name "*.cpp")
obj = $(src:%.c=%.o) 

game:player.cpp gamebox.cpp gameplay.cpp 
	g++ player.cpp gameplay.cpp gamebox.cpp  -o game  
