#ifndef HERO_H
#define HERO_H

#include <QObject>
#include <QWidget>
#include <QDialog>


class Hero : public QDialog
{
    Q_OBJECT
public:
    explicit Hero(QString mName, QWidget *parent = nullptr);
    ~Hero();
    QString image;
    QString name;
    int games;
    int wins;
protected:
    void accept() override;
};

#endif // HERO_H
