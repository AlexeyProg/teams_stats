#include "hero.h"

Hero::Hero(QString mName, QWidget *parent) : QDialog(parent),name(mName)
{
    this->setWindowTitle("Hero");
    this->setFixedSize(200,200);
}

void Hero::accept()
{
    QDialog::accept();
}

Hero::~Hero()
{

}
