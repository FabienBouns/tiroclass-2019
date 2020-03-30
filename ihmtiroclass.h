#ifndef IHMTIROCLASS_H
#define IHMTIROCLASS_H
#include <QObject>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QMutex>
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>
#include "dal.h"

namespace Ui {

class ihmtiroclass;
}

class ihmtiroclass : public QMainWindow
{
    Q_OBJECT

public:
    explicit ihmtiroclass(QWidget *parent = nullptr); // remplacer nullptr par 0 si probleme
    ~ihmtiroclass();
    void refresh();
    void connection();
    void recherche();
    void position();
    void restant();
    void addcompo();
    void reset();

private slots:  
    void on_quitterbutton_clicked();
    void on_connectionBDD_clicked();
    void on_load_clicked();
    void on_recherche_clicked();
    void on_takebutton_clicked();
    void on_AddObject_clicked();

private:
    Ui::ihmtiroclass *ui;
    QSqlDatabase database;
    QSqlTableModel *tableModel;
    DAL *query;
    QLineEdit *searchbar;
    QLineEdit *prendrebar;
    DAL *db;
    QString url;
    QString nbr;
    QString tableau[5];
    QString taketable[3];
    QSerialPort *serial;
};

#endif // IHMTIROCLASS_H
