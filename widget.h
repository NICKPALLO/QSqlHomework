#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QDialog
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
signals:
    void sig_sendData(QVector<QString> dbData);

private slots:

    void on_pb_cancel_clicked();

    void on_pb_ok_clicked();

private:
    Ui::Widget *ui;
    QVector<QString> data;
};
#endif // WIDGET_H
