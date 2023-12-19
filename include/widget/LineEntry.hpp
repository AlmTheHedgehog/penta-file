#pragma once
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <openssl/sha.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <QMouseEvent>

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
        QString getFilePath();
        LineType getLineType();
        QString getLineName();
        QString getChecksum();
        void showChecksum();

    public slots:
        void setSelection(bool selected);
     

    private:
        QLabel  *iconLabel, 
                *nameLabel, 
                *sizeLabel,
                *checksumLabel;
        LineType lineType;
        QString  name;
        qint64   size;
        QString  path;
        QString  checksum;
        bool isChecksumCalculated = false;
        void mouseDoubleClickEvent(QMouseEvent*) override;
        void mousePressEvent(QMouseEvent* event) override;
        void calculateChecksum();

    signals:
        void setNewPath(QString newPath);
        void setFilePath(QString filePath);

};

