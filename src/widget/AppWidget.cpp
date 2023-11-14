#include "widget/AppWidget.hpp"

AppWidget::AppWidget(QString path, QWidget *parent) :
            QWidget(parent), path(path), topBar(this), 
            mountedFoldersWidget(this), entriesWindow(path, this){
    setLayout(new QVBoxLayout());
    layout()->addWidget(&topBar);
    layout()->addWidget(&mountedFoldersWidget);
    layout()->addWidget(&entriesWindow);

    topBar.setPath(path);

    connect(&mountedFoldersWidget, &MainFolderWidget::folderButtonClicked, 
            this, &AppWidget::changePathToMountedFolder);
            
    
}

AppWidget::~AppWidget(){
}

void AppWidget::changePathToMountedFolder(QString path){
    topBar.setPath(path);
    entriesWindow.setNewPath(path);
}
