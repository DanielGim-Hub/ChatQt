
#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

#include "loginwidget.h"
#include "registrationwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class ClientMainWindow;
    class LoginWidget;
    class RegistrationWidget;
}
QT_END_NAMESPACE

class ClientMainWindow : public QMainWindow
{
    Q_OBJECT  // Макрос для системы сигналов/слотов Qt

public:
    ClientMainWindow(QWidget *parent = nullptr);  // Конструктор
    ~ClientMainWindow();  // Деструктор

    QTcpSocket* getSocket();  // Получить сокет
    QString getCurrentLogin() const;  // Получить текущий логин
    void setCurrentLogin(const QString& newCurrentLogin);  // Установить логин

    // Основные методы работы с чатом:
    void enterUserInChat(QString login, QString users);  // Вход пользователя
    void banUser();  // Блокировка пользователя
    void addUsersInCombobox(QString str);  // Добавление пользователей в выпадающий список
    void receiveMessagesBetweenTwoUsers(QString str);  // Получение приватных сообщений
    void receiveCommandMessageFromServer(QString cmd);  // Обработка команд от сервера

private slots:  // Слоты для обработки событий
    void disconnect();  // Отключение от сервера
    void openLoginWidget();  // Открытие окна авторизации
    void openRegistrationWidget();  // Открытие окна регистрации
    void on_connectButton_clicked();  // Обработка кнопки подключения
    void on_sendButton_clicked();  // Обработка кнопки отправки сообщения
    void readData();  // Чтение данных от сервера
    void exitUser();  // Выход пользователя

private:
    Ui::ClientMainWindow *ui;  // Указатель на интерфейс
    QTcpSocket *_socket;  // TCP-сокет для соединения

    // Виджеты:
    LoginWidget* _loginWidget;  // Окно авторизации
    RegistrationWidget* _registrationWidget;  // Окно регистрации

    bool _isOnline {};  // Флаг онлайн-статуса
    QString _currentLogin {};  // Текущий логин пользователя
};

#endif // CLIENTMAINWINDOW_H
