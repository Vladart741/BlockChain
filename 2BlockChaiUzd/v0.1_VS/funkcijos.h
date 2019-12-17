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
Block Mining(int difficulty, std::string prev, std::vector<Transaction>transactions, std::vector<std::string>block_name_history);

template< typename T >
std::string int_to_hex(T i);
#endif //FUNKCIJOS_H