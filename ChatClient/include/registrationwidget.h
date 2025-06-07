#ifndef REGISTRATIONWIDGET_H
#define REGISTRATIONWIDGET_H
#include <QWidget>
#include <memory>
#include <QTcpSocket>

namespace Ui {
class RegistrationWidget;
}

class RegistrationWidget : public QWidget // Класс виджета регистрации
{
    Q_OBJECT                // Макрос для системы сигналов/слотов Qt

public:
    explicit RegistrationWidget(QTcpSocket* socket, QWidget *parent = nullptr); // Конструктор
    ~RegistrationWidget();  // Деструктор

    // Геттеры для данных пользователя
    QString getName() const {return _userName;}     // Получить имя
    QString getLogin() const {return _userLogin;}   // Получить логин
    QString getPassword() const {return _userPassword;} // Получить пароль

    void registrationResult(int command); // Обработка результата регистрации

signals:                    // Секция сигналов (пока пустая)

private slots:              // Слоты для обработки событий
    void closeWidget();     // Закрытие виджета
    void on_okButton_clicked(); // Обработка нажатия OK

private:
    Ui::RegistrationWidget *ui; // Указатель на UI
    QTcpSocket* _socket;    // TCP-сокет для связи с сервером
    QString _userName;      // Имя пользователя
    QString _userLogin;     // Логин пользователя
    QString _userPassword;  // Пароль пользователя
};

#endif // REGISTRATIONWIDGET_H
