#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"page_login.h"
#include<QSqlTableModel>
#include "addstudentdialog.h"
#include "editstudentdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_refreshButton_clicked();

    void on_addButton_clicked();

    void on_modifyButton_clicked();

    void on_deleteButton_clicked();

    void on_selectButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    Page_Login pglg;

    QSqlDatabase db;         // 数据库连接
    QSqlTableModel *model;   // 数据模型

    void connectDatabase();  // 连接数据库
    void loadStudents();     // 加载学生数据
    QString getSelectedStudentId();

};
#endif // MAINWINDOW_H
