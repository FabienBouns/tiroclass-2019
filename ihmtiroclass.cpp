//bounoir Fabien
//interface utilisateur



#include "ihmtiroclass.h"
#include "ui_ihmtiroclass.h"
#include "dal.h"
#include <QObject>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QMutex>
#include <QMainWindow>
#include <QMessageBox>
#include <QtSql/QSqlTableModel>
#include <QSerialPort>
#include <QPixmap>



ihmtiroclass::ihmtiroclass(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ihmtiroclass)
{
    ui->setupUi(this);
    setWindowTitle("Mini-projet Tiroclass");
    setFixedSize(484,380);
    connection();
    QPixmap img("C:/Users/User/Bureau/tiroclass/tiroclass4/images.png");
    ui->image->setPixmap(img);

    serial = new QSerialPort;
    serial->setPortName("COM14");   //a changer en fonction du pc
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);
    qDebug() << "port configurer";
}

ihmtiroclass::~ihmtiroclass()
{
    delete ui;
    serial->close();
}

void ihmtiroclass::connection()
{
    db = new DAL();
    bool status = db->connection();
    if(status == true)
    {
        ui->connectionBDD->setEnabled(false);
    }
    else {
        ui->connectionBDD->setEnabled(true);
    }
    refresh();
}

void ihmtiroclass::refresh()
{
    tableModel = new QSqlTableModel();
    tableModel->setTable("Materiel");
    tableModel->select();
    tableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
    tableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    tableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantité"));
    tableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Tiroir"));
    ui->table->setModel(tableModel);
}

void ihmtiroclass::recherche()
{
position();     //Requête bdd position composant
restant();      //Requête bdd nbr de composants restants
}

void ihmtiroclass::position()
{
    QString ID = ui->searchbar->text();
    QString intID = ID;
    QString url = db->rechercher(intID);
    ui->textposition->setText(url);
}

void ihmtiroclass::restant()
{
    QString ID = ui->searchbar->text();
    QString intID = ID;
    QString nbr = db->quantite(intID);
    ui->textnbr->setText(nbr);
}

void ihmtiroclass::addcompo()      //ajouter composant dans la BDD
{
    tableau[1] = "";
    tableau[2] = "";
    tableau[3] = "";
    tableau[4] = "";

    QString Ref = ui->IdObject->text();
    QString Nom = ui->NomObject->text();
    QString Etage = ui->EtageObject->text();
    QString Nombre = ui->NombreObject->text();


    tableau[1] = Ref;        //reference
    tableau[2] = Nom;
    tableau[3] = Etage;
    tableau[4] = Nombre;

    if((Ref=="")||(Nom=="")||(Etage=="")||(Nombre==""))
    {
        QMessageBox::information(this, "Erreur", "Information Manquante");   //etage selectionner incorrect
    }
    else {

        if(Etage=="1")
        {
            QString toto = db->ajouter(tableau);
            reset();
        }
        else {
            if(Etage=="2")
            {
                QString toto = db->ajouter(tableau);
                reset();
            }
            else {
                if(Etage=="3")
                {
                    QString toto = db->ajouter(tableau);
                    reset();
                }
                else {
                    if(Etage=="4")
                    {
                        QString toto = db->ajouter(tableau);
                        reset();
                    }
                    else {
                        if(Etage=="5")
                        {
                            QString toto = db->ajouter(tableau);
                            reset();
                        }
                        else {
                            if(Etage=="6")
                            {
                                QString toto = db->ajouter(tableau);
                                reset();
                            }
                            else {
                                if(Etage=="7")
                                {
                                    QString toto = db->ajouter(tableau);
                                    reset();
                                }
                                else {
                                    if(Etage=="8")
                                    {
                                        QString toto = db->ajouter(tableau);
                                        reset();
                                    }
                                    else {
                                        if(Etage=="9")
                                        {
                                            QString toto = db->ajouter(tableau);
                                            reset();
                                        }
                                        else {
                                            QMessageBox::information(this, "erreur", "Numero de tiroir incorrect");   //etage selectionner incorrect
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void ihmtiroclass::reset()
{
    ui->IdObject->setText("");
    ui->NomObject->setText("");
    ui->NombreObject->setValue(1);
    ui->EtageObject->setText("");
    position();
    restant();
}

void ihmtiroclass::on_quitterbutton_clicked()
{
    this->close();
}

void ihmtiroclass::on_connectionBDD_clicked()   // a enlever
{
    connection();
}

void ihmtiroclass::on_load_clicked()        //a enlever
{
    refresh();
}

void ihmtiroclass::on_recherche_clicked()
{
    recherche();
}

void ihmtiroclass::on_takebutton_clicked()
{
    QString ID = ui->searchbar->text();
    QString intID = ID;
    int take = ui->spinBox->value();
    QString url = db->prendre(intID, take);
    qDebug() <<url;

    if(url=="1")            //envoie information au tiroclass par port COM
    {
        serial->write("1");

    }
    if(url=="2")
    {
        serial->write("2");

    }
    if(url=="3")
    {
        serial->write("3");

    }
    if(url=="4")
    {
        serial->write("4");

    }
    if(url=="5")
    {
        serial->write("5");

    }
    if(url=="6")
    {
        serial->write("6");

    }
    if(url=="7")
    {
        serial->write("7");

    }
    if(url=="8")
    {
        serial->write("8");

    }
    if(url=="9")
    {
        serial->write("9");

    }
    restant();
    refresh();
}

void ihmtiroclass::on_AddObject_clicked()
{
    addcompo();
    refresh();
}
