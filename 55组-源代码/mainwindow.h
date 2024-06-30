#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showViewImage();                   //查看近景函数
    void paintEvent(QPaintEvent *event);    //重写paintEvent函数，用于导航
    void findNearest();                     //寻找最近的地点函数
    void showRoutine();                     //查看游览路线函数

private:
    Ui::MainWindow *ui;                     //ui部分
};
#endif // MAINWINDOW_H
