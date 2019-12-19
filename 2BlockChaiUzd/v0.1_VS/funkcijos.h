#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>  
#include "struktura.h"
#include "sha256.h"
#include <vector>
#include <math.h> 
#include <random>
#include <chrono>
#include <bitset>
#include <algorithm>
#include <numeric>  
#include <functional>

#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H


#define FUNKCIJOS_H
int randomNum(int a, int b);
Transactions New_Transactions(int kiek, int kiek_useriu);
Users New_Users(int kiek);
Block Mining(int difficulty, std::string prev, std::vector<Transaction>transactions);
std::vector<int> Select_transaction(int a, int b, int n);
std::string GetTime();
std::vector<Transaction> BalansoTikrinimas(std::vector<Transaction> trasakcijos, std::vector<User> useriai);

Block SpecialMining(int difficulty, std::string prev, std::vector<Transaction>transactions, int mining_limit, int kiekTransakcijuBlokui);
NewBlock NewMining(int difficulty, std::string prev, std::vector<Transaction>transactions, int kiekTransakcijuBlokui, int miningLimit, int mining_Limit_update);

std::vector<Transaction> transfer_transactions(std::vector<int>pasirinkimai, std::vector<Transaction>transactions);
std::string create_merkle(std::vector<Transaction>transactions);

struct greater
{
	template<class T>
	bool operator()(T const &a, T const &b) const { return a > b; }
};

struct greater_for_transaction
{
	bool operator()(Transaction const &a, Transaction const &b) const { return a.sender > b.sender; }
};
struct greater_for_user
{
	bool operator()(User const &a, User const &b) const { return a.name > b.name; }
};
#endif //FUNKCIJOS_H