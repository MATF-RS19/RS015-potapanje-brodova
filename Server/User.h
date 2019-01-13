//
// Created by Nikola on 6.1.19..
//

#ifndef SERVER_USER_H
#define SERVER_USER_H


#include <string>

class User {
private:
    std::string name, secret;
    time_t lastActive;

public:
    User(std::string _name);

    void updateLastActive();

    bool timedOut();

    bool operator==(const User &rhs) const;

    bool operator!=(const User &rhs) const;

    const std::string &getName() const;

    const std::string &getSecret() const;
};


#endif //SERVER_USER_H
