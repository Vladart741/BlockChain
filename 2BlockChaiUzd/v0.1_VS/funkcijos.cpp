
#include "stdafx.h"
#include "funkcijos.h"
#include <iomanip>
#include <algorithm>
#include <assert.h>


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
std::vector<Transaction> BalansoTikrinimas(std::vector<Transaction> trasakcijos, std::vector<User> useriai)
{
	std::vector<Transaction> rez = trasakcijos;
	std::vector<User>user = useriai;

	std::sort(rez.begin(), rez.end(), greater_for_transaction());
	std::sort(user.begin(), user.end(), greater_for_user());

	for (int i = 0; i < user.size(); i++)
	{
		for (int j = 0; j < rez.size(); j++)
		{
			if (rez[j].sender == user[i].name && rez[j].amount > user[i].vladcoin)
			{
				rez.erase(rez.begin() + j);
			}
		}

	}
	return rez;
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

Block SpecialMining(int difficulty, std::string prev, std::vector<Transaction>transactions,int mining_limit, int kiekTransakcijuBlokui)
{
	Block NewBlock;

	NewBlock.prev_block_hash = prev;
	NewBlock.current_block_hash = "1";
	NewBlock.time_stamp = " ";
	NewBlock.version = "Version1";
	NewBlock.merkel_tree = " ";
	NewBlock.nonce = 0;
	NewBlock.difficulty_target = difficulty;
	NewBlock.transactions = transactions;

	for (int i = 0; i <mining_limit; i++)
	{
		int dif = difficulty;
		std::time_t result = std::time(nullptr); //timestamp

		std::string newHash = prev + std::asctime(std::localtime(&result)) + "Version1" + std::to_string(i);
		for (int a = 0; a < kiekTransakcijuBlokui; a++)
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

NewBlock NewMining(int difficulty, std::string prev, std::vector<Transaction>transactions, int kiekTransakcijuBlokui, int miningLimit, int mining_Limit_update)
{
	int mining_limit = miningLimit;
	int i = 0;
	NewBlock Winner;

	start:
	std::vector<int>pasirinktosTransakcijos = Select_transaction(0, transactions.size(), kiekTransakcijuBlokui);
	std::vector<Transaction>atrinktos_transakcijos = transfer_transactions(pasirinktosTransakcijos, transactions);

	Block Kandidatas = SpecialMining(difficulty, prev, atrinktos_transakcijos,mining_limit,kiekTransakcijuBlokui);

	if (Kandidatas.current_block_hash != "1" && i < 5)
	{
		Winner.block = Kandidatas;
		Winner.pasirinktosTransakcijos = pasirinktosTransakcijos;
	}
	else if (Kandidatas.current_block_hash != "1" && i < 5)
	{
		i++;
		goto start;
	}
	else
	{
		std::cout << "We need more mining!" << std::endl;
		i = 0;
		mining_limit += mining_Limit_update;
		goto start;
	}
	return Winner;
	
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



std::string GetTime()
{
	time_t rawtime;
	std::time(&rawtime);
	struct tm *tinfo = std::localtime(&rawtime);
	char buffer[12];
	strftime(buffer, 12, "%F", tinfo);
	return std::string(buffer);
}


std::vector<Transaction> transfer_transactions(std::vector<int>pasirinkimai,std::vector<Transaction>transactions)
{

	std::vector<Transaction> rez;
	int dydis = transactions.size();
	for (int i = 0; i < pasirinkimai.size(); i++)
	{
		std::string test = sha256(transactions[pasirinkimai[i]].sender + transactions[pasirinkimai[i]].getter + std::to_string(transactions[pasirinkimai[i]].amount));
		if (test == transactions[pasirinkimai[i]].id)
		{
			rez.push_back(transactions[pasirinkimai[i]]);
			transactions.erase(transactions.begin() + pasirinkimai[i]);
		}
		else
		{
			transactions.erase(transactions.begin() + pasirinkimai[i]);
		}

	}
	return rez;
}
std::string create_merkle(std::vector<Transaction>transactions)
{
	uint16_t size = transactions.size();
	std::vector<std::string> merkle(size);
	for (uint16_t i = 0; i < size; i++) {
		merkle[i] = transactions[i].id;
	}
	// Stop if hash list is empty or contains one element
	if (merkle.empty())
		return sha256(NULL);
	else if (merkle.size() == 1)
		return merkle[0];

	// While there is more than 1 hash in the list, keep looping...
	while (merkle.size() > 1)
	{
		// If number of hashes is odd, duplicate last hash in the list.
		if (merkle.size() % 2 != 0)
			merkle.push_back(merkle.back());
		// List size is now even.
		assert(merkle.size() % 2 == 0);

		// New hash list.
		std::vector<std::string> new_merkle;
		// Loop through hashes 2 at a time.
		for (auto it = 0; it < merkle.size(); it += 2)
		{
			// Join both current hashes together (concatenate).
			std::string concat_data = merkle[it] + merkle[it + 1];
			// Hash both of the hashes.
			std::string new_root = sha256(concat_data);
			// Add this to the new list.
			new_merkle.push_back(new_root);
		}
		// This is the new list.
		merkle = new_merkle;

		// DEBUG output -------------------------------------
		std::cout << "Current merkle hash list:" << std::endl;
		for (const auto& hash : merkle)
			std::cout << "  " << hash << std::endl;
		std::cout << std::endl;
		// --------------------------------------------------
	}
	// Finally we end up with a single item.
	return merkle[0];
}