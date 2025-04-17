#include "tool.h"

#include <sstream>
#include <random>

struct Transaction
{
    std::string sender;
    std::string receiver;
    double amount;

    std::string to_string() const {
        std::stringstream s;
        s << sender << " -> " << receiver << ": " << amount;
        return s.str();
    }

    void print() const {
        std::cout << to_string() << std::endl;
    }
};




Transaction get_random_transaction(const std::vector<std::string> &names, const int max_amount) {

    static std::mt19937 rng(static_cast<unsigned int>(time(nullptr)));
    std::uniform_int_distribution<> nameIndex(0, names.size() - 1);
    std::uniform_real_distribution<> amountDist(0.0, max_amount);

    std::string sender, receiver;
    sender = names[nameIndex(rng)];
    receiver = names[nameIndex(rng)];

    double amount = std::round(amountDist(rng) * 100.0) / 100.0; // round to 2 decimal places

    return {sender, receiver, amount};
}


