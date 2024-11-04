#include "constants.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "newprojectdialog.h"
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include <QDebug>
#include <QMap>
#include <QTreeWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionOpen_Project,
        &QAction::triggered, this, &MainWindow::on_actionOpen_Project_triggered);
        connect(ui->actionNew_Project, &QAction::triggered, this, &MainWindow::on_actionNew_Project_triggered);
    connect(ui->actionSave_Project_2, &QAction::triggered, this, &MainWindow::on_actionSave_Project_triggered);
    connect(ui->actionSave_Project_As, &QAction::triggered, this, &MainWindow::on_actionSave_Project_As_triggered);
    connect(ui->actionClose_Project, &QAction::triggered, this, &MainWindow::on_actionClose_Project_triggered);
    connect(ui->actionImport_Project, &QAction::triggered, this, &MainWindow::on_actionImport_Project_triggered);
    connect(ui->actionImport_Project_List, &QAction::triggered, this, &MainWindow::on_actionImport_Project_List_triggered);
    connect(ui->actionExport_Project, &QAction::triggered, this, &MainWindow::on_actionExport_Project_triggered);
    connect(ui->actionExport_Project_List, &QAction::triggered, this, &MainWindow::on_actionExport_Project_List_triggered);
    connect(ui->actionPreferences_Settings, &QAction::triggered, this, &MainWindow::on_actionPreferences_triggered);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);

    connect(ui->tabWidget, &QTabWidget::tabBarClicked, this, &MainWindow::on_tabWidget_tabBarClicked);

    connect(ui->button_AddProject, &QPushButton::clicked, this, &MainWindow::onAddNewProjectButtonClicked);

    // Add the root item to the tree widget
    rootItem = new QTreeWidgetItem(ui->treeWidget_Projects);
    rootItem->setText(0, "Projects");
    ui->treeWidget_Projects->addTopLevelItem(rootItem);

    setCentralWidget(ui->centralwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_Project_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Project", "", "DevTrack Files (*." + DEVTRACK_FILE_EXTENSION + ")");
    if (!fileName.isEmpty()) {
        qDebug() << "Opening project:" << fileName;
    }
}

void MainWindow::on_actionNew_Project_triggered() {
    NewProjectDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString projectName = dialog.getProjectName();
        QString projectDescription = dialog.getProjectDescription();
        QString projectDesignDocument = dialog.getProjectDesignDocument();

        QWidget *projectOverview = new QWidget();
        ui->tabWidget->addTab(projectOverview, projectName);

        qDebug() << "Creating a new project:" << projectName;
        qDebug() << "Project Description:" << projectDescription;
        qDebug() << "Project Design Document:" << projectDesignDocument;
    }
}

void MainWindow::on_actionSave_Project_triggered() {
    if (ui->tabWidget->count() == 0) {
        on_actionSave_Project_As_triggered();
    } else {
        qDebug() << "Saving the current project";
    }
}

void MainWindow::on_actionSave_Project_As_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Project As", "", "DevTrack Files (*.devtrack)");
    if (!fileName.isEmpty()) {
        qDebug() << "Saving project as:" << fileName;
    }
}

void MainWindow::on_actionClose_Project_triggered() {
    bool unsavedChanges = false;
    if (unsavedChanges) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Unsaved Changes", "You have unsaved changes. Do you really want to close the project?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }
    }
    ui->tabWidget->clear();
    qDebug() << "Closing the current project";
}

void MainWindow::on_actionImport_Project_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, "Import Project", "", "DevTrack Files (*.devtrack)");
    if (!fileName.isEmpty()) {
        qDebug() << "Importing project:" << fileName;
    }
}

void MainWindow::on_actionImport_Project_List_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, "Import Project List", "", "Project List Files (*.plist)");
    if (!fileName.isEmpty()) {
        qDebug() << "Importing project list:" << fileName;
    }
}

void MainWindow::on_actionExport_Project_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, "Export Project", "", "DevTrack Files (*.devtrack)");
    if (!fileName.isEmpty()) {
        qDebug() << "Exporting project:" << fileName;
    }
}

void MainWindow::on_actionExport_Project_List_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, "Export Project List", "", "Project List Files (*.plist)");
    if (!fileName.isEmpty()) {
        qDebug() << "Exporting project list:" << fileName;
    }
}

void MainWindow::on_actionPreferences_triggered() {
    qDebug() << "Opening Preferences";
}

void MainWindow::on_actionExit_triggered() {
    bool unsavedChanges = false;
    if (unsavedChanges) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Unsaved Changes", "You have unsaved changes. Do you really want to exit?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }
    }

    qDebug() << "Exiting DevTrack";
    QCoreApplication::quit();
}

void MainWindow::on_tabWidget_tabBarClicked(int index) {
    if (ui->tabWidget->tabText(index) == "Overview") {
        return;
    }

    QString projectName = ui->tabWidget->tabText(index);
    QWidget *projectDetails = new QWidget();
    ui->tabWidget->addTab(projectDetails, projectName + " Details");
    ui->tabWidget->setCurrentWidget(projectDetails);
    qDebug() << "Opening project details for:" << projectName;
}

void MainWindow::onAddNewProjectButtonClicked() {
    NewProjectDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString projectName = dialog.getProjectName();
        QString projectShortDescription = dialog.getProjectDescription();
        QString projectLongDescription = dialog.getProjectDesignDocument();

        // Add project to tree widget (under the root item)
        QTreeWidgetItem *projectItem = new QTreeWidgetItem(rootItem);
        projectItem->setText(0, projectName);

        // Store project details
        projectDetails[projectName] = {projectShortDescription, projectLongDescription};
    }
}
