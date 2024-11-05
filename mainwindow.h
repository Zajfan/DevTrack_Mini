#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class
 MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_Project_triggered();
    void on_actionNew_Project_triggered();
    void on_actionSave_Project_triggered();
    void on_actionSave_Project_As_triggered();
    void on_actionClose_Project_triggered();

    void on_actionImport_Project_triggered();

    void on_actionImport_Project_List_triggered();
    void on_actionExport_Project_triggered();
    void on_actionExport_Project_List_triggered();
    void on_actionPreferences_triggered();
    void on_actionExit_triggered();
    void on_tabWidget_tabBarClicked(int index);
    void onAddNewProjectButtonClicked();
    void onTreeWidget_Projects_itemSelectionChanged();

private:
    Ui::MainWindow *ui;
    QMap<QString, QPair<QString, QString>> projectDetails;
    QTreeWidgetItem *rootItem;
};
#endif // MAINWINDOW_H
