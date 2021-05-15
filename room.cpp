#include <iostream>
#include <ctime>
#include <algorithm>
#include "room.hpp"
#include "game.hpp"
#include "exceptions.hpp"

using namespace std;

Room::Room(string n, map<string, int> roles)
{
	name = n;
	addRoles(roles);
	for (int i = 0; i < villagers.size(); i++)
		players.push_back(villagers[i]);
	for (int i = 0; i < detectives.size(); i++)
		players.push_back(detectives[i]);
	for (int i = 0; i < doctors.size(); i++)
		players.push_back(doctors[i]);
	for (int i = 0; i < rouins.size(); i++)
		players.push_back(rouins[i]);
	for (int i = 0; i < mafias.size(); i++)
		players.push_back(mafias[i]);
	for (int i = 0; i < godFathers.size(); i++)
		players.push_back(godFathers[i]);
	for (int i = 0; i < silencers.size(); i++)
		players.push_back(silencers[i]);
	for (int i = 0; i < jokers.size(); i++)
		players.push_back(jokers[i]);
}

Room::~Room()
{	
	cerr << "in room destroctor"<<endl;
	for (int i = 0; i < players.size(); ++i)
		delete players[i];
}

void Room::addRoles(map<string, int> roles)
{
    map<string, int>::iterator itr; 
    for(itr = roles.begin(); itr != roles.end(); itr++){
	    if(itr->first == "Joker"){
	    	for (int i = 0; i < itr->second; i++){
	    		Joker* newPlayer = new Joker;
	        	jokers.push_back(newPlayer);
	    	}
	    }
	    else if(itr->first == "Villager"){
	    	for (int i = 0; i < itr->second; i++){
	    		Villager* newPlayer = new Villager;
	            villagers.push_back(newPlayer);
	            allVillagers.push_back(newPlayer);
	    	}
	    }
	    else if(itr->first == "Detective"){
	    	for (int i = 0; i < itr->second; i++){
	    		Detective* newPlayer = new Detective;
	        	detectives.push_back(newPlayer);
	            allVillagers.push_back(newPlayer);
	    	}
	    }
	    else if(itr->first == "Doctor"){
	    	for (int i = 0; i < itr->second; i++){
	    		Doctor* newPlayer = new Doctor;
	        	doctors.push_back(newPlayer);
	            allVillagers.push_back(newPlayer);
	    	}
	    }
	    else if(itr->first == "RouinTan"){
	    	for (int i = 0; i < itr->second; i++){
	    		Rouin* newPlayer = new Rouin;
	        	rouins.push_back(newPlayer);
	            allVillagers.push_back(newPlayer);
	    	}
	    }
	    else if(itr->first == "Mafia"){
	    	for (int i = 0; i < itr->second; i++){
	    		Mafia* newPlayer = new Mafia;
	        	mafias.push_back(newPlayer);
	        	allMafias.push_back(newPlayer);
	    	}
	    }
	    else if(itr->first == "GodFather"){
	    	for (int i = 0; i < itr->second; i++){
	    		GodFather* newPlayer = new GodFather;
	       		godFathers.push_back(newPlayer);
	        	allMafias.push_back(newPlayer);
	       	}
	    }    
	    else if(itr->first == "Silencer"){
	    	for (int i = 0; i < itr->second; i++){
	    		Silencer* newPlayer = new Silencer;
	       		silencers.push_back(newPlayer);
	        	allMafias.push_back(newPlayer);
	       	}
	    }
	    else
	        throw RoleException();
	}
}

void Room::printRoomState()
{
	cout << "Mafia = " << allMafias.size() << endl;
	cout << "Villager = " << allVillagers.size() << endl;
}

void Room::addUsers(const vector<string>& commandWords)
{
	if(players.size() >= (alivePlayerNames.size() + deadPlayerNames.size() + commandWords.size()-1)){
		for(int i = 1; i < commandWords.size(); i++){
			if(isRepeatedName(commandWords[i]))
				throw RepetitiveNameException();
		}
		for(int i = 1; i < commandWords.size(); i++)
			alivePlayerNames.push_back(commandWords[i]);
	}
	else
		throw RoomFullException();
	if(alivePlayerNames.size() == players.size()){
		this->assignRoles(alivePlayerNames);
		cout << "Day " << dayNum <<endl;
		isDay = true;
	}
}

bool Room::isRepeatedName(string newName)
{
	for(int i = 0; i < alivePlayerNames.size(); i++){
		if(newName == alivePlayerNames[i])
			return true;
	}
	return false;
}

void Room::endDay()
{
	if (!isDay)
		throw InputException();
	cout << "Died " << this->voteResult(players)->getName() << endl;
	cout << "Night " << nightNum << endl;
	dayNum++;
	isDay = false;
	for (int i = 0; i < players.size(); i++){
		players[i]->setVote("-");
		players[i]->setImmortal(false);
		players[i]->setSilent(false);
	}
}

void Room::endNight()
{
	if(isDay)
		throw InputException();
	cout << "Day" << dayNum << endl;
	if(!killChosen->getImmortal())
		killChosen->decreaseLife();
	if(killChosen->getLife() == 0){
		cout << "Killed " << killChosen->getName() << endl;
		killPlayer(killChosen);
	}
	if(silencers.size() != 0){
		cout << "Silenced";
		vector<string> sortedVictims;
		for(int i = 0; i < silencers.size(); i++)
			sortedVictims.push_back(silencers[i]->getVictim());
		sort(sortedVictims.begin(), sortedVictims.end());
		sortedVictims.erase( unique( sortedVictims.begin(), sortedVictims.end() ), sortedVictims.end() );
		for(int i = 0; i < sortedVictims.size(); i++)
			cout << " " << sortedVictims[i];
	}
	cout << endl;
	nightNum++;
	isDay = true;
	timeStage = VOTE_TIME;
	for(int i = 0; i < players.size(); i++)
		players[i]->setVote("-");
	for(int i = 0; i < detectives.size(); i++)
		detectives[i]->setSuspect("-");
	for(int i = 0; i < doctors.size(); i++)
		doctors[i]->setPatient("-");
	for(int i = 0; i < silencers.size(); i++)
		silencers[i]->setVictim("-");
}

void Room::killPlayer(Player* deadPlayer)
{
	deadPlayerNames.push_back(deadPlayer->getName());

	for (int i = 0; i < alivePlayerNames.size(); i++)
		if(deadPlayer->getName() == alivePlayerNames[i])
			alivePlayerNames.erase(alivePlayerNames.begin() + i);

	for (int i = 0; i < mafias.size(); i++)
		if(deadPlayer->getName() == mafias[i]->getName())
			mafias.erase(mafias.begin() + i);
	for (int i = 0; i < jokers.size(); i++)
		if(deadPlayer->getName() == jokers[i]->getName()){
			if(!isDay)
				jokers.erase(jokers.begin() + i);
			else{
				cout << "Do I look like a guy with a plan?" <<endl;
				endGame = true;
			}
		}
	for (int i = 0; i < villagers.size(); i++)
		if(deadPlayer->getName() == villagers[i]->getName())
			villagers.erase(villagers.begin() + i);
	for (int i = 0; i < doctors.size(); i++)
		if(deadPlayer->getName() == doctors[i]->getName())
			doctors.erase(doctors.begin() + i);
	for (int i = 0; i < detectives.size(); i++)
		if(deadPlayer->getName() == detectives[i]->getName())
			detectives.erase(detectives.begin() + i);
	for (int i = 0; i < rouins.size(); i++)
		if(deadPlayer->getName() == rouins[i]->getName())
			rouins.erase(rouins.begin() + i);
	for (int i = 0; i < godFathers.size(); i++)
		if(deadPlayer->getName() == godFathers[i]->getName())
			godFathers.erase(godFathers.begin() + i);
	for (int i = 0; i < silencers.size(); i++)
		if(deadPlayer->getName() == silencers[i]->getName())
			silencers.erase(silencers.begin() + i);

	for (int i = 0; i < allMafias.size(); i++)
		if(deadPlayer->getName() == allMafias[i]->getName())
			allMafias.erase(allMafias.begin() + i);	
	for (int i = 0; i < allVillagers.size(); i++)
		if(deadPlayer->getName() == allVillagers[i]->getName())
			allVillagers.erase(allVillagers.begin() + i);	

	for (int i = 0; i < players.size(); i++)
		if(deadPlayer->getName() == players[i]->getName())
			players.erase(players.begin() + i);
	
	checkGameResult();
}

void Room::dayVote(string voterName, string voteeName)
{
	for (int i = 0; i < players.size(); i++)
		if (voterName == players[i]->getName())
		{
			if (!(players[i]->getSilent())){
				checkSetVote(players[i], voteeName);
				return;
			}
			else
				throw SilencedBeforeException();
		}
	throw UnjoinedPlayerException();
}

void Room::nightVote(string voterName, string voteeName)
{
	bool found = false;
	for (int i = 0; i < allMafias.size(); i++)
		if (voterName == allMafias[i]->getName()){
			checkSetVote(allMafias[i], voteeName);
			found = true;
		}
	if(!found)
		throw UnMafiaVoteException();
	if(allMafiasVoted()){
		killChosen = this->voteResult(allMafias);
		cout << "Mafia try to kill " << killChosen->getName() << endl;
		if(detectives.size() != 0)
			timeStage = DETECT_TIME;
		else if(doctors.size() != 0)
			timeStage = HEAL_TIME;
		else if(silencers.size() != 0)
			timeStage = SILENT_TIME;
		else
			endNight();
	}
}

Player* Room::voteResult(vector<Player*> voters)
{
	vector<int> voteNums;
	int max = 0;
	int maxVotee = 0;
	for(int i = 0; i < players.size(); i++)	
		voteNums.push_back(0);
	for(int i = 0; i < voters.size(); i++)
		for(int j = 0; j < players.size(); j++)
			if (voters[i]->getVote() == players[j]->getName())
				voteNums[j]++;
	for(int i = 0; i < voteNums.size(); i++)
	{
		if(voteNums[i] >= max)
		{
			max = voteNums[i];
			maxVotee = i;
		}
	}
	return players[maxVotee];
}

void Room::assignRoles(vector<string> names)
{
	int randNum;
	srand (time(NULL));
	for (int i = 0; i < players.size() ; i++){
		randNum = rand() % (names.size());
		players[i]->setName(names[randNum]);
		names.erase(names.begin() + randNum);
	}
}

bool Room::allMafiasVoted()
{
	for (int i = 0; i < allMafias.size(); i++)
		if (allMafias[i]->getVote() == "-")
			return false;
	return true;
}

bool Room::checkGameResult()
{
	if(allMafias.size() == 0){
		cout << "Victory!" << endl;
		endGame = true;
	}
	if(allVillagers.size() <= allMafias.size()){
		cout << "Loose!" << endl;
		endGame = true;
	}
}

void Room::checkSetVote(Player* voter, string voteeName)
{
	for (int i = 0; i < players.size(); i++)
		if (voteeName == players[i]->getName()){
			voter->setVote(voteeName);
			return;
		}
	for (int i = 0; i < deadPlayerNames.size(); i++)
		if (voteeName == deadPlayerNames[i]){
			throw DeadUserException();
		}
	throw UnjoinedPlayerException();
}

void Room::detect(string ditectiveName, string suspectName)
{
	bool found = false;
	for (int i = 0; i < detectives.size(); i++)
		if (ditectiveName == detectives[i]->getName())
		{
			if(detectives[i]->getSuspect() == "-"){
				checkSetSuspect(detectives[i], suspectName);
				cout << suspectState(suspectName) << endl;
				found = true;
			}
			else
				throw RepetitiveDetectiveException();
		}
	if(!found)
		throw NotDetectiveException();
	if(allDetectivesVoted()){
		if(doctors.size() != 0)
			timeStage = HEAL_TIME;
		else if(silencers.size() != 0)
			timeStage = SILENT_TIME;
		else
			endNight();
	}
}

void Room::heal(string doctorName, string patientName)
{
	bool found = false;
	for (int i = 0; i < doctors.size(); i++)
		if (doctorName == doctors[i]->getName())
		{
			if(doctors[i]->getPatient() == "-"){
				checkSetPatient(doctors[i], patientName);
				findPlayer(patientName)->setImmortal(true);
				found = true;
			}
			else
				throw RepetitiveDoctorException();
		}
	if(!found)
		throw NotDoctorException();
	if(allDoctorsVoted()){
		if(silencers.size() != 0)
			timeStage = SILENT_TIME;
		else
			endNight();
	}
}

void Room::silent(string silencerName, string victimName)
{
	bool found = false;
	for (int i = 0; i < silencers.size(); i++)
		if (silencerName == silencers[i]->getName())
		{
			if(silencers[i]->getVictim() == "-"){
				checkSetVictim(silencers[i], victimName);
				findPlayer(victimName)->setSilent(true);
				found = true;
			}
			else
				throw RepetitiveSilencerException();
		}
	if(!found)
		throw NotSilencerException();
	if(allSilencersVoted()){
		endNight();
	}
}

void Room::checkSetSuspect(Detective* voter, string name)
{
	for (int i = 0; i < players.size(); i++)
		if (name == players[i]->getName()){
			voter->setSuspect(name);
			return;
		}
	for (int i = 0; i < deadPlayerNames.size(); i++)
		if (name == deadPlayerNames[i]){
			throw DeadPersonException();
		}
	throw UnjoinedPlayerException();
}

void Room::checkSetPatient(Doctor* voter, string name)
{
	for (int i = 0; i < players.size(); i++)
		if (name == players[i]->getName()){
			voter->setPatient(name);
			return;
		}
	for (int i = 0; i < deadPlayerNames.size(); i++)
		if (name == deadPlayerNames[i]){
			throw DeadPersonException();
		}
	throw UnjoinedPlayerException();
}

void Room::checkSetVictim(Silencer* voter, string name)
{
	for (int i = 0; i < players.size(); i++)
		if (name == players[i]->getName()){
			voter->setVictim(name);
			return;
		}
	for (int i = 0; i < deadPlayerNames.size(); i++)
		if (name == deadPlayerNames[i]){
			throw DeadPersonException();
		}
	throw UnjoinedPlayerException();
}

Player* Room::findPlayer(string name)
{
	for(int i=0; i < players.size(); i++)
		if(players[i]->getName() == name)
			return players[i];
	throw UnjoinedPlayerException();
}

string Room::suspectState(string suspectName)
{
	for(int i=0; i < mafias.size(); i++)
		if(mafias[i]->getName() == suspectName)
			return "Yes";
	for(int i=0; i < silencers.size(); i++)
		if(silencers[i]->getName() == suspectName)
			return "Yes";
	return "No";
}

bool Room::allDetectivesVoted()
{
	for (int i = 0; i < detectives.size(); i++)
		if (detectives[i]->getSuspect() == "-")
			return false;
	return true;
}

bool Room::allDoctorsVoted()
{
	for (int i = 0; i < doctors.size(); i++)
		if (doctors[i]->getPatient() == "-")
			return false;
	return true;	
}

bool Room::allSilencersVoted()
{
	for (int i = 0; i < silencers.size(); i++)
		if (silencers[i]->getVictim() == "-")
			return false;
	return true;	
}