#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QMessageBox>

LoginWidget::LoginWidget(QTcpSocket* socket, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget),
    _socket(socket)
{
    ui->setupUi(this);

    connect(ui->cancelButton, &QPushButton::clicked, this, &LoginWidget::closeWidget);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

// Метод обработки результата авторизации
void LoginWidget::loginResult(int command)
{
    switch (command) {      // Анализ кода команды от сервера
    case 121:               // Успешная авторизация
        // Установка зеленого текста в лейбле результата
        ui->loginResultLabel->setText(tr("<font color=green>Authentication was successful</font>"));

        // Создание и отображение диалогового окна с сообщением об успехе
        QMessageBox(QMessageBox::Information,
                    QObject::tr("Authentication"),
                    QObject::tr("Authentication user was successful!"),
                    QMessageBox::Ok).exec();

        closeWidget();      // Закрытие окна авторизации
        break;
    case 122:               // Ошибка авторизации
        // Установка красного текста с сообщением об ошибке
        ui->loginResultLabel->setText(tr("<font color=red>Authentication failed. Try again!</font>"));
        break;
    case 123:               // Пользователь уже онлайн
        // Установка красного текста с соответствующим сообщением
        ui->loginResultLabel->setText(tr("<font color=red>You are already online</font>"));
        break;
    default:                // Обработка неизвестных кодов
        break;              // Ничего не делаем
    }
}

// Метод закрытия виджета
void LoginWidget::closeWidget()
{
    this->close();          // Вызов метода закрытия окна
}

// Обработчик нажатия кнопки OK
void LoginWidget::on_okButton_clicked()
{
    QString message;        // Строка для формирования сообщения

    // Проверка, что оба поля заполнены
    if(!ui->loginEdit->text().isEmpty() && !ui->passwordEdit->text().isEmpty()) {
        // Формирование сообщения в формате "код команды;логин;пароль"
        message = "120;" + ui->loginEdit->text() + ";" + ui->passwordEdit->text();

        // Отправка сообщения через сокет (преобразование в UTF-8)
        _socket->write(message.toUtf8());
    }
    else {
        // Если поля не заполнены - показываем сообщение об ошибке красным цветом
        ui->loginResultLabel->setText(tr("<font color=red>All fields must be filled in</font>"));
    }
}

