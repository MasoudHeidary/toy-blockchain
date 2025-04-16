// #include "Transaction.h"
#include "Block.h"



int main(){

    // creating a transaction
    Transaction t {"Masoud", "Bob", 5};
    std::cout << t.to_string() << std::endl;


    std::vector<Transaction> t_list;
    for (int i=0; i<TRANSACTION_BLOCK_SIZE; i++)
        t_list.push_back(t);

    Block block {
        0,
        t_list,
        "0000000000000000000000000000000000000000000000000000000000000000"
    };

    std::cout << block.get_markle_root() << std::endl;

    return 0;
}