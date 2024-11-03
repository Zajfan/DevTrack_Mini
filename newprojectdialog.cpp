#include "newprojectdialog.h"
#include "ui_newprojectdialog.h"

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newprojectdialog)
{
    ui->setupUi(this);
}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}

QString NewProjectDialog::getProjectName() const
{
    return ui->projectNameLineEdit->text();
}

QString NewProjectDialog::getProjectDescription() const
{
    return ui->projectDescriptionTextEdit->toPlainText();
}

QString NewProjectDialog::getProjectDesignDocument() const
{
    return ui->projectDesignDocumentTextEdit->toPlainText();
}
