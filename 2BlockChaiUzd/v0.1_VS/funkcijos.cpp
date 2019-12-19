
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


Block Mining(int difficulty, std::string prev, std::vector<Transaction>transactions)
{
	Block NewBlock;
	
	for (int i = -1; i > -2; i++)
	{
		int dif = difficulty;
		std::time_t result = std::time(nullptr); //timestamp

		std::string newHash = prev + std::asctime(std::localtime(&result)) + "Version1" + std::to_string(i);
		for (int a = 0; a < transactions.size();a++)
		{
			newHash = newHash + transactions[a].id;
		}

		std::string test = sha256(newHash);
		for (int j = 0; j < difficulty; j++)
		{
			if (test[j] == '0')
			{

				dif = dif - 1;
			}

		}
		if (dif == 0 && prev != test)
		{
			NewBlock.prev_block_hash = prev;
			NewBlock.current_block_hash = test;

			NewBlock.time_stamp = std::asctime(std::localtime(&result));

			NewBlock.version = "Version1";
			NewBlock.merkel_tree = " ";
			NewBlock.nonce = i;
			NewBlock.difficulty_target = difficulty;
			NewBlock.transactions = transactions;

			break;
			
		}
	}
	return NewBlock;
}

std::vector<int> Select_transaction(int a, int b, int n)
{
	std::vector<int>pasirinktosT;
	for (int i = 0; i < n; i++)
	{
		pasirinktosT.push_back(randomNum(a,b));
		b = b - 1;
	}
	std::sort(pasirinktosT.begin(), pasirinktosT.end(), greater());
	return pasirinktosT;
}

template< typename T >
std::string int_to_hex(T i)
{
	std::stringstream stream;
	stream << std::hex << i;
	return stream.str();
}

std::string GetTime()
{
	time_t rawtime;
	std::time(&rawtime);
	struct tm *tinfo = std::localtime(&rawtime);
	char buffer[12];
	strftime(buffer, 12, "%F", tinfo);
	return std::string(buffer);
}

