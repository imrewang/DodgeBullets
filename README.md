## 一、简介

玩家通过鼠标控制火箭躲避一架UFO和越来越多的反弹子弹

## 二、数据结构

子弹：数组

## 三、截图

**（一） 项目结构**

![项目结构](https://github.com/imrewang/DodgeBullets/blob/main/DodgeBullets%E9%A1%B9%E7%9B%AE%E7%BB%93%E6%9E%84.png?raw=true)

**（二） 运行截图**

![运行截图](https://github.com/imrewang/DodgeBullets/blob/main/DodgeBullets%E8%BF%90%E8%A1%8C%E6%88%AA%E5%9B%BE.png?raw=true)

## 四、总结

**（一） 追踪问题**

技术：通过随机速度，根据坐标计算

效果：可以进行随机速度追踪

**（二）透明图片输出问题**

技术：EasyXPng.h，EasyXPng.cpp

效果：完成有透明背景图片的输出，增加了游戏的美观程度

**（三）#编译链接错误问题**

问题：xxx在main.obj中存在

解决：分开编写

学习：编译过程，以及重复包含问题

**（四）初始化速度问题**

技术：sin,cos

效果：比较好的初始化了小球的速度

## 五、环境

visual studio 2019

C++

## 六、改进方向

（一）EasyX透明背景

白底黑图的图片和背景图片做与运算，黑底彩图的图片和目标图片做或运算，得到透明背景。

（二）利用继承实现道具类，吃到道具后可以加命或子弹速度减慢。

（三）碰撞后给火箭一段时间的无敌状态。

（四）游戏结束后增加得分记录显示、游戏重玩等功能。

（五）玩家被击中后子弹和追踪者的出现位置
