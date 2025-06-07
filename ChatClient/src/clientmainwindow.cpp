
#include "clientmainwindow.h"
#include "ui_clientmainwindow.h"
#include <QMessageBox>
#include <QTime>
#include <QStringList>
#include <QtSql/QSqlDatabase>

ClientMainWindow::ClientMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientMainWindow)
{
    //начальные настройки интерфейса
    ui->setupUi(this);
    this->setWindowTitle("Chat Client");
    ui->ipLineEdit->setText("127.0.0.1");
    ui->portLineEdit->setText("5555");
    //отключение элементов интерейса до подключения
    ui->messageToAllRadioButton->setEnabled(false);
    ui->privateMessageRadioButton->setEnabled(false);
    ui->privateMessageFromRadioButton->setEnabled(false);
    ui->allPrivateMessagesRadioButton->setEnabled(false);
    ui->privateMessageRadioButton->setChecked(false);
    ui->privateMessageFromRadioButton->setChecked(false);

    ui->loginButton->setEnabled(false);
    ui->registrationButton->setEnabled(false);
    ui->exitUserButton->setEnabled(false);

    ui->messageLabel->setEnabled(false);
    ui->messageLineEdit->setEnabled(false);
    ui->sendButton->setEnabled(false);
    ui->currentUserLabel->setText("<font color=red>Current user:</font>");
    ui->chatWithTextEdit->hide();

    _isOnline = false;

    _socket=new QTcpSocket();

    // Соединение сигналов и дизайнов
    connect(ui->registrationButton, &QPushButton::clicked, this, &ClientMainWindow::openRegistrationWidget);
    connect(ui->loginButton, &QPushButton::clicked, this, &ClientMainWindow::openLoginWidget);
    connect(_socket,&QTcpSocket::readyRead,this,&ClientMainWindow::readData);
    connect(_socket, &QTcpSocket::disconnected, this, &ClientMainWindow::disconnect);
    connect(ui->closeButton, &QPushButton::clicked, this, &ClientMainWindow::close);
    connect(ui->exitUserButton, &QPushButton::clicked, this, &ClientMainWindow::exitUser);

    // Указатель через что будет список пользователей для приватного сообщения
    auto * const userscb = ui->usersComboBox;
    connect(ui->privateMessageRadioButton, &QRadioButton::toggled, this, [this, userscb](const auto on){
         // Обработка выбора приватного сообщения
        if(on) {
            userscb->setEnabled(true);
            userscb->setCurrentIndex(-1);
        }
        else {
            userscb->setEnabled(false);
            userscb->setCurrentIndex(-1);
            userscb->setCurrentText("");
            ui->usersStateLabel->setText("");
        }
    });
    // Когда выбираем логин пользователя из usersComboBox при включенном режиме privateMessageRadioButton
    connect(userscb, &QComboBox::currentTextChanged, this, [this,userscb](QString login){
        if(userscb->currentIndex() != -1 && ui->privateMessageRadioButton->isChecked()) {
            QString message = "146;" + login;// Формируем команду 146;login для запроса статуса
            _socket->write(message.toUtf8());
        }
    });
    // Аналогичная логика для режима «получить приватные сообщения от конкретного пользователя»
    auto* const userscb_private = ui->privateUsersComboBox;
    connect(ui->privateMessageFromRadioButton, &QRadioButton::toggled, this, [this, userscb_private](const auto on){
        if(on) {
            userscb_private->setEnabled(true);
            userscb_private->setCurrentIndex(-1);
            ui->chatWithTextEdit->show();
            ui->chatWithTextEdit->clear();
        }
        else {
            userscb_private->setCurrentIndex(-1);
            userscb_private->setCurrentText("");
            userscb_private->setEnabled(false);
            ui->chatWithTextEdit->hide();
        }
    });
    // Когда выбираем пользователя для просмотра истории приватных сообщений
    connect(userscb_private, &QComboBox::currentTextChanged, this, [this,userscb_private](QString login){
        ui->chatWithTextEdit->clear();
        if(userscb_private->currentIndex() != -1 && ui->privateMessageFromRadioButton->isChecked()) {
            QString message = "141;" + login;// Формируем команду 141;login для запроса истории
            _socket->write(message.toUtf8());
        }
    });
}
ClientMainWindow::~ClientMainWindow()
{
    delete _socket;
    delete ui;
}

QTcpSocket *ClientMainWindow::getSocket()
{
    return _socket;
}

QString ClientMainWindow::getCurrentLogin() const
{
    return _currentLogin;
}

void ClientMainWindow::setCurrentLogin(const QString &newCurrentLogin)
{
    _currentLogin = newCurrentLogin;
}
// Метод вызывается после успешного логина или регистрации, чтобы ввести пользователя в чат
void ClientMainWindow::enterUserInChat(QString login, QString users)
{
    QStringList lst;
    _isOnline = true;
    setCurrentLogin(login);
    lst = users.split(",");
    ui->usersOnlineListWidget->clear();

    for(auto& l : lst)
        ui->usersOnlineListWidget->addItem(l);
     // После входа в чат блокируем кнопки «Логин» и «Регистрация»
    ui->loginButton->setEnabled(false);
    ui->registrationButton->setEnabled(false);
    ui->exitUserButton->setEnabled(true);
    ui->currentUserLabel->setText(QString("<font color=green>Current user: %1</font>").arg(login));
    // Включаем радио-кнопки отправки сообщений и устанавливаем «отправить всем» по умолчанию
    ui->messageToAllRadioButton->setEnabled(true);
    ui->messageToAllRadioButton->setChecked(true);
    ui->privateMessageRadioButton->setEnabled(true);
    ui->privateMessageFromRadioButton->setEnabled(true);
    ui->allPrivateMessagesRadioButton->setEnabled(true);
    ui->allPrivateMessagesRadioButton->setChecked(true);
    // Пока что списки отправки приватных сообщений остаются неактивными
    ui->privateUsersComboBox->setEnabled(false);
    ui->usersComboBox->setEnabled(false);
    // Активируем метку и поле для ввода сообщения и кнопку «Отправить»
    ui->messageLabel->setEnabled(true);
    ui->messageLineEdit->setEnabled(true);
    ui->sendButton->setEnabled(true);
    _socket->write("145;"); // Отправляем на сервер команду 145;
    //(запрос обновленного списка пользователей)
}

// Метод для блокировки пользователя (BAN)
void ClientMainWindow::banUser()
{
    ui->currentUserLabel->setText(QString("<font color=red>Current user: %1 (in ban)</font>").arg(getCurrentLogin()));
    // Переводим все режимы отправки в неактивное состояние
    ui->messageToAllRadioButton->setChecked(true);
    ui->messageToAllRadioButton->setEnabled(false);
    ui->privateMessageRadioButton->setEnabled(false);
    ui->allPrivateMessagesRadioButton->setChecked(true);
    ui->allPrivateMessagesRadioButton->setEnabled(false);
    ui->privateMessageFromRadioButton->setEnabled(false);
    ui->privateUsersComboBox->setEnabled(false);
    ui->messageLabel->setEnabled(false);
    ui->messageLineEdit->setEnabled(false);
    ui->sendButton->setEnabled(false);
}

// Метод выхода пользователя из чата
void ClientMainWindow::exitUser()
{
    //все очищаем
    _isOnline = false;
    setCurrentLogin("");
    ui->allMessagesTextEdit->clear();
    ui->privateMessagesTextEdit->clear();
    ui->usersOnlineListWidget->clear();

     // Включаем кнопки «Логин» и «Регистрация», сбрасываем прочие элементы
    ui->loginButton->setEnabled(true);
    ui->registrationButton->setEnabled(true);
    ui->exitUserButton->setEnabled(false);
    ui->currentUserLabel->setText("<font color=red>Current user: </font>");
    ui->messageToAllRadioButton->setChecked(true);
    ui->messageToAllRadioButton->setEnabled(false);
    ui->privateMessageRadioButton->setEnabled(false);
    ui->allPrivateMessagesRadioButton->setChecked(true);
    ui->allPrivateMessagesRadioButton->setEnabled(false);
    ui->privateMessageFromRadioButton->setEnabled(false);
    ui->privateUsersComboBox->setEnabled(false);
    ui->messageLabel->setEnabled(false);
    ui->messageLineEdit->setEnabled(false);
    ui->sendButton->setEnabled(false);

    _socket->write("200");
}

//online-пользователи
void ClientMainWindow::addUsersInCombobox(QString str)
{
    QStringList users = str.split(",");
    ui->usersComboBox->clear();
    ui->privateUsersComboBox->clear();
    ui->usersComboBox->addItems(users);
    ui->usersComboBox->setCurrentIndex(-1);
    ui->usersComboBox->setCurrentText("");
    ui->privateUsersComboBox->addItems(users);
    ui->privateUsersComboBox->setCurrentIndex(-1);
    ui->privateUsersComboBox->setCurrentText("");
}

// Обрабатывает строки, полученные от сервера с историей переписки между двумя пользователями
void ClientMainWindow::receiveMessagesBetweenTwoUsers(QString str)
{
    if(ui->privateUsersComboBox->currentIndex() != -1) {
        if(str.isEmpty()) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Private messages");
            msgBox.setText("No messages with selected user");
            msgBox.resize(60,40);
            msgBox.exec();
        }
        else {
            QStringList messages = str.split("***");
            QString user1, user2, text;
            for(const auto& message : messages) {
                user1 = message.section(';',0,0);
                user2 = message.section(';',1,1);
                text = message.section(';',2);
                ui->chatWithTextEdit->append(tr("%1 write to %2:").arg(user1).arg(user2));
                ui->chatWithTextEdit->append(QString("<font color=gray>%1</font>").arg(text));
            }
        }
    }
}

// Обрабатывает командные сообщения от сервера, например, ответы об успешной/неуспешной отправке
void ClientMainWindow::receiveCommandMessageFromServer(QString cmd)
{
    //QMessageBox msgBox;

    switch(cmd.toInt()) {
    case 1:
    case 2:
        QMessageBox(QMessageBox::Information,
                    QObject::tr("Message"),
                    QObject::tr("Message was send!"),
                    QMessageBox::Ok).exec();
        break;
    case 3:
        QMessageBox(QMessageBox::Information,
                    QObject::tr("Logout user"),
                    QObject::tr("You have logged out of the chat"),
                    QMessageBox::Ok).exec();
        break;
    case 4:
        QMessageBox(QMessageBox::Critical,
                    QObject::tr("Error"),
                    QObject::tr("Error send message"),
                    QMessageBox::Ok).exec();
        break;
    default:
        break;
    }
}

//отключение или потеря соединения
void ClientMainWindow::disconnect()
{
    ui->sendButton->setEnabled(false);
    ui->connectButton->setText("Connect");

       // Показываем предупреждение, что соединение с сервером потеряно
    QMessageBox msgBox;
    msgBox.setWindowTitle("CAUTION");
    msgBox.setText("You are dissconnect from server!");
    msgBox.resize(60,30);
    msgBox.exec();

     // Деактивируем все кнопки и поля ввода, связанные с чатом
    ui->loginButton->setEnabled(false);
    ui->registrationButton->setEnabled(false);
    ui->exitUserButton->setEnabled(false);
    ui->messageToAllRadioButton->setEnabled(false);
    ui->messageToAllRadioButton->setChecked(true);
    ui->privateMessageRadioButton->setEnabled(false);
    ui->allPrivateMessagesRadioButton->setEnabled(false);
    ui->allPrivateMessagesRadioButton->setChecked(true);
    ui->privateMessageFromRadioButton->setEnabled(false);
    ui->messageLabel->setEnabled(false);
    ui->messageLineEdit->setEnabled(false);
    ui->sendButton->setEnabled(false);
    ui->allMessagesTextEdit->clear();
    ui->privateMessagesTextEdit->clear();
    ui->usersOnlineListWidget->clear();
    ui->currentUserLabel->setText("<font color=red>Current user:</font>");
    ui->ipLineEdit->setEnabled(true);
    ui->portLineEdit->setEnabled(true);
}
// Открывает модальное окно для логина пользователя
void ClientMainWindow::openLoginWidget()
{
    _loginWidget = new LoginWidget(_socket);
    _loginWidget->setWindowModality(Qt::ApplicationModal);
    _loginWidget->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    _loginWidget->show();
}
// Открывает модальное окно для регистрации пользователя
void ClientMainWindow::openRegistrationWidget()
{
    _registrationWidget = new RegistrationWidget(_socket);
    _registrationWidget->setWindowModality(Qt::ApplicationModal);
    _registrationWidget->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    _registrationWidget->show();
}

// Слот, вызываемый при клике на кнопку «Connect»/«Disconnect»
void ClientMainWindow::on_connectButton_clicked()
{
    QString ip;
    qint16 port;
    // Если кнопка сейчас в состоянии «Connect»
    if (ui->connectButton->text() == QString("Connect"))
    {
        ip=ui->ipLineEdit->text();
        port=ui->portLineEdit->text().toInt();

        _socket->abort();
        _socket->connectToHost(ip,port);

        if (!_socket->waitForConnected())
        {
            // Если соединиться не удалось — показываем сообщение об ошибке
            QMessageBox msgBox;
            msgBox.setWindowTitle("Client");
            msgBox.setText("Runtime Out");
            msgBox.resize(50,30);
            msgBox.exec();
            return;
        }
        // Если успешно подключились — показываем окно с подтверждением
        QMessageBox msgBox;
        msgBox.setWindowTitle("Client");
        msgBox.setText("Successful Connection");
        msgBox.resize(50,40);
        msgBox.exec();

        // Меняем текст кнопки на «Disconnect» и активируем кнопки «Login» и «Registration»
        ui->connectButton->setText("Disconnect");
        ui->loginButton->setEnabled(true);
        ui->registrationButton->setEnabled(true);
        ui->exitUserButton->setEnabled(false);
        ui->ipLineEdit->setEnabled(false);
        ui->portLineEdit->setEnabled(false);
    }

    else
    {
        // Если кнопка была «Disconnect» — отсоединяемся от хоста
        _socket->disconnectFromHost();

        // Меняем текст кнопки обратно на «Connect» и сбрасываем интерфейс
        ui->connectButton->setText("Connect");
        ui->loginButton->setEnabled(false);
        ui->registrationButton->setEnabled(false);
        ui->exitUserButton->setEnabled(false);
        ui->messageToAllRadioButton->setEnabled(false);
        ui->messageToAllRadioButton->setChecked(true);
        ui->privateMessageRadioButton->setEnabled(false);
        ui->allPrivateMessagesRadioButton->setEnabled(false);
        ui->allPrivateMessagesRadioButton->setChecked(true);
        ui->privateMessageFromRadioButton->setEnabled(false);
        ui->messageLabel->setEnabled(false);
        ui->messageLineEdit->setEnabled(false);
        ui->sendButton->setEnabled(false);
        ui->allMessagesTextEdit->clear();
        ui->privateMessagesTextEdit->clear();
        ui->usersOnlineListWidget->clear();
        ui->currentUserLabel->setText("<font color=red>Current user:</font>");
        ui->ipLineEdit->setEnabled(true);
        ui->portLineEdit->setEnabled(true);
    }
}

// Слот, вызываемый при нажатии на кнопку «Send» (Отправить сообщение)
void ClientMainWindow::on_sendButton_clicked()
{
    QString message;
    // Если выбрано «Отправить всем»
    if(ui->messageToAllRadioButton->isChecked()) {
        // Если поле сообщения пустое — сообщаем об ошибке
        if (ui->messageLineEdit->text().isEmpty()) {
            QMessageBox msgb;
            msgb.setText("Can't Send Empty Message");
            msgb.resize(60, 40);
            msgb.exec();
            return;
        }

        // Добавляем в общий чат текст «время From Me:» и само сообщение
        ui->allMessagesTextEdit->append(tr("<font color=darkSlateBlue>%1 From Me:</font>").arg(QTime::currentTime().toString()));
        ui->allMessagesTextEdit->append(QString("<font color=grey>%1</font>").arg(ui->messageLineEdit->text()));
        message = "130;" + ui->messageLineEdit->text();
        _socket->write(message.toUtf8());
        _socket->flush();
        ui->messageLineEdit->clear();
        ui->messageLineEdit->setFocus();
    }
     // Если выбрано «Отправить приватному пользователю»
    if(ui->privateMessageRadioButton->isChecked()) {
        QString reciever = ui->usersComboBox->currentText();// Получаем логин выбранного пользователя
         // Проверяем, что поле сообщения не пустое
        if(ui->messageLineEdit->text().isEmpty()) {
            QMessageBox msgb;
            msgb.setText("Can't Send Empty Message");
            msgb.resize(60, 40);
            msgb.exec();
            return;
        }
        // Проверяем, что пользователь выбран из списка
        if(ui->usersComboBox->currentIndex() == -1) {
            QMessageBox msgb;
            msgb.setText("You need to select a user!");
            msgb.resize(60, 40);
            msgb.exec();
            return;
        }
        // Если также открыт режим «просмотреть приватные сообщения от этого же пользователя»
        if(ui->privateMessageFromRadioButton->isChecked() && ui->privateUsersComboBox->currentText() == reciever) {
            // Добавляем в окно чата с конкретным пользователем «From Me: текст»
            ui->chatWithTextEdit->append(tr("%1 write to %2:").arg(getCurrentLogin()).arg(reciever));
            ui->chatWithTextEdit->append(QString("<font color=gray>%1</font>").arg(ui->messageLineEdit->text()));
        }
        message = "140;" + reciever + ";" + ui->messageLineEdit->text();
        _socket->write(message.toUtf8());
        _socket->flush();
        ui->messageLineEdit->clear();
        ui->messageLineEdit->setFocus();
    }
}

// Комментарий к использованию команд от сервера:
/*
   100 - новый пользователь присоединился к чату
   111 - регистрация (пользователь не добавлен в базу данных)
   112 - регистрация (пользователь добавлен в базу данных)
   113 - регистрация (пользователь уже существует)
   121 - логин (аутентификация успешна)
   122 - логин (аутентификация неудачна)
   123 - логин (пользователь уже онлайн)
   131 - отправка сообщения всем онлайн-клиентам
   141 - приватное сообщение
   142 - получить историю переписки между двумя пользователями
   146 - список пользователей для заполнения combobox
   147 - 148 - состояние пользователя (онлайн/офлайн) для приватного сообщения
   200 - пользователь вышел из чата
   300 - текущий пользователь забанен
   301 - пользователь забанен
   302 - текущий пользователь разбанен
   303 - пользователь разбанен
   500 - командные сообщения (ответы на действия клиента)
*/

// Метод обработки входящих данных из сокета
void ClientMainWindow::readData()
{
    QByteArray message;
    message = _socket->readAll();
    QString str = QString(message);
    QString cmd = str.section(';',0,0);
    int ind;
    QListWidgetItem* currentItem;

    switch (cmd.toInt()) {
    case 100:
        ui->allMessagesTextEdit->append(tr("<font color=green>%1 %2 join to Chat!</font>").arg(QTime::currentTime().toString()).arg(str.section(';',1)));
        ui->usersOnlineListWidget->addItem(str.section(';',1));
        ind = ui->usersComboBox->findText(str.section(';',1), Qt::MatchExactly);
        if(ind == -1) {
            ui->usersComboBox->addItem(str.section(';',1));
        }
        ind = ui->privateUsersComboBox->findText(str.section(';',1), Qt::MatchExactly);
        if(ind == -1) {
            ui->privateUsersComboBox->addItem(str.section(';',1));
        }
        break;
    case 111:
        _registrationWidget->registrationResult(111);
        break;
    case 112:
        _registrationWidget->registrationResult(112);
        enterUserInChat(str.section(';',1,1),str.section(';',2));
        break;
    case 113:
        _registrationWidget->registrationResult(113);
        break;
    case 121:
        _loginWidget->loginResult(121);
        enterUserInChat(str.section(';',1,1),str.section(';',2));
        break;
    case 122:
        _loginWidget->loginResult(122);
        break;
    case 123:
        _loginWidget->loginResult(123);
        break;
    case 131:
        ui->allMessagesTextEdit->append(tr("%1 %2 write:").arg(QTime::currentTime().toString()).arg(str.section(';',1,1)));
        ui->allMessagesTextEdit->append(QString("<font color=grey>%1</font>").arg(str.section(';',2)));
        break;
    case 141:
        if(ui->privateMessageFromRadioButton->isChecked() && ui->privateUsersComboBox->currentText() == str.section(";",1,1)) {
            ui->chatWithTextEdit->append(tr("%1 write to %2:").arg(str.section(";",1,1)).arg(getCurrentLogin()));
            ui->chatWithTextEdit->append(QString("<font color=gray>%1</font>").arg(str.section(';',2)));
        }
            ui->privateMessagesTextEdit->append(tr("%1 Message from %2:").arg(QTime::currentTime().toString()).arg(str.section(";",1,1)));
            ui->privateMessagesTextEdit->append(QString("<font color=grey>%1</font>").arg(str.section(';',2)));
        break;
    case 142:
        receiveMessagesBetweenTwoUsers(str.section(';',1));
        break;
    case 146:
        addUsersInCombobox(str.section(';',1));
        break;
    case 147:
        if(ui->usersComboBox->currentIndex() != -1)
            ui->usersStateLabel->setText("<font color=green>User online</font>");
        break;
    case 148:
        if(ui->usersComboBox->currentIndex() != -1)
            ui->usersStateLabel->setText("<font color=red>User offline</font>");
        break;
    case 200:
        ui->allMessagesTextEdit->append(QString("<font color=red>%1 %2 left the Chat!</font>").arg(QTime::currentTime().toString()).arg(str.section(';',1)));
        currentItem = ui->usersOnlineListWidget->findItems(str.section(';',1), Qt::MatchExactly)[0];
        delete ui->usersOnlineListWidget->takeItem(ui->usersOnlineListWidget->row(currentItem));
        break;
    case 300:
        ui->allMessagesTextEdit->append(QString("<font color=red>%1 You are in BAN!</font>").arg(QTime::currentTime().toString()));
        banUser();
        break;
    case 301:
        ui->allMessagesTextEdit->append(QString("<font color=red>%1 User with login %2 sent to ban!</font>").arg(QTime::currentTime().toString()).arg(str.section(';',1)));
        break;
    case 302:
        ui->allMessagesTextEdit->append(QString("<font color=green>%1 You are UNBAN!</font>").arg(QTime::currentTime().toString()));
        enterUserInChat(str.section(';',1,1),str.section(';',2));
        break;
    case 303:
        ui->allMessagesTextEdit->append(QString("<font color=green>%1 User with login %2 Unban!</font>").arg(QTime::currentTime().toString()).arg(str.section(';',1)));
        break;
    case 500:
        receiveCommandMessageFromServer(str.section(';',1));
        break;
    default:
        break;
    }
}



