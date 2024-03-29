#include "stdafx.h"
#include <iostream>
#include <chrono>
#include "funkcijos.h"




int main() {

	int kiekTransakciju = 1000;
	int kiekUseriu = 1000;
	
	int difficulty = 2;

	int kiekTransakcijuBlokui = 100;
	int miningLimit = 100000;
	int mining_limit_update = 100000;

	Users useriai = New_Users(kiekUseriu);
	//useriai.print_all_users();

	Transactions transakcijos = New_Transactions(kiekTransakciju, kiekUseriu);
	//transakcijos.print_all_transactions();

	BlockChain bc;

	std::string pasirinkimas;
	std::cout << "Kad paleisti v.01 ivesti (1) " << std::endl;
	std::cout << "Kad paleisti v.02 ivesti (2) " << std::endl;
	std::cout << "Kad paleisti v.03 ivesti (3) " << std::endl;
	std::cin>> pasirinkimas;

	if (pasirinkimas == "1")
	{
		int i = 0;
		while (i < kiekTransakciju / kiekTransakcijuBlokui)
		{
			std::vector<int>pasirinktosTransakcijos = Select_transaction(0, transakcijos.get_num_of_transactions()-1, kiekTransakcijuBlokui);
			if (i == 0)
			{
				Block rez = Mining(difficulty, "0", transakcijos.transfer_transactions(pasirinktosTransakcijos));
				bc.add_block(rez);
				std::cout << "BLOCKAS RASTAS!" << std::endl;
			}
			else
			{
				Block rez = Mining(difficulty, bc.prev_block_hash_get(i - 1), transakcijos.transfer_transactions(pasirinktosTransakcijos));
				bc.add_block(rez);
				std::cout << "BLOCKAS RASTAS!" << std::endl;
			}
			i++;
		}
		bc.print_all_blocks(transakcijos.get_num_of_transactions());

	}
	if (pasirinkimas == "2")
	{
		std::cout << "Before cleaning: " << transakcijos.get_num_of_transactions()<<std::endl;
		transakcijos.set_all_transactions(BalansoTikrinimas(transakcijos.get_all_transactions(),useriai.get_all_users()));
		std::cout << "After cleaning: " << transakcijos.get_num_of_transactions()<<std::endl;
		kiekTransakciju = transakcijos.get_num_of_transactions();

		int i = 0;
		if (kiekTransakciju % kiekTransakcijuBlokui == 0)
		{
			while (i < kiekTransakciju / kiekTransakcijuBlokui)
			{
				if (i == 0)
				{
					NewBlock rez = NewMining(difficulty, "0", transakcijos.get_all_transactions(),kiekTransakcijuBlokui,miningLimit,mining_limit_update);
					bc.add_block(rez.block);
					transakcijos.transfer_transactions(rez.pasirinktosTransakcijos);
					std::cout << "BLOCKAS RASTAS!" << std::endl;
				}
				else
				{
					NewBlock rez = NewMining(difficulty, bc.prev_block_hash_get(i - 1), transakcijos.get_all_transactions(), kiekTransakcijuBlokui, miningLimit, mining_limit_update);
					bc.add_block(rez.block);
					transakcijos.transfer_transactions(rez.pasirinktosTransakcijos);
					std::cout << "BLOCKAS RASTAS!" << std::endl;
				}
				i++;
			}
		}
		else
		{
			while (i < (kiekTransakciju / kiekTransakcijuBlokui))
			{
				if (i == 0)
				{
					NewBlock rez = NewMining(difficulty, "0", transakcijos.get_all_transactions(), kiekTransakcijuBlokui, miningLimit, mining_limit_update);
					bc.add_block(rez.block);
					transakcijos.transfer_transactions(rez.pasirinktosTransakcijos);
					std::cout << "BLOCKAS RASTAS!" << std::endl;
				}
				else
				{
					NewBlock rez = NewMining(difficulty, bc.prev_block_hash_get(i - 1), transakcijos.get_all_transactions(), kiekTransakcijuBlokui, miningLimit, mining_limit_update);
					bc.add_block(rez.block);
					transakcijos.transfer_transactions(rez.pasirinktosTransakcijos);
					std::cout << "BLOCKAS RASTAS!" << std::endl;
				}
				i++;
			}

				NewBlock rez = NewMining(difficulty, bc.prev_block_hash_get(bc.get_size() - 2), transakcijos.get_all_transactions(), kiekTransakciju % kiekTransakcijuBlokui, miningLimit, mining_limit_update);
				bc.add_block(rez.block);
				transakcijos.transfer_transactions(rez.pasirinktosTransakcijos);
				std::cout << "BLOCKAS RASTAS!" << std::endl;
		}
		
		bc.print_all_blocks(transakcijos.get_num_of_transactions());

		//transakcijos.print_all_transactions();
	}
	if (pasirinkimas == "3")
	{
		std::cout << "Before cleaning: " << transakcijos.get_num_of_transactions() << std::endl;
		transakcijos.set_all_transactions(BalansoTikrinimas(transakcijos.get_all_transactions(), useriai.get_all_users()));
		std::cout << "After cleaning: " << transakcijos.get_num_of_transactions() << std::endl;
		kiekTransakciju = transakcijos.get_num_of_transactions();

		int i = 0;
		if (kiekTransakciju % kiekTransakcijuBlokui == 0)
		{
			while (i < kiekTransakciju / kiekTransakcijuBlokui)
			{
				if (i == 0)
				{
					NewBlock rez = NewMining(difficulty, "0", transakcijos.get_all_transactions(), kiekTransakcijuBlokui, miningLimit, mining_limit_update);
					rez.block.merkel_tree = create_merkle(rez.block.transactions);
					bc.add_block(rez.block);
					transakcijos.transfer_transactions(rez.pasirinktosTransakcijos);
					std::cout << "BLOCKAS RASTAS!" << std::endl;
				}
				else
				{
					NewBlock rez = NewMining(difficulty, bc.prev_block_hash_get(i - 1), transakcijos.get_all_transactions(), kiekTransakcijuBlokui, miningLimit, mining_limit_update);
					rez.block.merkel_tree = create_merkle(rez.block.transactions);
					bc.add_block(rez.block);
					transakcijos.transfer_transactions(rez.pasirinktosTransakcijos);
					std::cout << "BLOCKAS RASTAS!" << std::endl;
				}
				i++;
			}
		}
		else
		{
			while (i < (kiekTransakciju / kiekTransakcijuBlokui))
			{
				if (i == 0)
				{
					NewBlock rez = NewMining(difficulty, "0", transakcijos.get_all_transactions(), kiekTransakcijuBlokui, miningLimit, mining_limit_update);
					rez.block.merkel_tree = create_merkle(rez.block.transactions);
					bc.add_block(rez.block);
					transakcijos.transfer_transactions(rez.pasirinktosTransakcijos);
					std::cout << "BLOCKAS RASTAS!" << std::endl;
				}
				else
				{
					NewBlock rez = NewMining(difficulty, bc.prev_block_hash_get(i - 1), transakcijos.get_all_transactions(), kiekTransakcijuBlokui, miningLimit, mining_limit_update);
					rez.block.merkel_tree = create_merkle(rez.block.transactions);
					bc.add_block(rez.block);
					transakcijos.transfer_transactions(rez.pasirinktosTransakcijos);
					std::cout << "BLOCKAS RASTAS!" << std::endl;
				}
				i++;
			}

			NewBlock rez = NewMining(difficulty, bc.prev_block_hash_get(bc.get_size() - 2), transakcijos.get_all_transactions(), kiekTransakciju % kiekTransakcijuBlokui, miningLimit, mining_limit_update);
			rez.block.merkel_tree = create_merkle(rez.block.transactions);
			bc.add_block(rez.block);
			transakcijos.transfer_transactions(rez.pasirinktosTransakcijos);
			std::cout << "BLOCKAS RASTAS!" << std::endl;
		}

		bc.print_all_blocks(transakcijos.get_num_of_transactions());

		//transakcijos.print_all_transactions();
	}
	


	return 0;

}

