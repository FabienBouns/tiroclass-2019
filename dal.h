#ifndef DAL_H
#define DAL_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QDebug>
#include <QString>
#include <QtSql>
#include <QFileInfo>

using namespace std;

class DAL
{
public:
    static DAL* Instance();
    int connection();
    QString rechercher(QString ID);
    QString quantite(QString ID);
    QString prendre(QString ID, int take);
    QString ajouter(QString tableau[]);
    DAL();
    ~DAL();

private:
    QSqlTableModel *tableModel;
    QSqlDatabase database;
    QString ID;
    QString url;
    QString nbr;
    QString ObjectID;
    QString ObjectNom;
    QString ObjectEtage;
    QString ObjectNombre;
    int enlever;
    int verification;
};

#endif // DAL_H
