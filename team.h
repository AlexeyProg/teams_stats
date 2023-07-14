#ifndef TEAM_H
#define TEAM_H

#include <QMap>
#include <QObject>

class Team
{

public:
    Team();
    QMap<int,QString> team_list;
    QMap<QString,QList<QString>> heroes_list;
};

#endif // TEAM_H
