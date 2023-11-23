#pragma once
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <openssl/sha.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "../rosourcesPaths.hpp"
#include "../macrologger.h"


#define FILE_READ_CHUNK (0x1000)

class LineEntry : public QPushButton {
    Q_OBJECT

    public:
        enum LineType{
            DIRECTORY,
            FILE
        };

        LineEntry(LineType lineType, QString name, QString path, qint64 size = 0, QWidget *parent = nullptr);
        virtual ~LineEntry();
        void setIcon(LineType lineType);

    private:
        QLabel  *iconLabel, 
                *nameLabel, 
                *sizeLabel;
        LineType lineType;
        QString  name;
        qint64   size;
        QString  path;
        QString  checksum;
        void mouseDoubleClickEvent(QMouseEvent*) override;

    public slots:
        void calculateChecksum();


    signals:
        void setNewPath(QString newPath);

};

