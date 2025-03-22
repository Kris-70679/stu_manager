#include "addstudentdialog.h"
#include "ui_addstudentdialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QPixmap>

AddStudentDialog::AddStudentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddStudentDialog)
{
    ui->setupUi(this);
    setWindowTitle("Add Student");
    setWindowIcon(QIcon (":/icon.png"));  // 设置窗口图标
}

AddStudentDialog::~AddStudentDialog()
{
    delete ui;
}

void AddStudentDialog::on_cancelButton_clicked()
{
    // 关闭当前对话框，返回 Rejected 状态
    this->reject();
}


void AddStudentDialog::on_confirmButton_clicked()
{
    QString studentId = ui->studentIdLineEdit->text(); // 学号
    QString username = ui->usernameLineEdit->text();   // 用户名
    QString password = ui->passwordLineEdit->text();                      // 默认密码
    QString birth = ui->birthLineEdit->text();          // 出生日期
    QString gender = ui->genderLineEdit->text();        // 性别
    int score = ui->scoreLineEdit->text().toInt();      // 成绩

    // 检查是否有空字段
    if (studentId.isEmpty() || username.isEmpty() || birth.isEmpty() || gender.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请填写所有字段！");
        return;
    }

    // 插入数据到数据库
    QSqlQuery query;
    query.prepare("INSERT INTO students (student_id, username, password, birth, gender, score) "
                  "VALUES (:student_id, :username, :password, :birth, :gender, :score)");

    query.bindValue(":student_id", studentId);
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":birth", birth);
    query.bindValue(":gender", gender);
    query.bindValue(":score", score);

    // 执行插入操作
    if (query.exec()) {
        QMessageBox::information(this, "成功", "学生信息添加成功！");
        this->accept(); // 关闭对话框并返回成功
    } else {
        QMessageBox::critical(this, "错误", "插入数据失败!");
    }
}

