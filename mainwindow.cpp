#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pglg.show();

    auto f = [&](){
        this->show();
    };

    connect(&pglg, &Page_Login::sendLoginSuccess,this,f);
    loadStudents();
    //ui->treeWidget->addTopLevelItem(new QTreeWidgetItem(ui->treeWidget, l));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectDatabase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("mydatabase"); // 替换为你的数据库名
    db.setUserName("test1");           // 替换为你的数据库用户名
    db.setPassword("12345678");         // 替换为你的数据库密码

    if(db.open()){
        QMessageBox::information(nullptr,"连接提示"," 连接成功");
    }else{
        QMessageBox::warning(nullptr,"连接提示"," 连接失败");
    }
}

void MainWindow::loadStudents()
{
    model = new QSqlTableModel(this, db);
    model->setTable("students");  // 绑定表
    model->setEditStrategy(QSqlTableModel::OnManualSubmit); // 手动提交模式
    model->select();  // 加载数据

    // 设置表头
    model->setHeaderData(0, Qt::Horizontal, "学号");
    model->setHeaderData(1, Qt::Horizontal, "用户名");
    model->setHeaderData(2, Qt::Horizontal, "密码");
    model->setHeaderData(3, Qt::Horizontal, "出生日期");
    model->setHeaderData(4, Qt::Horizontal, "性别");
    model->setHeaderData(5, Qt::Horizontal, "成绩");

    // 绑定数据到 QTableView
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents(); // 自动调整列宽
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    // 手动设置每列的宽度（可选）
    int columnCount = model->columnCount();
    for (int i = 0; i < columnCount; i++) {
        // 你可以根据需求设置列宽度，例如：
        ui->tableView->setColumnWidth(i, ui->tableView->width() / columnCount);
    }

}

QString MainWindow::getSelectedStudentId() {
    // 获取选中的行
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();

    // 如果没有选中行，弹出提示框并返回空字符串
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "Please select a student to edit.");
        return QString(); // 返回空字符串
    }

    // 获取选中的第一行
    int selectedRow = selectedRows.first().row();

    QString studentId = ui->tableView->model()->data(ui->tableView->model()->index(selectedRow, 0)).toString();
    return studentId;
}


void MainWindow::on_refreshButton_clicked()
{
    if (model) {
        model->select();  // 重新从数据库获取最新数据
        ui->tableView->resizeColumnsToContents(); // 重新调整列宽
    }
}


void MainWindow::on_addButton_clicked()
{
    // 创建 AddStudentDialog 对话框实例
    AddStudentDialog addDialog(this);

    // 弹出对话框并等待用户输入
    if (addDialog.exec() == QDialog::Accepted) {
        // 如果添加成功，更新学生列表
        loadStudents();
    }

}


void MainWindow::on_modifyButton_clicked()
{
    EditStudentDialog *editDialog = new EditStudentDialog(this, getSelectedStudentId());
    editDialog->exec();  // 使用 exec() 打开模态窗口
}


void MainWindow::on_deleteButton_clicked()
{
    // 获取选中的学生 ID
    QString studentId = getSelectedStudentId();

    // 如果没有选中学生，返回
    if (studentId.isEmpty()) {
        return;
    }

    // 弹出确认删除的对话框
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除", "确定要删除该学生信息吗？",
                                  QMessageBox::Yes | QMessageBox::No);

    // 如果点击了 "Yes"，则执行删除操作
    if (reply == QMessageBox::Yes) {
        // 执行删除操作
        QSqlQuery query;
        query.prepare("DELETE FROM students WHERE student_id = :student_id");
        query.bindValue(":student_id", studentId);

        if (query.exec()) {
            QMessageBox::information(this, "成功", "学生信息删除成功！");
            // 刷新界面，重新加载数据（例如：刷新 tableView）
            loadStudents();
        } else {
            QMessageBox::critical(this, "错误", "删除学生信息失败！");
        }
    }
}


void MainWindow::on_selectButton_clicked()
{
    QString information = ui->lineEdit->text();

    // 如果没有输入搜索信息，返回
    if (information.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入搜索内容！");
        return;
    }

    // 使用模糊搜索，查找学号、用户名、性别等
    QSqlQuery query;
    query.prepare("SELECT student_id, username, password, birth, gender, score "
                  "FROM students "
                  "WHERE student_id LIKE :information "
                  "OR username LIKE :information "
                  "OR gender LIKE :information "
                  "OR birth LIKE :information "
                  "OR score LIKE :information");

    // 添加 '%' 通配符以进行模糊匹配
    query.bindValue(":information", "%" + information + "%");

    // 执行查询
    if (query.exec()) {
        // 如果查询成功，将结果显示到表格中
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(query);
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
    } else {
        // 如果查询失败，弹出错误信息
        QMessageBox::critical(this, "错误", "搜索失败！");
    }
}



void MainWindow::on_exitButton_clicked()
{
    this->close();
}

