#include "worldcup23a2.h"

world_cup_t::world_cup_t() : playerGroups(UnionFind(&teamsTree,playersHashTable))
{

}

world_cup_t::~world_cup_t()
{
    // TODO: Your code goes here
}

StatusType world_cup_t::add_team(int teamId)
{
    if (teamId <= 0)
        return StatusType::INVALID_INPUT;
    if (teamsTree.find(teamId) != nullptr)
        return StatusType::FAILURE;
    try {
        Team* newTeam = new Team(teamId);
        teamsTree.insert(*newTeam,teamId);
        delete newTeam;
        newTeam = teamsTree.find(teamId);
        teamsTreeRanked.insert(newTeam,*newTeam);
    }
    catch (std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if (teamId <= 0)
        return StatusType::INVALID_INPUT;
    Team* team= teamsTree.find(teamId);
    if(team== nullptr)
    {
        return StatusType::FAILURE;
    }
    try {
        teamsTreeRanked.remove(*team);
        playerGroups.removeTeam(teamId);
        teamsTree.remove(teamId);
    }
    catch (const std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards, bool goalKeeper)
{
    //try catch!
    //need to update teamsTreeRanked by removing and adding to the tree
    if (playerId <= 0 || teamId <= 0 || (!spirit.isvalid()) || gamesPlayed < 0 || cards < 0)
        return StatusType::INVALID_INPUT;
    if (playersHashTable.find(playerId) != nullptr)
        return StatusType::FAILURE;

    Team* team = teamsTree.find(teamId);
    if (team == nullptr)
    {
        return StatusType::FAILURE;
    }
    teamsTreeRanked.remove(*team);
    playersHashTable.insert(playerId, spirit, gamesPlayed, ability, cards, goalKeeper);

    Player* player = playersHashTable.find(playerId);
    if (team->getNumPlayers() == 0)
    {
        team->setRootPlayer(player);
        player->setParent(nullptr);
        player->setTeamPtr(team);
        player->setTeamSpirit(permutation_t::neutral());
    }
    else
    {
        Player* parent = team->getRootPlayer();
        player->setParent(parent);
        player->setTeamSpirit(team->getTeamSpirit());

        //need to add color / r spirit here, after we realize how
    }
    team->setTeamSpirit(team->getTeamSpirit() * player->getSelfSpirit());
    team->setNumPlayers(team->getNumPlayers()+1);
    if (goalKeeper)
        team->setNumGoalKeepers(team->getNumGoalKeepers()+1);
    team->setSumAbility(team->getSumAbility()+player->getAbility());
    teamsTreeRanked.insert(team, *team);
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1<=0 || teamId2<=0 || teamId1==teamId2 )
    {
        return StatusType::INVALID_INPUT;
    }
    try {
        Team *team1 = this->teamsTree.find(teamId1);
        Team *team2 = this->teamsTree.find(teamId2);
        if (team1 == nullptr || team2 == nullptr || !team1->canPlay() || !team2->canPlay()) {
            return StatusType::FAILURE;
        }
        team1->getRootPlayer()->setRGamesPlayed(team1->getRootPlayer()->getRGamesPlayed()+1);
        team2->getRootPlayer()->setRGamesPlayed(team2->getRootPlayer()->getRGamesPlayed()+1);
        if (team1->getScore() == team2->getScore()) {
            if(team1->getTeamSpirit().strength()==team2->getTeamSpirit().strength())
            {
                team1->addPoints(1);
                team2->addPoints(1);
                return 0;
            }
            else if(team1->getTeamSpirit().strength()>team2->getTeamSpirit().strength())
            {
                team1->addPoints(3);
                return 2;
            } else{
                team2->addPoints(3);
                return 4;
            }

        } else if (team1->getScore() > team2->getScore()) {
            team1->addPoints(3);
            return 1;
        } else {
            team2->addPoints(3);
            return 3;
        }
    }
    catch (const std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
    if(playerId<=0)
    {
        return StatusType::INVALID_INPUT;
    }
    Player* player=playersHashTable.find(playerId);
    if(player== nullptr)
    {
        return StatusType::FAILURE;
    }
    int sum = player->getGamesPlayed();
    while (player != nullptr)
    {
        sum+= player->getRGamesPlayed();
        player = player->getParent();
    }
    return sum;
    Team* team = playerGroups.find(playerId);
    if (player == team->getRootPlayer())
    {
        return player->getRGamesPlayed() + player->getGamesPlayed();
    }
    int sum_old= team->getRootPlayer()->getRGamesPlayed() + player->getRGamesPlayed() + player->getGamesPlayed();
    return sum_old ;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    if(playerId<=0|| cards<0)
    {
        return StatusType::INVALID_INPUT;
    }
    Player* player=playersHashTable.find(playerId);
    if(player== nullptr)
    {
        return StatusType::FAILURE;
    }
    Team* team = playerGroups.find(playerId);
    if(team== nullptr)
    {
        return StatusType::FAILURE;
    }
    player->setCards(player->getCards()+cards);
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
    if(playerId<=0)
    {
        return StatusType::INVALID_INPUT;
    }
    Player* player=playersHashTable.find(playerId);
    if(player== nullptr)
    {
        return StatusType::FAILURE;
    }
	return player->getCards();
}

output_t<int> world_cup_t::get_team_points(int teamId)
{

    if(teamId<=0 )
    {
        return StatusType::INVALID_INPUT;
    }
    Team *team1 = this->teamsTree.find(teamId);
    if (team1 == nullptr) {
        return StatusType::FAILURE;
    }
	return team1->getPoints();
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
    if(teamsTreeRanked.getNumberOfNodes() == 0 ||i<0 || i>= teamsTreeRanked.getNumberOfNodes() )
    {
        return StatusType::FAILURE;
    }
    Team* team = teamsTreeRanked.findByIndex(i);
	return team->getTeamId();
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    if(playerId<=0)
    {
        return StatusType::INVALID_INPUT;
    }
    Player* player=playersHashTable.find(playerId);
    if(player== nullptr)
    {
        return StatusType::FAILURE;
    }
    Team* team = playerGroups.find(playerId);
    if(team== nullptr)
    {
        return StatusType::FAILURE;
    }
    if (team->getRootPlayer() == player)
    {
        permutation_t t=player->getTeamSpirit() * player->getSelfSpirit();
        return t;
    }
	return team->getRootPlayer()->getTeamSpirit()* player->getTeamSpirit()*player->getSelfSpirit();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
    if(teamId1<=0 || teamId2<=0 || teamId1==teamId2 )
    {
        return StatusType::INVALID_INPUT;
    }
    Team *team1 = this->teamsTree.find(teamId1);
    Team *team2 = this->teamsTree.find(teamId2);
    if (team1 == nullptr || team2 == nullptr) {
        return StatusType::FAILURE;
    }
    try{
        teamsTreeRanked.remove(*team2);
        teamsTreeRanked.remove(*team1);
        Team* unitedTeam = playerGroups.unite(teamId1,teamId2);
        teamsTreeRanked.insert(unitedTeam,*unitedTeam);
    }
    catch (std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}
