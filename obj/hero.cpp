#include "hero.h"
#include <QDebug>

Hero::Hero(QString mName, int mGames, int mWins) : name(mName), games(mGames), wins(mWins)
{
    file_path = ":/" + mName + ".png";
    pix.load(file_path);
}

void Hero::openImage()
{

}

