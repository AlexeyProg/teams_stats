#include "teamicon.h"

TeamIcon::TeamIcon(QString team_name,QList<Hero *> &heroes_list,QWidget *parent)
    : QDialog{parent}, heroes(heroes_list), cur_team_name(team_name)
{
    this->setWindowTitle(cur_team_name);
    this->setFixedSize(350,550);
    QLabel *title = new QLabel(this);
    title->setText(cur_team_name);


    QFont font_title = title->font();
    font_title.setPointSize(32);
    font_title.setBold(true);
    title->setFont(font_title);




    QTextBrowser *t_browser = new QTextBrowser(this);
    t_browser->setGeometry(5,70,320,400);
//    t_browser->move(30,50);

    for(auto h : heroes)
    {
        float winrate = std::round(static_cast<float>(h->wins) / h->games * 100.0) / 100.0 * 100;

        content += QString("%1 - games: %2 , wins : %3 (winrate = %4%)\n").arg(h->name,
                                                                            QString::number(h->games),
                                                                            QString::number(h->wins),
                                                                            QString::number(winrate));
    }
    t_browser->setText(content);
}
