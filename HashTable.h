//
// Created by aviaa on 28/12/2022.
//

#ifndef DATA_STRUCTURES2_HASHTABLE_H
#define DATA_STRUCTURES2_HASHTABLE_H

#include "Player.h"

class HashTable
{
private:
    Player** arr; //dynamic arr
    int tableSize;
    int numPlayers;
    const int LOAD_FACTOR = 1;
    const int INIT_TABLE_SIZE = 10;

    const ERROR_PLAYER_EXSITS = -1;
    const OK = 1;

    void rehash();
    void expend();

public:
    HashTable();
    ~HashTable();
    int insert(int playerId, int teamId,
                const permutation_t &spirit, int gamesPlayed,
                int ability, int cards, bool goalKeeper);
    Player* find(int playerId);

};

#endif //DATA_STRUCTURES2_HASHTABLE_H
