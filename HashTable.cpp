//
// Created by aviaa on 28/12/2022.
//

#include "HashTable.h"

HashTable::HashTable() : tableSize(INIT_TABLE_SIZE), numPlayers(0), arr(new Player*[INIT_TABLE_SIZE]) {

}

HashTable::~HashTable() {
    delete[] arr;
}

int HashTable::insert(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards,
                       bool goalKeeper)
{
    Player* newPlayer = new Player(playerId,spirit, gamesPlayed,ability,cards,goalKeeper);
    int index = playerId % tableSize; //our hash function
    if (arr[index] == nullptr)
        arr[index] = newPlayer;
    else
    {
        Player* temp = arr[index];
        if (temp->getId() == playerId)
            return ERROR_PLAYER_EXSITS;
        while (temp->getNextInHash() != nullptr)
        {
            temp = temp->getNextInHash();
            if (temp->getId() == playerId)
                return ERROR_PLAYER_EXSITS;
        }
    }



    return OK;
}
