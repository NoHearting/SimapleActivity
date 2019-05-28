#ifndef CREATECHILDACTIVITY_H
#define CREATECHILDACTIVITY_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class CreateChildActivity;
}

class CreateChildActivity : public QDialog
{
    Q_OBJECT

public:
    explicit CreateChildActivity(QString win_name = "",QWidget *parent = 0);
    ~CreateChildActivity();

    /// @brief 清空两个编辑框的内容
    ///
    void clear();

private slots:
    void on_pushButton_finished_clicked();

private:
    Ui::CreateChildActivity *ui;
signals:
    void created(QString act_name,QString act_description);
};

#endif // CREATECHILDACTIVITY_H
