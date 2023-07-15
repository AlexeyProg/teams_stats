#ifndef REQUESTER_H
#define REQUESTER_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>


#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include "datacontainer.h"



class Requester : public QObject
{
    Q_OBJECT
public:
    explicit Requester(QObject *parent = nullptr);
    QMap<int,QString> mp_teams;

    int mTeamID;

    void get_teams(QUrl &path);
    void get_heroes(int id);
    QNetworkAccessManager *manage;
    DataContainer *container;



signals:
    void teamsReady();
    void heroesReady();

public slots:
    void showReply(QNetworkReply *r);
    void handleTeam_map(const QMap<int, QString>& mp_teams);

};

#endif // REQUESTER_H
