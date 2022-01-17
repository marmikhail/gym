#ifndef ARMGYM_H
#define ARMGYM_H

#include <QMainWindow>
#include <QtSql>
#include "customerssql.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ArmGym; }
QT_END_NAMESPACE

// Главный класс приложения, инкапсулирует всю логику работы
class ArmGym : public QMainWindow
{
    Q_OBJECT

public:
    // Конструктор. Инициализирует графический интерфейс, начальные характеристики работы приложения и логику работы сигналов
    ArmGym(int _codeGym, QWidget *parent = nullptr);
    // Деструктор
    ~ArmGym();

private slots:

    // Переход в режим "Абонементы"
    void action_triggered();
    // Переход на гравную страницу
    void mainInfo();
    // Поиск клиента по Фамилии
    void findCustomersByName();
    // Обработка двойного нажатия на таблицы
    void doubleClickHandler(const QModelIndex &ind);
    // Добавление абонемента
    void addCustButton_clicked();
    // Изменение абонемента
    void changeCustButton_clicked();
    // Удаление абонемента
    void deleteCustButton_clicked();
    // Добавить информацию
    void addInfo();
    // Получить информацию
    void getInfo();

private:
    //  Хранит указатель на объект класса для работы с графическим интерфейсом
    Ui::ArmGym *ui;
    // Хранит указатель на модель таблицы
    QSqlQueryModel *model;
    // Хранит индекс рассматриваемого объекта (если создается новый объект = -1)
    int currentInd = -1;
    // Хранит код спортзала, к которому принадлежит работающий пользователь
    int codeGym;
    // Демонстрирует данные по всем абонементам
    void showCustomer();
};
#endif // ARMGYM_H
