#include "stdafx.h"
#include <iostream>
#include <chrono>
#include "funkcijos.h"

int main() {

	
	Users useriai = New_Users(1000);
	//useriai.print_all_users();
	Transactions transakcijos = New_Transactions(10000,1000);
	//transakcijos.print_all_transactions();
	std::vector<std::string>block_name_history;
	BlockChain bc;
	int i = 0;

	while(i<9)
	{
		if (i == 0)
		{
			Block rez = Mining(3, "0", transakcijos.transfer_transactions(),block_name_history);
			bc.add_block(rez);
			block_name_history.push_back(bc.prev_block_hash_get(0));
		}
		else
		{
			Block rez = Mining(3, bc.prev_block_hash_get(i-1), transakcijos.transfer_transactions(),block_name_history);
			bc.add_block(rez);
			block_name_history.push_back(bc.prev_block_hash_get(i));
		}
		i++;
	}
	bc.print_all_blocks(transakcijos.get_num_of_transactions());
	

	


	return 0;

}

