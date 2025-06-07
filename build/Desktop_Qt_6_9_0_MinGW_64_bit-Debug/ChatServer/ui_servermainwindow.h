/********************************************************************************
** Form generated from reading UI file 'servermainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERMAINWINDOW_H
#define UI_SERVERMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
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

class Ui_ServerMainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QLineEdit *portLineEdit;
    QPushButton *connectButton;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLineEdit *clientCountLineEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *authUsersLineEdit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QLineEdit *allUsersLineEdit;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QTextEdit *allMessagesTextEdit;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_2;
    QFormLayout *formLayout;
    QLabel *label_8;
    QComboBox *user1ComboBox;
    QLabel *label_9;
    QComboBox *user2ComboBox;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer;
    QPushButton *showChatPushButton;
    QSpacerItem *horizontalSpacer_4;
    QTextEdit *privateMessagesTextEdit;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QTextEdit *informationFromClientTextEdit;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *allUsersRadioButton;
    QRadioButton *usersOnlineRadioButton;
    QRadioButton *inBanRadioButton;
    QListWidget *usersListWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *banUserPushButton;
    QPushButton *disconnectUserPushButton;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *closeButton;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QMainWindow *ServerMainWindow)
    {
        if (ServerMainWindow->objectName().isEmpty())
            ServerMainWindow->setObjectName("ServerMainWindow");
        ServerMainWindow->resize(729, 729);
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        ServerMainWindow->setFont(font);
        ServerMainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(ServerMainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_8 = new QVBoxLayout(centralwidget);
        verticalLayout_8->setObjectName("verticalLayout_8");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 10, -1, 10);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        portLineEdit = new QLineEdit(centralwidget);
        portLineEdit->setObjectName("portLineEdit");
        portLineEdit->setMinimumSize(QSize(140, 0));
        portLineEdit->setMaximumSize(QSize(170, 16777215));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(false);
        portLineEdit->setFont(font1);

        horizontalLayout->addWidget(portLineEdit);

        connectButton = new QPushButton(centralwidget);
        connectButton->setObjectName("connectButton");

        horizontalLayout->addWidget(connectButton);


        verticalLayout_8->addLayout(horizontalLayout);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(23);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(-1, 5, -1, 6);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(5);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setMargin(3);
        label_6->setIndent(0);

        horizontalLayout_3->addWidget(label_6);

        clientCountLineEdit = new QLineEdit(centralwidget);
        clientCountLineEdit->setObjectName("clientCountLineEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(clientCountLineEdit->sizePolicy().hasHeightForWidth());
        clientCountLineEdit->setSizePolicy(sizePolicy1);
        clientCountLineEdit->setMinimumSize(QSize(40, 0));
        clientCountLineEdit->setMaximumSize(QSize(50, 25));
        clientCountLineEdit->setBaseSize(QSize(0, 0));
        clientCountLineEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        clientCountLineEdit->setReadOnly(true);

        horizontalLayout_3->addWidget(clientCountLineEdit);


        horizontalLayout_8->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(5);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        horizontalLayout_6->addWidget(label_5);

        authUsersLineEdit = new QLineEdit(centralwidget);
        authUsersLineEdit->setObjectName("authUsersLineEdit");
        authUsersLineEdit->setMinimumSize(QSize(40, 0));
        authUsersLineEdit->setMaximumSize(QSize(50, 16777215));
        authUsersLineEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        authUsersLineEdit->setReadOnly(true);

        horizontalLayout_6->addWidget(authUsersLineEdit);


        horizontalLayout_8->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(5);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");

        horizontalLayout_7->addWidget(label_7);

        allUsersLineEdit = new QLineEdit(centralwidget);
        allUsersLineEdit->setObjectName("allUsersLineEdit");
        allUsersLineEdit->setMinimumSize(QSize(40, 0));
        allUsersLineEdit->setMaximumSize(QSize(50, 16777215));
        allUsersLineEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        allUsersLineEdit->setReadOnly(true);

        horizontalLayout_7->addWidget(allUsersLineEdit);


        horizontalLayout_8->addLayout(horizontalLayout_7);

        horizontalSpacer = new QSpacerItem(160, 20, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);

        horizontalLayout_8->setStretch(3, 1);

        verticalLayout_8->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName("verticalLayout");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        allMessagesTextEdit = new QTextEdit(centralwidget);
        allMessagesTextEdit->setObjectName("allMessagesTextEdit");
        allMessagesTextEdit->setMinimumSize(QSize(250, 0));
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(true);
        allMessagesTextEdit->setFont(font2);
        allMessagesTextEdit->setReadOnly(true);

        verticalLayout->addWidget(allMessagesTextEdit);


        horizontalLayout_5->addLayout(verticalLayout);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        verticalLayout_5->addWidget(label_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        formLayout->setFieldGrowthPolicy(QFormLayout::FieldGrowthPolicy::AllNonFixedFieldsGrow);
        formLayout->setRowWrapPolicy(QFormLayout::RowWrapPolicy::DontWrapRows);
        formLayout->setHorizontalSpacing(7);
        formLayout->setVerticalSpacing(5);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setFont(font1);

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_8);

        user1ComboBox = new QComboBox(centralwidget);
        user1ComboBox->setObjectName("user1ComboBox");
        user1ComboBox->setMinimumSize(QSize(100, 0));
        user1ComboBox->setMaximumSize(QSize(120, 16777215));
        user1ComboBox->setFont(font1);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, user1ComboBox);

        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setFont(font1);

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_9);

        user2ComboBox = new QComboBox(centralwidget);
        user2ComboBox->setObjectName("user2ComboBox");
        user2ComboBox->setMinimumSize(QSize(100, 0));
        user2ComboBox->setMaximumSize(QSize(120, 16777215));
        user2ComboBox->setFont(font1);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, user2ComboBox);


        horizontalLayout_2->addLayout(formLayout);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalSpacer = new QSpacerItem(20, 19, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);

        verticalLayout_4->addItem(verticalSpacer);

        showChatPushButton = new QPushButton(centralwidget);
        showChatPushButton->setObjectName("showChatPushButton");
        showChatPushButton->setMinimumSize(QSize(100, 0));
        showChatPushButton->setMaximumSize(QSize(120, 16777215));

        verticalLayout_4->addWidget(showChatPushButton);


        horizontalLayout_2->addLayout(verticalLayout_4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_5->addLayout(horizontalLayout_2);

        privateMessagesTextEdit = new QTextEdit(centralwidget);
        privateMessagesTextEdit->setObjectName("privateMessagesTextEdit");
        privateMessagesTextEdit->setMinimumSize(QSize(250, 0));
        privateMessagesTextEdit->setFont(font2);
        privateMessagesTextEdit->setReadOnly(true);

        verticalLayout_5->addWidget(privateMessagesTextEdit);

        verticalLayout_5->setStretch(2, 1);

        horizontalLayout_5->addLayout(verticalLayout_5);


        verticalLayout_7->addLayout(horizontalLayout_5);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        verticalLayout_3->addWidget(label_4);

        informationFromClientTextEdit = new QTextEdit(centralwidget);
        informationFromClientTextEdit->setObjectName("informationFromClientTextEdit");
        informationFromClientTextEdit->setMinimumSize(QSize(250, 0));
        informationFromClientTextEdit->setMaximumSize(QSize(16777215, 300));
        QFont font3;
        font3.setPointSize(8);
        font3.setBold(false);
        informationFromClientTextEdit->setFont(font3);
        informationFromClientTextEdit->setReadOnly(true);

        verticalLayout_3->addWidget(informationFromClientTextEdit);


        verticalLayout_7->addLayout(verticalLayout_3);

        verticalLayout_7->setStretch(0, 1);

        horizontalLayout_9->addLayout(verticalLayout_7);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(-1, 0, -1, -1);
        allUsersRadioButton = new QRadioButton(centralwidget);
        allUsersRadioButton->setObjectName("allUsersRadioButton");
        allUsersRadioButton->setChecked(true);

        verticalLayout_6->addWidget(allUsersRadioButton);

        usersOnlineRadioButton = new QRadioButton(centralwidget);
        usersOnlineRadioButton->setObjectName("usersOnlineRadioButton");

        verticalLayout_6->addWidget(usersOnlineRadioButton);

        inBanRadioButton = new QRadioButton(centralwidget);
        inBanRadioButton->setObjectName("inBanRadioButton");

        verticalLayout_6->addWidget(inBanRadioButton);

        usersListWidget = new QListWidget(centralwidget);
        usersListWidget->setObjectName("usersListWidget");
        usersListWidget->setMinimumSize(QSize(140, 0));
        usersListWidget->setMaximumSize(QSize(160, 16777215));
        usersListWidget->setFont(font);

        verticalLayout_6->addWidget(usersListWidget);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, 4, -1, -1);
        banUserPushButton = new QPushButton(centralwidget);
        banUserPushButton->setObjectName("banUserPushButton");
        banUserPushButton->setMinimumSize(QSize(0, 30));

        verticalLayout_2->addWidget(banUserPushButton);

        disconnectUserPushButton = new QPushButton(centralwidget);
        disconnectUserPushButton->setObjectName("disconnectUserPushButton");
        disconnectUserPushButton->setMinimumSize(QSize(0, 30));

        verticalLayout_2->addWidget(disconnectUserPushButton);


        verticalLayout_6->addLayout(verticalLayout_2);


        horizontalLayout_9->addLayout(verticalLayout_6);

        horizontalLayout_9->setStretch(0, 1);

        verticalLayout_8->addLayout(horizontalLayout_9);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        closeButton = new QPushButton(centralwidget);
        closeButton->setObjectName("closeButton");
        closeButton->setMinimumSize(QSize(130, 30));
        QFont font4;
        font4.setPointSize(11);
        font4.setBold(true);
        closeButton->setFont(font4);

        horizontalLayout_4->addWidget(closeButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_8->addLayout(horizontalLayout_4);

        ServerMainWindow->setCentralWidget(centralwidget);

        retranslateUi(ServerMainWindow);

        QMetaObject::connectSlotsByName(ServerMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ServerMainWindow)
    {
        ServerMainWindow->setWindowTitle(QCoreApplication::translate("ServerMainWindow", "ServerMainWindow", nullptr));
        label->setText(QCoreApplication::translate("ServerMainWindow", "Port:", nullptr));
        connectButton->setText(QCoreApplication::translate("ServerMainWindow", "Connect", nullptr));
        label_6->setText(QCoreApplication::translate("ServerMainWindow", "Connected clients count:", nullptr));
        label_5->setText(QCoreApplication::translate("ServerMainWindow", "Authorized users", nullptr));
        label_7->setText(QCoreApplication::translate("ServerMainWindow", "All users", nullptr));
        label_2->setText(QCoreApplication::translate("ServerMainWindow", "All Messages in Chat", nullptr));
        label_3->setText(QCoreApplication::translate("ServerMainWindow", "Private messages between", nullptr));
        label_8->setText(QCoreApplication::translate("ServerMainWindow", "First user", nullptr));
        label_9->setText(QCoreApplication::translate("ServerMainWindow", "Second user", nullptr));
        showChatPushButton->setText(QCoreApplication::translate("ServerMainWindow", "Show", nullptr));
        label_4->setText(QCoreApplication::translate("ServerMainWindow", "Informaition console", nullptr));
        allUsersRadioButton->setText(QCoreApplication::translate("ServerMainWindow", "All users", nullptr));
        usersOnlineRadioButton->setText(QCoreApplication::translate("ServerMainWindow", "Users online", nullptr));
        inBanRadioButton->setText(QCoreApplication::translate("ServerMainWindow", "Users in ban", nullptr));
        banUserPushButton->setText(QCoreApplication::translate("ServerMainWindow", "Ban user", nullptr));
        disconnectUserPushButton->setText(QCoreApplication::translate("ServerMainWindow", "Disconnect user", nullptr));
        closeButton->setText(QCoreApplication::translate("ServerMainWindow", "Close Server", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServerMainWindow: public Ui_ServerMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERMAINWINDOW_H
