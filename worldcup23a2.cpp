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
    if(team== nullptr || team->getNumPlayers()>0)
    {
        return StatusType::FAILURE;
    }
    try {
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
    playersHashTable.insert(playerId, spirit, gamesPlayed, ability, cards, goalKeeper);
    Player* player = playersHashTable.find(playerId);
    Team* team = teamsTree.find(teamId);
    if (team == nullptr)
    {

    }

    if (team->getNumPlayers() == 0)
    {
        team->setRootPlayer(player);
        player->setParent(nullptr);
        player->setTeamPtr(team);
    }
    else
    {
        Player* parent = team->getRootPlayer();
        player->setParent(parent);
        player->setTeamSpirit(team->getTeamSpirit());
        //need to add color / r spirit here, after we realize how
    }
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
        team1->setFactorGamesPlayed(1 + team1->getFactorGamesPlayed());
        team2->setFactorGamesPlayed(1 + team2->getFactorGamesPlayed());
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
	// TODO: Your code goes here
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	return permutation_t();
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
    Team* unitedTeam = playerGroups.unite(teamId1,teamId2);
	return StatusType::SUCCESS;
}
