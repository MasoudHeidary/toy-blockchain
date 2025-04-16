#include <iostream>
#include <sstream>

struct Transaction
{
    std::string sender;
    std::string receiver;
    double amount;

    std::string to_string() const {
        std::stringstream s;
        s << sender << "@" << receiver << ":" << amount;
        return s.str();
    }
};




