#ifndef __GAME_H__
#define __GAME_H__

#include "room.hpp"

class Game
{
	public:
		~Game();
		void playGame();
		Room* createRoom(std::vector<std::string>& commandWords);
		void chooseAction(std::vector<std::string>& commandWords);
		Room* findRoom(const std::string& name);

		std::vector<Room*> getRooms(){
			return rooms;
		};	
	private:
		Room* currentRoom;	
		std::vector<Room*> rooms;
};

#endif