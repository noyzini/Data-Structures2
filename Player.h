#ifndef DATA_STRUCTURES_PLAYER_H
#define DATA_STRUCTURES_PLAYER_H

#include "Team.h"
#include "AVLTree.h"
#include "wet2util.h"

class Team;

class Player {
    private:
        int playerId;
        const permutation_t selfSpirit;

        int gamesPlayed;
        int ability;
        int cards;
        bool isGoalKeeper;


        Player* parent;
        Team* teamPtr;
        int negativeFactor;
        int rGamesPlayed;
        permutation_t RSpirit;
        Player* nextInHash;

    public:
        Player() = default;
        Player(int playerId, permutation_t spirit, int gamesPlayed, int ability, int cards, bool goalKeeper);
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

        permutation_t getRSpirit();
        void setRSpirit(permutation_t t);
        permutation_t getSelfSpirit();


        void setNextInHash(Player* player);
        Player* getNextInHash() const;

        void setTeamPtr (Team* t);
        Team* getTeamPtr() const;
        Player* getParent();
        void  setParent (Player* parent);
};



#endif //DATA_STRUCTURES_PLAYER_H
