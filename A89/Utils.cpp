#include "Utils.h"
#include <sstream>
#include <string>
#include <vector>


using namespace std;

std::string trim(const std::string& stringToTrim) //removes leading and trailing whitespaces
{
	string result(stringToTrim);
	size_t position = result.find_first_not_of(" ");
	if (position != -1)
		result.erase(0, position);
	position = result.find_last_not_of(" ");
	if (position != std::string::npos)
		result.erase(position + 1);
	return result;
}

std::vector<std::string> tokenize(const std::string& stringToTokenize, char delimiter)  //splits a string into a vector of strings
{
	vector<string> result;
	stringstream ss(stringToTokenize);
	string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);
	return result;
}
