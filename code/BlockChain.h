#include "Block.h"

class BlockChain
{
private:
    
public:
    std::vector<Block> blocks;

    BlockChain();
    ~BlockChain();

    void add_block(Block block) {
        if (block.index != blocks.size()) 
            throw std::runtime_error("block index is incorrect, and it should be continuous");

        if (not block.is_valid())
            throw std::runtime_error("invalid block can not be added to the chain");
        
        if (blocks.size() > 0)
            if (block.last_hash != blocks[blocks.size()-1].block_hash)
                throw std::runtime_error("last_hash is not compatible with chain last hash");

        blocks.push_back(block);
    }

    std::string get_last_hash() {
        return blocks[blocks.size() - 1].block_hash;
    }

    bool is_valid() const {
        for (size_t i=0; i<blocks.size(); i++) {
            if (not blocks[i].is_valid())
                return false;
            
            if (i > 0)
                if (blocks[i].last_hash != blocks[i-1].block_hash)
                    return false;
        }
        return true;
    }

    std::string invalidity_reason() const {
        std::stringstream reason;

        for (size_t index=0; index < blocks.size(); index++) {
            if (index > 0)
                if(blocks[index].last_hash != blocks[index - 1].block_hash)
                    reason << " - Block [" << index << "] is not following the Block[" << index-1 << "] Hash \n";
            
            const Block &block = blocks[index];
            if (not block.is_valid()) {
                reason << " - Block [" << index << "] Hash is an invalid Hash (as the content is altered) \n";

                if (block.markle_root != block.get_markle_root())
                    reason << " - Block [" << index << "] invalid MerkleRoot (as Transactions are altered) \n";

                if (not block.is_hash_lead())
                    reason << " - Block [" << index << "] Hash is not leading with zero \n";
            }

        }

        return reason.str();
    }

    void print() const {
        using namespace std;
        cout << "Chain size:\t" << blocks.size() << endl;
        cout << "Is Valid:\t" << (is_valid() ? "TRUE" : "FALSE") << endl;
        cout << "Chain Hash sequence:\t" << endl;
        for (const Block& block : blocks)
            cout << " - " << block.last_hash << " -> " << block.block_hash << endl;
    }
};

BlockChain::BlockChain()
{
}

BlockChain::~BlockChain()
{
}
