#include "Transaction.h"
#include "hash.h"
#include <ctime>
#include <vector>

#define TRANSACTION_BLOCK_SIZE 10

class Block {

public:
    int index;
    time_t timestamp;
    std::vector<Transaction> transactions;
    std::string last_hash;
    std::string markle_root;
    std::string block_hash;
    int nonce;

    Block(int idx, std::vector<Transaction> txs, std::string prev)
        : index(idx), transactions(txs), last_hash(prev), nonce(0)
    {
        if (txs.size() != TRANSACTION_BLOCK_SIZE)
            throw "wrong transaction size";

        timestamp = time(nullptr);
        markle_root = get_markle_root();
        // hash = mineBlock();
    }

    std::string get_markle_root() const {
        std::stringstream s;
        for(const auto& t: transactions)
            s << sha256(t.to_string());
        return sha256(s.str());
    }

};