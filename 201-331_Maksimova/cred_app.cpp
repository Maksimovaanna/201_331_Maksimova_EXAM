#include "cred_app.h"
#include "ui_cred_app.h"
#include <QDialog>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <QItemDelegate>
#include <iostream>
#include <QEvent>
#include <vector>
#include <algorithm>
#include <iterator>
#include <QClipboard>
#include <QString>
#include <ctime>
#include <QMessageBox>


//конструктор
cred_app::cred_app(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cred_app)
{
    ui->setupUi(this);
}


//хеш-функция для проверки пин-кода
std::string cred_app::check_pincode(QString user_code){
    QString code = user_code;
    QByteArray hash = QCryptographicHash::hash(code.toUtf8(), QCryptographicHash::Sha256);
    hash = hash.toBase64();
    QString q_hash = QString(hash);
    std::string str_hash = q_hash.toStdString().substr(1,32);
    return str_hash;
}


//создание таблицы
void cred_app::createUI(const QStringList &headers){
    ui->pass_manager->setColumnCount(1); // Указываем число колонок
    ui->pass_manager->setShowGrid(true); // Включаем сетку
    // Разрешаем выделение только одного элемента
    ui->pass_manager->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->pass_manager->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем заголовки колонок
    ui->pass_manager->setHorizontalHeaderLabels(headers);
    // Растягиваем последнюю колонку на всё доступное пространство
    ui->pass_manager->horizontalHeader()->setStretchLastSection(true);

    ui->pass_manager->setEditTriggers(QAbstractItemView::NoEditTriggers);
    numbers();
}


//функция события qlineedit (реагирует на нажатие на какой-то элемент)
bool cred_app::eventFilter(QObject* watched, QEvent* event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
            if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(watched))
            {
                Q_FOREACH(const QLineEdit* i, findChildren<QLineEdit*>())
                i->disconnect();

                int row = lineEdit->property("row").toInt();
                if (k != 4) {
                    for (int i = 0; i < 12; i++)
                    {

                        if (i != row){
                            lineEdit_number = new QLineEdit(mass[i]);
                            lineEdit_number->setEchoMode(QLineEdit::Password);
                            lineEdit_number->setProperty("row", i);
                            lineEdit_number->setProperty("column", 0);
                            lineEdit_number->setReadOnly(true);
                            lineEdit_number->installEventFilter(this);

                            ui->pass_manager->setCellWidget(i, 0, lineEdit_number);
                            ui->pass_manager->setStyleSheet("QLineEdit { border: none }");
                        }
                        //если строка соответствует выборке, то появляется число
                        else {
                            lineEdit_number = new QLineEdit(mass[i]);
                            lineEdit_number->setEchoMode(QLineEdit::Normal); //число отображается в открытом виде
                            lineEdit_number->setReadOnly(true);
                            lineEdit_number->setStyleSheet("QLineEdit { background: rgb(0, 255, 255); selection-background-color: rgb(233, 99, 0); }");
                            ui->pass_manager->setCellWidget(i, 0, lineEdit_number);
                            ui->pass_manager->setStyleSheet("QLineEdit { border: none }");

                            k += 1;
                            summary += mass[i].toInt();
                            ui->summ->setText(QString::number(summary));

                            if (k == 4) {
                                QMessageBox msgBox;
                                msgBox.setWindowTitle("Игра закончена");
                                QString text = QString::number(summary);
                                msgBox.setText(text);
                                msgBox.exec();
                                numbers(); //происходит сброс игры
                                ui->summ->setText("");
                            }
                        }
                    }
                }
         }
    }
    return QObject::eventFilter(watched, event);
}


//заполнение таблицы
void cred_app::numbers() {
    ui->pass_manager->setRowCount(0); //сброс

    //заполнение массива через функцию рандомизации
    srand((int)time(0));

    for (int i = 0; i < 12; i++)
    {
        mass[i] = QString::number((rand() % 9999));
    }

    k = 0; //на этом этапе счетчик обнулен
    summary = 0; //на этом этапе сумма равна 0

    //заполнение таблицы из данных, находящихся в массиве
    for (int i = 0; i < 12; i++)
    {
                ui->pass_manager->insertRow(i);

                lineEdit_number = new QLineEdit(mass[i]);
                lineEdit_number->setEchoMode(QLineEdit::Password);
                lineEdit_number->setProperty("row", i);

                lineEdit_number->setReadOnly(true);
                lineEdit_number->installEventFilter(this);

                ui->pass_manager->setCellWidget(i, 0, lineEdit_number);
                ui->pass_manager->setStyleSheet("QLineEdit { border: none }");
    }
}


//деструктор
cred_app::~cred_app()
{
    delete ui;
}





