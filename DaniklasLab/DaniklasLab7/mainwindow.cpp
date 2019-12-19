#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_db = QSqlDatabase::addDatabase("QSQLITE"); //соединение объекта базы данных с СУБД
    m_db.setDatabaseName("myDB");  //определение имени базы данных
    query = new QSqlQuery(m_db); // создание объекта для запроса
    if(!m_db.open()) // проверка на ошибку при открытии или создании базы данных
         throw "can't open database";
    if(!m_db.tables().contains("Firm")) // если в базе не существует таблица  Firm,
    {
         query->clear(); // очистка запроса
         query->exec("CREATE   TABLE   Firm(ID   INTEGER   PRIMARY   KEY,Route VARCHAR, Price INTEGER,Client VARCHAR);");  // исполнение запроса на добавление запис
         query->clear();
         query->exec("INSERT INTO Firm (ID,Route,Price,Client) VALUES (1,'Perm-Moscow', 100,'Vasiliy');");
         query->clear();
         query->exec("INSERT INTO Firm (ID,Route,Price,Client) VALUES (2,'Perm-Moscow', 250,'Andrey');");
    }
    if(!m_db.tables().contains("Person")) // если в базе не существует таблица  Person,
    {
         query->clear(); // очистка запроса
         query->exec("CREATE   TABLE   Person(ID   INTEGER   PRIMARY   KEY, Name VARCHAR, Age INTEGER);");  // исполнение запроса на добавление запис
         query->clear();
         query->exec("INSERT INTO Person(ID,Name,Age) VALUES (1,'Vasiliy', 23);");
         query->clear();
         query->exec("INSERT INTO Person(ID,Name,Age) VALUES (2,'Andrey',32);");
    }
    model = new QSqlTableModel(this,m_db); // создание редактируемой модели базы данных
    modelperson=new QSqlTableModel(this,m_db);
    model->setTable("Firm"); // создание модели таблицы  Person
    modelperson->setTable("Person");
    model->select(); //заполнение модели данными
    modelperson->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);// выбор стратегии
    modelperson->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setModel(model); //соединение модели// и ее табличного представления в форме
    ui->tableView_2->setModel(modelperson);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete query;
    delete model;
}



void MainWindow::on_filterDataButton_clicked()
{
    model->sort(2,Qt::AscendingOrder);
    model->select();
    ui->tableView->setModel(model);
}

void MainWindow::on_filterData2Button_clicked()
{
     model->sort(2,Qt::DescendingOrder);
     model->select();
     ui->tableView->setModel(model);
}

void MainWindow::on_pushButtonAdd_clicked()
{

    if(ui->lineEditClient->text().isEmpty()||ui->lineEditPrice->text().isEmpty()||ui->lineEditID->text().isEmpty()||ui->lineEditRoute->text().isEmpty())
            return;
    QString id = ui->lineEditID->text();
    QString Client = ui->lineEditClient->text();
    QString route = ui->lineEditRoute->text();
    QString Price = ui->lineEditPrice->text();
    QString buf = tr("INSERT INTO Firm (ID,Route,Price,Client) VALUES (")+id+tr(",'")+route+tr("',")+Price+tr(",'")+Client+tr("');");
    query->clear();
    query->exec(buf);
    buf = tr("INSERT INTO Person(ID,Name) VALUES (")+id+tr(",'")+Client+tr("');");
    query->clear();
    query->exec(buf);

    model->select();
    modelperson->select();
}

void MainWindow::on_pushButtonRem_clicked()
{
     if(ui->lineEditID->text().isEmpty())
         return;
     QString id = ui->lineEditID->text();
     query->clear();
     query->exec(tr("DELETE FROM Person WHERE ID = ")+id);
     query->clear();
     query->exec(tr("DELETE FROM Firm WHERE ID = ")+id);
     model->select();
     modelperson->select();
}

void MainWindow::on_pushButtonRemPerson_clicked()
{
    if(ui->lineEditIDPerson->text().isEmpty())
        return;
    QString id = ui->lineEditIDPerson->text();
    query->clear();
    query->exec(tr("DELETE FROM Person WHERE ID = ")+id);
    query->clear();
    query->exec(tr("DELETE FROM Firm WHERE ID = ")+id);
    model->select();
    modelperson->select();
}

void MainWindow::on_pushButtonAdd_2_clicked()
{
    if(ui->lineEditClient_2->text().isEmpty()||ui->lineEditAge->text().isEmpty())
        return;

    QString id =ui->lineEditIDPerson->text();
    QString Client = ui->lineEditClient_2->text();
    QString Age = ui->lineEditAge->text();
    QString buf = tr("INSERT INTO Person(ID,Name,Age) VALUES (")+id+tr(",'")+Client+tr("',")+Age+tr(");");
    query->clear();
    query->exec(buf);
    buf = tr("INSERT INTO Firm (ID,Client) VALUES (")+id+tr(",'")+Client+tr("');");
    query->clear();
    query->exec(buf);

    model->select();
    modelperson->select();

}

void MainWindow::on_filterDataButton_2_clicked()
{
    model->sort(3,Qt::AscendingOrder);
    model->select();
    ui->tableView->setModel(model);
}


void MainWindow::on_filterDataButton_3_clicked()
{
    model->sort(3,Qt::DescendingOrder);
    model->select();
    ui->tableView->setModel(model);
}

void MainWindow::on_filterDataButton_4_clicked()
{
    modelperson->sort(1,Qt::AscendingOrder);
    modelperson->select();
    ui->tableView_2->setModel(modelperson);
}

void MainWindow::on_filterDataButton_5_clicked()
{
    modelperson->sort(1,Qt::DescendingOrder);
    modelperson->select();
    ui->tableView_2->setModel(modelperson);
}
