#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_allDataViewButton_clicked();

    void on_filterDataButton_clicked();

    void on_filterData2Button_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonRem_clicked();

    void on_pushButtonAddPerson_clicked();

    void on_pushButtonRemPerson_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase m_db; // объект базы данных
    QSqlQuery* query; // указатель на запрос
    QSqlTableModel* model; // указатель на таблицу данных в приложении
    QSqlTableModel* modelperson; // указатель на таблицу данных в приложении
};
#endif // MAINWINDOW_H
