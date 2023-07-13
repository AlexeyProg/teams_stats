#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QMap>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMap<int,QString> mp_teams;

private:
    void getTeamId(QString team);
    Ui::MainWindow *ui;

signals:
    void teamsDataReady(const QMap<int, QString>& teams);


public slots:
    void showReply(QNetworkReply *r);
    void handleTeam_map(const QMap<int, QString>& mp_teams);
};
#endif // MAINWINDOW_H
