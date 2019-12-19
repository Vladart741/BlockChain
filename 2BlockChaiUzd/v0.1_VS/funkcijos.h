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

template< typename T >
std::string int_to_hex(T i);
struct greater
{
	template<class T>
	bool operator()(T const &a, T const &b) const { return a > b; }
};
#endif //FUNKCIJOS_H