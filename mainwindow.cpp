#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QNetworkAccessManager *manage = new QNetworkAccessManager(this);
    connect(manage, SIGNAL(finished(QNetworkReply*)), this, SLOT(showReply(QNetworkReply*)));
    QUrl url("https://api.opendota.com/api/teams");
    manage->get(QNetworkRequest(url));

    connect(this,SIGNAL(teamsDataReady(QMap<int, QString>)), this, SLOT(handleTeam_map(QMap<int, QString>)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getTeamId(QString team)
{

}

void MainWindow::accessNetworkManager()
{

}

void MainWindow::showReply(QNetworkReply *r)
{
//    qDebug() << r->readAll();
    QByteArray response = r->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);

    //qDebug() << jsonResponse;
    if(jsonResponse.isArray())
    {
        QJsonArray jsonArray = jsonResponse.array();
        foreach (const QJsonValue &value, jsonArray)
        {
            QJsonObject jsonObj = value.toObject();
            QString team_name = jsonObj["name"].toString();
            int team_id = jsonObj["team_id"].toInt();
            mp_teams.insert(team_id,team_name);
           // qDebug() << team_name << team_id;
        }
        emit teamsDataReady(mp_teams);
    }

}

void MainWindow::handleTeam_map(const QMap<int, QString> &mp_teams)
{
//    for(auto it = mp_teams.begin(); it != mp_teams.end(); ++it)
//    {
//        qDebug() << "ID : " << it.key() << " , team name : " << it.value();
//    }
    for(auto it = mp_teams.begin(); it != mp_teams.end(); it++)
    {

    }
}

