//bounoir Fabien
//communication interface / base de donnée

#include "dal.h"
#include "ihmtiroclass.h"
#include "ui_ihmtiroclass.h"
#include <iostream>
#include <QMessageBox>

using namespace std;

DAL::DAL()
{
    cout<<"Creation DAL OK !!!"<<endl;
}

DAL::~DAL()
{

}

int DAL::connection()    //connection base de donnée
{
    QSqlDatabase database = QSqlDatabase::addDatabase ("QSQLITE");
    //database.setDatabaseName("C:/Users/utilisateur/Desktop/tiroclass.db"); // chemin acces BDD en cours
    database.setDatabaseName("C:/Users/User/Bureau/tiroclass.db");   // chemin acces BDD maison
    bool status = database.open();
    if(status==true)
    {
        cout<<"vous etes connecte"<<endl;
    }
    else
    {
        cout<<"la connection a echouee"<<endl;
    }
    return status;
}

QString DAL::rechercher(QString ID)    //requete pour la place dans le tiroclass
{
    url="";
    QSqlQuery query;
    query.prepare("SELECT Tiroir FROM Materiel WHERE ID = :ID");
    query.bindValue(":ID",ID);
    query.exec();
    if (query.exec())
    {
        while(query.next())
        {
            url = query.value(0).toString();
        }
    }
    return url;
}

QString DAL::quantite(QString ID)   // requete pour le nombre restant dans le tiroclass
{
    nbr ="";
    QSqlQuery quantite;
    quantite.prepare("SELECT Quantite FROM Materiel WHERE ID = :ID");
    quantite.bindValue(":ID",ID);
    quantite.exec();
    if (quantite.exec())
    {
        while(quantite.next())
        {
            nbr = quantite.value(0).toString();
        }
    }
    return nbr;
}

QString DAL::prendre(QString ID, int take)        //requete pour enlever composant tiroclass
{
    enlever = 0;
    QSqlQuery demande;
    demande.prepare("SELECT Quantite FROM Materiel WHERE ID = :ID");
    demande.bindValue(":ID",ID);
    demande.exec();
    if (demande.exec())
    {
        while(demande.next())
        {
            enlever = demande.value(0).toInt();
            if(take<enlever)
            {
                enlever = enlever - take;
            }
            else {
                enlever= enlever - enlever;
            }
        }
    }
    QSqlQuery retirer;
    retirer.prepare("UPDATE Materiel SET Quantite = ? WHERE ID = ? ");
    retirer.bindValue(0,enlever);
    retirer.bindValue(1,ID);
    retirer.exec();
    if (retirer.exec())
    {
        cout<<"enlever avec succees"<<endl;
    }
    return url;
}

QString DAL::ajouter(QString tableau[])     //requete ajouter composant tiroclass
{
    QString ID = tableau[1];
    QString Nom = tableau[2];
    QString Etage = tableau[3];
    QString Nombre = tableau[4];
    verification = 0;
    QSqlQuery verif;
    verif.prepare("SELECT EXISTS (SELECT * FROM Materiel WHERE ID = :ID )");
    verif.bindValue(":ID",ID);
    verif.exec();

    if (verif.exec())
    {
        while(verif.next())
        {
            verification = verif.value(0).toInt();
            if(verification == 0)
            {
                QSqlQuery add;
                add.prepare("INSERT INTO Materiel (ID, Nom, Quantite, Tiroir) VALUES ( :ID , :NOM , :NOMBRE , :ETAGE );");
                add.bindValue(":ID",ID);
                add.bindValue(":NOM",Nom);
                add.bindValue(":NOMBRE",Nombre);
                add.bindValue(":ETAGE",Etage);
                add.exec();
                cout<<"ajouter avec succes"<<endl;
            }
            else {
                QSqlQuery alter;
                alter.prepare("UPDATE Materiel SET NOM = :NOM, Quantite = :NOMBRE, Tiroir = :ETAGE WHERE id = :ID");
                alter.bindValue(":ID",ID);
                alter.bindValue(":NOM",Nom);
                alter.bindValue(":NOMBRE",Nombre);
                alter.bindValue(":ETAGE",Etage);
                alter.exec();
                qDebug() << "alter realiser";
            }
        }
    }
    return "";
}
