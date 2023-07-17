#ifndef TEAM_H
#define TEAM_H

#include <QMap>
#include <QList>
#include <QObject>
#include "hero.h"

class Team
{

public:
    Team();
    QMap<int,QString> team_list;
    QMap<QString,QPair<int,int>> heroes_list;


    ////////
    int id;
    QString name;
    QList<Hero*> heroes;
};

#endif // TEAM_H
