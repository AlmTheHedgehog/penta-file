#pragma once
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QString>
#include <QPixmap>
#include <QtGlobal>
#include <QMenu>
#include <QMenuBar>
#include <QMainWindow>
#include <QAction>
#include <QLineEdit>
#include <QPushButton>
#include <QDir>

#include "../rosourcesPaths.hpp"
#include "../macrologger.h"

class MainFolderWidget : public QWidget{
    Q_OBJECT

    public:
        MainFolderWidget(QWidget *parent = nullptr);
        virtual ~MainFolderWidget();

    signals:
        void folderButtonClicked(const QString &path);

    private slots:
        void handleFolderButtonClick(const QString &path);

    private:
        struct FolderButton {
            QString name;
            QString path;
            QPushButton *button;
        };

        QList<FolderButton> buttonsList;
};