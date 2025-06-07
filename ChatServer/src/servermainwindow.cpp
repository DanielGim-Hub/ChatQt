#include "servermainwindow.h"
#include "ui_servermainwindow.h"
#include <QTime>
#include <QMessageBox>
#include <QStringList>
#include <QFont>
#include <algorithm>

ServerMainWindow::ServerMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ServerMainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Chat Server");
    ui->portLineEdit->setText("5555");

    _server = new QTcpServer();
    _server->setMaxPendingConnections(10);
    ui->clientCountLineEdit->setText(QString::number(_allClients.size()));
    _onlineUsers = 0;
    ui->authUsersLineEdit->setText(QString::number(_onlineUsers));
    _allUsers = 0;
    ui->allUsersLineEdit->setText(QString::number(_allUsers));
    ui->allUsersRadioButton->setEnabled(false);
    ui->usersOnlineRadioButton->setEnabled(false);
    ui->inBanRadioButton->setEnabled(false);
    ui->banUserPushButton->setEnabled(false);
    ui->disconnectUserPushButton->setEnabled(false);
    ui->user1ComboBox->setEnabled(false);
    ui->user2ComboBox->setEnabled(false);
    ui->showChatPushButton->setEnabled(false);

    // работа с базой данных
    _database = new SQLiteDataBase();
    if(_database->openDatabase())
    {
        // Выводим сообщение об успешном соединении
        ui->informationFromClientTextEdit->append(tr("<font color=darkGreen>%1 The Connection to the database was successful!</font>").arg(QTime::currentTime().toString()));
        if(_database->createTables()) {
            // Таблицы созданы/найдены
            ui->informationFromClientTextEdit->append(tr("<font color=darkGreen>%1 Database Tables successfully found or created</font>").arg(QTime::currentTime().toString()));
        }
        else {
            ui->connectButton->setEnabled(false);
            // Выводим сообщение об ошибке
            ui->informationFromClientTextEdit->append(tr("<font color=darkRed>%1 The search or creation of database tables failed</font>").arg(QTime::currentTime().toString()));
        }
    }
    // Если не удалось открыть базу данных
    else {
        QMessageBox(QMessageBox::Information,
                    QObject::tr("Error"),
                    QObject::tr("Connection with database failed!"),
                    QMessageBox::Ok).exec();// Показываем сообщение об ошибке соединения с БД
        ui->connectButton->setEnabled(false);// Отключаем кнопку запуска сервера
        ui->informationFromClientTextEdit->append(tr("<font color=darkRed>%1 The Connection to the database failed!</font>").arg(QTime::currentTime().toString()));
    }

    connect(_server,&QTcpServer::newConnection,this,&ServerMainWindow::newConnect);
    connect(ui->closeButton, &QPushButton::clicked, this, &ServerMainWindow::close);

    // Когда переключамся на радиокнопку «Все пользователи»
    connect(ui->allUsersRadioButton, &QRadioButton::toggled, this, [this](const auto on){
        if(on) {
            QVector<QString> users = _database->getAllUsers();
            for(auto& user : users) {
                ui->usersListWidget->addItem(user);// Добавляем каждого в список
            }
            ui->banUserPushButton->setEnabled(false);
            ui->disconnectUserPushButton->setEnabled(false);
            ui->banUserPushButton->setText("Ban user");
        }
        else {
            ui->usersListWidget->clear();
        }
    });

    // Когда переключаемся на Забаненные пользователи
    connect(ui->inBanRadioButton, &QRadioButton::toggled, this, [this](const auto on){
        if(on) {
            for(Client* user : _allClients) { // Перебираем всех подключённых клиентов
                if(user->isInBan())
                    ui->usersListWidget->addItem(user->getName());// Добавляем в список
            }
            ui->banUserPushButton->setEnabled(false);
            ui->disconnectUserPushButton->setEnabled(false);
        }
        else {
            ui->usersListWidget->clear();
        }
    });

    connect(ui->usersListWidget, &QListWidget::itemClicked, this, [this](QListWidgetItem *item){
        if(ui->usersOnlineRadioButton->isChecked()) {
            ui->banUserPushButton->setEnabled(true);
            ui->disconnectUserPushButton->setEnabled(true);
            for(Client* user : _allClients) {
                if((user->getName() == item->text()) && user->isInBan()) {
                    ui->banUserPushButton->setText("Unban user");
                    break;
                }
                else {
                    ui->banUserPushButton->setText("Ban user");
                }
            }
        }
        else if(ui->inBanRadioButton->isChecked()) {
            ui->banUserPushButton->setEnabled(true);
            ui->disconnectUserPushButton->setEnabled(false);
            ui->banUserPushButton->setText("Unban user");
        }
        else {
            ui->banUserPushButton->setEnabled(false);
            ui->disconnectUserPushButton->setEnabled(false);
        }
    });

    connect(ui->usersOnlineRadioButton, &QRadioButton::toggled, this, [this](const auto on){
        if(on) {
            for(Client* user : _allClients) {
                if(user->isOnline())
                    ui->usersListWidget->addItem(user->getName());
            }
        }
        else {
            ui->usersListWidget->clear();
        }
    });
}

ServerMainWindow::~ServerMainWindow()
{
    _server->close();
    _server->deleteLater();
    delete ui;
}

Client* ServerMainWindow::getClientBySocket(QTcpSocket* socket)
{
    for(Client* client : _allClients) {
        QTcpSocket* clientSocket = client->getSocket();
        if(socket == clientSocket) {
            return client;
        }
    }
    return nullptr;
}

// Метод удаления клиента из контейнера _allClients по его сокету
void ServerMainWindow::removeClient(QTcpSocket *socket)
{
    _allClients.remove(_allClients.indexOf(getClientBySocket(socket)));
}

// Метод проверки, онлайн ли пользователь с заданным логином
void ServerMainWindow::userIsOnline(QTcpSocket* socket, QString login)
{
    if(!login.isEmpty()) {
        for(Client* user : _allClients) {
            if((user->getName() == login) && user->isOnline()) {
                socket->write("147;");// Отправляем код 147 (пользователь онлайн)
            }
        }
        socket->write("148;"); // После проверки отправляем код 148 (если пользователь оффлайн)
    }
}
// Слот, вызываемый при поступлении нового входящего соединения от QTcpServer
void ServerMainWindow::newConnect()
{
    QTcpSocket* clientSocket = _server->nextPendingConnection();// Получаем сокет нового клиента

    _client = new Client(clientSocket);
    int port = _client->getPort();

    connect(clientSocket, &QTcpSocket::readyRead, this, &ServerMainWindow::readData);
    connect(clientSocket, &QTcpSocket::disconnected, this, &ServerMainWindow::disconnect);

    _allClients.push_back(_client);
    ui->clientCountLineEdit->setText(QString::number(_allClients.size()));  // Добавляем нового клиента в список всех клиентов
    ui->informationFromClientTextEdit->append(tr("<font color=darkGreen>%1 New client connect from port number %2</font>")
                                                  .arg(QTime::currentTime().toString())
                                                  .arg(QString::number(port)));
}

// Слот, вызываемый, когда один из клиентов отключается
void ServerMainWindow::disconnect()
{
    QTcpSocket* currentSocket = qobject_cast<QTcpSocket*>(sender()); // Получаем сокет, вызвавший событие
    for(Client* client : _allClients) {
        QTcpSocket* clientSocket = client->getSocket(); // Получаем сокет каждого клиента
        if(currentSocket == clientSocket) {       // Если найден отключившийся клиент
            if(!client->getName().isEmpty()) {    // Если у клиента задан логин (он был авторизован)
                QListWidgetItem* currentItem = ui->usersListWidget->findItems(client->getName(), Qt::MatchExactly)[0]; // Находим элемент в списке
                // Если клиент был онлайн и отображается в режиме «Пользователи онлайн» — удаляем из списка
                if(client->isOnline() && ui->usersOnlineRadioButton->isChecked()) {
                    delete ui->usersListWidget->takeItem(ui->usersListWidget->row(currentItem));
                }
                // Если клиент был в бане и отображается в режиме «Забаненные» — удаляем
                if(client->isInBan() && ui->inBanRadioButton->isChecked()) {
                    delete ui->usersListWidget->takeItem(ui->usersListWidget->row(currentItem));
                }
                ui->authUsersLineEdit->setText(QString::number(--_onlineUsers)); // Уменьшаем счётчик онлайн-пользователей
                QString message = "200;" + getClientBySocket(currentSocket)->getName(); // Код 200
                sendMessageToAllButOne(message.toUtf8(), currentSocket); // Оповещаем остальных
            }
            removeClient(currentSocket);           // Удаляем клиента из списка _allClients
            currentSocket->deleteLater();          // Планируем удаление QTcpSocket
            ui->clientCountLineEdit->setText(QString::number(_allClients.size())); // Обновляем число клиентов
            ui->informationFromClientTextEdit->append(tr("<font color=darkRed>%1 Client from port number %2 disconnect</font>")
                                                          .arg(QTime::currentTime().toString()) // Время отключения
                                                          .arg(client->getPort()));            // Порт отключившегося клиента
            break;                                 // Выходим из цикла, так как клиент найден
        }
    }
}

/* COMMANDS FROM CLIENTS
   110 - registration (регистрация)
   120 - login (логин)
   130 - message to all online clients (сообщение всем)
   140 - send private message (приватное сообщение)
   141 - get chat between two users (получить историю приватного чата)
   145 - send list of users (запрос списка пользователей)
   146 - user is online or not (запрос статуса пользователя)
   200 - logout user (выход пользователя)
*/

// Слот для обработки входящих данных от клиента
void ServerMainWindow::readData()
{
    QByteArray message;
    QTcpSocket* currentSocket = qobject_cast<QTcpSocket*>(sender());
    message =  currentSocket->readAll();
    QString str = QString(message);
    QString cmd = str.section(';',0,0);

    switch (cmd.toInt()) {
    case 110:
        ui->informationFromClientTextEdit->append(tr("%1 Requested command from client: Registration").arg(QTime::currentTime().toString()));
        registration(currentSocket, str.section(';',1,1), str.section(';',2,2), str.section(';',3,3));
        break;
    case 120:
        ui->informationFromClientTextEdit->append(tr("%1 Requested command from client: Login").arg(QTime::currentTime().toString()));
        login(currentSocket, str.section(';',1,1), str.section(';',2,2));
        break;
    case 130:
        ui->informationFromClientTextEdit->append(tr("%1 Requested command from client: Send message to all").arg(QTime::currentTime().toString()));
        ui->allMessagesTextEdit->append(tr("%1 %2 write:").arg(QTime::currentTime().toString()).arg(getClientBySocket(currentSocket)->getName()));
        ui->allMessagesTextEdit->append(QString("<font color=dimGray>%1</font>").arg(str.section(';',1)));
        sendMessageToAll(currentSocket, str.section(';',1));
        break;
    case 140:
        ui->informationFromClientTextEdit->append(tr("%1 Requested command from client: Send private message").arg(QTime::currentTime().toString()));
        sendPrivateMessage(currentSocket, str.section(';',1,1), str.section(';',2));
        break;
    case 141:
        ui->informationFromClientTextEdit->append(tr("%1 Requested command from client: Get chat between two users").arg(QTime::currentTime().toString()));
        getChatBetweenTwoUsers(currentSocket,str.section(';',1));
        break;
    case 145:
        ui->informationFromClientTextEdit->append(tr("%1 Requested command from client: Send list of users").arg(QTime::currentTime().toString()));
        sendListOfUsers(currentSocket);
        break;
    case 146:
        ui->informationFromClientTextEdit->append(tr("%1 Requested command from client: User is online or not").arg(QTime::currentTime().toString()));
        userIsOnline(currentSocket,str.section(';',1));
        break;
    case 200:
        ui->informationFromClientTextEdit->append(tr("%1 Requested command from client: Logout").arg(QTime::currentTime().toString()));
        logOut(currentSocket);
        break;
    default:
        break;
    }
}

// Отправка сообщения всем, кроме указанного сокета
void ServerMainWindow::sendMessageToAllButOne(QByteArray message, QTcpSocket* socket)
{
    for (int i = 0; i < _allClients.size(); ++i) {
        QTcpSocket* clientSocket = _allClients.at(i)->getSocket(); // Получаем сокет каждого клиента
        if(socket != clientSocket && _allClients.at(i)->isOnline()) { // Если сокет не совпадает и клиент онлайн
            clientSocket->write(message);                 // Отправляем сообщение
        }
    }
}

// Отправка сообщения только одному указанному сокету
void ServerMainWindow::sendMessageToOne(QByteArray message, QTcpSocket *socket)
{
    for (int i = 0; i < _allClients.size(); ++i) {
        QTcpSocket* clientSocket = _allClients.at(i)->getSocket(); // Получаем сокет
        if(socket == clientSocket) {                         // Если совпадает с целевым
            clientSocket->write(message);                    // Отправляем сообщение
        }
    }
}

// Обработка регистрации нового пользователя
void ServerMainWindow::registration(QTcpSocket* socket, QString name, QString login, QString password)
{
    int res = _database->addUser(name, login, password); // Добавляем пользователя в БД
    QString message;
    switch (res) {
    case 0:// Ошибка добавления в БД
        message = QTime::currentTime().toString() + " User with login " + login + " not added in database! Registration failed...";
        ui->informationFromClientTextEdit->append(message);
        socket->write("111");
        break;
    case 1:  // Пользователь успешно добавлен
        message = QTime::currentTime().toString() + " User with login " + login + " add in database! Registration success...";
        getClientBySocket(socket)->setState(true);             // Устанавливаем состояние клиента как онлайн
        getClientBySocket(socket)->setName(login);             // Устанавливаем имя клиента
        _onlineUsers++;                                         // Увеличиваем счётчик онлайн-пользователей
        ui->authUsersLineEdit->setText(QString::number(_onlineUsers)); // Обновляем отображение онлайн
        ui->allUsersLineEdit->setText(QString::number((ui->allUsersLineEdit->text().toInt())+1)); // Увеличиваем общее число пользователей
        ui->informationFromClientTextEdit->append(message);    // Выводим сообщение об успехе

        // Если в UI выбран режим «Все пользователи» или «Пользователи онлайн», добавляем логин в список
        if(ui->allUsersRadioButton->isChecked() || ui->usersOnlineRadioButton->isChecked())
            ui->usersListWidget->addItem(login);

        ui->user1ComboBox->addItem(login);
        ui->user2ComboBox->addItem(login);

         // Формируем сообщение клиенту с кодом 112 и списком всех онлайн-пользователей
        message = "112;" + login + ";";
        for(Client* user : _allClients) {
            if(user->isOnline())
                message += user->getName() + ",";
        }
        message.resize(message.size()-1);
        socket->write(message.toUtf8());

        message = "100;" + login;// Код 100;логин
        sendMessageToAllButOne(message.toUtf8(), socket);
        break;
    case 2:// Пользователь уже существует
        message = QTime::currentTime().toString() + " User with login " + login + " is already exists";
        ui->informationFromClientTextEdit->append(message);
        socket->write("113");// Отправляем код 113 (логин уже занят)
        break;
    default:
        break;
    }
}

// Обработка логина пользователя
void ServerMainWindow::login(QTcpSocket *socket, QString login, QString password)
{
    bool res = _database->checkUserByLoginAndPassword(login, password); // существует ли пользователь и соответствует ли пароль
    bool isAlreadyOnline = false;                                       // пользователь уже онлайн
    for(Client* user : _allClients) {
        if((user->getName() == login) && user->isOnline()) {            // Если логин совпал и клиент онлайн
            isAlreadyOnline = true;
        }
    }
    QString message;
    if(res && !isAlreadyOnline) {                                        // Если учетные данные верны и пользователь ещё не онлайн
        message = QTime::currentTime().toString() + " The user with login " + login + " was authenticated";
        getClientBySocket(socket)->setState(true);
        getClientBySocket(socket)->setName(login);
        _onlineUsers++;
        ui->authUsersLineEdit->setText(QString::number(_onlineUsers));
        ui->informationFromClientTextEdit->append(message);              // Выводим сообщение об успешной аутентификации
        if(ui->usersOnlineRadioButton->isChecked())
            ui->usersListWidget->addItem(login);

           // Формируем сообщение клиенту с кодом 121 и списком онлайн-пользователей
        message = "121;" + login + ";";
        for(Client* user : _allClients) {
            if(user->isOnline())
                message += user->getName() + ",";
        }
        message.resize(message.size()-1);
        socket->write(message.toUtf8());

        // Оповещаем остальных клиентов о входе нового (код 100)
        message = "100;" + login;
        sendMessageToAllButOne(message.toUtf8(), socket);
    }
    else if(isAlreadyOnline) {
        message = QTime::currentTime().toString() + " The user with login " + login + " is already online";
        ui->informationFromClientTextEdit->append(message);
        socket->write("123;");// Отправляем код 123 (пользователь уже онлайн)
    }
    else {
        message = QTime::currentTime().toString() + " The user with login " + login + " was not authenticated";
        ui->informationFromClientTextEdit->append(message);
        socket->write("122");// Отправляем код 122 (аутентификация неуспешна)
    }
}

// Обработка выхода пользователя
void ServerMainWindow::logOut(QTcpSocket *socket)
{
    ui->informationFromClientTextEdit->append(tr("<font color=darkRed>%1 The user with login %2 logged out the chat</font>").arg(QTime::currentTime().toString()).arg(getClientBySocket(socket)->getName()));
    ui->authUsersLineEdit->setText(QString::number(--_onlineUsers));
    if(ui->usersOnlineRadioButton->isChecked()) {
        QListWidgetItem* currentItem = ui->usersListWidget->findItems(getClientBySocket(socket)->getName(), Qt::MatchExactly)[0];
        delete ui->usersListWidget->takeItem(ui->usersListWidget->row(currentItem));
    }
    QString message = "200;" + getClientBySocket(socket)->getName();
    sendMessageToAllButOne(message.toUtf8(), socket);
    socket->write("500;3");
    getClientBySocket(socket)->setName("");
    getClientBySocket(socket)->setState(false);
}

void ServerMainWindow::sendMessageToAll(QTcpSocket *socket, QString text)
{
    QString message;
    bool res = _database->addMessageToAll(getClientBySocket(socket)->getName(), text);// Сохраняем сообщение в БД
    if(res) {
        for (int i = 0; i < _allClients.size(); ++i) {
            QTcpSocket* onlineClientSocket = _allClients.at(i)->getSocket();
            if(socket != onlineClientSocket && _allClients.at(i)->isOnline()) {// Если не текущий и онлайн
                message = "131;" + getClientBySocket(socket)->getName() + ";" + text;
                onlineClientSocket->write(message.toUtf8());// Отправляем сообщение каждому
            }
        }
        socket->write("500;1"); // Отправляем клиенту код 500;1 (успешная отправка)
    }
    else {
        socket->write("500;4");// Отправляем клиенту код 500;4 (ошибка отправки)
    }
}

// Обработка отправки приватного сообщения
void ServerMainWindow::sendPrivateMessage(QTcpSocket *socket, QString reciever, QString text)
{
    QString message;
    bool res = _database->addPrivateMessage(getClientBySocket(socket)->getName(), reciever, text); // Сохраняем приватное сообщение в БД
    if(res) {
        for (Client* client : _allClients) {
            if(client->getName() == reciever) { // Если имя совпадает с получателем
                message = "141;" + getClientBySocket(socket)->getName() + ";" + text;
                client->getSocket()->write(message.toUtf8());// Отправляем приватное сообщение получателю
            }
        }
        socket->write("500;2");// Отправляем клиенту код 500;2 (успешный приватный)
    }
    else {
        socket->write("500;4");// Код 500;4 (ошибка отправки)
    }
}

// Отправка списка всех пользователей клиенту
void ServerMainWindow::sendListOfUsers(QTcpSocket *socket)
{
    QVector<QString> users = _database->getAllUsers(); // Получаем список пользователей из БД
    QString str;// Буфер для строки списка
    for (auto& user : users) {
        if(user != getClientBySocket(socket)->getName())
            str += user + ",";
    }
    str.resize(str.size()-1);// Удаляем последнюю запятую
    QString message = "146;" + str;
    socket->write(message.toUtf8());
}

// Получение истории чата между двумя пользователями
void ServerMainWindow::getChatBetweenTwoUsers(QTcpSocket *socket, QString user2) // Получаем все записи в формате «user1;user2;text»
{
    QVector<QString> messages = _database->getMessagesBetweenTwoUsers(getClientBySocket(socket)->getName(),user2);
    QString str;
    if(messages.size()>0) {
        for(auto& mes : messages) {
            str += mes + "***";
        }
        str.resize(str.size()-3);
        QString message = "142;" + str;
        socket->write(message.toUtf8());
    }
    else
        socket->write("142;");  // Если нет сообщений, отправляем «142;» (пустая история)
}

// Слот, вызываемый при клике на кнопку «Connect»/«Disconnect» сервера
void ServerMainWindow::on_connectButton_clicked()
{
    if(ui->connectButton->text() == QString("Connect")) {      // Если сейчас кнопка «Connect»
        qint16 port = ui->portLineEdit->text().toInt();

        if(!_server->listen(QHostAddress::Any, port)) {        // Пытаемся запустить сервер на указанном порту
            QMessageBox(QMessageBox::Critical,
                        QObject::tr("Error"),
                        _server->errorString(),                // Если не удалось, показываем ошибку
                        QMessageBox::Ok).exec();
            return;
        }
        ui->connectButton->setText("Disconnect");
        ui->portLineEdit->setEnabled(false);
        ui->allUsersRadioButton->setEnabled(true);
        ui->usersOnlineRadioButton->setEnabled(true);
        ui->inBanRadioButton->setEnabled(true);
        ui->user1ComboBox->setEnabled(true);
        ui->user2ComboBox->setEnabled(true);
        ui->showChatPushButton->setEnabled(true);
        ui->allUsersLineEdit->setText(QString::number(_database->getAllUsers().size())); // Отображаем число всех пользователей из БД

        QVector<QString> users = _database->getAllUsers();     // Получаем всех пользователей из БД
        for(auto& user : users) {
            ui->usersListWidget->addItem(user);
            ui->user1ComboBox->addItem(user);
            ui->user2ComboBox->addItem(user);
        }
        ui->user1ComboBox->setCurrentIndex(-1);                // Сбрасываем выбор ComboBox 1
        ui->user2ComboBox->setCurrentIndex(-1);                // Сбрасываем выбор ComboBox 2

        QVector<QString> messages = _database->get10MessagesToAll(); // Получаем последние 10 сообщений из общего чата из БД
        QString user1, text;
        for(const auto& message : messages) {
            user1 = message.section(';',0,0);
            text = message.section(';',1);
            ui->allMessagesTextEdit->append(tr("%1 write:").arg(user1)); // Добавляем строку «user1 write:»
            ui->allMessagesTextEdit->append(QString("<font color=gray>%1</font>").arg(text)); // Добавляем текст серым цветом
        }
    }
    else {                                                     // Если кнопка сейчас «Disconnect»
        for(Client* client : _allClients) {
            if(client->getSocket()->state() == QAbstractSocket::ConnectedState) { // Если клиент ещё подключён
                client->getSocket()->disconnectFromHost();     // Принудительно отключаем клиента
            }
        }
        _server->close();
        ui->connectButton->setText("Connect");
        ui->portLineEdit->setEnabled(true);
        ui->allUsersRadioButton->setEnabled(false);
        ui->usersOnlineRadioButton->setEnabled(false);
        ui->user1ComboBox->setEnabled(false);
        ui->user2ComboBox->setEnabled(false);
        ui->showChatPushButton->setEnabled(false);
        ui->allUsersRadioButton->setChecked(true);
        ui->banUserPushButton->setEnabled(false);
        ui->disconnectUserPushButton->setEnabled(false);
        ui->user1ComboBox->clear();
        ui->user2ComboBox->clear();
        ui->usersListWidget->clear();
        ui->allMessagesTextEdit->clear();
        ui->privateMessagesTextEdit->clear();
        ui->informationFromClientTextEdit->clear();
    }
}

// Слот для кнопки «Show Chat» — показать историю приватных сообщений между двумя выбранными пользователями
void ServerMainWindow::on_showChatPushButton_clicked()
{
    ui->privateMessagesTextEdit->clear();
    QString sender, reciever, text;
    QString user1 = ui->user1ComboBox->currentText();
    QString user2 = ui->user2ComboBox->currentText();
    QVector<QString> messages = _database->getMessagesBetweenTwoUsers(user1,user2); // Получаем список сообщений из БД
    if(messages.isEmpty()) {                            // Если список пуст
        ui->privateMessagesTextEdit->append("No messages between users!");
    }
    else {
        for(const auto& message : messages) {
            sender = message.section(';',0,0);           // Извлекаем отправителя (до первого ';')
            reciever = message.section(';',1,1);         // Извлекаем получателя (между первым и вторым ';')
            text = message.section(';',2);               // Извлекаем текст (всё после второго ';')
            ui->privateMessagesTextEdit->append(tr("%1 write to %2:").arg(sender).arg(reciever)); // Добавляем строку «sender write to receiver:»
            ui->privateMessagesTextEdit->append(QString("<font color=gray>%1</font>").arg(text)); // Добавляем текст сообщения серым цветом
        }
    }
}

// Слот для кнопки «Disconnect User» — принудительное отключение выбранного пользователя
void ServerMainWindow::on_disconnectUserPushButton_clicked()
{
    QListWidgetItem* item = ui->usersListWidget->currentItem();      // Получаем текущий выбранный элемент списка
    QString user = item->text();
    for(Client* client : _allClients) {
        if((client->getName() == user) && client->isOnline()) {       // Если имя совпадает и клиент онлайн
            QString message = "200;" + client->getName();             // Формируем сообщение «200;логин»
            sendMessageToAllButOne(message.toUtf8(), client->getSocket()); // Оповещаем остальных
            client->getSocket()->deleteLater();
            removeClient(client->getSocket());                        // Удаляем клиента из списка _allClients
            QListWidgetItem* currentItem = ui->usersListWidget->findItems(user, Qt::MatchExactly)[0];
            delete ui->usersListWidget->takeItem(ui->usersListWidget->row(currentItem));
            ui->authUsersLineEdit->setText(QString::number(--_onlineUsers));
            ui->clientCountLineEdit->setText(QString::number(_allClients.size()));
            ui->informationFromClientTextEdit->append(tr("<font color=darkRed>%1 Client from port number %2 disconnect</font>")
                                                          .arg(QTime::currentTime().toString())
                                                          .arg(client->getPort()));
            break;
        }
    }
}

// Слот для кнопки «Ban User» / «Unban User» — бан и разбан выбранного пользователя
void ServerMainWindow::on_banUserPushButton_clicked()
{
    QListWidgetItem* item = ui->usersListWidget->currentItem();      // Получаем выбранный элемент списка
    QString user = item->text();
    for(Client* client : _allClients) {
        if(client->getName() == user) {
            if(ui->banUserPushButton->text() == QString("Ban user")) {
                ui->banUserPushButton->setText("Unban user");
                client->setBan(true);
                QString message = "300;";                              // Формируем сообщение «300;» (уведомление о бане)
                sendMessageToOne(message.toUtf8(), client->getSocket());

                message = "301;" + client->getName();                 // Формируем сообщение «301;логин» (уведомление остальным)
                sendMessageToAllButOne(message.toUtf8(), client->getSocket());

                ui->informationFromClientTextEdit->append(tr("<font color=darkRed>%1 Client with login %2 sent to ban</font>")
                                                              .arg(QTime::currentTime().toString())
                                                              .arg(client->getName()));
                break;
            }
            else {
                ui->banUserPushButton->setText("Ban user");
                client->setBan(false);
                QString message;
                ui->informationFromClientTextEdit->append(tr("<font color=darkGreen>%1 Client with login %2 unban</font>")
                                                              .arg(QTime::currentTime().toString())
                                                              .arg(client->getName()));

                // Формируем сообщение «302;логин;список_онлайн»
                message = "302;" + client->getName() + ";";
                for(Client* user1 : _allClients) {
                    if(user1->isOnline())
                        message += user1->getName() + ",";               // Добавляем логин в строку
                }
                message.resize(message.size()-1);                        // Удаляем лишнюю запятую
                client->getSocket()->write(message.toUtf8());

                // Формируем сообщение «303;логин» (уведомление остальным о разбане)
                message = "303;" + client->getName();
                sendMessageToAllButOne(message.toUtf8(), client->getSocket()); // Отправляем всем, кроме разбаненного

                if(ui->inBanRadioButton->isChecked()) {
                    QListWidgetItem* currentItem = ui->usersListWidget->findItems(user, Qt::MatchExactly)[0];
                    delete ui->usersListWidget->takeItem(ui->usersListWidget->row(currentItem));
                }
            }
        }
    }
}
