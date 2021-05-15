#ifndef __HELPER_H__
#define __HELPER_H__

#include <vector>
#include <string>

#define FIRST_NUM 3
#define FIRST_ROLE 2
#define ROOM_NAME 1

#define SWITCH_INPUTS_NUM 2
#define STATE_INPUTS_NUM 1
#define END_INPUTS_NUM 1
#define VOTE_INPUTS_NUM 3
#define ASK_INPUTS_NUM 3

#define VOTE_TIME 0
#define DETECT_TIME 1
#define HEAL_TIME 2
#define SILENT_TIME 3

std::vector<std::string> extractWords( const std::string &str );
bool isNonNegativeInt(const std::string& str);

#endif