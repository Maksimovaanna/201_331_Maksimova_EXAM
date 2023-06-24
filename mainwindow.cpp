#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QJsonDocument>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cred = new cred_app;
    ui->error->setVisible(false);
    connect(cred, &cred_app::ShowMW,this,&MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_Ok_clicked()
{
    //если хеш пин-кода совпадет с имеющимся, то вход в приложение будет успешным
    if (ui->code_text->text() == '1234')
    {
        qDebug() << QString::fromStdString(cred->check_pincode(ui->code_text->text()));
        this->close();
        cred->open_json();
        cred->show();
        cred->createUI(QStringList() << trUtf8("Number")
                        << trUtf8("Site")
                        << trUtf8("Login")
                        << trUtf8("Password")
        );


    }

    else
    {
        ui->error->setVisible(true);
    }
}
