//
// Created by aviaa on 28/12/2022.
//

#include "HashTable.h"

HashTable::HashTable() : tableSize(INIT_TABLE_SIZE), numPlayers(0), arr(new Player*[INIT_TABLE_SIZE]) {

}

HashTable::~HashTable() {
    delete[] arr;
}

void HashTable::insert(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards,
                       bool goalKeeper)
{
    Player newPlayer = new Player();

}
