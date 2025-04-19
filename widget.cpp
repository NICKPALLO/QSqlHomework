#include "widget.h"
#include "database.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->le_host->setText("981757-ca08998.tmweb.ru");
    ui->le_dbName->setText("netology_cpp");
    ui->le_login->setText("netology_usr_cpp");
    ui->le_pass->setText("CppNeto3");
    ui->spB_port->setValue(5432);
    data.resize(NUM_DATA_FOR_CONNECT_TO_DB);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pb_cancel_clicked()
{
    this->close();
}


void Widget::on_pb_ok_clicked()
{
    data[hostName] = ui->le_host->text();
    data[dbName] = ui->le_dbName->text();
    data[login] = ui->le_login->text();
    data[pass] = ui->le_pass->text();
    data[port] = ui->spB_port->text();
    emit sig_sendData(data);
    this->close();
}

