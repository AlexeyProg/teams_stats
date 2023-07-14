#include "requester.h"

Requester::Requester(QObject *parent)
    : QObject{parent}
{
    manage = new QNetworkAccessManager(this);
    connect(manage, SIGNAL(finished(QNetworkReply*)), this, SLOT(showReply(QNetworkReply*)));
    QUrl url("https://api.opendota.com/api/teams");
    //manage->get(QNetworkRequest(url));
    get_teams(url);
    team = new Team();

    //connect(this,SIGNAL(teamsDataReady(QMap<int, QString>)), this, SLOT(handleTeam_map(QMap<int, QString>)));

}

Team* Requester::take_obj()
{
    return team;
}

void Requester::get_teams(QUrl &path)
{
    QNetworkRequest req(path);
    req.setAttribute(QNetworkRequest::User, "teams");
    manage->get(QNetworkRequest(req));
}

void Requester::get_heroes(QUrl &path)
{
    QNetworkRequest req(path);
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
                team->team_list.insert(team_id,team_name);
                // qDebug() << team_name << team_id;
            }
            emit teamsReady();
        }
//        else if(type == "heroes")
//        {
//            foreach (const  QJsonValue &value, jsonArray)
//            {
//                QJsonObject obj = value.toObject();
//                QString name = obj["localized_name"].toString();
//                int games = obj["games_played"].toInt();
//                int wins = obj["wins"].toInt();
//            }
//        }
    }

}

void Requester::handleTeam_map(const QMap<int, QString> &mp_teams)
{
//    for(auto it = mp_teams.begin(); it != mp_teams.end(); ++it)
//    {
//        qDebug() << "ID : " << it.key() << " , team name : " << it.value();
//    }


}
