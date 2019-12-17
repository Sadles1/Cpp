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
    if(!m_db.tables().contains("Firm")) // если в базе не существует таблица  Person,
    {
         query->clear(); // очистка запроса
         query->exec("CREATE   TABLE   Firm(ID   INTEGER   PRIMARY   KEY, Name VARCHAR, Route VARCHAR, Price INTEGER);");  // исполнение запроса на добавление запис
         query->clear();
         query->exec("INSERT INTO Firm (ID,Name,Route,Price) VALUES (1,'Firm1','Perm-Moscow', 20);");
         query->clear();
         query->exec("INSERT INTO Firm (ID,Name,Route,Price) VALUES (2,'Firm2','Perm-Moscow', 37);");
    }
    if(!m_db.tables().contains("Person")) // если в базе не существует таблица  Person,
    {
         query->clear(); // очистка запроса
         query->exec("CREATE   TABLE   Person(ID   INTEGER   PRIMARY   KEY, Name VARCHAR, Route VARCHAR, Firm VARCHAR);");  // исполнение запроса на добавление запис
         query->clear();
         query->exec("INSERT INTO Person(ID,Name,Route,Firm) VALUES (1,'Andrey','Perm-Moscow', 'Firm1');");
         query->clear();
         query->exec("INSERT INTO Person(ID,Name,Route,Firm) VALUES (2,'Elena','Perm-Moscow', 'Firm2');");
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
    ui->tableView_3->setModel(model);
    ui->tableView_4->setModel(modelperson);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete query;
    delete model;
}


void MainWindow::on_allDataViewButton_clicked()
{
    model->setFilter("");
    model->select();
    ui->tableView->setModel(model);
}

void MainWindow::on_filterDataButton_clicked()
{
    model->setFilter("Price>20");
    model->select();
    ui->tableView->setModel(model);
}

void MainWindow::on_filterData2Button_clicked()
{
     model->setFilter("Price<21");
     model->select();
     ui->tableView->setModel(model);
}

void MainWindow::on_pushButtonAdd_clicked()
{

    if(ui->lineEditName->text().isEmpty()||ui->lineEditRemainingTour->text().isEmpty()||ui->lineEditID->text().isEmpty()||ui->lineEditRoute->text().isEmpty())
            return;
    QString id = ui->lineEditID->text();
    QString name = ui->lineEditName->text();
    QString route = ui->lineEditRoute->text();
    QString RemaingTour = ui->lineEditRemainingTour->text();
    QString buf = tr("INSERT INTO Firm (ID,Name,Route,Price) VALUES (")+id+tr(",'")+name+tr("','")+route+tr("',")+RemaingTour+tr(");");
    query->clear();
    query->exec(buf);
    model->select();
}

void MainWindow::on_pushButtonRem_clicked()
{
     if(ui->lineEditID->text().isEmpty())
         return;
     QString id = ui->lineEditID->text();
     query->clear();
     query->exec(tr("DELETE FROM Firm WHERE ID = ")+id);
     model->select();
}

void MainWindow::on_pushButtonAddPerson_clicked()
{
    if(ui->lineEditNamePerson->text().isEmpty()||ui->lineEditFirm->text().isEmpty()||ui->lineEditIDPerson->text().isEmpty()||ui->lineEditRoutePerson->text().isEmpty())
            return;
    QString id = ui->lineEditIDPerson->text();
    QString name = ui->lineEditNamePerson->text();
    QString route = ui->lineEditRoutePerson->text();
    QString firm = ui->lineEditFirm->text();
    QString buf = tr("INSERT INTO Person(ID,Name,Route,Firm) VALUES (")+id+tr(",'")+name+tr("','")+route+tr("','")+firm+tr("');");
    query->clear();
    query->exec(buf);
    modelperson->select();
}

void MainWindow::on_pushButtonRemPerson_clicked()
{
    if(ui->lineEditIDPerson->text().isEmpty())
        return;
    QString id = ui->lineEditIDPerson->text();
    query->clear();
    query->exec(tr("DELETE FROM Person WHERE ID = ")+id);
    modelperson->select();
}
