#pragma once
#include <QLabel>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>
#include <QPushButton>

#include "../rosourcesPaths.hpp"
#include "../macrologger.h"

class PropertiesWindow : public QWidget {
    Q_OBJECT

    public:
        PropertiesWindow(QString objectPath, QWidget *parent = nullptr);
        virtual ~PropertiesWindow();

    private slots:
        void fileProperties();
        void directoryProperties();

    private:
        QString objectPath;
        QFileInfo* object;
        QLabel nameLable;
        QLabel sizeLable;
        QLabel typeLable;
        QLabel pathLable;
        QLabel birthDateLable;
        QLabel lastModifiedLable;
        QLabel ownerLable;
        QLabel permissionsLable;

    signals:
        
};
