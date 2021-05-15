#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

class Player
{
	public:
		Player();
		void setVote(std::string);
		void decreaseLife();
		void setName(std::string n){
			name =n;
		}
		void setImmortal(bool state){
			immortal = state;
		}
		void setSilent(bool state){
			silent = state;
		}
		std::string getVote(){
			return vote;
		};
		std::string getName(){
			return name;
		};
		int getLife(){
			return life;
		};	
		bool getImmortal(){
			return immortal;
		};			
		bool getSilent(){
			return silent;
		};	
	protected:
		std::string name;
		int life;
		bool immortal = false;
		bool silent = false;
	private:
		std::string vote = "-";
};

#endif