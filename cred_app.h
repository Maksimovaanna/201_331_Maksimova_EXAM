#ifndef CRED_APP_H
#define CRED_APP_H
#include <QDialog>
#include <QTableWidgetItem>
#include <QLineEdit>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <windows.h>
#include <QCryptographicHash>

//using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class cred_app; }
QT_END_NAMESPACE



class cred_app : public QDialog
{
    Q_OBJECT

public:
    cred_app(QWidget *parent = nullptr);
    ~cred_app();
    void createUI(const QStringList &headers);
    std::string check_pincode(QString user_code);
    QString mass[12]; //массив, в котором хранятся рандомные числа от 0 до 9999
    int summary; //сумма, выводимая на экран
    int k; //счетчик, позволяющий складывать числа ровно 4 раза

private:
    Ui::cred_app *ui;
    QLineEdit *lineEdit_number;
    void numbers();
    void add_cred(QString site, QString login, QString password);
    bool eventFilter(QObject* watched, QEvent* event);


signals:
    void ShowMW();//функция для возврата на окно MW

private slots:
    //void on_pass_manager_cellDoubleClicked(int row, int column);

};

#endif // CRED_APP_H

