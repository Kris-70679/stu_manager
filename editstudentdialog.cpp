#include "editstudentdialog.h"
#include "ui_editstudentdialog.h"
#include <QSqlQuery>
#include <QMessageBox>
EditStudentDialog::EditStudentDialog(QWidget *parent, const QString &studentId)
    : QDialog(parent)
    , ui(new Ui::EditStudentDialog)
{
    ui->setupUi(this);

    setWindowTitle("Modify Student");
    setWindowIcon(QIcon (":/icon.png"));  // 设置窗口图标
    loadStudentInfo(studentId);

}

EditStudentDialog::~EditStudentDialog()
{
    delete ui;
}

void EditStudentDialog::loadStudentInfo(const QString &studentId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM students WHERE student_id = ?");
    query.addBindValue(studentId);

    if (query.exec() && query.next()) {
        ui->studentIdLineEdit->setText(query.value("student_id").toString());
        ui->usernameLineEdit->setText(query.value("username").toString());
        ui->passwordLineEdit->setText(query.value("password").toString());
        ui->birthLineEdit->setText(query.value("birth").toString());
        ui->genderLineEdit->setText(query.value("gender").toString());
        ui->scoreLineEdit->setText(query.value("score").toString());
    } else {
        // 查询失败，提示错误信息
        QMessageBox::warning(this, "Error", "Failed to load student data.");
        qDebug() << "Error loading student data:";
    }
}

void EditStudentDialog::on_cancelButton_clicked()
{
    this->reject();
}

void EditStudentDialog::on_confirmButton_clicked()
{
    QString studentId = ui->studentIdLineEdit->text(); // 学号
    QString username = ui->usernameLineEdit->text();   // 用户名
    QString password = ui->passwordLineEdit->text();   // 密码
    QString birth = ui->birthLineEdit->text();          // 出生日期
    QString gender = ui->genderLineEdit->text();        // 性别
    int score = ui->scoreLineEdit->text().toInt();      // 成绩

    // 检查是否有空字段
    if (studentId.isEmpty() || username.isEmpty() || birth.isEmpty() || gender.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请填写所有字段！");
        return;
    }
    // 确保 score 是有效的整数
    if (score <= 0) {
        QMessageBox::warning(this, "输入错误", "成绩必须是有效的正整数！");
        return;
    }
    // 更新数据到数据库
    QSqlQuery query;
    query.prepare("UPDATE students SET username = :username, password = :password, "
                  "birth = :birth, gender = :gender, score = :score "
                  "WHERE student_id = :student_id");

    query.bindValue(":student_id", studentId);
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":birth", birth);
    query.bindValue(":gender", gender);
    query.bindValue(":score", score);

    // 执行更新操作
    if (query.exec()) {
        QMessageBox::information(this, "成功", "学生信息修改成功！");
        this->accept(); // 关闭对话框并返回成功
    } else {
        QMessageBox::critical(this, "错误", "学生信息修改失败: " + query.lastQuery());
    }
}

