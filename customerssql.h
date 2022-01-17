#ifndef CUSTOMERSSQL_H
#define CUSTOMERSSQL_H

#include <QMainWindow>
#include <QtSql>

//Класс для работы с таблицами БД
class CustomersSQL
{
public:
    // Конструктор по умолчанию
    CustomersSQL();
    // Деструктор по умолчанию
    ~CustomersSQL();
    // Инсерт в таблицу с абонементами
    void insert(QString name, QString tariff, QString duration, int codeGym);
    // Апдейт таблицы с абонементами
    void update(QString name, QString tariff, QString duration, int Id);
    // Удаление из таблицы с абонементами
    void deleteC(int Id);
    // Селект из таблицы с абонементами по ИД абонемента
    QSqlQuery selectById(int Id);
    //  Селект из таблицы с абонементами по коду спортзала
    QSqlQuery selectC(int codeGym);
    // Селект из таблицы с абонементами по фамилии
    QSqlQuery selectByName(QString name, int codeGym);
    // Селект названия спортзала для отображения на главной странице
    QString armText(int codeGym);
    // Селект информации (новостей) по спортзалу либо по системе
    QSqlQuery getInfo(int codeGym);
    // Инсерт информации в таблицу
    void insertI(QString info, int codeGym);
};


#endif // CUSTOMERSSQL_H
