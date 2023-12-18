#pragma once
#include <QLabel>
#include <QDir>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>
#include <QPushButton>
#include <QLineEdit>

#include "../rosourcesPaths.hpp"
#include "../macrologger.h"

class PropertiesWindow : public QWidget {
    Q_OBJECT

    public:
        PropertiesWindow(QString objectPath, QWidget *parent = nullptr);
        virtual ~PropertiesWindow();

    private slots:
        void createProperties();
        void createPermissionsWidget();
        void createInfoWidget();

    private:
        QString objectPath;
        QFileInfo* object;
        QLineEdit* nameEdit;
        QWidget* permissionsWidget;
        QLayout* permissionsLayout;
        QWidget* infoWidget;
        QLayout* infoLayout;
        QLabel nameLabel;
        QLabel sizeLabel;
        QLabel typeLabel;
        QLabel pathLabel;
        QLabel birthDateLabel;
        QLabel lastModifiedLabel;
        QLabel ownerLabel;
        QLabel permissionsLabel;

        qint64 dirSize(QString path);
        QString formatSize(qint64 size);

    signals:
  
};
