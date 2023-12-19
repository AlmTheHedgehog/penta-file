#include "widget/AppWidget.hpp"

AppWidget::AppWidget(QString path, QWidget *parent) :
            QWidget(parent), path(path), topBar(this), 
            mountedFoldersWidget(this), entriesWindow(path, this){
    setLayout(new QVBoxLayout());
    layout()->addWidget(&topBar);
    layout()->addWidget(&mountedFoldersWidget);
    layout()->addWidget(&entriesWindow);

    topBar.setPath(path);
      
    connectSignals();
 

}

AppWidget::~AppWidget(){
}

void AppWidget::changePathToMountedFolder(QString path){
    topBar.setPath(path);
    entriesWindow.setNewPath(path);
}

void AppWidget::connectSignals(){
    connect(&topBar, &TopBarWidget::copySignal,
                &entriesWindow, &EntriesWindow::copySelectedLine);
    connect(&topBar, &TopBarWidget::pasteSignal,
                &entriesWindow, &EntriesWindow::pasteSelectedLine);
    connect(&topBar, &TopBarWidget::cutSignal,
                &entriesWindow, &EntriesWindow::cutSelectedLine);
    connect(&topBar, &TopBarWidget::deleteSignal,
                &entriesWindow, &EntriesWindow::deleteSelectedLine);
    connect(&topBar, &TopBarWidget::addNewFolderSignal,
                &entriesWindow, &EntriesWindow::addNewFolder);
    connect(&topBar, &TopBarWidget::renameSignal,
                &entriesWindow, &EntriesWindow::renameSelectedLine);
    connect(&topBar, &TopBarWidget::checksumVerificationSignal,
                &entriesWindow, &EntriesWindow::createNewChecksumVerificationWindow);

    connect(&entriesWindow, &EntriesWindow::turnOnChecksumVerificationForSelectedLineSignal,
                &topBar, &TopBarWidget::turnOnVerifyChecksumButton);

    connect(&mountedFoldersWidget, &MainFolderWidget::folderButtonClicked,
                this, &AppWidget::changePathToMountedFolder);
    connect(&entriesWindow, &EntriesWindow::setNewPathSignal,
                &topBar, &TopBarWidget::setPath);
    connect(&topBar, &TopBarWidget::newPathSignal,
                &entriesWindow, &EntriesWindow::setNewPath);
    connect(&topBar, &TopBarWidget::searchByHashSignal,
                &entriesWindow, &EntriesWindow::searchByHash);

}


