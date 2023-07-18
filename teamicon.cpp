#include "teamicon.h"

TeamIcon::TeamIcon(QString team_name,QList<Hero *> &heroes_list,QWidget *parent)
    : QDialog{parent}, heroes(heroes_list), cur_team_name(team_name)
{
    this->setWindowTitle(cur_team_name);
    this->setFixedSize(600,770);
    QLabel *title = new QLabel(this);
    title->setText(cur_team_name);


    QFont font_title = title->font();
    font_title.setPointSize(32);
    font_title.setBold(true);
    title->setFont(font_title);



//    QTextBrowser *t_browser = new QTextBrowser(this);
//    t_browser->setGeometry(5,70,320,400);

//    for(auto h : heroes)
//    {

//        float winrate = std::round(static_cast<float>(h->wins) / h->games * 100.0) / 100.0 * 100;

//        content += QString("%1 - games: %2 , wins : %3 (winrate = %4%)\n").arg(h->name,
//                                                                            QString::number(h->games),
//                                                                            QString::number(h->wins),
//                                                                            QString::number(winrate));
//    }
//    t_browser->setText(content);






    QGridLayout *layout = new QGridLayout;

    int row = 0;
    int col = 0;



    for(Hero *h : heroes)
    {
        if(col == 8)
        {
            col = 0;
            row = row + 2;
        }
        float winrate = std::round(static_cast<float>(h->wins) / h->games * 100.0) / 100.0 * 100;
        QLabel *l = new QLabel;
        l->setPixmap(h->pix);
        l->setFixedSize(h->pix.size());
        //l->setText(h->name);
        QLabel *p = new QLabel;
        p->setText(QString::number(winrate) + "%");
        layout->addWidget(l,row,col,Qt::AlignHCenter);
        layout->addWidget(p,row+1,col,Qt::AlignHCenter);

        //row++;
        col++;
    }
    setLayout(layout);
}
