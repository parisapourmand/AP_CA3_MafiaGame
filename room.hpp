#ifndef __ROOM_H__
#define __ROOM_H__

#include <vector>
#include <string>
#include <map>
#include "villager.hpp"
#include "mafia.hpp"
#include "sideRoles.hpp"
#include "detective.hpp"
#include "doctor.hpp"
#include "rouin.hpp"
#include "godfather.hpp"
#include "silencer.hpp"
#include "joker.hpp"
#include "helperFunctions.hpp"

class Room
{
	public:
		Room(){};
		Room(std::string n, std::map<std::string, int> roles);
		~Room();
		void addRoles(std::map<std::string, int> roles);
		void printRoomState();
		void addUsers(const std::vector<std::string>& commandWords);
		bool isRepeatedName(std::string newName);
		void dayVote(std::string voterName, std::string voteeName);
		void nightVote(std::string voterName, std::string voteeName);
		void checkSetVote(Player* voter, std::string voteeName);
		void endDay();
		void endNight();
		Player* voteResult(std::vector<Player*>);
		void killPlayer(Player* deadPlayer);
		void assignRoles(std::vector<std::string> names);
		bool allMafiasVoted();
		bool checkGameResult();
		void nightAfterMafia();
		void detect(std::string ditectiveName, std::string suspectName);
		void heal(std::string ditectiveName, std::string suspectName);
		void silent(std::string ditectiveName, std::string suspectName);
		void checkSetSuspect(Detective* voter, std::string name);
		void checkSetPatient(Doctor* voter, std::string name);
		void checkSetVictim(Silencer* voter, std::string name);
		std::string suspectState(std::string suspectName);
		Player* findPlayer(std::string name);
		bool allSilencersVoted();
		bool allDoctorsVoted();
		bool allDetectivesVoted();

		std::string getName(){
			return name;
		};
		bool getIsDay(){
			return isDay;
		};
		bool getEndGame(){
			return endGame;
		};
		int getTimeStage(){
			return timeStage;
		};
		private:
		std::string name;
		std::vector<Player*> players;
		std::vector<Player*> allMafias;
		std::vector<Player*> allVillagers;

		std::vector<Mafia*> mafias;
		std::vector<GodFather*> godFathers;
		std::vector<Silencer*> silencers;
		std::vector<Villager*> villagers;
		std::vector<Detective*> detectives;
		std::vector<Doctor*> doctors;
		std::vector<Rouin*> rouins;
		std::vector<Joker*> jokers;

		std::vector<std::string> alivePlayerNames;
		std::vector<std::string> deadPlayerNames;
		
		Player* killChosen;

		int dayNum = 1;
		int nightNum = 1;
		int timeStage = VOTE_TIME;
		bool isDay;
		bool endGame = false;
};

#endif