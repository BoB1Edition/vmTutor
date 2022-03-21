#include "Tools.h"

static std::string* SplitString(std::string &str, const char delimetr) {
    int count = 0;
    for(int i=0; i<str.size(); i++) {
        if(str[i] == delimetr) count++;
    }
    std::string *strings=new std::string[count+1];
    std::string tmp="";
    int j=0;
    for(int i=0; i<str.size(); i++) {
        if(str[i] == delimetr || i == str.size()) {
            strings[j]=tmp;
            j++;
            continue;
        }
        tmp+=tmp+str[i];
    }
    return strings;
}