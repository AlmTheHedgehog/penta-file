#include "widget/TopBarWidget.hpp"

TopBarWidget::TopBarWidget(QWidget *parent) :
                QWidget(parent){
    
    menuBar = new QMenuBar(this);

    

    createActions();
    createMenus(menuBar);
}

void TopBarWidget::createMenus(QMenuBar *menuBar){
    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(addNewFolderAct);
    fileMenu->addAction(addNewFileAct);
    fileMenu->addAction(deleteAct);

    editMenu = menuBar->addMenu(tr("&Edit"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    
    helpMenu = menuBar->addMenu(tr("&Help"));

    menuBar->addSeparator();
    menuBar->addAction(undoAct);
    menuBar->addAction(redoAct);
}

void TopBarWidget::createActions(){

    cutAct = new QAction(tr("&Cut"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, &QAction::triggered, this, &TopBarWidget::cut);

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, &QAction::triggered, this, &TopBarWidget::copy);

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, &QAction::triggered, this, &TopBarWidget::paste);

    undoAct = new QAction(this);
    undoAct->setIcon(QIcon(UNDO_ICON_URL));
  //  undoAct->setIconVisibleInMenu(true);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last operation"));
    connect(undoAct, &QAction::triggered, this, &TopBarWidget::undo);

    redoAct = new QAction(this);
    redoAct->setIcon(QIcon(REDO_ICON_URL));
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo the last operation"));
    connect(redoAct, &QAction::triggered, this, &TopBarWidget::redo);

    addNewFolderAct = new QAction(tr("&Add new folder"), this);
    addNewFolderAct->setStatusTip(tr("Add new folder"));
    connect(addNewFolderAct, &QAction::triggered, this, &TopBarWidget::addNewFolder);
    
    addNewFileAct = new QAction(tr("&Add new file"), this);
    addNewFileAct->setStatusTip(tr("Add new file"));
    connect(addNewFileAct, &QAction::triggered, this, &TopBarWidget::addNewFile);

    deleteAct = new QAction(tr("&Delete"), this);
    deleteAct->setStatusTip(tr("Delete item"));
    connect(deleteAct, &QAction::triggered, this, &TopBarWidget::deleteItem);
}

void TopBarWidget::cut(){
    LOG_DEBUG("Cut");
}

void TopBarWidget::copy(){
    LOG_DEBUG("Copy");
}

void TopBarWidget::paste(){
    LOG_DEBUG("Paste");
}

void TopBarWidget::undo(){
    LOG_DEBUG("Undo");
}

void TopBarWidget::redo(){
    LOG_DEBUG("Redo");
}

void TopBarWidget::addNewFolder(){
    LOG_DEBUG("Add new folder");
}

void TopBarWidget::addNewFile(){
    LOG_DEBUG("Add new file");
}

void TopBarWidget::deleteItem(){
    LOG_DEBUG("Delete item");
}


TopBarWidget::~TopBarWidget()
{
    delete menuBar;
}
