#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QTextBrowser>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("OpenDota_API v1.0");
    this->setStyleSheet("background-color: #ffecf3;");

    req = new Requester();

    createContacts();
    createFinderLine();
    createTable();
    line_finder->setStyleSheet("color : red;padding: 3px; background-color: white; border: 1px solid #CCCCCC; border-radius: 3px;");
    team_table->setStyleSheet("color : green;background-color: black; border: 1px solid #CCCCCC;");
    count_label->setStyleSheet("font-weight: bold; font-size: 12px; color: #333333;");
    this->setFixedSize(360,600);

    QPixmap pix_dota(":/dota2.png");
    QLabel *logo = new QLabel(this);
    logo->setPixmap(pix_dota);
    logo->setFixedSize(pix_dota.size());
    logo->move(320,5);

    connect(req, SIGNAL(teamsReady()), this, SLOT(takeTeamsData()));
    connect(req, SIGNAL(heroesReady()), this, SLOT(takeTeamsHeros()));
    connect(contacts_button, SIGNAL(clicked()), this, SLOT(show_contacts()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createFinderLine()
{
    line_finder = new QLineEdit(this);
    line_finder->setGeometry(50,20,200,20);
    connect(line_finder, &QLineEdit::returnPressed, this, &MainWindow::find);

    QLabel *search = new QLabel(this);
    search->setText("Search:");
    search->setGeometry(5,20,55,20);
    search->setStyleSheet("color : black");

    count_label = new QLabel(this);
    count_label->setGeometry(250,20,70,20);
}

void MainWindow::createTable()
{
    team_table = new QTableWidget(this);
    team_table->setGeometry(5,50,340,500);
    team_table->setColumnCount(1);

    team_table->setColumnWidth(0,290);
    QStringList horHeaders;
    horHeaders << "team name";
    team_table->setHorizontalHeaderLabels(horHeaders);

}

void MainWindow::fillTable(QTableWidget *table, QMap<QString, int> &list)
{
    int row = 0;
    table_rows = list.size();
    table->setRowCount(table_rows);

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

void MainWindow::createContacts()
{
    contacts_button = new QPushButton(this);
    contacts_button->setText("Contacts");
    contacts_button->setStyleSheet("color : green; background-color : #ff8bb4");
    contacts_button->setGeometry(20,570,60,20);

}

void MainWindow::takeTeamsData()
{
    container = req->container;
    fillTable(team_table, container->team_list);
    connect(team_table, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(teamVote(QTableWidgetItem*)));

}

void MainWindow::takeTeamsHeros()
{

    QList<Hero*> h = container->heroByTeam.value(current_team_id);

    icon = new TeamIcon(curr_team_name, h);
    icon->exec();
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
    curr_team_name = name;
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

void MainWindow::show_contacts()
{
    QMessageBox::information(this, "Contacts", "Github: https://github.com/AlexeyProg", QMessageBox::Ok);
}

