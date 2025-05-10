#include "tool.h"
#include <string>

Tool::Tool() {}
bool Tool::search(std::string goal,std::string base){
    int goalL=goal.length(),baseL=base.length();
    for(int i=0;i<baseL-goalL+1;i++){
        if(base.substr(i,goalL)==goal)
            return true;
        else
            continue;
    }
    return false;
}
bool Tool::isNumber(int length,std::string base){
    for(int i=0;i<length;i++){
        if(base[i]>='0'&&base[i]<='9')
            continue;
        else
            return false;
    }
    return true;
}
