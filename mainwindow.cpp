#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    req = new Requester();
    team = req->take_obj();
    connect(req, SIGNAL(teamsReady()), this, SLOT(takeTeamsData()));

    createTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createTable()
{
    team_table = new QTableWidget(this);
    team_table->setGeometry(250,50,500,500);
    team_table->setColumnCount(2);
    team_table->setColumnWidth(1,250);

}

void MainWindow::fillTable(QTableWidget *table, QMap<int, QString> &teams)
{
    int row = 0;
    int row_count = teams.size();
    table->setRowCount(row_count);
    for(auto it = teams.begin(); it != teams.end(); it++)
    {
        QTableWidgetItem *id = new QTableWidgetItem(it.key());
        QTableWidgetItem *name = new QTableWidgetItem(it.value());
        table->setItem(row, 0, id);
        table->setItem(row, 1, name);
        ++row;
    }
}

void MainWindow::takeTeamsData()
{
    //qDebug() << team->team_list[2];

    fillTable(team_table, team->team_list);
}

