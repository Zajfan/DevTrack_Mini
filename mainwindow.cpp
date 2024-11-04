#include "constants.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "newprojectdialog.h"
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Connect menu items to slots
    connect(ui->actionOpen_Project, &QAction::triggered, this, &MainWindow::on_actionOpen_Project_triggered);
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

    // Connect tab widget signal to slot
    connect(ui->tabWidget, &QTabWidget::tabBarClicked, this, &MainWindow::on_tabWidget_tabBarClicked);

    // Set central widget
    setCentralWidget(ui->centralwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_Project_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Project", "", "DevTrack Files (*." + DEVTRACK_FILE_EXTENSION + ")");
    if (!fileName.isEmpty()) {
        // Load the project from the selected file
        // For example, you might read the file and populate the tab view
        qDebug() << "Opening project:" << fileName;
    }
}

void MainWindow::on_actionNew_Project_triggered() {
    NewProjectDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString projectName = dialog.getProjectName();
        QString projectDescription = dialog.getProjectDescription();
        QString projectDesignDocument = dialog.getProjectDesignDocument();

        // Create a new project tab
        QWidget *projectOverview = new QWidget();
        ui->tabWidget->addTab(projectOverview, projectName);

        // Optionally, store the project description and design document
        // For example, you might add them to the projectOverview widget

        qDebug() << "Creating a new project:" << projectName;
        qDebug() << "Project Description:" << projectDescription;
        qDebug() << "Project Design Document:" << projectDesignDocument;
    }
}

void MainWindow::on_actionSave_Project_triggered() {
    // Check if a project is open, then save or use Save As logic
    if (ui->tabWidget->count() == 0) {
        on_actionSave_Project_As_triggered();
    } else {
        // Save the current project
        qDebug() << "Saving the current project";
    }
}

void MainWindow::on_actionSave_Project_As_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Project As", "", "DevTrack Files (*.devtrack)");
    if (!fileName.isEmpty()) {
        // Save the project to the specified file
        qDebug() << "Saving project as:" << fileName;
    }
}

void MainWindow::on_actionClose_Project_triggered() {
    // Check for unsaved changes, then clear project data and reset UI
    bool unsavedChanges = false; // Replace with actual condition to check for unsaved changes
    if (unsavedChanges) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Unsaved Changes", "You have unsaved changes. Do you really want to close the project?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No) {
            return; // Do not close
        }
    }
    ui->tabWidget->clear();
    qDebug() << "Closing the current project";
}

void MainWindow::on_actionImport_Project_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, "Import Project", "", "DevTrack Files (*.devtrack)");
    if (!fileName.isEmpty()) {
        // Import the project from the selected file
        qDebug() << "Importing project:" << fileName;
    }
}

void MainWindow::on_actionImport_Project_List_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, "Import Project List", "", "Project List Files (*.plist)");
    if (!fileName.isEmpty()) {
        // Import the project list from the selected file
        qDebug() << "Importing project list:" << fileName;
    }
}

void MainWindow::on_actionExport_Project_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, "Export Project", "", "DevTrack Files (*.devtrack)");
    if (!fileName.isEmpty()) {
        // Export the current project to the specified file
        qDebug() << "Exporting project:" << fileName;
    }
}

void MainWindow::on_actionExport_Project_List_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, "Export Project List", "", "Project List Files (*.plist)");
    if (!fileName.isEmpty()) {
        // Export the project list to the specified file
        qDebug() << "Exporting project list:" << fileName;
    }
}

void MainWindow::on_actionPreferences_triggered() {
    // Open preferences dialog
    qDebug() << "Opening Preferences";
}

void MainWindow::on_actionExit_triggered() {
    // Check for unsaved changes
    bool unsavedChanges = false; // Replace with actual condition to check for unsaved changes
    if (unsavedChanges) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Unsaved Changes", "You have unsaved changes. Do you really want to exit?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No) {
            return; // Do not exit
        }
    }

    // Close the application
    qDebug() << "Exiting DevTrack";
    QCoreApplication::quit();
}

void MainWindow::on_tabWidget_tabBarClicked(int index) {
    // Check if the clicked tab is the "Overview" tab
    if (ui->tabWidget->tabText(index) == "Overview") {
        return; // Do nothing if it's the Overview tab
    }

    // For other tabs, open project details in a new tab (as before)
    QString projectName = ui->tabWidget->tabText(index);
    QWidget *projectDetails = new QWidget();
    ui->tabWidget->addTab(projectDetails, projectName + " Details");
    ui->tabWidget->setCurrentWidget(projectDetails);
    qDebug() << "Opening project details for:" << projectName;
}
