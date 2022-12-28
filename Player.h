#ifndef DATA_STRUCTURES_PLAYER_H
#define DATA_STRUCTURES_PLAYER_H

#include "Team.h"
#include "AVLTree.h"
#include "wet2util.h"

class Team;

class Player {
private:

    int playerId;
    int cards;
    int gamesPlayed;
    bool isGoalKeeper;
    int negativeFactor;

    const permutation_t &selfSpirit;
    permutation_t teamSpirit; //PI
    permutation_t color;

    Player* nextInHash;
    Player* parent;
    Team* teamPtr;

public:
    Player() = default;
    Player(int playerId,int gamesPlayed, int cards, bool goalKeeper, const permutation_t &selfSpirit);
    //Player(Player& p) = default;
    ~Player();
    int getId() const;
    int getCards() const;
    void setCards(int cards);
    int getGamesPlayed() const;
    void setGamesPlayed(int gamesPlayed);
    bool getIsGoalKeeper() const;
    void setNegativeFactor(int factor);
    int getNegativeFactor() const;


    void setTeamPtr (Team* t);
    Team* getTeamPtr() const;

    /*
    bool operator>(const Player& player2) const;
    bool operator<(const Player& player2) const;
    bool operator!=(Player& player2) const;
    bool operator==(Player& player2) const;
     */
};



#endif //DATA_STRUCTURES_PLAYER_H
