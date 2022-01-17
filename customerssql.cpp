#include "customerssql.h"

CustomersSQL::CustomersSQL(){}
CustomersSQL::~CustomersSQL(){}


void CustomersSQL::insert(QString name, QString tariff, QString duration, int codeGym)
{
    QSqlQuery request;

    request.prepare(R"(INSERT INTO Customers (Name, Tariff, Duration, CodeGym, DateOfPurchase)
                       VALUES (?, (SELECT Code from D_Tariff where Name LIKE ?), ?, ?, DATE('now')))");
    request.addBindValue(QString("%1").arg(name));
    request.addBindValue(QString("%2").arg(tariff));
    request.addBindValue(QString("%3").arg(duration));
    request.addBindValue(QString("%4").arg(codeGym));

    request.exec();
    qDebug() << request.lastError();
}

void CustomersSQL::update(QString name, QString tariff, QString duration, int Id)
{
    QSqlQuery request;

    request.prepare(R"(UPDATE Customers SET
                       Name = ?,
                       Tariff = (SELECT Code from D_Tariff where Name LIKE ?),
                       Duration = ? WHERE id = ?)");
    request.addBindValue(QString("%1").arg(name));
    request.addBindValue(QString("%2").arg(tariff));
    request.addBindValue(QString("%3").arg(duration));
    request.addBindValue(QString("%4").arg(Id));

    request.exec();
    qDebug() << request.lastError();
}

void CustomersSQL::deleteC(int Id)
{
     QSqlQuery request;

     request.prepare(R"(DELETE FROM Customers WHERE Id = ?)");
     request.addBindValue(Id);

     request.exec();
     qDebug() << request.lastError();
}

QSqlQuery CustomersSQL::selectById(int Id)
{
    QSqlQuery request;

    request.prepare(R"(SELECT c.Name as ФИО, dt.Name as Тариф, c.Duration as Длительность
                FROM Customers c
                LEFT JOIN D_Tariff dt on dt.Code = c.Tariff
                WHERE c.Id = ?)");
    request.addBindValue(Id);

    qDebug() << request.exec();
    request.first();
    return request;
}

QSqlQuery CustomersSQL::selectC(int codeGym)
{
    QSqlQuery request;

    request.prepare(R"(SELECT c.id as ID, c.Name as ФИО, dt.Name as Тариф, c.DateOfPurchase as `Дата Приобретения`, c.Duration as Длительность, date (c.DateOfPurchase, c.Duration || " month") as `Действителен До`
                    FROM Customers c
                    LEFT JOIN D_Gym dg on dg.Code = c.CodeGym
                    LEFT JOIN D_Tariff dt on dt.Code = c.Tariff
                    WHERE c.CodeGym = ? ORDER BY id DESC LIMIT 100)");
    request.addBindValue(QString("%1").arg(codeGym));

    qDebug() << request.exec();
    return request;
}

QSqlQuery CustomersSQL::selectByName(QString name, int codeGym)
{
    QSqlQuery request;

    request.prepare(R"(SELECT c.id as ID, c.Name as ФИО, dt.Name as Тариф, c.DateOfPurchase as `Дата Приобретения`, c.Duration as Длительность, date (c.DateOfPurchase, c.Duration || " month") as `Действителен До` FROM Customers c
                    LEFT JOIN D_Gym dg on dg.Code = c.CodeGym
                    LEFT JOIN D_Tariff dt on dt.Code = c.Tariff
                    WHERE c.Name LIKE ? and c.CodeGym = ?)");
    request.addBindValue(QString("%%1%").arg(name));
    request.addBindValue(QString("%2").arg(codeGym));

    if(!request.exec()) qDebug() << "Ошибка выполнения sql запроса";
    return request;
}

QString CustomersSQL::armText(int codeGym)
{
    QSqlQuery request;

    request.prepare(R"(SELECT Name FROM D_Gym where Code = ?)");
    request.addBindValue(QString("%1").arg(codeGym));

    request.exec();
    request.first();

    return request.value(0).toString();
}

QSqlQuery CustomersSQL::getInfo(int codeGym)
{

    QSqlQuery request;

    request.prepare(R"(SELECT Info, DateWrite FROM Info where CodeGym = :codeGym ORDER BY Id DESC LIMIT 10)");
    request.bindValue(":codeGym", codeGym);

    request.exec();

    qDebug() << request.lastError();
    return request;
}

void CustomersSQL::insertI(QString info, int codeGym)
{
    QSqlQuery request;

    request.prepare(R"(INSERT INTO Info (Info, DateWrite, CodeGym)
                       VALUES (?, DATE('now'), ?))");
    request.addBindValue(QString("%1").arg(info));
    request.addBindValue(QString("%2").arg(codeGym));

    request.exec();
    qDebug() << request.lastError();
}
