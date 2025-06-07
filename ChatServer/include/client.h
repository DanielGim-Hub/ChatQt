#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QString>

class Client : public QObject        // Объявляем класс Client, наследующий от QObject
{
    Q_OBJECT                          // Макрос Qt для поддержки механизмов сигналов/слотов
public:
    explicit Client(QTcpSocket* socket, QObject *parent = nullptr); // Конструктор, принимает указатель на QTcpSocket
    ~Client();                       // Деструктор

    QTcpSocket* getSocket() const;    // Метод, возвращающий указатель на сокет
    int getPort() const;              // Метод, возвращающий порт удалённого соединения
    void setName(QString name);       // Метод для установки имени клиента (логина)
    QString getName() const;          // Метод для получения имени клиента
    void setState(bool state);        // Метод для установки состояния "онлайн/офлайн"
    bool isOnline();                  // Метод для проверки, онлайн ли клиент
    bool isInBan();                   // Метод для проверки, находится ли клиент в бане
    void setBan(bool ban);            // Метод для установки флага бана

private:
    QTcpSocket* _socket;              // Указатель на TCP-сокет клиента
    QString _clientName {};           // Переменная для хранения имени (логина) клиента
    bool _isOnline {};                // Флаг, указывающий, онлайн ли клиент
    bool _inBan {};                   // Флаг, указывающий, находится ли клиент в бане

signals:                              // Раздел сигналов (пока пустой, сигналы не определены)

};

#endif // CLIENT_H
