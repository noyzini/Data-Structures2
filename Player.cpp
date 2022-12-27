#include "Player.h"

Player::Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper) :
 playerId(playerId), teamId(teamId),goals(goals),cards(cards),gamesPlayed(gamesPlayed),isGoalKeeper(goalKeeper)
{
    this->nextBetter= nullptr;
    this->nextWorse= nullptr;

}

int Player::getId() const{
    return playerId;
}

int Player::getTeamId() const{
    return teamId;
}

int Player::getGoals() const {
    return goals;
}

void Player::setGoals(int newGoals) {
    this->goals = newGoals;
}

int Player::getCards() const {
    return cards;
}

void Player::setCards(int newCards) {
    this->cards = newCards;
}

int Player::getGamesPlayed() const {
    return gamesPlayed;
}

void Player::setGamesPlayed(int newGamesPlayed) {
    this->gamesPlayed = newGamesPlayed;
}

bool Player::getIsGoalKeeper() const {
    return isGoalKeeper;
}

bool Player::operator>(const Player& player2) const  {
    //player1 > player2:
    if (this->goals != player2.goals)
        return this->goals > player2.goals;
    if (this->cards != player2.cards)
        return this->cards < player2.cards;
    return this->playerId > player2.playerId;
}

bool Player::operator<(const Player& player2) const {
    //player1 < player2
    return player2 > *this;
}

void Player::setNextBetter(Player *player) {
    this->nextBetter = player;
}

Player* Player::getNextBetter() {
    return nextBetter;
}

void Player::setNextWorse(Player *player) {
    this->nextWorse = player;
}

Player *Player::getNextWorse() {
    return nextWorse;
}

void Player::setNegativeFactor(int factor) {
    this->negativeFactor=factor;
}

int Player::getNegativeFactor() const {
    return this->negativeFactor;
}

bool Player::operator==(Player &player2) const {
    return (this->playerId==player2.playerId);
}

bool Player::operator!=(Player &player2) const {
    return !(*this==player2);
}

void Player::setTeamPtr(Team *t) {
    this->teamPtr=t;
}

Team *Player::getTeamPtr() const {
    return this->teamPtr;
}

Player *Player::closestPlayer( Player &player1,  Player &player2) {
    if(abs(player2.goals- this->goals)>abs(player1.goals- this->goals))
    {
        return &player1;
    } else if(abs(player1.goals- this->goals)>abs(player2.goals- this->goals))
    {
        return &player2;
    } else
    {
        if(abs(player2.cards- this->cards)>abs(player1.cards- this->cards))
        {
            return &player1;
        }else if(abs(player1.cards- this->cards)>abs(player2.cards- this->cards))
        {
            return &player2;
        } else
        {
            if(abs(player2.playerId- this->playerId)>abs(player1.playerId- this->playerId))
            {
                return &player1;
            }else if(abs(player1.playerId- this->playerId)>abs(player2.playerId- this->playerId))
            {
                return &player2;
            }

            if(player1.playerId>player2.playerId)
                return &player1;
            else
                return &player2;
        }
    }
}

void Player::setTeamId(int id) {
    this->teamId = id;
}


