#ifndef DATA_STRUCTURES_PLAYER_H
#define DATA_STRUCTURES_PLAYER_H

#include "Team.h"
#include "AVLTree.h"

class Team;

class Player {
private:

    int playerId;
    int teamId;
    int goals;
    int cards;
    int gamesPlayed;
    bool isGoalKeeper;
    Team* teamPtr;
    int negativeFactor;

    Player* nextBetter;
    Player* nextWorse;

public:
    Player() = default;
    Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper);
    Player(Player& p) = default;
    ~Player() = default;
    int getId() const;
    int getTeamId() const;
    void setTeamId(int id);
    int getGoals() const;
    void setGoals(int goals);
    int getCards() const;
    void setCards(int cards);
    int getGamesPlayed() const;
    void setGamesPlayed(int gamesPlayed);
    bool getIsGoalKeeper() const;
    void setNegativeFactor(int factor);
    int getNegativeFactor() const;


    void setTeamPtr (Team* t);
    Team* getTeamPtr() const;

    void setNextBetter(Player* player);
    Player* getNextBetter();
    void setNextWorse(Player* player);
    Player* getNextWorse();

    Player* closestPlayer( Player& player1, Player& player2);

    bool operator>(const Player& player2) const;
    bool operator<(const Player& player2) const;
    bool operator!=(Player& player2) const;
    bool operator==(Player& player2) const;
};



#endif //DATA_STRUCTURES_PLAYER_H
