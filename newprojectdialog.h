#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class newprojectdialog;
}

class NewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewProjectDialog(QWidget *parent = nullptr);
    ~NewProjectDialog();

    QString getProjectName() const;
    QString getProjectDescription() const;
    QString getProjectDesignDocument() const;

private:
    Ui::newprojectdialog *ui;
};

#endif // NEWPROJECTDIALOG_H
