#ifndef __DOCTOR_H__
#define __DOCTOR_H__

#include "villager.hpp"

class Doctor : public Villager
{
	public:
		void setPatient(std::string s){
			patient = s;
		}
		std::string getPatient(){
			return patient;
		}
	private:
		std::string patient = "-";
};

#endif