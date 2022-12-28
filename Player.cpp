#include "Player.h"


Player::Player(int playerId, const permutation_t &spirit, int gamesPlayed, int ability, int cards,
               bool goalKeeper) :
        playerId(playerId), selfSpirit(spirit), gamesPlayed(gamesPlayed),ability(ability), cards(cards), isGoalKeeper(goalKeeper),parent(
        nullptr),teamPtr(nullptr),negativeFactor(0)
{
    color = permutation_t::neutral();
    teamSpirit = permutation_t::neutral();
    nextInHash = nullptr;
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

Player *Player::getParent() {
    return this->parent;
}

void Player::setParent(Player* parent) {
    this->parent=parent;
}

Player::~Player() {
    delete nextInHash;
}

void Player::setNextInHash(Player *player) {
    nextInHash = player;
}

Player *Player::getNextInHash() const {
    return nextInHash;
}

int Player::getAbility() const {
    return ability;
}

void Player::setAbility(int newAbility) {
    this->ability = newAbility;
}

permutation_t Player::getTeamSpirit() {
    return teamSpirit;
}

void Player::setTeamSpirit(permutation_t t) {
    teamSpirit=t;
}


