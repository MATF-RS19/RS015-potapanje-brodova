//
// Created by Nikola on 6.1.19..
//

#include "User.h"
#include "Helper.h"

User::User(std::string _name) {
    name = std::move(_name);
    secret = Helper::getRandomString(10);
}

bool User::operator==(const User &rhs) const {
    return name == rhs.name &&
           secret == rhs.secret;
}

bool User::operator!=(const User &rhs) const {
    return !(rhs == *this);
}

const std::string &User::getName() const {
    return name;
}

const std::string &User::getSecret() const {
    return secret;
}
