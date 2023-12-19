#include "widget/NotificationWindow.hpp"

NotificationWindow::NotificationWindow(QString msg, NotificationType notificationType, QWidget *parent):
                                        PopupWindowB(parent), notificationType(notificationType){
    setLayout(new QVBoxLayout(this));
    msgLabel.setText(msg);
    okButton.setText("OK");
    layout()->addWidget(&msgLabel);
    layout()->addWidget(&okButton);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    styleComponents();
    connect(&okButton, &QPushButton::clicked, this, &NotificationWindow::closeWindow);
    LOG_INFO("Message window openned. Text: \"%s\"", msg.toLatin1().data());
}

NotificationWindow::~NotificationWindow(){
}

void NotificationWindow::styleComponents(){
    switch(notificationType){
        case NotificationType::ERROR:
            setWindowTitle("Error");
            msgLabel.setStyleSheet("QLabel { color : red; }");
            break;
        case NotificationType::INFORMATION:
            setWindowTitle("Info");
            break;
    }
}

void NotificationWindow::closeWindow(){
    destroy();
    deleteLater();
}