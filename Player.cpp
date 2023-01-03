#include "Player.h"


Player::Player(int playerId, permutation_t spirit, int gamesPlayed, int ability, int cards,
               bool goalKeeper) :
        playerId(playerId), selfSpirit(spirit), gamesPlayed(gamesPlayed),ability(ability), cards(cards), isGoalKeeper(goalKeeper),parent(
        nullptr),teamPtr(nullptr),negativeFactor(0),rGamesPlayed(0)
{
    RSpirit = permutation_t::neutral();
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

void Player::setNegativeFactor(int factor) {
    this->negativeFactor=factor;
}

int Player::getNegativeFactor() const {
    return this->negativeFactor;
}

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

permutation_t Player::getRSpirit() {
    return RSpirit;
}

void Player::setRSpirit(permutation_t t) {
    RSpirit=t;
}

int Player::getRGamesPlayed() const {
    return rGamesPlayed;
}

void Player::setRGamesPlayed(int newr) {
    rGamesPlayed=newr;
}

permutation_t Player::getSelfSpirit() {
    return selfSpirit;
}


