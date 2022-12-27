#ifndef DATA_STRUCTURES_TEAM_H
#define DATA_STRUCTURES_TEAM_H

#include "Player.h"
#include "AVLTree.h"

class Player;


class Team {
private:
    int teamId;
    int points;
    int numPlayers;
    int numGoalKeepers;
    int power;
    int gamesPlayedFactor;

    Player* top_player;
    AVLTree<Player*,int>* playersIdTreePtr;
    AVLTree<Player*,Player>* playersScoresTreePtr;

public:
    bool deleteTree = true;
    Team(int teamId, int points);
    Team(Team& team) = default;
    ~Team();
    int getTeamId() const;
    int getFactorGamesPlayed() const;
    int getNumPlayers() const;
    void setNumPlayers(int num);
    void setFactorGamesPlayed(int factor);
    bool haveGoalKeeper() const;
    int getNumGoalKeepers() const;
    void setNumGoalKeepers(int num);
    bool isValidForWorldCup() const;
    void insert(Player* player);
    void remove(Player* player);
    int getScore() const;
    void addPoints(int newPoints);
    int getPower() const;
    int getPoints() const;
    bool canPlay() const;
    void setPower( int power);
    Player* getTopPlayer() const;
    void setTopPlayer(Player* top);
    AVLTree<Player*,int>* getPlayersIdTree() const;
    void setPlayersIdTree(AVLTree<Player*,int>* tree);
    AVLTree<Player*,Player>* getPlayersScoreTree() const;
    void setPlayersScoresTree(AVLTree<Player*,Player>* tree);
    void updatePlayersId();
};

#endif //DATA_STRUCTURES_TEAM_H
