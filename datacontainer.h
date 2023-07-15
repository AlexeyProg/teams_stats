#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QObject>
#include <QMap>
#include <QList>

#include "hero.h"
#include "team.h"

class DataContainer
{
public:
    DataContainer();
    void addTeam(Team *team);
    void addHeroToTeam(int teamId, QList<Hero *> &heroes);

    QMap<int, QList<Hero*>> heroByTeam;


    QMap<QString,int> team_list;

    ~DataContainer();
};

#endif // DATACONTAINER_H
