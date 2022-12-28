#include "Team.h"

Team::Team(int teamId) :
teamId(teamId),points(0),numPlayers(0),numGoalKeepers(0),sumAbility(0),gamesPlayedFactor(0),rootPlayer(nullptr),teamSpirit(permutation_t::neutral())
{

}

int Team::getFactorGamesPlayed() const {
    return gamesPlayedFactor;
}

void Team::setFactorGamesPlayed(int factor) {
    this->gamesPlayedFactor = factor;
}

bool Team::haveGoalKeeper() const {
    return numGoalKeepers > 0;
}


int Team::getTeamId() const
{
    return teamId;
}

int Team::getNumPlayers() const {
    return numPlayers;
}

int Team::getSumAbility() const {
    return sumAbility;
}

bool Team::canPlay() const {
    if(this->haveGoalKeeper())
        return true;
    return false;
}

int Team::getScore() const {
    return this->sumAbility+ this->points;
}

void Team::addPoints(int newPoints) {
    this->points+=newPoints;
}

int Team::getPoints() const {
    return this->points;

}

void Team::setSumAbility(int sumAbility) {
    this->sumAbility = sumAbility;
}

void Team::setNumPlayers(int num) {
    this->numPlayers = num;
}

int Team::getNumGoalKeepers() const {
    return numGoalKeepers;
}

void Team::setNumGoalKeepers(int num) {
    this->numGoalKeepers = num;
}

Player* Team::getRootPlayer() {
    return this->rootPlayer;
}

void Team::setRootPlayer(Player *player) {
    this->rootPlayer=player;
}

permutation_t Team::getTeamSpirit() {
    return teamSpirit;
}

void Team::setTeamSpirit(permutation_t newSpirit) {
    teamSpirit=newSpirit;
}




