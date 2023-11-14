#pragma once

#include "EntriesWindow.hpp"
#include "MainFolderWidget.hpp"
#include "TopBarWidget.hpp"

class AppWidget : public QWidget {
    Q_OBJECT

    public:
        AppWidget(QString path = "", QWidget *parent = nullptr);
        virtual ~AppWidget();

    private slots:
        void changePathToMountedFolder(QString path);

    private:
        QString path;
        TopBarWidget topBar;
        MainFolderWidget mountedFoldersWidget;
        EntriesWindow entriesWindow;
};
