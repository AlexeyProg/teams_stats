#include "datacontainer.h"

DataContainer::DataContainer()
{

}

void DataContainer::addTeam(Team *team)
{
    team_list.insert(team->name,team->id);
}

void DataContainer::addHeroToTeam(int teamId, QList<Hero*> &heroes)
{
    heroByTeam.insert(teamId, heroes);
}
