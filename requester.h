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

#include "team.h"
#include "hero.h"



class Requester : public QObject
{
    Q_OBJECT
public:
    explicit Requester(QObject *parent = nullptr);
    QMap<int,QString> mp_teams;
    Team *team;
    Team *take_obj();
    void get_teams(QUrl &path);
    void get_heroes(QUrl &path);
    QNetworkAccessManager *manage;


signals:
    void teamsReady();

public slots:
    void showReply(QNetworkReply *r);
    void handleTeam_map(const QMap<int, QString>& mp_teams);

};

#endif // REQUESTER_H
