#pragma once
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

#include "../macrologger.h"

class AgreeDialog : public QDialog {
    Q_OBJECT

    public:
        AgreeDialog(QString message, QWidget *parent = nullptr);
        virtual ~AgreeDialog();
    
    private:
        QLabel msgLabel;
        QPushButton agreeButton;
        QPushButton cancelButton;

};
