    #ifndef TEAMICON_H
#define TEAMICON_H

#include <QDialog>
#include <QTextBrowser>
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>

#include "obj/hero.h"


class TeamIcon : public QDialog
{
    Q_OBJECT
public:
    explicit TeamIcon(QString team_name, QList<Hero*> &heroes_list, QWidget *parent = nullptr);

private:
    QList<Hero*> heroes;
    QString content;
    QString cur_team_name;
    QList<QPushButton*> button_list;
private slots:
    void openWinrate();

signals:

};

#endif // TEAMICON_H
