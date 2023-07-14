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


    createFinderLine();
    createTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createFinderLine()
{
    line_finder = new QLineEdit(this);
    line_finder->setGeometry(290,20,200,20);
    connect(line_finder, &QLineEdit::returnPressed, this, &MainWindow::find);

    count_label = new QLabel(this);
    count_label->setGeometry(500,20,40,20);
}

void MainWindow::createTable()
{
    team_table = new QTableWidget(this);
    team_table->setGeometry(250,50,500,500);
    team_table->setColumnCount(2);
    team_table->setColumnWidth(1,360);
    QStringList horHeaders;
    horHeaders << "team id" << "team name";
    team_table->setHorizontalHeaderLabels(horHeaders);

}

void MainWindow::fillTable(QTableWidget *table, QMap<int, QString> &teams)
{
    int row = 0;
    table_rows = teams.size();
    table->setRowCount(table_rows);
    for(auto it = teams.begin(); it != teams.end(); it++)
    {
        if(it.value().isEmpty())
        {
            continue;
        }
        QTableWidgetItem *id = new QTableWidgetItem(QString::number(it.key()));
        QTableWidgetItem *name = new QTableWidgetItem(it.value());
        name->setFlags(name->flags() | Qt::ItemIsSelectable);
        table->setItem(row, 0, id);
        table->setItem(row, 1, name);
        ++row;

    }
}

void MainWindow::takeTeamsData()
{
    fillTable(team_table, team->team_list);
    connect(team_table, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(teamVote(QTableWidgetItem*)));

}

void MainWindow::find()
{
    QString search = line_finder->text();
    int count_of_finders = 0;
    for(int row = 0; row < table_rows; row++)
    {
        QTableWidgetItem *name = team_table->item(row,1);
        if(name && name->text().contains(search, Qt::CaseInsensitive))
        {
            team_table->setRowHidden(row, false);
            count_of_finders++;
        }
        else
        {
            team_table->setRowHidden(row,true);
        }
    }
    count_label->setText(QString(" : %1").arg(count_of_finders));
}

void MainWindow::teamVote(QTableWidgetItem *item)
{
    qDebug() << item->text();
    Hero *hero = new Hero("qqq",this);
    hero->show();
}

