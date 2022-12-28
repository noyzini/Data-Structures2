#include "Player.h"


Player::Player(int playerId, int gamesPlayed, int cards, bool goalKeeper, const permutation_t &selfSpirit) :
        playerId(playerId), gamesPlayed(gamesPlayed),cards(cards),isGoalKeeper(goalKeeper), selfSpirit(selfSpirit)
{
    permutation_t t = permutation_t();
    color = t.neutral();
    teamSpirit = t.neutral();
}

int Player::getId() const{
    return playerId;
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

/*
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
*/
void Player::setNegativeFactor(int factor) {
    this->negativeFactor=factor;
}

int Player::getNegativeFactor() const {
    return this->negativeFactor;
}

/*
bool Player::operator==(Player &player2) const {
    return (this->playerId==player2.playerId);
}

bool Player::operator!=(Player &player2) const {
    return !(*this==player2);
}
 */

void Player::setTeamPtr(Team *t) {
    this->teamPtr=t;
}

Team *Player::getTeamPtr() const {
    return this->teamPtr;
}

