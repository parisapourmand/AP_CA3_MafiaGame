#ifndef __DETECTIVE_H__
#define __DETECTIVE_H__

#include "villager.hpp"

class Detective : public Villager
{
	public:
		void setSuspect(std::string s){
			suspect = s;
		}
		std::string getSuspect(){
			return suspect;
		}
	private:
		std::string suspect = "-";
};

#endif