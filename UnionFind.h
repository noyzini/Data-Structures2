//
// Created by Noy Zini on 28/12/2022.
//

#ifndef DATA_STRUCTURES2_UNIONFIND_H
#define DATA_STRUCTURES2_UNIONFIND_H
#include "AVLTree.h"
#include "Team.h"
#include "HashTable.h"

class UnionFind {
private:
    AVLTree<Team,int> * teams;
    HashTable& players;
public:
    UnionFind(AVLTree<Team,int>* teams,HashTable& players);
    Team* find(int playerId);
    Team* unite(int team1, int team2);
    void removeTeam(int teamId);

};

#endif //DATA_STRUCTURES2_UNIONFIND_H
