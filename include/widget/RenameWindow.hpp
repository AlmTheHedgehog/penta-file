#pragma once
#include <QLabel>
#include <QDir>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include "NotificationWindow.hpp"
#include "PopupWindowB.hpp"
#include "../rosourcesPaths.hpp"
#include "../macrologger.h"

class RenameWindow : public PopupWindowB {
    Q_OBJECT

    public:
        RenameWindow(QString path, QWidget *parent = nullptr);
        virtual ~RenameWindow();

    private slots:
        void rename();
        void closeWindow();
       

    private:
        QString path;
        QLineEdit* nameEdit;
        QPushButton okButton;
        QPushButton cancelButton;

    signals:
        void renameSignal(QString path, QString newName);
        void renameDone();

};