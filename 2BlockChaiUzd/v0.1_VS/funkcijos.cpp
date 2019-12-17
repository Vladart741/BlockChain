
#include "stdafx.h"
#include "funkcijos.h"
#include <iomanip>




std::mt19937 randomly_seeded_engine() {

	// create a seed sequence of several reasonably random values
	std::seed_seq seed_seq{ (unsigned int)std::random_device{}(),
						   (unsigned int)std::chrono::system_clock::now().time_since_epoch().count(),
						   (unsigned int)std::random_device{}(),
						   (unsigned int)std::chrono::steady_clock::now().time_since_epoch().count(),
						   (unsigned int)std::random_device{}() };

	return std::mt19937(seed_seq); // note: the seed sequence provides a warm up sequence for the rng
}

int randomNum(int a, int b) {

	static auto rng = randomly_seeded_engine();
	static std::uniform_int_distribution<int> distribution;

	distribution.param(std::uniform_int_distribution<int>::param_type{ a, b });
	return distribution(rng);
}

Users New_Users(int kiek)
{
	Users useriai;
	for (int i = 0; i < kiek; i++)
	{
		std::string id = sha256("Vardas" + std::to_string(i));

		int amount = randomNum(100, 1000000);
		User naujas = { id,"Vardas" + std::to_string(i),amount };
		useriai.add_user(naujas);
	}
	return useriai;
}
Transactions New_Transactions(int kiek, int kiek_useriu)
{
	Transactions tranz;
	for (int i = 0; i < kiek; i++)
	{
		int amount = randomNum(100, 1000000);
		std::string sender = "Vardas" + std::to_string(randomNum(1, kiek_useriu));
		std::string getter = "Vardas" + std::to_string(randomNum(1, kiek_useriu));
		std::string id = sha256(sender+getter+std::to_string(amount));
		Transaction naujas = { id,sender,getter,amount };
		tranz.add_transaction(naujas);
	}
	return tranz;

}


Block Mining(int difficulty, std::string prev, std::vector<Transaction>transactions, std::vector<std::string>block_name_history)
{
	Block NewBlock;
	
	for (int i = 0; i < 100000000; i++)
	{
		int dif = difficulty;
		std::string test = sha256(int_to_hex(i));
		for (int j = 0; j < difficulty; j++)
		{
			if (test[j] == '0')
			{
				dif = dif - 1;
			}

		}
		int sutapimai = 0;
		for (int i = 0; i < block_name_history.size(); i++)
		{
			if (test == block_name_history[i])
			{
				sutapimai++;
			}
		}
		if (dif == 0 && prev != test && sutapimai == 0)
		{
			NewBlock.prev_block_hash = prev;
			NewBlock.current_block_hash = test;

			NewBlock.time_stamp = "now";			

			NewBlock.version = "1";
			NewBlock.merkel_tree = "1";
			NewBlock.nonce = int_to_hex(i);
			NewBlock.difficulty_target = difficulty;
			NewBlock.transactions = transactions;

			break;
			
		}
	}
	return NewBlock;
}


template< typename T >
std::string int_to_hex(T i)
{
	std::stringstream stream;
	stream << std::hex << i;
	return stream.str();
}
