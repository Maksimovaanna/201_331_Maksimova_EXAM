#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QJsonDocument>
#include <windows.h>
#include <QFile>

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
    QFile file("hash.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    //считываем файл для шифрования
    QString value = file.readAll();
    std::string pin = value.toUtf8().constData();
    //если хеш пин-кода совпадет с имеющимся, то вход в приложение будет успешным
    if (cred->check_pincode(ui->code_text->text()) == pin)
    {
        //qDebug() << QString::fromStdString(cred->check_pincode(ui->code_text->text()));
        this->close();
        file.close();
        cred->show();
        cred->createUI(QStringList() << "Number");
    }

    else
    {
        ui->error->setVisible(true);
    }

}
