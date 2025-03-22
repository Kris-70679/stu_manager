#ifndef EDITSTUDENTDIALOG_H
#define EDITSTUDENTDIALOG_H

#include <QDialog>

namespace Ui {
class EditStudentDialog;
}

class EditStudentDialog : public QDialog
{
    Q_OBJECT

public:
   explicit EditStudentDialog(QWidget *parent = nullptr, const QString &studentId = QString());
    ~EditStudentDialog();


private slots:
    void on_cancelButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::EditStudentDialog *ui;
    void loadStudentInfo(const QString &studentId);  // 加载学生信息的函数
};

#endif // EDITSTUDENTDIALOG_H
