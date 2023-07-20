#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMap>
#include <QDebug>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPixmap>
#include <QPushButton>

#include "requester.h"
#include "obj/datacontainer.h"
#include "teamicon.h"


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
    TeamIcon *icon;
    Requester *req;
    DataContainer *container;

    void createFinderLine();
    void createTable();
    QTableWidget *team_table;
    void fillTable(QTableWidget *table, QMap<QString, int> &list);
    QLineEdit *line_finder;
    QLabel *count_label;

    int table_rows;

    QString curr_team_name;
    int current_team_id;

    void createContacts();
    QPushButton *contacts_button;

private slots:
    void takeTeamsData();
    void takeTeamsHeros();
    void find();
    void teamVote(QTableWidgetItem *item);
    void show_contacts();
};
#endif // MAINWINDOW_H
