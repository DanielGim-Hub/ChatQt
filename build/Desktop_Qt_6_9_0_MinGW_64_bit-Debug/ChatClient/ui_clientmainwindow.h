/********************************************************************************
** Form generated from reading UI file 'clientmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTMAINWINDOW_H
#define UI_CLIENTMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientMainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_6;
    QLineEdit *ipLineEdit;
    QLabel *label;
    QLineEdit *portLineEdit;
    QPushButton *connectButton;
    QGroupBox *userMenuGroupBox;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *loginButton;
    QPushButton *registrationButton;
    QPushButton *exitUserButton;
    QLabel *currentUserLabel;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QTextEdit *allMessagesTextEdit;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *privateMessageFromRadioButton;
    QComboBox *privateUsersComboBox;
    QSpacerItem *horizontalSpacer_4;
    QTextEdit *chatWithTextEdit;
    QRadioButton *allPrivateMessagesRadioButton;
    QTextEdit *privateMessagesTextEdit;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QListWidget *usersOnlineListWidget;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout_8;
    QRadioButton *messageToAllRadioButton;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *privateMessageRadioButton;
    QComboBox *usersComboBox;
    QLabel *usersStateLabel;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *messageLabel;
    QLineEdit *messageLineEdit;
    QPushButton *sendButton;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *closeButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QMainWindow *ClientMainWindow)
    {
        if (ClientMainWindow->objectName().isEmpty())
            ClientMainWindow->setObjectName("ClientMainWindow");
        ClientMainWindow->resize(687, 752);
        ClientMainWindow->setMinimumSize(QSize(0, 0));
        ClientMainWindow->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        ClientMainWindow->setFont(font);
        ClientMainWindow->setAutoFillBackground(false);
        centralwidget = new QWidget(ClientMainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setFont(font);
        verticalLayout_5 = new QVBoxLayout(centralwidget);
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 10, -1, 10);
        horizontalSpacer = new QSpacerItem(270, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");

        horizontalLayout->addWidget(label_6);

        ipLineEdit = new QLineEdit(centralwidget);
        ipLineEdit->setObjectName("ipLineEdit");
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(false);
        ipLineEdit->setFont(font1);

        horizontalLayout->addWidget(ipLineEdit);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        portLineEdit = new QLineEdit(centralwidget);
        portLineEdit->setObjectName("portLineEdit");
        portLineEdit->setFont(font1);

        horizontalLayout->addWidget(portLineEdit);

        connectButton = new QPushButton(centralwidget);
        connectButton->setObjectName("connectButton");

        horizontalLayout->addWidget(connectButton);


        verticalLayout_5->addLayout(horizontalLayout);

        userMenuGroupBox = new QGroupBox(centralwidget);
        userMenuGroupBox->setObjectName("userMenuGroupBox");
        userMenuGroupBox->setEnabled(true);
        userMenuGroupBox->setAlignment(Qt::AlignCenter);
        userMenuGroupBox->setFlat(false);
        horizontalLayout_6 = new QHBoxLayout(userMenuGroupBox);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(-1, -1, -1, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(-1, -1, -1, 6);
        loginButton = new QPushButton(userMenuGroupBox);
        loginButton->setObjectName("loginButton");

        horizontalLayout_5->addWidget(loginButton);

        registrationButton = new QPushButton(userMenuGroupBox);
        registrationButton->setObjectName("registrationButton");

        horizontalLayout_5->addWidget(registrationButton);

        exitUserButton = new QPushButton(userMenuGroupBox);
        exitUserButton->setObjectName("exitUserButton");

        horizontalLayout_5->addWidget(exitUserButton);


        horizontalLayout_6->addLayout(horizontalLayout_5);


        verticalLayout_5->addWidget(userMenuGroupBox);

        currentUserLabel = new QLabel(centralwidget);
        currentUserLabel->setObjectName("currentUserLabel");
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        currentUserLabel->setFont(font2);
        currentUserLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(currentUserLabel);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName("verticalLayout");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        allMessagesTextEdit = new QTextEdit(centralwidget);
        allMessagesTextEdit->setObjectName("allMessagesTextEdit");
        allMessagesTextEdit->setMinimumSize(QSize(250, 0));
        QFont font3;
        font3.setPointSize(9);
        font3.setBold(true);
        allMessagesTextEdit->setFont(font3);
        allMessagesTextEdit->setReadOnly(true);

        verticalLayout->addWidget(allMessagesTextEdit);


        horizontalLayout_11->addLayout(verticalLayout);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        verticalLayout_4->addWidget(label_3);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setAlignment(Qt::AlignCenter);
        horizontalLayout_9 = new QHBoxLayout(groupBox_2);
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        privateMessageFromRadioButton = new QRadioButton(groupBox_2);
        privateMessageFromRadioButton->setObjectName("privateMessageFromRadioButton");
        privateMessageFromRadioButton->setFont(font1);

        horizontalLayout_2->addWidget(privateMessageFromRadioButton);

        privateUsersComboBox = new QComboBox(groupBox_2);
        privateUsersComboBox->setObjectName("privateUsersComboBox");
        privateUsersComboBox->setMaximumSize(QSize(120, 16777215));
        privateUsersComboBox->setFont(font1);

        horizontalLayout_2->addWidget(privateUsersComboBox);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        horizontalLayout_2->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_2);

        chatWithTextEdit = new QTextEdit(groupBox_2);
        chatWithTextEdit->setObjectName("chatWithTextEdit");
        chatWithTextEdit->setMinimumSize(QSize(250, 180));
        chatWithTextEdit->setFont(font3);
        chatWithTextEdit->setReadOnly(true);

        verticalLayout_2->addWidget(chatWithTextEdit);

        allPrivateMessagesRadioButton = new QRadioButton(groupBox_2);
        allPrivateMessagesRadioButton->setObjectName("allPrivateMessagesRadioButton");
        allPrivateMessagesRadioButton->setFont(font1);
        allPrivateMessagesRadioButton->setChecked(true);

        verticalLayout_2->addWidget(allPrivateMessagesRadioButton);

        privateMessagesTextEdit = new QTextEdit(groupBox_2);
        privateMessagesTextEdit->setObjectName("privateMessagesTextEdit");
        privateMessagesTextEdit->setMinimumSize(QSize(250, 180));
        privateMessagesTextEdit->setFont(font3);
        privateMessagesTextEdit->setReadOnly(true);

        verticalLayout_2->addWidget(privateMessagesTextEdit);

        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(3, 1);

        horizontalLayout_9->addLayout(verticalLayout_2);


        verticalLayout_4->addWidget(groupBox_2);


        horizontalLayout_11->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(10, -1, -1, -1);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        verticalLayout_3->addWidget(label_4);

        usersOnlineListWidget = new QListWidget(centralwidget);
        usersOnlineListWidget->setObjectName("usersOnlineListWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(usersOnlineListWidget->sizePolicy().hasHeightForWidth());
        usersOnlineListWidget->setSizePolicy(sizePolicy);
        usersOnlineListWidget->setMinimumSize(QSize(130, 0));
        usersOnlineListWidget->setMaximumSize(QSize(140, 16777215));
        usersOnlineListWidget->setFont(font);

        verticalLayout_3->addWidget(usersOnlineListWidget);


        horizontalLayout_11->addLayout(verticalLayout_3);


        verticalLayout_5->addLayout(horizontalLayout_11);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setAlignment(Qt::AlignCenter);
        horizontalLayout_10 = new QHBoxLayout(groupBox);
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(20);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        messageToAllRadioButton = new QRadioButton(groupBox);
        messageToAllRadioButton->setObjectName("messageToAllRadioButton");
        messageToAllRadioButton->setChecked(true);

        horizontalLayout_8->addWidget(messageToAllRadioButton);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        privateMessageRadioButton = new QRadioButton(groupBox);
        privateMessageRadioButton->setObjectName("privateMessageRadioButton");

        horizontalLayout_3->addWidget(privateMessageRadioButton);

        usersComboBox = new QComboBox(groupBox);
        usersComboBox->setObjectName("usersComboBox");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(usersComboBox->sizePolicy().hasHeightForWidth());
        usersComboBox->setSizePolicy(sizePolicy1);
        usersComboBox->setMinimumSize(QSize(110, 0));
        usersComboBox->setMaximumSize(QSize(120, 16777215));
        QFont font4;
        font4.setPointSize(9);
        font4.setBold(false);
        usersComboBox->setFont(font4);
        usersComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_3->addWidget(usersComboBox);

        horizontalLayout_3->setStretch(1, 1);

        horizontalLayout_8->addLayout(horizontalLayout_3);

        usersStateLabel = new QLabel(groupBox);
        usersStateLabel->setObjectName("usersStateLabel");
        QFont font5;
        font5.setPointSize(8);
        font5.setBold(false);
        usersStateLabel->setFont(font5);

        horizontalLayout_8->addWidget(usersStateLabel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);

        horizontalLayout_8->setStretch(3, 1);

        horizontalLayout_10->addLayout(horizontalLayout_8);


        verticalLayout_5->addWidget(groupBox);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(-1, 0, -1, 4);
        messageLabel = new QLabel(centralwidget);
        messageLabel->setObjectName("messageLabel");
        messageLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        messageLabel->setMargin(0);
        messageLabel->setIndent(10);

        horizontalLayout_7->addWidget(messageLabel);

        messageLineEdit = new QLineEdit(centralwidget);
        messageLineEdit->setObjectName("messageLineEdit");
        messageLineEdit->setFont(font1);

        horizontalLayout_7->addWidget(messageLineEdit);

        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName("sendButton");

        horizontalLayout_7->addWidget(sendButton);


        verticalLayout_5->addLayout(horizontalLayout_7);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, 10, -1, -1);
        closeButton = new QPushButton(centralwidget);
        closeButton->setObjectName("closeButton");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(closeButton->sizePolicy().hasHeightForWidth());
        closeButton->setSizePolicy(sizePolicy2);
        closeButton->setMaximumSize(QSize(120, 16777215));
        closeButton->setFont(font2);

        horizontalLayout_4->addWidget(closeButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_4);

        ClientMainWindow->setCentralWidget(centralwidget);

        retranslateUi(ClientMainWindow);

        QMetaObject::connectSlotsByName(ClientMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ClientMainWindow)
    {
        ClientMainWindow->setWindowTitle(QCoreApplication::translate("ClientMainWindow", "ClientMainWindow", nullptr));
        label_6->setText(QCoreApplication::translate("ClientMainWindow", "IP address:", nullptr));
        label->setText(QCoreApplication::translate("ClientMainWindow", "Port:", nullptr));
        connectButton->setText(QCoreApplication::translate("ClientMainWindow", "Connect", nullptr));
        userMenuGroupBox->setTitle(QCoreApplication::translate("ClientMainWindow", "User menu", nullptr));
        loginButton->setText(QCoreApplication::translate("ClientMainWindow", "Login", nullptr));
        registrationButton->setText(QCoreApplication::translate("ClientMainWindow", "Registration", nullptr));
        exitUserButton->setText(QCoreApplication::translate("ClientMainWindow", "Exit", nullptr));
        currentUserLabel->setText(QCoreApplication::translate("ClientMainWindow", "Current user: ", nullptr));
        label_2->setText(QCoreApplication::translate("ClientMainWindow", "All Messages in Chat", nullptr));
        label_3->setText(QCoreApplication::translate("ClientMainWindow", "Private messages for current user", nullptr));
        groupBox_2->setTitle(QString());
        privateMessageFromRadioButton->setText(QCoreApplication::translate("ClientMainWindow", "Chat with", nullptr));
        allPrivateMessagesRadioButton->setText(QCoreApplication::translate("ClientMainWindow", "New private messages (in real time)", nullptr));
        label_4->setText(QCoreApplication::translate("ClientMainWindow", "Users online", nullptr));
        groupBox->setTitle(QString());
        messageToAllRadioButton->setText(QCoreApplication::translate("ClientMainWindow", "Message to all", nullptr));
        privateMessageRadioButton->setText(QCoreApplication::translate("ClientMainWindow", "Private message", nullptr));
        usersStateLabel->setText(QString());
        messageLabel->setText(QCoreApplication::translate("ClientMainWindow", "Enter message:", nullptr));
        sendButton->setText(QCoreApplication::translate("ClientMainWindow", "Send", nullptr));
        closeButton->setText(QCoreApplication::translate("ClientMainWindow", "Close Client", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientMainWindow: public Ui_ClientMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTMAINWINDOW_H
