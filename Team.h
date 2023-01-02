#ifndef DATA_STRUCTURES_TEAM_H
#define DATA_STRUCTURES_TEAM_H

#include "Player.h"
#include "AVLTree.h"
#include "wet2util.h"

class Player;


class Team {
private:
    int teamId;
    int points;
    int numPlayers;
    int numGoalKeepers;
    int sumAbility;
    int gamesPlayedFactor;
    Player* rootPlayer;
    permutation_t teamSpirit;


public:

    Team(int teamId);
    Team(Team& team) = default;
    ~Team() = default;
    int getTeamId() const;
    int getFactorGamesPlayed() const;
    int getNumPlayers() const;
    void setNumPlayers(int num);
    void setFactorGamesPlayed(int factor);
    bool haveGoalKeeper() const;
    int getNumGoalKeepers() const;
    void setNumGoalKeepers(int num);

    int getScore() const;
    void addPoints(int newPoints);
    int getPoints() const;
    int getPower() const;
    int getSumAbility() const;
    bool canPlay() const;
    void setSumAbility( int SumAbility);

    Player* getRootPlayer();
    void setRootPlayer(Player* player);
    permutation_t getTeamSpirit();
    void setTeamSpirit(permutation_t newSpirit);

    bool operator>(const Team& team2) const;
    bool operator<(const Team& team2) const;
    bool operator!=(Team& team2) const;
    bool operator==(Team& team2) const;
};

#endif //DATA_STRUCTURES_TEAM_H
