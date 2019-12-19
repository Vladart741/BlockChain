#include "stdafx.h"
#include <iostream>
#include <chrono>
#include "funkcijos.h"



int main() {

	int kiekTransakciju = 1000;
	int kiekUseriu = 1000;
	int kiekTransakcijuBlokui = 100;

	Users useriai = New_Users(kiekUseriu);
	//useriai.print_all_users();


	Transactions transakcijos = New_Transactions(kiekTransakciju, kiekUseriu);

	//transakcijos.print_all_transactions();
	BlockChain bc;
	int i = 0;

	while(i<kiekTransakciju/kiekTransakcijuBlokui)
	{
		std::vector<int>pasirinktosTransakcijos = Select_transaction(0, transakcijos.get_num_of_transactions(), kiekTransakcijuBlokui);
		if (i == 0)
		{
			Block rez = Mining(2, "0", transakcijos.transfer_transactions(pasirinktosTransakcijos));
			bc.add_block(rez);
			std::cout << "BLOCKAS RASTAS!" << std::endl;
		}
		else
		{
			Block rez = Mining(2, bc.prev_block_hash_get(i-1), transakcijos.transfer_transactions(pasirinktosTransakcijos));
			bc.add_block(rez);
			std::cout << "BLOCKAS RASTAS!" << std::endl;
		}
		i++;
	}
	bc.print_all_blocks(transakcijos.get_num_of_transactions());

	


	return 0;

}

