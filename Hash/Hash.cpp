// Hash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <set>
#include "HashTable.h"

bool My(int a, int b) 
{
    return a > b;
}

int main()
{
    HashTable<std::string, std::string> table;

    table.Insert("Dog", "Value");

    std::cout << table.Search("Dog");

    table.Search("Dog") = "Hello";

    std::cout << table.Search("Dog");
}

