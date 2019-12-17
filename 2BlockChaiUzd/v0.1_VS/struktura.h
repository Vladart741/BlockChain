#pragma once
#include <iostream>
#include "funkcijos.h"
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
	std::string nonce;
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

	void add_block(Block naujas) { blocks.push_back(naujas); }
	std::string prev_block_hash_get(int id) { return blocks[id].current_block_hash; }
	void print_all_blocks()
	{
		for (int i = 0; i < blocks.size(); i++)
		{
			std::cout << "-------------------------------------------" << std::endl;
			std::cout << "BLOCK " + i<< std::endl;
			std::cout <<blocks[i].prev_block_hash << std::endl;
			std::cout <<blocks[i].current_block_hash << std::endl;
			std::cout <<blocks[i].time_stamp << std::endl;
			std::cout <<blocks[i].version << std::endl;
			std::cout <<blocks[i].merkel_tree << std::endl;
			std::cout <<blocks[i].nonce + " (HEX)" << std::endl;
			std::cout <<blocks[i].difficulty_target << std::endl;

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

	void add_transaction(Transaction naujas) { transactions.push_back(naujas); }
	void print_all_transactions()
	{
		for (int i = 0; i < transactions.size(); i++)
		{
			std::cout << transactions[i].id << " " << transactions[i].sender << " " << transactions[i].getter << " "<<transactions[i].amount << std::endl;
		}
	}
	std::vector<Transaction> transfer_transactions()
	{
		
		std::vector<Transaction> rez;
		for (int i = 0; i < 100; i++)
		{
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> dist6(1, transactions.size()); 

			int a = dist6(rng);
			rez.push_back(transactions[a]);
			transactions.erase(transactions.begin() + a);
		}
		return rez;
	}

};


#endif //INC_0_1V_STRUKTURA_H
