#include "armgym.h"
#include "./ui_armgym.h"
#include <QMessageBox>
#include <QStyle>
#include <QScrollBar>

ArmGym::ArmGym(int _codeGym, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ArmGym)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    codeGym = _codeGym;

    model = new QSqlQueryModel;

    ui->armLabel->setText(CustomersSQL().armText(codeGym) + " спортзал - АРМ");
    getInfo();

    connect(ui->findCustomerButton, SIGNAL(clicked()), this, SLOT(findCustomersByName()));
    connect(ui->customersTable, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(doubleClickHandler(const QModelIndex &)));
    connect(ui->goAddCustButton, SIGNAL(clicked()), this, SLOT(action_triggered()));
    connect(ui->deleteCustButton, SIGNAL(clicked()), this, SLOT(deleteCustButton_clicked()));
    connect(ui->changeCustButton, SIGNAL(clicked()), this, SLOT(changeCustButton_clicked()));
    connect(ui->addCustButton, SIGNAL(clicked()), this, SLOT(addCustButton_clicked()));
    connect(ui->custInfo, SIGNAL(triggered()), this, SLOT(action_triggered()));
    connect(ui->mainInfo, SIGNAL(triggered()), this, SLOT(mainInfo()));
    connect(ui->addInfo, SIGNAL(clicked()), this, SLOT(addInfo()));
}
ArmGym::~ArmGym()
{
    delete ui;
    delete model;
}

void ArmGym::findCustomersByName()
{
    QString name = ui->findCustomerLine->text();
    QSqlQuery request;

    qDebug() << name;

    request = CustomersSQL().selectByName(name, codeGym);

            model->setQuery(request);
            ui->customersTable->resizeColumnsToContents();
            ui->findCustomerLine->clear();
}


void ArmGym::action_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->goAddCustButton->close();
    ui->customersTable->setModel(model);

    currentInd = -1;
    showCustomer();
}

void ArmGym::mainInfo()
{
     ui->stackedWidget->setCurrentIndex(0);
     getInfo();
}

void ArmGym::showCustomer() {
    QSqlQuery request;

    ui->fioLine->clear();
    ui->tariffCombo->setCurrentIndex(0);
    ui->durationLine->clear();

    qDebug() << currentInd;

    if (currentInd == -1) {
        request = CustomersSQL().selectC(codeGym);

        model->setQuery(request);

        ui->customersTable->resizeColumnsToContents();
        ui->goAddCustButton->close();
        ui->buttonStackedWidget->setCurrentIndex(0);

    } else {
        request = CustomersSQL().selectById(currentInd);

        ui->fioLine->setText(request.value(0).toString());
        ui->tariffCombo->setCurrentText(request.value(1).toString());
        ui->durationLine->setText(request.value(2).toString());

        ui->buttonStackedWidget->setCurrentIndex(1);
        ui->goAddCustButton->show();
    }
}

void ArmGym::doubleClickHandler(const QModelIndex &ind) {
    currentInd = ui->customersTable->model()->data(ui->customersTable->model()->index(ind.row(), 0)).toInt();

    showCustomer();
}


void ArmGym::addCustButton_clicked()
{
    QString name= ui->fioLine->text();
    QString tariff= ui->tariffCombo->currentText();
    QString duration= ui->durationLine->text();


    if (name == NULL || tariff == NULL || duration == NULL)
    {
        QMessageBox::information(this, "Добавить", "Заполните все поля!");
    } else
    {
        CustomersSQL().insert(name, tariff, duration, codeGym);
        showCustomer();
    }
}


void ArmGym::changeCustButton_clicked()
{
    QString name= ui->fioLine->text();
    QString tariff= ui->tariffCombo->currentText();
    QString duration= ui->durationLine->text();

    if (name == NULL || tariff == NULL || duration == NULL)
    {
        QMessageBox::information(this, "Изменить", "Заполните все поля!");
    } else
    {
        CustomersSQL().update(name, tariff, duration, currentInd);

        currentInd = -1;
        showCustomer();
    }

}


void ArmGym::deleteCustButton_clicked()
{

    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Удалить", "Вы уверены, что хотите удалить?",
                                                               (QMessageBox::Yes | QMessageBox::No));

    if (reply == QMessageBox::Yes)
    {
        CustomersSQL().deleteC(currentInd);

        currentInd = -1;
        showCustomer();
    }
    else qDebug() << "No is clicked";
}


void ArmGym::addInfo()
{
    QString info = ui->infoText->toHtml();


    if (info == NULL)
    {
        QMessageBox::information(this, "Добавить", "Введите текст!");
    } else
    {
        CustomersSQL().insertI(info, codeGym);
        getInfo();
        ui->infoText->clear();
    }
}

void ArmGym::getInfo()
{
    ui->InfoBrowser->clear();

    QSqlQuery request = CustomersSQL().getInfo(codeGym);
    int size(0);

    while (request.next())
    {
        if (size == 0)
        ui->InfoBrowser->insertHtml("<p><b>" + request.value(1).toString()
                                    + "</b></p><p>" + request.value(0).toString() + "</p>");
        else if (size % 2 != 0)
        ui->InfoBrowser->insertHtml("<p><hr/></p><p><b>" + request.value(1).toString()
                                    + "</b></p><p>" + request.value(0).toString() + "</p>");
        else
        ui->InfoBrowser->insertHtml("<p><hr/></p><p><b>" + request.value(1).toString()
                                    + "</b></p><p>" + request.value(0).toString() + "</p>");
        size++;
    }
    qDebug() << "size: " << size;

}
