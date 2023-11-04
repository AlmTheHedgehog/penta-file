#pragma once
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

#include "../rosourcesPaths.hpp"
#include "../macrologger.h"

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
        void mouseDoubleClickEvent(QMouseEvent*) override;
        QLabel  *iconLabel, 
                *nameLabel, 
                *sizeLabel;
        LineType lineType;
        QString  name;
        qint64   size;
        QString  path;

    signals:
        void setNewPath(QString newPath);

};

