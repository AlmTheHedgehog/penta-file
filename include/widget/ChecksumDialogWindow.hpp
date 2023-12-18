#pragma once
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFontMetrics>

#include "PopupWindowB.hpp"
#include "../rosourcesPaths.hpp"
#include "../macrologger.h"

class ChecksumDialogWindow : public PopupWindowB {
    Q_OBJECT

    public:
        ChecksumDialogWindow(QString fileName, QString checksum, QWidget *parent = nullptr);
        virtual ~ChecksumDialogWindow();

    private slots:
        void verifyChecksum(bool);

    private:
        QString fileName;
        QString checksum;
        QLabel nameLable;
        QLineEdit checksumLine;
        QLabel compareToLable;
        QLineEdit lineInput;
        QPushButton verifyButton;
};
