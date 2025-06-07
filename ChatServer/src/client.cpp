#include "client.h"                   // Подключаем соответствующий заголовочный файл класса Client

// Конструктор класса Client
Client::Client(QTcpSocket* socket, QObject *parent)
    : QObject{parent}                 // Вызываем конструктор базового класса QObject с указанием parent
{
    _socket = socket;                 // Сохраняем переданный указатель на сокет в приватное поле
    _isOnline = false;                // Изначально клиент считается оффлайн
    _inBan = false;                   // Изначально клиент не в бане
}

// Деструктор класса Client
Client::~Client()
{
    _socket->deleteLater();         // Планируем удаление сокета после выхода из цикла событий Qt
}

// Метод возвращает указатель на текущий QTcpSocket
QTcpSocket* Client::getSocket() const
{
    return _socket;                   // Возвращаем приватное поле _socket
}

// Метод возвращает порт, с которого подключился клиент
int Client::getPort() const
{
    return _socket->peerPort();       // Получаем порт удалённой стороны через peerPort()
}

// Метод устанавливает имя (логин) клиента
void Client::setName(QString name)
{
    _clientName = name;               // Присваиваем приватному полю переданный логин
}

// Метод возвращает имя (логин) клиента
QString Client::getName() const
{
    return _clientName;               // Возвращаем приватное поле _clientName
}

// Метод устанавливает состояние "онлайн/офлайн"
void Client::setState(bool state)
{
    _isOnline = state;                // Присваиваем приватному полю _isOnline значение state
}

// Метод проверяет, онлайн ли клиент
bool Client::isOnline()
{
    return _isOnline;                 // Возвращаем текущее значение флага _isOnline
}

// Метод проверяет, находится ли клиент в бане
bool Client::isInBan()
{
    return _inBan;                    // Возвращаем текущее значение флага _inBan
}

// Метод устанавливает флаг бана для клиента
void Client::setBan(bool ban)
{
    _inBan = ban;                     // Присваиваем приватному полю _inBan значение ban
}
