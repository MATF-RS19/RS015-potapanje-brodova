//
// Created by Nikola on 6.1.19..
//

#ifndef SERVER_USER_H
#define SERVER_USER_H


#include <string>

class User {
private:
    std::string name, secret;

public:
    User(std::string _name);

    bool operator==(const User &rhs) const;

    bool operator!=(const User &rhs) const;
};


#endif //SERVER_USER_H
