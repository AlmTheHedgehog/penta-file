#pragma once
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QMouseEvent>

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
        QString getFilePath();
        LineType getLineType();
        QString getLineName();

    public slots:
        void setSelection(bool selected);
     

    private:
        void mouseDoubleClickEvent(QMouseEvent*) override;
        void mousePressEvent(QMouseEvent* event) override;
        QLabel  *iconLabel, 
                *nameLabel, 
                *sizeLabel;
        LineType lineType;
        QString  name;
        qint64   size;
        QString  path;

    signals:
        void setNewPath(QString newPath);
        void setFilePath(QString filePath);

};

