#include "cred_app.h"
#include "ui_cred_app.h"
#include <QDialog>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QFile>
#include <QCoreApplication>
#include <QDir>
#include <QItemDelegate>
#include <iostream>
#include <QEvent>
#include <vector>
#include <algorithm>
#include <iterator>
#include <QClipboard>
#include <QString>


cred_app::cred_app(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cred_app)
{
    ui->setupUi(this);
}


std::string cred_app::check_pincode(QString user_code){
    QString code = user_code;
    QByteArray hash = QCryptographicHash::hash(code.toUtf8(), QCryptographicHash::Sha256);
    hash = hash.toBase64();
    QString q_hash = QString(hash);
    std::string str_hash = q_hash.toStdString().substr(1,32);
    //qDebug() << "hash" << q_hash;
    return str_hash;
}


void cred_app::createUI(const QStringList &headers){
    ui->pass_manager->setColumnCount(1); // Указываем число колонок
    //ui->pass_manager->setRowCount(12);
    ui->pass_manager->setShowGrid(true); // Включаем сетку
    // Разрешаем выделение только одного элемента
    ui->pass_manager->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->pass_manager->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем заголовки колонок
    ui->pass_manager->setHorizontalHeaderLabels(headers);
    // Растягиваем последнюю колонку на всё доступное пространство
   // ui->pass_manager->horizontalHeader()->setStretchLastSection(true);
    // Скрываем колонку под номером 0
    //ui->pass_manager->hideColumn(0);
    ui->pass_manager->setEditTriggers(QAbstractItemView::NoEditTriggers);

}


//функция события qlineedit
bool cred_app::eventFilter(QObject* watched, QEvent* event)
{

    if(event->type() == QEvent::MouseButtonPress)
    {
        if(QLineEdit* lineEdit = qobject_cast<QLineEdit*>(watched))
        {
            Q_FOREACH(const QLineEdit* i, findChildren<QLineEdit*>())
            i->disconnect();

            int row = lineEdit->property("row").toInt();
            int column = lineEdit->property("column").toInt();



            //в clipboard будут храниться данные буфера
            QClipboard *clipboard = QGuiApplication::clipboard();


        }
    }
    return QObject::eventFilter(watched, event);
}


void cred_app::numbers() {
        ui->pass_manager->setRowCount(0); //сброс
        int i = 0;

        for (int i = 0; i < 12; i++)
        {

                    ui->pass_manager->insertRow(i);

                    QString random = QString::number((rand() % 9999));
                    qDebug() << random;
                    lineEdit_number = new QLineEdit(random);
                    lineEdit_number->setEchoMode(QLineEdit::Normal);
                    lineEdit_number->setProperty("row", i);
                    lineEdit_number->setProperty("column", 1);
                    lineEdit_number->setReadOnly(true);
                    lineEdit_number->installEventFilter(this);

                    ui->pass_manager->setCellWidget(i, 1, lineEdit_number);
                    ui->pass_manager->setStyleSheet("QLineEdit { border: none }");
        }

}




cred_app::~cred_app()
{
    delete ui;
}





