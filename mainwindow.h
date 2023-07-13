#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMap>
#include <QDebug>
#include <QTableWidget>

#include "requester.h"


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
    Ui::MainWindow *ui;
    Requester *req;
    Team *team;

    void createTable();
    QTableWidget *team_table;
    void fillTable(QTableWidget *table, QMap<int,QString> &teams);

private slots:
    void takeTeamsData();
};
#endif // MAINWINDOW_H
