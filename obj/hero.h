#ifndef HERO_H
#define HERO_H

#include <QObject>
#include <QFile>
#include <QPixmap>


class Hero
{
public:
    Hero(QString mName, int mGames, int mWins);

    QString name;
    int games;
    int wins;
    QString file_path;
    QPixmap pix;

private:
    void openImage();


};

#endif // HERO_H
