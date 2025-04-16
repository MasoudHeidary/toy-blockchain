#include "Transaction.h"
#include "hash.h"
#include <ctime>
#include <vector>
#include <random>

#define TRANSACTION_BLOCK_SIZE 10
#define MINE_DIFFICULTY 6

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

    void mine_block() {
        std::string leadzero(MINE_DIFFICULTY, '0');
        std::string hash;

        do {
            nonce++;
            timestamp = time(nullptr);

            hash = get_block_hash();
        } while (hash.substr(0, MINE_DIFFICULTY) != leadzero);
        
        block_hash = hash;
    }

    void print() const {
        using namespace std;
        cout << "Block #" << index << endl;
        cout << "Timestamp: " << timestamp << endl;
        cout << "Previous Hash: " << last_hash << endl;
        cout << "Merkle Root: " << markle_root << endl;
        cout << "Nonce: " << nonce << endl;
        cout << "Block Hash: " << block_hash << endl;
        cout << "Transactions: " << endl;
        for (auto& tx : transactions)
            cout << "  - " << tx.to_string() << endl;
        cout << "-----------------------------" << endl;
    }
};