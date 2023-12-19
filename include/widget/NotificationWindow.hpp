#pragma once
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include "PopupWindowB.hpp"
#include "../rosourcesPaths.hpp"
#include "../macrologger.h"

class NotificationWindow : public PopupWindowB {
    Q_OBJECT

    public:
        enum NotificationType{ERROR, INFORMATION};

        NotificationWindow(QString msg, NotificationType notificationType, QWidget *parent = nullptr);
        virtual ~NotificationWindow();

    private:
        NotificationType notificationType;
        QLabel msgLabel;
        QPushButton okButton;

        void styleComponents();
    
    public slots:
        void closeWindow();
};
