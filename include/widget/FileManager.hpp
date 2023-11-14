#pragma once
#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include "QLineEdit"
#include "MainFolderWidget.hpp"
#include "TopBarWidget.hpp"
#include "EntriesWindow.hpp"

class FileManager : public QWidget{
    Q_OBJECT

    public:
        FileManager(QWidget *parent = nullptr);
        virtual ~FileManager();

    public slots:
        void updateTopBarPath(const QString &newPath);

    private:
        MainFolderWidget *mainFolderWidget;
        TopBarWidget *topBarWidget;
        EntriesWindow *entriesWindow;
        
        QDir *currentPath;
};