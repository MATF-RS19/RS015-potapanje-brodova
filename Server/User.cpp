//
// Created by Nikola on 6.1.19..
//

#include "User.h"

User::User(std::string _name) {
    name = std::move(_name);
    secret = "test"; // TODO random string
}

bool User::operator==(const User &rhs) const {
    return name == rhs.name &&
           secret == rhs.secret;
}

bool User::operator!=(const User &rhs) const {
    return !(rhs == *this);
}
