//
// Created by Noy Zini on 28/12/2022.
//

#include "UnionFind.h"

Team* UnionFind::find(int playerId) {
    //finding the team by running up the playersHashTable parents
    //the final source is the root
    Player* source = players.find(playerId);
    if(source== nullptr)
    {
        return nullptr;
    }
    int sumGames=0;
    permutation_t sumTeamSpirit=permutation_t::neutral();
    while (source->getParent()!= nullptr)
    {
        sumGames+=source->getRGamesPlayed();
        sumTeamSpirit=source->getTeamSpirit()*sumTeamSpirit;
        source=source->getParent();
    }
    Team* team=source->getTeamPtr();
    //running up again and making "cuts" connecting players on the chain to the root(source)
    Player* runner= players.find(playerId);
    Player* parent;
    int gamesToSub=0;
    permutation_t subTeamSpirit=permutation_t::neutral();
    while (runner->getParent()!= nullptr && runner->getParent()->getParent()!= nullptr)
    {
        parent=runner->getParent();
        runner->setParent(source);

        int newGamesPlayed=sumGames-gamesToSub;
        gamesToSub+=runner->getRGamesPlayed();
        permutation_t newSpirit=sumTeamSpirit*subTeamSpirit.inv();
        subTeamSpirit=runner->getTeamSpirit()*subTeamSpirit;

        runner->setRGamesPlayed(newGamesPlayed);
         runner->setTeamSpirit(newSpirit);

        runner=parent;
    }
    return team;
}

Team *UnionFind::unite(int team1, int team2) {
    Team* buyer = teams->find(team1);
    Team* bought= teams->find(team2);
    //choosing the bigger team and uniting to that team
    // team 1 is bigger and is the buyer
    if(buyer->getNumPlayers()==0 && bought->getNumPlayers()==0)
    {
    }
    else if(buyer->getNumPlayers() >= bought->getNumPlayers())
    {
        if(bought->getNumPlayers()!=0) {
            bought->getRootPlayer()->setParent(buyer->getRootPlayer());
            //updating for spirit
            bought->getRootPlayer()->setTeamSpirit(buyer->getRootPlayer()->getTeamSpirit().inv()*buyer->getTeamSpirit() * bought->getRootPlayer()->getTeamSpirit());
            buyer->setTeamSpirit(buyer->getTeamSpirit() * bought->getTeamSpirit());
            //updating games played
            bought->getRootPlayer()->setRGamesPlayed(
                    bought->getRootPlayer()->getRGamesPlayed() - buyer->getRootPlayer()->getRGamesPlayed());

            bought->getRootPlayer()->setTeamPtr(nullptr);
        }
    }
    else// team 2 is bigger and team 1 is the buyer
    {
        if(buyer->getNumPlayers()!=0) {
            buyer->getRootPlayer()->setParent(bought->getRootPlayer());
            //updating for spirit
            bought->getRootPlayer()->setTeamSpirit(buyer->getTeamSpirit() * bought->getRootPlayer()->getTeamSpirit());
            buyer->getRootPlayer()->setTeamSpirit(
                    bought->getRootPlayer()->getTeamSpirit().inv() * buyer->getRootPlayer()->getTeamSpirit());
            buyer->setTeamSpirit(buyer->getTeamSpirit() * bought->getTeamSpirit());
            //updating games played
            buyer->getRootPlayer()->setRGamesPlayed(buyer->getRootPlayer()->getRGamesPlayed() - bought->getRootPlayer()->getRGamesPlayed());

            buyer->getRootPlayer()->setTeamPtr(nullptr);
        }
        buyer->setRootPlayer(bought->getRootPlayer());
        bought->getRootPlayer()->setTeamPtr(buyer);
    }
    buyer->addPoints(bought->getPoints());
    buyer->setNumPlayers(bought->getNumPlayers()+buyer->getNumPlayers());
    buyer->setNumGoalKeepers(buyer->getNumGoalKeepers()+bought->getNumGoalKeepers());
    buyer->setSumAbility(buyer->getSumAbility()+bought->getSumAbility());

    this->teams->remove(team2);
    return buyer;
}

void UnionFind::removeTeam(int teamId) {
    Team* team =teams->find(teamId);
    if (team->getRootPlayer() != nullptr)
        team->getRootPlayer()->setTeamPtr(nullptr);
    team->setRootPlayer(nullptr);
}

UnionFind::UnionFind(AVLTree<Team, int>* teams, HashTable& players) :teams(teams), players(players){
}






