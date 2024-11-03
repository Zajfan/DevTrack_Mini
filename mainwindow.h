#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Project {
public:
    Project(const QString& name, const QString& description)
        : m_name(name), m_description(description)
    {}

    QString getName() const { return m_name; }
    QString getDescription() const { return m_description; }

private:
    QString m_name;
    QString m_description;
    // ... other project attributes (due date, priority, etc.) ...
};

class MainWindow : public QMainWindow
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

private:
    Ui::MainWindow *ui;
    QList<Project*> projectList;
};
#endif // MAINWINDOW_H
