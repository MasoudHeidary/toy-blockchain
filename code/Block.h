#include "Transaction.h"
#include "hash.h"
#include <ctime>
#include <vector>
#include <random>
#include <chrono>

#define TRANSACTION_BLOCK_SIZE 10
#define MINE_DIFFICULTY 5

class Block {

public:
    int index;
    time_t timestamp;
    std::vector<Transaction> transactions;
    std::string last_hash;
    std::string markle_root;
    std::string block_hash;
    long nonce;

    Block(int idx, std::vector<Transaction> txs, std::string prev)
        : index(idx), transactions(txs), last_hash(prev), nonce(0)
    {
        if (txs.size() != TRANSACTION_BLOCK_SIZE)
            throw "wrong transaction size";

        markle_root = get_markle_root();
    }

    std::string get_markle_root() const {
        std::stringstream s;
        for(const auto& t: transactions)
            s << sha256(t.to_string());
        return sha256(s.str());
    }

    std::string get_block_hash() const {
        std::stringstream s;
        s << index << timestamp << markle_root << last_hash << nonce;
        return sha256(s.str());
    }

    double mine_block() {
        auto _start_time = std::chrono::high_resolution_clock::now();

        do {
            nonce++;
            block_hash = get_block_hash();
        } while (not is_hash_lead());

        auto _end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(_end_time - _start_time);
        return duration.count();
    }

    // Block Hash starting with n '0's
    bool is_hash_lead() const {
        std::string leadzero(MINE_DIFFICULTY, '0');
        return (block_hash.substr(0, MINE_DIFFICULTY) == leadzero);
    }

    bool is_valid() const {
        if (markle_root != get_markle_root())
            return false;

        if (block_hash != get_block_hash())
            return false;

        if (not is_hash_lead())
            return false;
        
        return true;
    }

    void print() const {
        using namespace std;
        cout << "Block #" << index << endl;
        cout << "Timestamp: " << timestamp << endl;
        cout << "Previous Hash: " << last_hash << endl;
        cout << "Merkle Root: " << markle_root << endl;
        cout << "Nonce: " << nonce << endl;
        cout << "Block Hash: " << block_hash << endl;
        cout << "Is Valid: " << (is_valid() ? "TRUE" : "FALSE") << endl;
        cout << "Transactions: " << endl;
        for (auto& tx : transactions)
            cout << "  - " << tx.to_string() << endl;
    }
};
