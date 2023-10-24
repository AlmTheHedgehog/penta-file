#pragma once
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QString>
#include <QPixmap>
#include <QtGlobal>

#include "../rosourcesPaths.hpp"
#include "../macrologger.h"

class LineEntryWidget : public QWidget {
    Q_OBJECT

    public:
        enum LineType{
            DIRECTORY,
            FILE
        };

        LineEntryWidget(LineType lineType, QString name, qint64 size, QWidget *parent = nullptr);
        virtual ~LineEntryWidget();
        void setIcon(LineType lineType);

    private:
        QLabel  *iconLabel, 
                *nameLabel, 
                *sizeLabel;
        LineType lineType;
        QString name;
        qint64 size;

};

