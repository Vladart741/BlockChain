#pragma once
#include <iostream>
#include "funkcijos.h"
#include "sha256.h"
#include <string>
#include <vector>
#include <random>

#ifndef INC_0_1V_STRUKTURA_H
#define INC_0_1V_STRUKTURA_H


struct User
{
	std::string public_key;
	std::string name;
	double vladcoin;
};
struct  Transaction
{
	std::string id;
	std::string sender;
	std::string getter;
	int amount;
};
struct  Block
{
	std::string prev_block_hash;
	std::string current_block_hash;
	std::string time_stamp;
	std::string version;
	std::string merkel_tree;
	int nonce;
	int difficulty_target;
	std::vector<Transaction>transactions;
};

class BlockChain
{
private:
	std::vector<Block> blocks;

public:
	std::vector<Block> blockchain_get() const { return blocks; }
	Block one_block_get(int ID) const { return blocks[ID]; }
	int get_size() const { return blocks.size(); }

	void add_block(Block naujas) { blocks.push_back(naujas); }
	std::string prev_block_hash_get(int id) { return blocks[id].current_block_hash; }
	void print_all_blocks(int dydis)
	{
		for (int i = 0; i < blocks.size(); i++)
		{
			std::cout << "-------------------------------------------" << std::endl;
			std::cout << "BLOCK " + std::to_string(i)<< std::endl;
			std::cout <<"Prev block: "<<blocks[i].prev_block_hash << std::endl;
			std::cout <<"Curr block: "<<blocks[i].current_block_hash << std::endl;
			std::cout<<"Time stamp: "<<blocks[i].time_stamp << std::endl;
			std::cout <<"Version: "<<blocks[i].version << std::endl;
			std::cout <<"Merkel tree: "<<blocks[i].merkel_tree << std::endl;
			std::cout <<"Nonce: "<<blocks[i].nonce << std::endl;
			std::cout <<"Difficulty target: "<<blocks[i].difficulty_target << std::endl;
			std::cout << "Number of trasactions: " << blocks[i].transactions.size() << std::endl;
			std::cout << "Liko nepriskirtu trasakciju: " << dydis << std::endl;
		}
	}
};

class Users
{
private:
	std::vector<User>users;
public:
	std::vector<User> get_all_users() const { return users; }
	User get_one_user(int ID) const { return users[ID]; }

	void add_user(User naujas) { users.push_back(naujas); }
	void print_all_users()
	{
		for (int i = 0; i < users.size(); i++)
		{
			std::cout << users[i].public_key << " " << users[i].name << " " << users[i].vladcoin << " " << std::endl;
		}
	}
};
class Transactions
{
private:
	std::vector<Transaction>transactions;
public:
	int get_num_of_transactions() { return transactions.size(); }
	std::vector<Transaction> get_all_transactions() const { return transactions; }
	Transaction get_one_trasaction(int ID) const { return transactions[ID]; }


	
	void set_all_transactions(std::vector<Transaction>naujas) { transactions = naujas; }
	void add_transaction(Transaction naujas) { transactions.push_back(naujas); }
	void print_all_transactions()
	{
		for (int i = 0; i < transactions.size(); i++)
		{
			std::cout << transactions[i].id << " " << transactions[i].sender << " " << transactions[i].getter << " "<<transactions[i].amount << std::endl;
		}
	}
	std::vector<Transaction> transfer_transactions(std::vector<int>pasirinkimai)
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


};
struct NewBlock
{
	Block block;
	std::vector<int>pasirinktosTransakcijos;
};

#endif //INC_0_1V_STRUKTURA_H
