/**
 * @file        Block.h
 * @author      [Your Name]
 * @date        April 2025
 * @brief       Header file for the Block structure in a simple blockchain implementation.
 * 
 * This file defines the data structure for a blockchain block, including its
 * hash, previous hash, Merkle root, and list of transactions. The block supports
 * basic functionality such as computing the hash and generating the Merkle root.
 * 
 * Project:     Simple Blockchain for Cybersecurity Course
 * University:  University of Houston
 */

#include "BlockChain.h"


int main(){
    const int max_tx_amount = 10;

    // global parameters
    std::cout << "GLOBAL PARAMETER" << std::endl;
    std::cout << " - Transaction size in one Block:\t" <<  TRANSACTION_BLOCK_SIZE << std::endl;
    std::cout << " - Mining difficulty (Mined Hash 0 leading length): \t" << MINE_DIFFICULTY << std::endl;
    coutln();

    // creating a transaction
    std::cout << "one signle transaction:" << std::endl;
    
    Transaction t {"Alice", "Bob", 5};
    
    t.print();
    coutln();
    
    
    // random transactions
    std::cout << "a single random transactions:" << std::endl;
    
    std::vector<std::string> names = {
        "Alice", "Bob", "Charlie", "Dave", "Eve",
        "Frank", "Grace", "Heidi", "Ivan", "Judy"
    };
    Transaction rt = get_random_transaction(names, max_tx_amount);

    rt.print();
    coutln();


    // making list of transactions for one Block
    std::cout << "list of random transaction for one Block" << std::endl;

    std::vector<Transaction> tx_list = random_tx_lst(names, max_tx_amount, TRANSACTION_BLOCK_SIZE);
    for (const auto &tx: tx_list) {
        tx.print();
    }
    coutln();


    // making one single Block
    std::cout << "making the first Block in the Chain using these Transactions" << std::endl;

    Block first_block {
        0,
        tx_list,
        "0000000000000000000000000000000000000000000000000000000000000000"
    };

    double exe_time = first_block.mine_block();
    
    std::cout << "the mined Block:" << std::endl;
    first_block.print();
    std::cout << "mining time: " << exe_time << "s" << std::endl;
    coutln();


    // pusing this block to BlockChain
    std::cout << "adding this block to the BlockChain as first Block!" << std::endl;
    BlockChain chain;

    chain.add_block(first_block);
    chain.print();
    coutln();


    // adding 9 more blocks to the BlockChain
    std::cout << "adding 9 more Blocks to the BlockChain" << std::endl;
    
    for (int index=1; index<10; index++){
        std::vector<Transaction> tx_list;
        Block block {
            index,
            random_tx_lst(names, max_tx_amount, TRANSACTION_BLOCK_SIZE),
            chain.get_last_hash(),
        };

        double exetime = block.mine_block();
        chain.add_block(block);

        std::cout << " - Block [" << index << "] mined in " << exetime << "s" << std::endl;
    }
    coutln();

    std::cout << "Chain with size of 10 Block:" << std::endl;
    chain.print();
    coutln();



    // manipulating explanation
    std::cout << "Making modifications in each part of the BlockChain will violate the Chain Validation" << std::endl;

    std::cout << "Example:" << std::endl;

    std::cout << "\n - replacing one transaction in Block[5] with a random transaction" << std::endl;
    chain.blocks[5].transactions[0] = get_random_transaction(names, max_tx_amount);
    std::cout << "#? Invalidity Reasoning: \n" << chain.invalidity_reason() << std::endl;


    std::cout << "\n - Lets calculate the MarkleRoot Hash" << std::endl;
    chain.blocks[5].markle_root = chain.blocks[5].get_markle_root();
    std::cout << "#? Invalidity Reasoning: \n" << chain.invalidity_reason() << std::endl;

    std::cout << "\n - Lets calculate the Block Hash (We do need to Mine the Block as the Hash Itself should be valid)" << std::endl;
    chain.blocks[5].mine_block();
    std::cout << "#? Invalidity Reasoning: \n" << chain.invalidity_reason() << std::endl;
    std::cout << "WHAT TO DO? We need to Mine all the Blocks after this which is computationally impossible" << std::endl;


    return 0;
}