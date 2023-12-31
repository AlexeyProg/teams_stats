#include "teamicon.h"
#include <QPushButton>

TeamIcon::TeamIcon(QString team_name,QList<Hero *> &heroes_list,QWidget *parent)
    : QDialog{parent}, heroes(heroes_list), cur_team_name(team_name)
{
    this->setWindowTitle(cur_team_name);
    this->setFixedSize(600,770);


    QGridLayout *layout = new QGridLayout;

    int row = 0;
    int col = 0;
    layout->setGeometry(QRect(0,150,this->width(),this->height()));


    for(Hero *h : heroes)
    {
        if(col == 8)
        {
            col = 0;
            row = row + 2;
        }
//        float winrate = std::round(static_cast<float>(h->wins) / h->games * 100.0) / 100.0 * 100;
//        QLabel *l = new QLabel;
//        l->setPixmap(h->pix);
//        l->setFixedSize(h->pix.size());
//        //l->setText(h->name);
//        QLabel *p = new QLabel;
//        p->setText(QString::number(winrate) + "%" + QString::number(h->games));
//        layout->addWidget(l,row,col,Qt::AlignHCenter);
//        layout->addWidget(p,row+1,col,Qt::AlignHCenter);


        QPushButton *butt = new QPushButton;
        QIcon icon(h->pix);
        butt->setProperty("butt_name",h->name);
        //QString ss = butt->property("button_name").toString();
        butt->setIcon(icon);
        butt->setFlat(true);
        butt->setIconSize(QSize(32,32));
        button_list.append(butt);
        layout->addWidget(butt,row,col,Qt::AlignHCenter);


        col++;
    }
    setLayout(layout);


    for(QPushButton *button : button_list)
    {
        connect(button, SIGNAL(clicked()), this, SLOT(openWinrate()));
    }
}

void TeamIcon::openWinrate()
{
    QString button_nick = sender()->property("butt_name").toString();
//    QDialog *di = new QDialog();
//    di->setGeometry(550,350,200,200);
//    QLabel *l = new QLabel(di);
    QString main_str = "";
    for(Hero *h : heroes)
    {
        if(h->name == button_nick)
        {
            float winrate = std::round(static_cast<float>(h->wins) / h->games * 100.0) / 100.0 * 100;
            main_str.append("Hero : " + button_nick + "\n" +
                       "Winrate : " + QString::number(winrate) + " %\n" +
                       "Games :" + QString::number(h->games) + "\n" +
                       "Wins : " + QString::number(h->wins));
        }
    }
    QMessageBox::information(this, button_nick, main_str, QMessageBox::Ok);
}
