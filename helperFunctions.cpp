#include <iostream>
#include <vector>
#include <string>
#include "helperFunctions.hpp"

using namespace std;

vector<string> extractWords( const string &str )
{
	vector<string> result;
    string::size_type start = 0;
    string::size_type found = str.find(' ', start);

    while (found != string::npos){
        if (found > start)
        	result.push_back(str.substr(start, found - start));
        start = found + 1;
        found = str.find(' ', start);
    }
    result.push_back(str.substr(start));
    return result;
}

bool isNonNegativeInt(const string& str)
{
    for(int i=0; i < str.size(); i++){
        if( str[i] < '0' || str[i] > '9' )
            return false;
    }
    return true;
}