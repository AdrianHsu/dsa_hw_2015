#ifndef HASHNODE_H
#define HASHNODE_H

#include <string>
typedef unsigned int longint;
using namespace std; //std::string

class HashNode {

public:
	HashNode(){}
	longint& getElement(const int i);
	void setKey(const string k){ _key = k;}
	void setURL(const string s){ DisplayURL = s;}
	string& getKey(){return _key;}
	string& getURL(){return DisplayURL;}

protected:
	string _key;
	string DisplayURL;

	longint Click;
	longint Impression;
	longint AdID;
	longint AdvertiserID;
	longint Depth;
	longint Position;
	longint QueryID;
	longint KeywordID;
	longint TitleID;
	longint DescriptionID;
	longint UserID;
};
#endif