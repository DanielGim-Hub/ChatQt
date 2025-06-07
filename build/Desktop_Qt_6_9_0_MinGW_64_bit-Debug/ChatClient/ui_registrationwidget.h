/********************************************************************************
** Form generated from reading UI file 'registrationwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATIONWIDGET_H
#define UI_REGISTRATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegistrationWidget
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *nameEdit;
    QLabel *label_2;
    QLineEdit *loginEdit;
    QLabel *label_3;
    QLineEdit *passwordEdit;
    QLabel *label_4;
    QLineEdit *confirmPasswordEdit;
    QLabel *registrationResultLabel;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QWidget *RegistrationWidget)
    {
        if (RegistrationWidget->objectName().isEmpty())
            RegistrationWidget->setObjectName("RegistrationWidget");
        RegistrationWidget->resize(397, 201);
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        RegistrationWidget->setFont(font);
        RegistrationWidget->setToolTipDuration(-1);
        verticalLayout = new QVBoxLayout(RegistrationWidget);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(RegistrationWidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        nameEdit = new QLineEdit(RegistrationWidget);
        nameEdit->setObjectName("nameEdit");
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(false);
        nameEdit->setFont(font1);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, nameEdit);

        label_2 = new QLabel(RegistrationWidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        loginEdit = new QLineEdit(RegistrationWidget);
        loginEdit->setObjectName("loginEdit");
        loginEdit->setFont(font1);
        loginEdit->setToolTipDuration(-1);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, loginEdit);

        label_3 = new QLabel(RegistrationWidget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        passwordEdit = new QLineEdit(RegistrationWidget);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setFont(font1);
        passwordEdit->setToolTipDuration(-1);
        passwordEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, passwordEdit);

        label_4 = new QLabel(RegistrationWidget);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_4);

        confirmPasswordEdit = new QLineEdit(RegistrationWidget);
        confirmPasswordEdit->setObjectName("confirmPasswordEdit");
        confirmPasswordEdit->setFont(font1);
        confirmPasswordEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, confirmPasswordEdit);


        verticalLayout->addLayout(formLayout);

        registrationResultLabel = new QLabel(RegistrationWidget);
        registrationResultLabel->setObjectName("registrationResultLabel");
        registrationResultLabel->setFont(font1);
        registrationResultLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(registrationResultLabel);

        verticalSpacer = new QSpacerItem(20, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        okButton = new QPushButton(RegistrationWidget);
        okButton->setObjectName("okButton");

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(RegistrationWidget);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(RegistrationWidget);

        QMetaObject::connectSlotsByName(RegistrationWidget);
    } // setupUi

    void retranslateUi(QWidget *RegistrationWidget)
    {
        RegistrationWidget->setWindowTitle(QCoreApplication::translate("RegistrationWidget", "Registration Form", nullptr));
        label->setText(QCoreApplication::translate("RegistrationWidget", "Name *", nullptr));
#if QT_CONFIG(tooltip)
        nameEdit->setToolTip(QCoreApplication::translate("RegistrationWidget", "<html><head/><body><p align=\"center\"><span style=\" color:#aa007f;\">Characters [a-z,A-Z] </span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("RegistrationWidget", "Login *", nullptr));
#if QT_CONFIG(tooltip)
        loginEdit->setToolTip(QCoreApplication::translate("RegistrationWidget", "<html><head/><body><p align=\"center\"><span style=\" color:#aa007f;\">From 6 to 10 characters [a-z,A-Z,0-9,_] </span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_3->setText(QCoreApplication::translate("RegistrationWidget", "Password *", nullptr));
#if QT_CONFIG(tooltip)
        passwordEdit->setToolTip(QCoreApplication::translate("RegistrationWidget", "<html><head/><body><p align=\"center\"><span style=\" color:#aa007f;\">From 6 to 10 characters [a-z,A-Z,0-9,_] </span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_4->setText(QCoreApplication::translate("RegistrationWidget", "Confirm password *", nullptr));
        confirmPasswordEdit->setText(QString());
        registrationResultLabel->setText(QString());
        okButton->setText(QCoreApplication::translate("RegistrationWidget", "Ok", nullptr));
        cancelButton->setText(QCoreApplication::translate("RegistrationWidget", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegistrationWidget: public Ui_RegistrationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATIONWIDGET_H
