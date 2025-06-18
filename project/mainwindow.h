#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QAction>
#include <QStackedWidget>
#include<QListWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_addBT_clicked();

    void on_findBT_clicked();

    void on_delFind_clicked();

    void on_delBT_clicked();
    void showAll();
    void showClassmates();
    void showColleagues();
    void showFriends();
    void showRelatives();
    void showNearBirth();

    void on_NSall_clicked();
    void on_BSall_clicked();

    // 同学
    void on_NScla_clicked();
    void on_BScla_clicked();

    // 同事
    void on_NScol_clicked();
    void on_BScol_clicked();

    // 朋友
    void on_NSfri_clicked();
    void on_BSfri_clicked();

    // 亲戚
    void on_NSrel_clicked();
    void on_BSrel_clicked();

    void on_queryBT_clicked();
    void on_birthdayItemClicked(QListWidgetItem* item);

    void on_updateFind_clicked();
    void on_updateBT_clicked();

private:
    Ui::MainWindow *ui;
    template<class T>
    void sortAndDisplay(bool byName, QListWidget* listWidget, QWidget* pageWidget);
};
#endif // MAINWINDOW_H
