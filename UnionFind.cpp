//
// Created by Noy Zini on 28/12/2022.
//

#include "UnionFind.h"

Team* UnionFind::find(int playerId) {
    //finding the team by running up the players parents
    //the final source is the root
    Player* source = players.find(playerId);
    if(source== nullptr)
    {
        return nullptr;
    }
    int sumGames=source->getGamesPlayed();
    permutation_t sumTeamSpirit=source->getTeamSpirit();
    while (source->getParent()!= nullptr)
    {
        source=source->getParent();
        sumGames+=source->getGamesPlayed();
        sumTeamSpirit=source->getTeamSpirit()*sumTeamSpirit;
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
        gamesToSub+=runner->getGamesPlayed();
        permutation_t newSpirit=sumTeamSpirit*subTeamSpirit.inv();
        subTeamSpirit=runner->getTeamSpirit()*sumTeamSpirit;

        runner->setGamesPlayed(newGamesPlayed);
        runner->setTeamSpirit(newSpirit);

        runner=parent;
    }
    return team;
}

Team *UnionFind::unite(int team1, int team2) {
    Team* team_first = teams->find(team1);
    Team* team_second= teams->find(team2);
    //choosing the bigger team and uniting to that team
    if(team_first->getNumPlayers()>team_second->getNumPlayers())
    {
        team_second->getRootPlayer()->setParent(team_first->getRootPlayer());
        this->teams->remove(team2);
        return team_first;
    }
    else
    {
        team_first->getRootPlayer()->setParent(team_second->getRootPlayer());
        this->teams->remove(team1);
        return team_second;
    }
}

void UnionFind::removeTeam(int teamId) {
    Team* team =teams->find(teamId);
    team->getRootPlayer()->setTeamPtr(nullptr);
    team->setRootPlayer(nullptr);
}





