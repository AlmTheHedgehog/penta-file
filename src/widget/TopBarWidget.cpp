#include "widget/TopBarWidget.hpp"

TopBarWidget::TopBarWidget(QWidget *parent) :
                QWidget(parent){
    
    menuBar = new QMenuBar(this);
    createActions();
    createMenus(menuBar);

    pathField = new QLineEdit(this);
    searchButton = new QPushButton(this);
    createSearchField(pathField, searchButton);
    
    QHBoxLayout *topBarLayout = new QHBoxLayout;

    menuBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    topBarLayout->addWidget(menuBar);
    pathField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    topBarLayout->addWidget(pathField);
    searchButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    topBarLayout->addWidget(searchButton);
    topBarLayout->addStretch();  // Optional: Add stretch to push widgets to the left

    topBarLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(topBarLayout);
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


void TopBarWidget::createSearchField(QLineEdit *pathField, QPushButton *searchButton){
    QString currentPath = QDir::currentPath();

    pathField->setText(currentPath);
    searchButton->setText("Go");
    connect(searchButton, &QPushButton::clicked, this, &TopBarWidget::searchPath);
}

void TopBarWidget::searchPath() {
    QString path = pathField->text();
    
    // Perform actions with the entered path, e.g., navigate to the directory, etc.
    // Add your logic here based on what you want to do with the entered path.
    
    // For now, let's just print the path
    LOG_DEBUG("Path");
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
    // pathField->setText(newPath);
    QDir dir(pathField->text());
    if(dir.cdUp()){
        pathField->setText(dir.absolutePath());
        emit newPathSignal(dir.absolutePath());
    }else{
        LOG_ABNORMAL("Parent directory doesnt exist, Can`t cdUp()");
    }
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

void TopBarWidget::setPath(const QString &newPath) {
    LOG_DEBUG("path:%s", newPath.toLatin1().data());
    pathField->setText(newPath);
}

TopBarWidget::~TopBarWidget(){
}
