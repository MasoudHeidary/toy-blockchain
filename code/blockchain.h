#include "Block.h"

class BlockChain
{
private:
    
public:
    std::vector<Block> chain;

    BlockChain();
    ~BlockChain();

    void add_block(Block block) {
        if (not block.is_valid())
            throw "invalid block can not be added to the chain";
        
        if (chain.size() > 0)
            if (block.last_hash != chain[chain.size()-1].block_hash)
                throw "last_hash is not compatible with chain last hash";

        chain.push_back(block);
    }

    bool is_valid() const {
        for (size_t i=0; i<chain.size(); i++) {
            if (not chain[i].is_valid())
                return false;
            
            if (i > 0)
                if (chain[i].last_hash != chain[i-1].block_hash)
                    return false;
        }
        return true;
    }

    void print() const {
        using namespace std;
        cout << "Size: " << chain.size() << endl;
        cout << "Is Valid: " << (is_valid() ? "TRUE" : "FALSE") << endl;
        cout << "Hash Chain: " << endl;
        for (const Block& block : chain)
            cout << block.last_hash << " -> " << block.block_hash << endl;
        cout << "-----------------------------" << endl;
    }
};

BlockChain::BlockChain()
{
}

BlockChain::~BlockChain()
{
}
