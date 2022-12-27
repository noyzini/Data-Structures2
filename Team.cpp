#include "Team.h"

Team::Team(int teamId, int points) :
teamId(teamId),points(points),numPlayers(0),numGoalKeepers(0),power(0),gamesPlayedFactor(0),top_player(nullptr)
{
    playersIdTreePtr = nullptr;
    playersScoresTreePtr = nullptr;
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

bool Team::isValidForWorldCup() const {
    return ((numPlayers >= 11) && haveGoalKeeper());

}

void Team::remove(Player *player)
{
    power -= player->getGoals() - player->getCards();
    bool wasTop = false;
    if (player == top_player)
    {
        wasTop = true;
    }
    if (player->getIsGoalKeeper())
        numGoalKeepers--;

    this->numPlayers--;
    this->playersScoresTreePtr->remove(*player);
    int id = player->getId();
    this->playersIdTreePtr->remove(id);

    if (wasTop)
    {
        if (numPlayers == 0)
            top_player = nullptr;
        else
        {
            Node<Player *, Player> *temp = playersScoresTreePtr->getRoot();
            while (temp->right != nullptr)
                temp = temp->right;
            top_player = temp->data;
        }
    }
    if (numPlayers == 0)
    {
        delete playersIdTreePtr;
        playersIdTreePtr = nullptr;
        delete playersScoresTreePtr;
        playersScoresTreePtr = nullptr;
    }
}

int Team::getTeamId() const
{
    return teamId;
}

int Team::getNumPlayers() const {
    return numPlayers;
}

AVLTree<Player *, int> *Team::getPlayersIdTree() const {
    return playersIdTreePtr;
}

void Team::insert(Player *player)
{
    if (playersIdTreePtr == nullptr)
    {
        playersIdTreePtr = new AVLTree<Player*,int>();
        playersScoresTreePtr = new AVLTree<Player*, Player>();
    }

    playersIdTreePtr->insert(player,player->getId());
    playersScoresTreePtr->insert(player,*player);
    player->setNegativeFactor(this->gamesPlayedFactor);
    numPlayers++;
    if(player->getIsGoalKeeper())
    {
        this->numGoalKeepers++;
    }
    if (top_player == nullptr || *player > *top_player)
        top_player = player;
    power += player->getGoals() - player->getCards();
    player->setTeamPtr(this);
}

AVLTree<Player*, Player>* Team::getPlayersScoreTree() const {
    return this->playersScoresTreePtr;
}

int Team::getPower() const {
    return power;
}

bool Team::canPlay() const {
    if(this->numPlayers>=11 && this->haveGoalKeeper())
        return true;
    return false;
}

int Team::getScore() const {
    return this->power+ this->points;
}

void Team::addPoints(int newPoints) {
    this->points+=newPoints;
}

int Team::getPoints() const {
    return this->points;

}

void Team::setPower(int newPower) {
    this->power = newPower;
}

Player *Team::getTopPlayer() const
{
    return this->top_player;
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

void Team::setTopPlayer(Player *top) {
    this->top_player = top;
}

void Team::setPlayersIdTree(AVLTree<Player *, int> *tree) {
    playersIdTreePtr = tree;
}

void Team::setPlayersScoresTree(AVLTree<Player *, Player> *tree) {
    playersScoresTreePtr = tree;
}

Team::~Team() {
    if (deleteTree == false) {
        deleteTree = true;
        return;
    }
    if (playersIdTreePtr!= nullptr)
        delete playersIdTreePtr;
    playersIdTreePtr = nullptr;
    if(playersScoresTreePtr!= nullptr)
        delete playersScoresTreePtr;
    playersScoresTreePtr = nullptr;
    top_player = nullptr;
}

void Team::updatePlayersId() {

    if (numPlayers > 0)
    {
        Node<Player *, int> **playersArray = new Node<Player *, int> *[numPlayers];
        playersIdTreePtr->extractInOrder(playersIdTreePtr->getRoot(), playersArray);
        for (int i = 0; i < numPlayers; i++) {
            playersArray[i]->data->setTeamPtr(this);
            playersArray[i]->data->setTeamId(this->teamId);
        }
        delete[] playersArray;
    }
}




