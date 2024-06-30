#include "mainwindow.h"
#include "node.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QPixmap>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("PKU_map");

    connect(ui->ViewButton, &QPushButton::clicked, this, &MainWindow::showViewImage);     //查看近景槽
    connect(ui->SearchButton, &QPushButton::clicked, this, [=](){ this->update(); });     //导航路线槽
    connect(ui->ShortestButton, &QPushButton::clicked, this, &MainWindow::findNearest);   //查找距离最近槽
    connect(ui->TravelButton, &QPushButton::clicked, this, &MainWindow::showRoutine);     //查找游览路线槽

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showViewImage()
{
    QString viewText = ui->ViewcomboBox->currentText();

    if ( viewText == "无"){}

    else if ( viewText == "未名湖")
    {
        QWidget w;
        w.setWindowTitle("未名湖");
        w.setStyleSheet("QWidget { border-image: url(:/new/prefix1/WeimingLake); }");
        w.resize(800,1000);
        w.show();
        QEventLoop loop;
        loop.exec();
    }

    else if ( viewText == "博雅塔")
    {
        QWidget w;
        w.setWindowTitle("博雅塔");
        w.setStyleSheet("QWidget { border-image: url(:/new/prefix1/BoyaTower); }");
        w.resize(800,1200);
        w.show();
        QEventLoop loop;
        loop.exec();
    }

    else if ( viewText == "图书馆")
    {
        QWidget w;
        w.setWindowTitle("图书馆");
        w.setStyleSheet("QWidget { border-image: url(:/new/prefix1/Library); }");
        w.resize(1000,600);
        w.show();
        QEventLoop loop;
        loop.exec();
    }

    else if ( viewText == "西门")
    {
        QWidget w;
        w.setWindowTitle("西门");
        w.setStyleSheet("QWidget { border-image: url(:/new/prefix1/WestGate); }");
        w.resize(1100,700);
        w.show();
        QEventLoop loop;
        loop.exec();
    }

    else if ( viewText == "华表")
    {
        QWidget w;
        w.setWindowTitle("华表");
        w.setStyleSheet("QWidget { border-image: url(:/new/prefix1/Huabiao); }");
        w.resize(1200,800);
        w.show();
        QEventLoop loop;
        loop.exec();
    }

    else if ( viewText == "百周年纪念讲堂")
    {
        QWidget w;
        w.setWindowTitle("百周年纪念讲堂");
        w.setStyleSheet("QWidget { border-image: url(:/new/prefix1/pkuHall); }");
        w.resize(1200,900);
        w.show();
        QEventLoop loop;
        loop.exec();
    }
}

void MainWindow::findNearest()
{
    QString nowPlace = ui->GocomboBox->currentText();
    QString findThing = ui->ShortestcomboBox->currentText();

    if (findThing == "食堂")
    {
        if (nowPlace == "无")
        {
            ui->FindResultEdit->setText("");
            return;
        }
        ui->FindResultEdit->setText(places[nowPlace].findNearestDining());
    }

    if (findThing == "大门")
    {
        if (nowPlace == "无")
        {
            ui->FindResultEdit->setText("");
            return;
        }
        ui->FindResultEdit->setText(places[nowPlace].findNearestGate());
    }
}

void MainWindow::showRoutine()
{
    QString routineText = ui->TravelcomboBox->currentText();
    if (routineText == "精华路线（1h）")
    {
        QWidget w;
        w.setWindowTitle("精华路线");
        w.setStyleSheet("QWidget { border-image: url(:/new/prefix1/EssenceRoutine); }");
        w.resize(1200,1400);
        w.show();
        QEventLoop loop;
        loop.exec();
    }
    else if (routineText == "经典路线（2h）")
    {
        QWidget w;
        w.setWindowTitle("经典路线");
        w.setStyleSheet("QWidget { border-image: url(:/new/prefix1/ClassicRoutine); }");
        w.resize(1200,1400);
        w.show();
        QEventLoop loop;
        loop.exec();
    }
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPixmap pixmap(":/new/prefix1/PKU_map.png");
    QPainter painter(this);
    painter.drawPixmap(0,0,pixmap);    //绘制地图

    QPen pen(Qt::red,6);
    painter.setPen(pen);
    //painter.drawLine(0,0, 700, 1130);
    QString startText = ui->GocomboBox->currentText();       //获取起始地
    QString endText = ui->TerminalcomboBox->currentText();   //获取目的地

    if (startText == "无" || endText == "无"){ return; }

    painter.setFont(QFont("Arial",20));
    painter.drawText(places[startText].x, places[startText].y, places[startText].name);    //在地图上标明起始地
    painter.drawText(places[endText].x, places[endText].y, places[endText].name);          //在地图上标明目的地

    ui->WalkTimeEdit->setText(caculateWalkingTime(places[startText], places[endText]));    //显示步行时间
    ui->BikeTimeEdit->setText(caculateBikingTime(places[startText], places[endText]));     //显示骑行时间

    //导航判断模块
    if ((startText == "东门" && endText == "博雅塔") || (startText == "博雅塔" && endText == "东门"))
    {
        painter.drawLine(EastGate.x, EastGate.y, crossNearLiJiao.x, crossNearLiJiao.y);
        painter.drawLine(crossNearLiJiao.x, crossNearLiJiao.y, crossNearYaoGan.x, crossNearYaoGan.y);
        painter.drawLine(crossNearYaoGan.x, crossNearYaoGan.y, BoyaTower.x, BoyaTower.y);
    }

    else if ((startText == "东门" && endText == "西门") || (startText == "西门" && endText == "东门"))
    {
        painter.drawLine(EastGate.x, EastGate.y, Library.x, Library.y);
        painter.drawLine(Library.x, Library.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, ShaoYuan.x, ShaoYuan.y);
        painter.drawLine(ShaoYuan.x, ShaoYuan.y, crossNearHuaBiao.x, crossNearHuaBiao.y);
        painter.drawLine(crossNearHuaBiao.x, crossNearHuaBiao.y, WestGate.x, WestGate.y);
    }

    else if ((startText == "东门" && endText == "南门") || (startText == "南门" && endText == "东门"))
    {
        painter.drawLine(EastGate.x, EastGate.y, Library.x, Library.y);
        painter.drawLine(Library.x, Library.y, SouthGate.x, SouthGate.y);
    }

    else if ((startText == "东门" && endText == "图书馆") || (startText == "图书馆" && endText == "东门"))
    {
        painter.drawLine(EastGate.x, EastGate.y, Library.x, Library.y);
    }

    else if ((startText == "东门" && endText == "百周年纪念讲堂") || (startText == "百周年纪念讲堂" && endText == "东门"))
    {
        painter.drawLine(EastGate.x, EastGate.y, Library.x, Library.y);
        painter.drawLine(Library.x, Library.y, Hall.x, Hall.y);
    }

    else if ((startText == "东门" && endText == "新太阳学生中心（文创店）") || (startText == "新太阳学生中心（文创店）" && endText == "东门"))
    {
        painter.drawLine(EastGate.x, EastGate.y, Library.x, Library.y);
        painter.drawLine(Library.x, Library.y, NewSun.x, NewSun.y);
    }

    else if ((startText == "东门" && endText == "静园（革命烈士纪念碑）") || (startText == "静园（革命烈士纪念碑）" && endText == "东门"))
    {
        painter.drawLine(EastGate.x, EastGate.y, Library.x, Library.y);
        painter.drawLine(Library.x, Library.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, JingYuan.x, JingYuan.y);
    }

    else if ((startText == "东门" && endText == "勺园") || (startText == "勺园" && endText == "东门"))
    {
        painter.drawLine(EastGate.x, EastGate.y, Library.x, Library.y);
        painter.drawLine(Library.x, Library.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, ShaoYuan.x, ShaoYuan.y);
    }

    else if ((startText == "东门" && endText == "农园") || (startText == "农园" && endText == "东门"))
    {
        painter.drawLine(EastGate.x, EastGate.y, crossNearLiJiao.x, crossNearLiJiao.y);
        painter.drawLine(crossNearLiJiao.x, crossNearLiJiao.y, NongYuan.x, NongYuan.y);
    }

    else if ((startText == "东门" && endText == "家园") || (startText == "家园" && endText == "东门"))
    {
        painter.drawLine(EastGate.x, EastGate.y, Library.x, Library.y);
        painter.drawLine(Library.x, Library.y, crossNearSouthGate.x, crossNearSouthGate.y);
        painter.drawLine(crossNearSouthGate.x, crossNearSouthGate.y, JiaYuan.x, JiaYuan.y);
    }

    else if ((startText == "西门" && endText == "南门") || (startText == "南门" && endText == "西门"))
    {
        painter.drawLine(WestGate.x, WestGate.y, crossNearHuaBiao.x, crossNearHuaBiao.y);
        painter.drawLine(crossNearHuaBiao.x, crossNearHuaBiao.y, ShaoYuan.x, ShaoYuan.y);
        painter.drawLine(ShaoYuan.x, ShaoYuan.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, SouthGate.x, SouthGate.y);
    }

    else if ((startText == "西门" && endText == "博雅塔") || (startText == "博雅塔" && endText == "西门"))
    {
        painter.drawLine(WestGate.x, WestGate.y, crossNearHuaBiao.x, crossNearHuaBiao.y);
        painter.drawLine(crossNearHuaBiao.x, crossNearHuaBiao.y, ShaoYuan.x, ShaoYuan.y);
        painter.drawLine(ShaoYuan.x, ShaoYuan.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, Library.x, Library.y);
        painter.drawLine(Library.x, Library.y, crossNearLiJiao.x, crossNearLiJiao.y);
        painter.drawLine(crossNearLiJiao.x, crossNearLiJiao.y, crossNearYaoGan.x, crossNearYaoGan.y);
        painter.drawLine(crossNearYaoGan.x, crossNearYaoGan.y, BoyaTower.x, BoyaTower.y);
    }

    else if ((startText == "西门" && endText == "图书馆") || (startText == "图书馆" && endText == "西门"))
    {
        painter.drawLine(WestGate.x, WestGate.y, crossNearHuaBiao.x, crossNearHuaBiao.y);
        painter.drawLine(crossNearHuaBiao.x, crossNearHuaBiao.y, ShaoYuan.x, ShaoYuan.y);
        painter.drawLine(ShaoYuan.x, ShaoYuan.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, Library.x, Library.y);
    }

    else if ((startText == "西门" && endText == "百周年纪念讲堂") || (startText == "百周年纪念讲堂" && endText == "西门"))
    {
        painter.drawLine(WestGate.x, WestGate.y, crossNearHuaBiao.x, crossNearHuaBiao.y);
        painter.drawLine(crossNearHuaBiao.x, crossNearHuaBiao.y, ShaoYuan.x, ShaoYuan.y);
        painter.drawLine(ShaoYuan.x, ShaoYuan.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, Library.x, Library.y);
        painter.drawLine(Library.x, Library.y, Hall.x, Hall.y);
    }

    else if ((startText == "西门" && endText == "新太阳学生中心（文创店）") || (startText == "新太阳学生中心（文创店）" && endText == "西门"))
    {
        painter.drawLine(WestGate.x, WestGate.y, crossNearHuaBiao.x, crossNearHuaBiao.y);
        painter.drawLine(crossNearHuaBiao.x, crossNearHuaBiao.y, ShaoYuan.x, ShaoYuan.y);
        painter.drawLine(ShaoYuan.x, ShaoYuan.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, Library.x, Library.y);
        painter.drawLine(Library.x, Library.y, NewSun.x, NewSun.y);
    }

    else if ((startText == "西门" && endText == "静园（革命烈士纪念碑）") || (startText == "静园（革命烈士纪念碑）" && endText == "西门"))
    {
        painter.drawLine(WestGate.x, WestGate.y, crossNearHuaBiao.x, crossNearHuaBiao.y);
        painter.drawLine(crossNearHuaBiao.x, crossNearHuaBiao.y, ShaoYuan.x, ShaoYuan.y);
        painter.drawLine(ShaoYuan.x, ShaoYuan.y, JingYuan.x, JingYuan.y);
    }

    else if ((startText == "西门" && endText == "勺园") || (startText == "勺园" && endText == "西门"))
    {
        painter.drawLine(WestGate.x, WestGate.y, crossNearHuaBiao.x, crossNearHuaBiao.y);
        painter.drawLine(crossNearHuaBiao.x, crossNearHuaBiao.y, ShaoYuan.x, ShaoYuan.y);
    }

    else if ((startText == "西门" && endText == "农园") || (startText == "农园" && endText == "西门"))
    {
        painter.drawLine(WestGate.x, WestGate.y, crossNearHuaBiao.x, crossNearHuaBiao.y);
        painter.drawLine(crossNearHuaBiao.x, crossNearHuaBiao.y, ShaoYuan.x, ShaoYuan.y);
        painter.drawLine(ShaoYuan.x, ShaoYuan.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, Library.x, Library.y);
        painter.drawLine(Library.x, Library.y, NewSun.x, NewSun.y);
        painter.drawLine(NewSun.x, NewSun.y, NongYuan.x, NongYuan.y);
    }

    else if ((startText == "西门" && endText == "家园") || (startText == "家园" && endText == "西门"))
    {
        painter.drawLine(WestGate.x, WestGate.y, crossNearHuaBiao.x, crossNearHuaBiao.y);
        painter.drawLine(crossNearHuaBiao.x, crossNearHuaBiao.y, ShaoYuan.x, ShaoYuan.y);
        painter.drawLine(ShaoYuan.x, ShaoYuan.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, Library.x, Library.y);
        painter.drawLine(Library.x, Library.y, crossNearSouthGate.x, crossNearSouthGate.y);
        painter.drawLine(crossNearSouthGate.x, crossNearSouthGate.y, JiaYuan.x, JiaYuan.y);
    }

    else if ((startText == "南门" && endText == "博雅塔") || (startText == "博雅塔" && endText == "南门"))
    {
        painter.drawLine(SouthGate.x, SouthGate.y, Library.x, Library.y);
        painter.drawLine(Library.x, Library.y, crossNearLiJiao.x, crossNearLiJiao.y);
        painter.drawLine(crossNearLiJiao.x, crossNearLiJiao.y, crossNearYaoGan.x, crossNearYaoGan.y);
        painter.drawLine(crossNearYaoGan.x, crossNearYaoGan.y, BoyaTower.x, BoyaTower.y);
    }

    else if ((startText == "南门" && endText == "图书馆") || (startText == "图书馆" && endText == "南门"))
    {
        painter.drawLine(SouthGate.x, SouthGate.y, Library.x, Library.y);
    }

    else if ((startText == "南门" && endText == "百周年纪念讲堂") || (startText == "百周年纪念讲堂" && endText == "南门"))
    {
        painter.drawLine(SouthGate.x, SouthGate.y, Hall.x, Hall.y);
    }

    else if ((startText == "南门" && endText == "新太阳学生中心（文创店）") || (startText == "新太阳学生中心（文创店）" && endText == "南门"))
    {
        painter.drawLine(SouthGate.x, SouthGate.y, NewSun.x, NewSun.y);
    }

    else if ((startText == "南门" && endText == "静园（革命烈士纪念碑）") || (startText == "静园（革命烈士纪念碑）" && endText == "南门"))
    {
        painter.drawLine(SouthGate.x, SouthGate.y, Library.x, Library.y);
        painter.drawLine(Library.x, Library.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, JingYuan.x, JingYuan.y);
    }

    else if ((startText == "南门" && endText == "勺园") || (startText == "勺园" && endText == "南门"))
    {
        painter.drawLine(SouthGate.x, SouthGate.y, Library.x, Library.y);
        painter.drawLine(Library.x, Library.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, ShaoYuan.x, ShaoYuan.y);
    }

    else if ((startText == "南门" && endText == "农园") || (startText == "农园" && endText == "南门"))
    {
        painter.drawLine(SouthGate.x, SouthGate.y, NewSun.x, NewSun.y);
        painter.drawLine(NewSun.x, NewSun.y, NongYuan.x, NongYuan.y);
    }

    else if ((startText == "南门" && endText == "家园") || (startText == "家园" && endText == "南门"))
    {
        painter.drawLine(SouthGate.x, SouthGate.y, crossNearSouthGate.x, crossNearSouthGate.y);
        painter.drawLine(crossNearSouthGate.x, crossNearSouthGate.y, JiaYuan.x, JiaYuan.y);
    }

    else if ((startText == "博雅塔" && endText == "图书馆") || (startText == "图书馆" && endText == "博雅塔"))
    {
        painter.drawLine(Library.x, Library.y, crossNearLiJiao.x, crossNearLiJiao.y);
        painter.drawLine(crossNearLiJiao.x, crossNearLiJiao.y, crossNearYaoGan.x, crossNearYaoGan.y);
        painter.drawLine(crossNearYaoGan.x, crossNearYaoGan.y, BoyaTower.x, BoyaTower.y);
    }

    else if ((startText == "博雅塔" && endText == "百周年纪念讲堂") || (startText == "百周年纪念讲堂" && endText == "博雅塔"))
    {
        painter.drawLine(Hall.x, Hall.y, Library.x, Library.y);
        painter.drawLine(Library.x, Library.y, crossNearLiJiao.x, crossNearLiJiao.y);
        painter.drawLine(crossNearLiJiao.x, crossNearLiJiao.y, crossNearYaoGan.x, crossNearYaoGan.y);
        painter.drawLine(crossNearYaoGan.x, crossNearYaoGan.y, BoyaTower.x, BoyaTower.y);
    }

    else if ((startText == "博雅塔" && endText == "新太阳学生中心（文创店）") || (startText == "新太阳学生中心（文创店）" && endText == "博雅塔"))
    {
        painter.drawLine(NewSun.x, NewSun.y, Library.x, Library.y);
        painter.drawLine(Library.x, Library.y, crossNearLiJiao.x, crossNearLiJiao.y);
        painter.drawLine(crossNearLiJiao.x, crossNearLiJiao.y, crossNearYaoGan.x, crossNearYaoGan.y);
        painter.drawLine(crossNearYaoGan.x, crossNearYaoGan.y, BoyaTower.x, BoyaTower.y);
    }

    else if ((startText == "博雅塔" && endText == "静园（革命烈士纪念碑）") || (startText == "静园（革命烈士纪念碑）" && endText == "博雅塔"))
    {
        painter.drawLine(Library.x, Library.y, crossNearLiJiao.x, crossNearLiJiao.y);
        painter.drawLine(crossNearLiJiao.x, crossNearLiJiao.y, crossNearYaoGan.x, crossNearYaoGan.y);
        painter.drawLine(crossNearYaoGan.x, crossNearYaoGan.y, BoyaTower.x, BoyaTower.y);
        painter.drawLine(Library.x, Library.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, JingYuan.x, JingYuan.y);
    }

    else if ((startText == "博雅塔" && endText == "勺园") || (startText == "勺园" && endText == "博雅塔"))
    {
        painter.drawLine(Library.x, Library.y, crossNearLiJiao.x, crossNearLiJiao.y);
        painter.drawLine(crossNearLiJiao.x, crossNearLiJiao.y, crossNearYaoGan.x, crossNearYaoGan.y);
        painter.drawLine(crossNearYaoGan.x, crossNearYaoGan.y, BoyaTower.x, BoyaTower.y);
        painter.drawLine(Library.x, Library.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, ShaoYuan.x, ShaoYuan.y);
    }

    else if ((startText == "博雅塔" && endText == "农园") || (startText == "农园" && endText == "博雅塔"))
    {
        painter.drawLine(BoyaTower.x, BoyaTower.y, crossNearYaoGan.x, crossNearYaoGan.y);
        painter.drawLine(crossNearYaoGan.x, crossNearYaoGan.y, NongYuan.x, NongYuan.y);
    }

    else if ((startText == "博雅塔" && endText == "家园") || (startText == "家园" && endText == "博雅塔"))
    {
        painter.drawLine(crossNearYaoGan.x, crossNearYaoGan.y, BoyaTower.x, BoyaTower.y);
        painter.drawLine(crossNearLiJiao.x, crossNearLiJiao.y, crossNearYaoGan.x, crossNearYaoGan.y);
        painter.drawLine(Library.x, Library.y, crossNearLiJiao.x, crossNearLiJiao.y);
        painter.drawLine(Library.x, Library.y, crossNearSouthGate.x, crossNearSouthGate.y);
        painter.drawLine(crossNearSouthGate.x, crossNearSouthGate.y, JiaYuan.x, JiaYuan.y);
    }

    else if ((startText == "图书馆" && endText == "百周年纪念讲堂") || (startText == "百周年纪念讲堂" && endText == "图书馆"))
    {
        painter.drawLine(Library.x, Library.y, Hall.x, Hall.y);
    }

    else if ((startText == "图书馆" && endText == "新太阳学生中心（文创店）") || (startText == "百新太阳学生中心（文创店）" && endText == "图书馆"))
    {
        painter.drawLine(Library.x, Library.y, NewSun.x, NewSun.y);
    }

    else if ((startText == "图书馆" && endText == "静园（革命烈士纪念碑）") || (startText == "静园（革命烈士纪念碑）" && endText == "图书馆"))
    {
        painter.drawLine(Library.x, Library.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, JingYuan.x, JingYuan.y);
    }

    else if ((startText == "图书馆" && endText == "勺园") || (startText == "勺园" && endText == "图书馆"))
    {
        painter.drawLine(Library.x, Library.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, ShaoYuan.x, ShaoYuan.y);
    }

    else if ((startText == "图书馆" && endText == "农园") || (startText == "农园" && endText == "图书馆"))
    {
        painter.drawLine(Library.x, Library.y, crossNearLiJiao.x, crossNearLiJiao.y);
        painter.drawLine(crossNearLiJiao.x, crossNearLiJiao.y, NongYuan.x, NongYuan.y);
    }

    else if ((startText == "图书馆" && endText == "家园") || (startText == "家园" && endText == "图书馆"))
    {
        painter.drawLine(Library.x, Library.y, crossNearSouthGate.x, crossNearSouthGate.y);
        painter.drawLine(crossNearSouthGate.x, crossNearSouthGate.y, JiaYuan.x, JiaYuan.y);
    }

    else if ((startText == "百周年纪念讲堂" && endText == "新太阳学生中心（文创店）") || (startText == "百新太阳学生中心（文创店）" && endText == "百周年纪念讲堂"))
    {
        painter.drawLine(Hall.x, Hall.y, NewSun.x, NewSun.y);
    }

    else if ((startText == "百周年纪念讲堂" && endText == "静园（革命烈士纪念碑）") || (startText == "静园（革命烈士纪念碑）" && endText == "百周年纪念讲堂"))
    {
        painter.drawLine(Hall.x, Hall.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, JingYuan.x, JingYuan.y);
    }

    else if ((startText == "百周年纪念讲堂" && endText == "勺园") || (startText == "勺园" && endText == "百周年纪念讲堂"))
    {
        painter.drawLine(Hall.x, Hall.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, ShaoYuan.x, ShaoYuan.y);
    }

    else if ((startText == "百周年纪念讲堂" && endText == "农园") || (startText == "农园" && endText == "百周年纪念讲堂"))
    {
        painter.drawLine(Hall.x, Hall.y, NewSun.x, NewSun.y);
        painter.drawLine(NewSun.x, NewSun.y, NongYuan.x, NongYuan.y);
    }

    else if ((startText == "百周年纪念讲堂" && endText == "家园") || (startText == "家园" && endText == "百周年纪念讲堂"))
    {
        painter.drawLine(Hall.x, Hall.y, crossNearSouthGate.x, crossNearSouthGate.y);
        painter.drawLine(crossNearSouthGate.x, crossNearSouthGate.y, JiaYuan.x, JiaYuan.y);
    }

    else if ((startText == "新太阳学生中心（文创店）" && endText == "静园（革命烈士纪念碑）") || (startText == "静园（革命烈士纪念碑）" && endText == "新太阳学生中心（文创店）"))
    {
        painter.drawLine(NewSun.x, NewSun.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, JingYuan.x, JingYuan.y);
    }

    else if ((startText == "新太阳学生中心（文创店）" && endText == "勺园") || (startText == "勺园" && endText == "新太阳学生中心（文创店）"))
    {
        painter.drawLine(NewSun.x, NewSun.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, ShaoYuan.x, ShaoYuan.y);
    }

    else if ((startText == "新太阳学生中心（文创店）" && endText == "农园") || (startText == "农园" && endText == "新太阳学生中心（文创店）"))
    {
        painter.drawLine(NewSun.x, NewSun.y, NongYuan.x, NongYuan.y);
    }

    else if ((startText == "新太阳学生中心（文创店）" && endText == "家园") || (startText == "家园" && endText == "新太阳学生中心（文创店）"))
    {
        painter.drawLine(NewSun.x, NewSun.y, crossNearSouthGate.x, crossNearSouthGate.y);
        painter.drawLine(crossNearSouthGate.x, crossNearSouthGate.y, JiaYuan.x, JiaYuan.y);
    }

    else if ((startText == "静园（革命烈士纪念碑）" && endText == "勺园") || (startText == "勺园" && endText == "静园（革命烈士纪念碑）"))
    {
        painter.drawLine(JingYuan.x, JingYuan.y, ShaoYuan.x, ShaoYuan.y);
    }

    else if ((startText == "静园（革命烈士纪念碑）" && endText == "农园") || (startText == "农园" && endText == "静园（革命烈士纪念碑）"))
    {
        painter.drawLine(Library.x, Library.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, JingYuan.x, JingYuan.y);
        painter.drawLine(Library.x, Library.y, crossNearLiJiao.x, crossNearLiJiao.y);
        painter.drawLine(crossNearLiJiao.x, crossNearLiJiao.y, NongYuan.x, NongYuan.y);
    }

    else if ((startText == "静园（革命烈士纪念碑）" && endText == "家园") || (startText == "家园" && endText == "静园（革命烈士纪念碑）"))
    {
        painter.drawLine(Library.x, Library.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, JingYuan.x, JingYuan.y);
        painter.drawLine(Library.x, Library.y, crossNearSouthGate.x, crossNearSouthGate.y);
        painter.drawLine(crossNearSouthGate.x, crossNearSouthGate.y, JiaYuan.x, JiaYuan.y);
    }

    else if ((startText == "勺园" && endText == "农园") || (startText == "农园" && endText == "勺园"))
    {
        painter.drawLine(JingYuan.x, JingYuan.y, ShaoYuan.x, ShaoYuan.y);
        painter.drawLine(Library.x, Library.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, JingYuan.x, JingYuan.y);
        painter.drawLine(Library.x, Library.y, crossNearLiJiao.x, crossNearLiJiao.y);
        painter.drawLine(crossNearLiJiao.x, crossNearLiJiao.y, NongYuan.x, NongYuan.y);
    }

    else if ((startText == "勺园" && endText == "家园") || (startText == "家园" && endText == "勺园"))
    {
        painter.drawLine(JingYuan.x, JingYuan.y, ShaoYuan.x, ShaoYuan.y);
        painter.drawLine(Library.x, Library.y, turnUpLibrary.x, turnUpLibrary.y);
        painter.drawLine(turnUpLibrary.x, turnUpLibrary.y, JingYuan.x, JingYuan.y);
        painter.drawLine(Library.x, Library.y, crossNearSouthGate.x, crossNearSouthGate.y);
        painter.drawLine(crossNearSouthGate.x, crossNearSouthGate.y, JiaYuan.x, JiaYuan.y);
    }

    else if ((startText == "农园" && endText == "家园") || (startText == "家园" && endText == "农园"))
    {
        painter.drawLine(NewSun.x, NewSun.y, NongYuan.x, NongYuan.y);
        painter.drawLine(NewSun.x, NewSun.y, crossNearSouthGate.x, crossNearSouthGate.y);
        painter.drawLine(crossNearSouthGate.x, crossNearSouthGate.y, JiaYuan.x, JiaYuan.y);
    }

}
