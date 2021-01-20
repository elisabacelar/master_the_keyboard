#include "login.h"
#include "ui_login.h"

static QSqlDatabase DataBase=QSqlDatabase::addDatabase("QSQLITE");

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    DataBase.setDatabaseName("D:/Documentos/QT Creator/teste-1/test_1/data/data_mtk.db");

    if(!DataBase.open())
    {
        ui->label->setText("Database not open");
    } else
    {
        ui->label->setText("Database open");
    }
}

Login::~Login()
{
    delete ui;
}


void Login::on_btnLogin_clicked()
{
    QString username = ui->txtUsername->text();
    QString password = ui->txtPassword->text();

    if(!DataBase.isOpen())
    {
        qDebug()<<"Failed to open database.";
        return;
    }
    QSqlQuery query;
    if(query.exec("select * from tbMtk where user='"+username+"' and password='"+password+"'"))
    {
        int count=0;
        while(query.next())
        {
            count++;
        }
        if(count>0)
        {
            this->close();
            MainWindow window1;
            window1.setModal(true);
            window1.exec();
        } else
        {
           ui->label->setText("User not found");
           ui->txtUsername->clear();
           ui->txtPassword->clear();
           ui->txtUsername->setFocus();
        }
    }
}
