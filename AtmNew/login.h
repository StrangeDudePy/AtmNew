#ifndef LOGIN_H
#define LOGIN_H

#include <string>
using namespace std;



class signupmenu {
public:
    signupmenu();

    string removeSpaces(const std::string& str);

    string getName();

    string formatName(const std::string& input);

    bool is_digits(const std::string& str);

    int getID();

    string getPassword();

    int newuser();
};



#endif
