#ifndef __SILENCER_H__
#define __SILENCER_H__

#include "mafia.hpp"

class Silencer : public Mafia
{
	public:
		void setVictim(std::string s){
			victim = s;
		}
		std::string getVictim(){
			return victim;
		}
	private:
		std::string victim = "-";
};

#endif