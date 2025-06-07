#include "registrationwidget.h"
#include "ui_registrationwidget.h"
#include <QMessageBox>
//#include <QRegExp>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

RegistrationWidget::RegistrationWidget(QTcpSocket* socket, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationWidget),
    _socket(socket)
{
    ui->setupUi(this);

    // Настройка валидаторов для полей ввода:
    QRegularExpression regexp("[a-zA-Z]+"); // Только буквы для имени
    ui->nameEdit->setValidator(new QRegularExpressionValidator(regexp, this));

    QRegularExpression regExp("\\w{1,10}"); // Буквы, цифры, подчеркивание (1-10 символов)
    ui->loginEdit->setValidator(new QRegularExpressionValidator(regExp, this));
    ui->passwordEdit->setValidator(new QRegularExpressionValidator(regExp, this));

    // Соединение кнопки Cancel с закрытием виджета
    connect(ui->cancelButton, &QPushButton::clicked, this, &RegistrationWidget::closeWidget);
}

RegistrationWidget::~RegistrationWidget()
{
    delete ui;
}

// Обработка результата регистрации
void RegistrationWidget::registrationResult(int command)
{
    switch (command) {
    case 111: // Ошибка добавления в БД
        ui->registrationResultLabel->setText("<font color=red>User with login " + _userLogin +
                                             " not added in database! Registration failed</font>");
        break;

    case 112: // Успешная регистрация
        ui->registrationResultLabel->setText("<font color=green>User with login " + _userLogin +
                                             " add in database! Registration success</font>");
        // Показ сообщения об успехе
        QMessageBox(QMessageBox::Information,
                    QObject::tr("Registration"),
                    QObject::tr("Registration of a new user was successful!"),
                    QMessageBox::Ok).exec();
        this->close();      // Закрытие окна
        break;

    case 113: // Пользователь уже существует
        ui->registrationResultLabel->setText("<font color=red>User with login " + _userLogin +
                                             " is already exists! Try again</font>");
        break;

    default: // Неизвестный код
        break;
    }
}

// Закрытие виджета
void RegistrationWidget::closeWidget()
{
    this->close();          // Вызов стандартного закрытия
}

// Обработка нажатия OK
void RegistrationWidget::on_okButton_clicked()
{
    QString message;        // Сообщение для сервера

    // Проверка заполненности всех полей
    if(!ui->nameEdit->text().isEmpty() &&
        !ui->loginEdit->text().isEmpty() &&
        !ui->passwordEdit->text().isEmpty() &&
        !ui->confirmPasswordEdit->text().isEmpty())
    {
        // Проверка совпадения паролей
        if(ui->passwordEdit->text() == ui->confirmPasswordEdit->text())
        {
            // Сохранение данных
            _userName = ui->nameEdit->text();
            _userLogin = ui->loginEdit->text();
            _userPassword = ui->passwordEdit->text();

            // Формирование сообщения (110 - код регистрации)
            message = "110;" + _userName + ";" + _userLogin + ";" + _userPassword;
            _socket->write(message.toUtf8()); // Отправка
        }
        else
        {
            // Ошибка: пароли не совпадают
            ui->registrationResultLabel->setText(tr("<font color=red>Passwords don't match. Try again.</font>"));
        }
    }
    else
    {
        // Ошибка: не все поля заполнены
        ui->registrationResultLabel->setText(tr("<font color=red>All fields must be filled in</font>"));
    }
}

