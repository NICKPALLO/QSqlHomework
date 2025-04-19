#include "database.h"
#include <cstdint>
#include <qcontainerfwd.h>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qtablewidget.h>

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{
    dataBase = new QSqlDatabase( );

    tableView = new QTableView();

    querryModel = new QSqlQueryModel();

}

DataBase::~DataBase()
{
    delete dataBase;
    if (model)
    {
    delete model;
    }
    delete querryModel;
    //delete tableView;
}

/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase(QString driver, QString nameDB)
{
    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);
}

/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase(QVector<QString> data)
{
    ///Для подключения необходимо передать параметры БД в объект класса.

    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());

    bool statusConnect = dataBase->open( );
    emit sig_SendStatusConnection(statusConnect);
}

/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{
    dataBase->database(nameDb);
    dataBase->close( );
}

/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 * \return
 */
void DataBase::RequestToDB(QString request)
{
    querryModel->setQuery(QSqlQuery(request, *dataBase));
    emit sig_SendStatusRequest(querryModel->lastError());
}

/*!
 * \brief Метод читае ответ, полученный от БД при помощи QSqlQuery
 * \param answerType - тип ответа
 */
void DataBase::ReadAnswerFromDB(int requestType)
{
    switch (requestType) {
    case requestAllFilms:
    {
        tableView->setModel(model);
        emit sig_SendDataFromDB(tableView,requestType);
        break;
    }
    case requestComedy:
    case requestHorrors:
    {
        tableView->setModel(querryModel);
        emit sig_SendDataFromDB(tableView,requestType);
        break;
    }
    default:
        break;
    }
}


/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{

    return dataBase->lastError( );
}

void DataBase::getAllTable()
{
    model->select();
    emit sig_SendStatusRequest(model->lastError());


}

void DataBase::createModel()
{
    if(!model)
    {
        model = new QSqlTableModel(nullptr,QSqlDatabase::database(DB_NAME));

        model->setTable("film");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    }
}

void DataBase::deleteTableView()
{
    delete tableView;
}
