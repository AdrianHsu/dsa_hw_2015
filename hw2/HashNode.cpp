#include "HashNode.h"

longint& HashNode::getElement(const int i) { //an easier way to access class members
    
    switch(i){ //protected members
    default:
    case  0:    return Click;
    case  1:    return Impression;
    //case  2:    return DisplayURL;
    case  3:    return AdID;
    case  4:    return AdvertiserID;
    case  5:    return Depth;
    case  6:    return Position;
    case  7:    return QueryID;
    case  8:    return KeywordID;
    case  9:    return TitleID;
    case 10:    return DescriptionID;
    case 11:    return UserID;
    }
}