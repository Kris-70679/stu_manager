#include "page_login.h"
#include "ui_page_login.h"

Page_Login::Page_Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Page_Login)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.75.133");
    db.setDatabaseName("mydatabase");
    db.setUserName("test1");
    db.setPassword("12345678");

    if(db.open()){
        QMessageBox::information(nullptr,"连接提示"," 连接成功");
    }else{
        QMessageBox::warning(nullptr,"连接提示"," 连接失败");
    }
}

Page_Login::~Page_Login()
{
    delete ui;
}

void Page_Login::login(const QString &tableName)
{
    QSqlQuery query;
    QString sql = QString("SELECT * FROM %1 WHERE username = :username AND password = :password").arg(tableName);

    query.prepare(sql);
    query.bindValue(":username", ui->username->text());
    query.bindValue(":password", ui->password->text());

    if (!query.exec()) {
        qDebug() << "查询失败: " << query.lastQuery();
    } else if (query.next()) {
        qDebug() << "登录成功！用户：" << ui->username->text();
        emit sendLoginSuccess();
    } else {
        qDebug() << "登录失败：用户名或密码错误";
        QMessageBox::warning(nullptr, "登陆提示", "用户名或密码错误，登陆失败");
    }
}

void Page_Login::on_btn_login_clicked()
{
    //数据库查找用户名和密码
    if (ui->admin_radioButton->isChecked()) {
        qDebug() << "用户选择了管理员模式";
        login("admins");
    } else if (ui->stu_radioButton->isChecked()) {
        qDebug() << "用户选择了学生模式";
        login("students");
    }
}


void Page_Login::on_btn_exit_clicked()
{
    exit(0);
}

