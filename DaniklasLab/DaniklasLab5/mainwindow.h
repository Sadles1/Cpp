#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void digits_numbers();
    void on_pushButton_dot_clicked();
    void operations();
    void on_pushButton_clear_clicked();
    void on_pushButton_res_clicked();
    void math_operations();
    void on_pushButton_ln_clicked();
    void on_pushButton_arcsin_clicked();
    void on_pushButton_sqrt_clicked();
    void on_pushButton_clicked();
    void on_pushButton_sqr_clicked();
    void on_pushButton_pow_clicked();
};
#endif // MAINWINDOW_H
