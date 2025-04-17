// #include "Transaction.h"
#include "Block.h"



int main(){
    const int max_tx_amount = 10;

    // creating a transaction
    std::cout << "one signle transaction:" << std::endl;
    
    Transaction t {"Alice", "Bob", 5};
    
    t.print();
    coutln();


    // random transactions
    std::cout << "one random transaction:" << std::endl;
    
    std::vector<std::string> names = {
        "Alice", "Bob", "Charlie", "Dave", "Eve",
        "Frank", "Grace", "Heidi", "Ivan", "Judy"
    };
    Transaction rt = get_random_transaction(names, max_tx_amount);

    rt.print();
    coutln();


    // making list of transactions for one Block
    std::cout << "list of random transaction for one Block" << std::endl;

    std::vector<Transaction> tx_list;
    for (int i=0; i<TRANSACTION_BLOCK_SIZE; i++) {
        Transaction t = get_random_transaction(names, max_tx_amount);
        tx_list.push_back(t);

        std::cout << "trasaction [" << i << "]: " << t.to_string() << std::endl;
    }
    coutln();

    // making one single Block
    std::cout << "making the first Block in the Chain using these Transactions" << std::endl;

    Block block {
        0,
        tx_list,
        "0000000000000000000000000000000000000000000000000000000000000000"
    };

    double exe_time = block.mine_block();
    
    std::cout << "the mined Block:" << std::endl;
    block.print();
    std::cout << "mining time: " << exe_time << "s" << std::endl;
    coutln();

    

    return 0;
}