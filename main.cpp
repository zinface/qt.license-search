
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QMainWindow>

void moveCenter(MainWindow &wm) {
    QDesktopWidget *desktop = QApplication::desktop();
    wm.move((desktop->width() - wm.width()) /2,(desktop->height() - wm.height()) /2);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("开源许可证查询工具 - v0.0");
    MainWindow wm;
    wm.show();
   
    moveCenter(wm);

    return a.exec();
}
