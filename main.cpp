#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <windows.h>
#include <QMessageBox>
#include <iostream>
#include <TlHelp32.h>
#include <vector>
#include <QProcess>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    setlocale(LC_ALL, "rus");
    MainWindow w;
    w.show();
    return a.exec();
}
