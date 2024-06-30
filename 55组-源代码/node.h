#ifndef NODE_H
#define NODE_H

#include<QString>
#include<map>

class node
{
public:
    int x;
    int y;
    QString name;

    node();
    node(int a, int b, QString s);
    QString findNearestDining();                       //寻找最近的食堂
    QString findNearestGate();                         //寻找最近的大门
};

QString caculateBikingTime(node place1, node place2);  //计算骑行时间
QString caculateWalkingTime(node place1, node place2); //计算步行时间

//具体地点对应node
extern node EastGate;
extern node SouthGate;
extern node WestGate;
extern node BoyaTower;
extern node WeimingLake;
extern node Library;
extern node Hall;
extern node NewSun;
extern node JingYuan;
extern node ShaoYuan;
extern node NongYuan;
extern node JiaYuan;

//地点名字 到 地点对应node 的映射
extern std::map<QString, node> places;

//具体路口对应node
extern node crossNearLiJiao;
extern node crossNearYaoGan;
extern node crossNearHuaBiao;
extern node crossNearSouthGate;
extern node turnUpLibrary;

#endif // NODE_H
