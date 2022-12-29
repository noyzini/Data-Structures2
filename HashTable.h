//
// Created by aviaa on 28/12/2022.
//

#ifndef DATA_STRUCTURES2_HASHTABLE_H
#define DATA_STRUCTURES2_HASHTABLE_H

#include "Player.h"

class HashTable
{
    typedef Player* PlayerPtr;
private:

    static const int INIT_TABLE_SIZE = 10;
    Player** arr; //dynamic arr
    int tableSize;
    int numPlayers;
    const int LOAD_FACTOR = 1;


    static const int ERROR_PLAYER_EXISTS = -1;
    static const int OK = 1;

    void doubleArrSize();
    static int addToArrByFunction(Player** arr, int arrSize, Player* newPlayer);

public:
    HashTable();
    ~HashTable();
    int insert(int playerId, permutation_t spirit, int gamesPlayed, int ability, int cards, bool goalKeeper);
    Player* find(int playerId) const;
};

#endif //DATA_STRUCTURES2_HASHTABLE_H
