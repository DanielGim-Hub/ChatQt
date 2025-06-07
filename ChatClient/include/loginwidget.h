#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <memory>
#include <QTcpSocket>

namespace Ui {              // Пространство имен для сгенерированного UI-класса
class LoginWidget;          // Предварительное объявление класса формы UI
}

class LoginWidget : public QWidget  // Основной класс виджета авторизации
{
    Q_OBJECT                // Макрос Qt для поддержки сигналов/слотов и RTTI

public:
    explicit LoginWidget(QTcpSocket* socket, QWidget *parent = nullptr);  // Конструктор с параметрами
    ~LoginWidget();         // Деструктор

    void loginResult(int command);  // Метод обработки результата авторизации от сервера

signals:                    // Секция сигналов (в данном классе пустая)
         // Сигналы используются для оповещения других объектов

private slots:              // Секция слотов (методов, вызываемых по сигналам)
    void closeWidget();     // Слот для закрытия виджета
    void on_okButton_clicked();  // Слот-обработчик нажатия кнопки OK

private:
    Ui::LoginWidget *ui;    // Указатель на сгенерированный интерфейс
    QTcpSocket* _socket;    // Указатель на TCP-сокет для связи с сервером
};

#endif // LOGINWIDGET_H
