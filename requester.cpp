#include "requester.h"

Requester::Requester(QObject *parent)
    : QObject{parent}
{
    manage = new QNetworkAccessManager(this);
    connect(manage, SIGNAL(finished(QNetworkReply*)), this, SLOT(showReply(QNetworkReply*)));
    QUrl url("https://api.opendota.com/api/teams");
    //manage->get(QNetworkRequest(url));
    get_teams(url);
    //team = new Team();
    container = new DataContainer();

}

void Requester::get_teams(QUrl &path)
{
    QNetworkRequest req(path);
    req.setAttribute(QNetworkRequest::User, "teams");
    manage->get(QNetworkRequest(req));
}

void Requester::get_heroes(int id)
{
    mTeamID = id;
    QString str = QString("https://api.opendota.com/api/teams/%1/heroes").arg(mTeamID);
    QUrl url(str);
    QNetworkRequest req(url);
    req.setAttribute(QNetworkRequest::User, "heroes");
    manage->get(QNetworkRequest(req));
}

void Requester::showReply(QNetworkReply *r)
{
    //    qDebug() << r->readAll();
    QString type = r->request().attribute(QNetworkRequest::User).toString();

    QByteArray response = r->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);

    //qDebug() << jsonResponse;
    if(jsonResponse.isArray())
    {
        QJsonArray jsonArray = jsonResponse.array();
        if(type == "teams")
        {
            foreach (const QJsonValue &value, jsonArray)
            {
                QJsonObject jsonObj = value.toObject();
                QString team_name = jsonObj["name"].toString();
                int team_id = jsonObj["team_id"].toInt();
                //team->team_list.insert(team_id,team_name);
                // qDebug() << team_name << team_id;

                Team *team = new Team();
                team->id = team_id;
                team->name = team_name;
                container->addTeam(team);

            }
            emit teamsReady();
        }
        else if(type == "heroes")
        {
            QList<Hero*> list_1;
            foreach (const  QJsonValue &value, jsonArray)
            {
                QJsonObject obj = value.toObject();
                QString name = obj["localized_name"].toString();
                int games = obj["games_played"].toInt();
                int wins = obj["wins"].toInt();
                Hero *hero =new Hero();
                hero->name = name;
                hero->games = games;
                hero->wins = wins;
                list_1.append(hero);
            }
            container->addHeroToTeam(mTeamID,list_1);
            emit heroesReady();
        }
    }

}

void Requester::handleTeam_map(const QMap<int, QString> &mp_teams)
{
//    for(auto it = mp_teams.begin(); it != mp_teams.end(); ++it)
//    {
//        qDebug() << "ID : " << it.key() << " , team name : " << it.value();
//    }


}
