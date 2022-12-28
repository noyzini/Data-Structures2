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
    int ability;
    bool isGoalKeeper;
    int negativeFactor;

    const permutation_t &selfSpirit;
    permutation_t teamSpirit; //PI
    permutation_t color;

    int rGamesPlayed;

    Player* nextInHash;
    Player* parent;
    Team* teamPtr;

public:
    Player() = default;
    Player(int playerId, const permutation_t &spirit, int gamesPlayed, int ability, int cards, bool goalKeeper);
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
    int getAbility() const;
    void setAbility(int newAbility);

    int getRGamesPlayed() const;
    void setRGamesPlayed(int newr);

    permutation_t getTeamSpirit();
    void setTeamSpirit(permutation_t t);
    permutation_t getSelfSpirit();


    void setNextInHash(Player* player);
    Player* getNextInHash() const;

    void setTeamPtr (Team* t);
    Team* getTeamPtr() const;
    Player* getParent();
    void  setParent (Player* parent);

    /*
    bool operator>(const Player& player2) const;
    bool operator<(const Player& player2) const;
    bool operator!=(Player& player2) const;
    bool operator==(Player& player2) const;
     */
};



#endif //DATA_STRUCTURES_PLAYER_H
