#include <iostream>
#include "game.hpp"
#include "helperFunctions.hpp"
#include "exceptions.hpp"

using namespace std;

Game::~Game()
{
	for(int i=0; i < rooms.size(); i++)
		delete rooms[i];
}

void Game::playGame()
{
	string commandLine;
	while(getline(cin, commandLine))
	{	
		vector<string> commandWords = extractWords(commandLine);
		try{
			chooseAction(commandWords);
		}
		catch(InvalidRoomException){
			cout << "Invalid room name" << endl;
		}
		catch(RoleException){
			cout << "Invalid role" << endl;
		}
		catch(RepetitiveNameException){
			cout << "Invalid command, one of the usernames already exist." << endl;
		}
		catch(RoomFullException){
			cout << "many users" << endl;
		}
		catch(UnjoinedPlayerException){
			cout << "User not joined" << endl;
		}	
		catch(SilencedBeforeException){
			cout << "This user has been silenced before" << endl;
		}
		catch(DeadUserException){
			cout << "User already died" << endl;
		}
		catch(UnMafiaVoteException){
			cout << "This user can not vote" << endl;
		}
		catch(DeadPersonException){
			cout << "Person is dead" << endl;
		}	
		catch(RepetitiveDetectiveException){
			cout << "Detective has already asked" << endl;
		}	
		catch(NotDetectiveException){
			cout << "User can not ask" << endl;
		}		
		catch(RepetitiveDoctorException){
			cout << "Doctor has already healed" << endl;
		}	
		catch(NotDoctorException){
			cout << "User can not heal" << endl;
		}	
		catch(RepetitiveSilencerException){
			cout << "Silencer has already silenced" << endl;
		}	
		catch(NotSilencerException){
			cout << "User can not silence" << endl;
		}		
		catch(InputException){
			cout << "Invalid Command" << endl;
		}
	}
}

Room* Game::createRoom(vector<string>& commandWords)
{ 
	if(commandWords.size() % 2 == 1)
        throw InputException();
    for(int i = FIRST_NUM; i < commandWords.size(); i+=2 )
	    if(!isNonNegativeInt(commandWords[i]))
	       throw InputException();
	map<string, int> theRoles;
	for(int i = FIRST_ROLE; i < commandWords.size(); i+=2 ){
		if(commandWords[i][0] != '-')
   			throw InputException();
   		else{
   			commandWords[i].erase(commandWords[i].begin());
            theRoles.insert(pair<string, int>(commandWords[i], stoi(commandWords[i+1]))); 
        }        
   	}
	for(int i=0; i < rooms.size(); i++)
		if(rooms[i]->getName() == commandWords[ROOM_NAME])
			throw InvalidRoomException();
	Room* theRoom = new Room(commandWords[ROOM_NAME],theRoles);
	rooms.push_back(theRoom);
	return theRoom;
}

Room* Game::findRoom(const string& name)
{
	for(int i=0; i < rooms.size(); i++)
		if(rooms[i]->getName() == name)
			return rooms[i];
	throw InvalidRoomException();
}

void Game::chooseAction(vector<string>& commandWords)
{
	if(commandWords[0] == "Create_room")
		currentRoom = createRoom(commandWords);
	else if(commandWords[0] == "Switch_room" && commandWords.size() == SWITCH_INPUTS_NUM)
			currentRoom = findRoom(commandWords[ROOM_NAME]);
	else if(commandWords[0] == "Get_room_state" && commandWords.size() == STATE_INPUTS_NUM)
			currentRoom->printRoomState();
	else if(commandWords[0] == "Join")
			currentRoom->addUsers(commandWords);
	else if(commandWords[0] == "Vote" && commandWords.size() == VOTE_INPUTS_NUM && currentRoom->getTimeStage() == VOTE_TIME)
	{
		if(currentRoom->getIsDay()/*join complete*/)
			currentRoom->dayVote(commandWords[1], commandWords[2]);
		else
			currentRoom->nightVote(commandWords[1], commandWords[2]);
	}
	else if(commandWords[0] == "End_vote" && commandWords.size() == END_INPUTS_NUM)
		currentRoom->endDay();
	else if(commandWords[0] == "Detect" && commandWords.size() == ASK_INPUTS_NUM && currentRoom->getTimeStage() == DETECT_TIME)
		currentRoom->detect(commandWords[1], commandWords[2]);
	else if(commandWords[0] == "Heal" && commandWords.size() == ASK_INPUTS_NUM && currentRoom->getTimeStage() == HEAL_TIME)
		currentRoom->heal(commandWords[1], commandWords[2]);
	else if(commandWords[0] == "Silent" && commandWords.size() == ASK_INPUTS_NUM && currentRoom->getTimeStage() == SILENT_TIME)
		currentRoom->silent(commandWords[1], commandWords[2]);
	else
		throw InputException();

	for(int i=0; i < rooms.size(); i++)
		if(rooms[i]->getEndGame()){
			delete rooms[i];
			rooms.erase(rooms.begin() + i);
		}
}