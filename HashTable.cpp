//
// Created by aviaa on 28/12/2022.
//

#include "HashTable.h"

//const int INIT_TABLE_SIZE = 10;

HashTable::HashTable() : tableSize(INIT_TABLE_SIZE), numPlayers(0), arr(new Player*[INIT_TABLE_SIZE])
{
    for (int i = 0; i < INIT_TABLE_SIZE; i++)
    {
        arr[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < tableSize; i++)
    {
        delete arr[i];
        arr[i] = nullptr;
    }
    delete[] arr;

}

int HashTable::insert(int playerId, const permutation_t &spirit, int gamesPlayed, int ability, int cards,
                       bool goalKeeper)
{
    Player* newPlayer = new Player(playerId,spirit, gamesPlayed,ability,cards,goalKeeper);
    if (addToArrByFunction(arr,tableSize,newPlayer) == ERROR_PLAYER_EXISTS)
        return ERROR_PLAYER_EXISTS;
    numPlayers++;
    if (numPlayers/tableSize >= LOAD_FACTOR)
    {
        doubleArrSize();
    }
    return OK;
}


void HashTable::doubleArrSize()
{
    int newTableSize = tableSize * 2;
    Player** newArr = new Player*[newTableSize];
    for (int i = 0 ; i < newTableSize; i++)
    {
        newArr[i] = nullptr;
    }
    Player* current;
    for (int i = 0 ; i < tableSize; i++)
    {
        current = arr[i];
        while (current != nullptr)
        {
            addToArrByFunction(newArr,newTableSize,current);
            current = current->getNextInHash();
        }
    }
    tableSize = newTableSize;
    delete[] arr;
    arr = newArr;
}

int HashTable::addToArrByFunction(Player **arr, int arrSize, Player* newPlayer)
{
    int playerId = newPlayer->getId();
    int index = playerId % arrSize; //the hash function
    if (arr[index] == nullptr)
    {
        arr[index] = newPlayer;
    }
    else
    {
        Player* current = arr[index];
        if (current->getId() == playerId)
            return ERROR_PLAYER_EXISTS;
        Player* next = current->getNextInHash();
        while (next != nullptr)
        {
            if (next->getId() == playerId)
                return ERROR_PLAYER_EXISTS;
            current = next;
            next = next->getNextInHash();
        }
        current->setNextInHash(newPlayer);
    }
    return OK;
}

Player* HashTable::find(int playerId) const {
    int index = playerId % tableSize; //the hash function
    Player* current = arr[index];
    while (current != nullptr)
    {
        if (current->getId() == playerId)
            return current;
        current = current->getNextInHash();
    }
    return nullptr;
}
