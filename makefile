CC := g++

all: play.out

play.out: main.o helperFunctions.o game.o room.o player.o villager.o mafia.o sideRoles.o detective.o doctor.o rouin.o godfather.o silencer.o joker.o

	$(CC) main.o helperFunctions.o game.o room.o player.o villager.o mafia.o sideRoles.o detective.o doctor.o rouin.o godfather.o silencer.o joker.o $(CCFLAGS) -o play.out


main.o: game.hpp main.cpp
	$(CC) -c main.cpp -o main.o

game.o: room.hpp helperFunctions.hpp exceptions.hpp game.hpp game.cpp
	$(CC) -c game.cpp -o game.o

room.o: villager.hpp detective.hpp doctor.hpp rouin.hpp mafia.hpp godfather.hpp silencer.hpp sideRoles.hpp joker.hpp exceptions.hpp game.hpp room.hpp room.cpp
	$(CC) -c room.cpp -o room.o

detective.o: villager.hpp detective.hpp detective.cpp
	$(CC) -c detective.cpp -o detective.o

doctor.o: villager.hpp doctor.hpp doctor.cpp
	$(CC) -c doctor.cpp -o doctor.o

rouin.o: villager.hpp rouin.hpp rouin.cpp
	$(CC) -c rouin.cpp -o rouin.o

godfather.o: mafia.hpp godfather.hpp godfather.cpp
	$(CC) -c godfather.cpp -o godfather.o

silencer.o: mafia.hpp silencer.hpp silencer.cpp
	$(CC) -c silencer.cpp -o silencer.o

joker.o: sideRoles.hpp joker.hpp joker.cpp
	$(CC) -c joker.cpp -o joker.o

villager.o: player.hpp villager.hpp villager.cpp
	$(CC) -c villager.cpp -o villager.o

mafia.o: player.hpp mafia.hpp mafia.cpp
	$(CC) -c mafia.cpp -o mafia.o

sideRoles.o: player.hpp sideRoles.hpp sideRoles.cpp
	$(CC) -c sideRoles.cpp -o sideRoles.o

player.o: player.hpp player.cpp
	$(CC) -c player.cpp -o player.o

helperFunctions.o: helperFunctions.hpp helperFunctions.cpp
	$(CC) -c helperFunctions.cpp -o helperFunctions.o

.PHONY: clean
clean:
	rm -r *.o 