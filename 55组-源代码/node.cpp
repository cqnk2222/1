#include "node.h"

#include<QString>
#include<QPainter>
#include<QDebug>
#include<cmath>
#include<map>
node::node()
{
}

node::node(int a, int b, QString s)
{
    x = a;
    y = b;
    name = s;
}

QString node::findNearestDining()
{
    int timeNong = abs(this->x - NongYuan.x) + abs(this->y - NongYuan.y);
    int timeShao = abs(this->x - ShaoYuan.x) + abs(this->y - ShaoYuan.y);
    int timeJia = abs(this->x - JiaYuan.x) + abs(this->y - JiaYuan.y);
    if (timeNong < timeShao && timeNong < timeJia)
    {
        return "农园";
    }
    else if (timeJia < timeShao && timeJia < timeNong)
    {
        return "家园";
    }
    else
    {
        return "勺园";
    }
}

QString node::findNearestGate()
{
    int timeEast = abs(this->x - EastGate.x) + abs(this->y - EastGate.y);
    int timeWest = abs(this->x - WestGate.x) + abs(this->y - WestGate.y);
    int timeSouth = abs(this->x - SouthGate.x) + abs(this->y - SouthGate.y);
    if (timeEast < timeWest && timeEast < timeSouth)
    {
        return "东门";
    }
    else if (timeWest < timeEast && timeWest < timeSouth)
    {
        return "西门";
    }
    else
    {
        return "南门";
    }
}

QString caculateBikingTime(node place1, node place2)
{
    int distance = abs(place1.x - place2.x) + abs(place1.y - place2.y);
    double time = (double)distance / 210 ;
    QString stime = QString::number( time, 'f', 1) + "(分钟)";
    return stime;
}

QString caculateWalkingTime(node place1, node place2)
{
    int distance = abs(place1.x - place2.x) + abs(place1.y - place2.y);
    double time = (double)distance / 90 ;
    QString stime = QString::number( time, 'f', 1) + "(分钟)";
    return stime;
}


extern node EastGate(1100,540, "东门");
extern node SouthGate(700,1250, "南门");
extern node WestGate(100,180, "西门");
extern node BoyaTower(725,275, "博雅塔");
extern node WeimingLake(725,275, "未名湖");
extern node Library(700,540, "图书馆");
extern node Hall(700,800, "百讲");
extern node NewSun(700,900,"新太阳");
extern node JingYuan(390,460,"静园");
extern node ShaoYuan(200,460, "勺园");
extern node NongYuan(820,870,"农园");
extern node JiaYuan(400,1130,"家园");

extern std::map<QString, node> places = {{ "东门", EastGate}, { "南门", SouthGate }, { "西门", WestGate },
                                        { "博雅塔", BoyaTower }, { "未名湖", WeimingLake }, { "图书馆", Library },
                                        { "百周年纪念讲堂", Hall }, { "新太阳学生中心（文创店）", NewSun}, { "静园（革命烈士纪念碑）", JingYuan},
                                        { "勺园", ShaoYuan }, { "农园", NongYuan }, { "家园", JiaYuan} };

extern node crossNearLiJiao(840,540,"理教路口");
extern node crossNearYaoGan(840,420,"遥感楼路口");
extern node crossNearHuaBiao(200,230,"华表路口");
extern node crossNearSouthGate(700,1130,"南门路口");
extern node turnUpLibrary(700,460,"图书馆拐角");

