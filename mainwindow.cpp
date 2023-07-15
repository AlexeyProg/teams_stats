#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextBrowser>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    req = new Requester();

    connect(req, SIGNAL(teamsReady()), this, SLOT(takeTeamsData()));
    connect(req, SIGNAL(heroesReady()), this, SLOT(takeTeamsHeros()));


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
    team_table->setColumnCount(1);

    team_table->setColumnWidth(0,360);
    QStringList horHeaders;
    horHeaders << "team name";
    team_table->setHorizontalHeaderLabels(horHeaders);

}

void MainWindow::fillTable(QTableWidget *table, QMap<QString, int> &list)
{
    int row = 0;
    table_rows = list.size();
    table->setRowCount(table_rows);

//    for(auto tm : list)
//    {
//        if(tm->name.isEmpty())
//            continue;
//        QTableWidgetItem *name = new QTableWidgetItem(tm->name);
//        name->setFlags(name->flags() | Qt::ItemIsSelectable);
//        table->setItem(row,0,name);
//        ++row;
//    }
    for(auto it = list.begin(); it != list.end(); it++)
    {
        if(it.key().isEmpty())
            continue;
        QTableWidgetItem *name = new QTableWidgetItem(it.key());
        name->setFlags(name->flags() | Qt::ItemIsSelectable);
        table->setItem(row,0,name);
        ++row;
    }

}

void MainWindow::takeTeamsData()
{
    container = req->container;
//    for(auto item : container->team_list)
//    {
//        qDebug() << item->name;       // tut work
//    }
    fillTable(team_table, container->team_list);
    connect(team_table, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(teamVote(QTableWidgetItem*)));

}

void MainWindow::takeTeamsHeros()
{
    QString str = "";
    QTextBrowser *t = new QTextBrowser(this);
    t->setGeometry(100,200,300,300);
    QList<Hero*> h = container->heroByTeam.value(current_team_id);
    for(auto hero : h)
    {
        double winrate = hero->wins / hero->games;
        qDebug() << winrate;
        str += QString("%1 - games: %2 , wins : %3 (winrate = %4);\n").arg(hero->name,
                                                         QString::number(hero->games),
                                                         QString::number(hero->wins),
                                                         QString::number(winrate));
    }
    t->setText(str);
    t->show();
}

void MainWindow::find()
{
    QString search = line_finder->text();
    int count_of_finders = 0;
    for(int row = 0; row < table_rows; row++)
    {
        QTableWidgetItem *name = team_table->item(row,0);
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
    count_label->setText(QString(" : %1 items").arg(count_of_finders));
}

void MainWindow::teamVote(QTableWidgetItem *item)
{
    QString name = item->text();
    auto it = container->team_list.find(name);
    if(it != container->team_list.end())
    {
        int id = it.value();
        current_team_id = id;
        req->get_heroes(id);
    }
    else
    {
        qDebug() << "Something is wrong with key searcher";
    }
}

