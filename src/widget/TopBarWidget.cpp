#include "widget/TopBarWidget.hpp"

TopBarWidget::TopBarWidget(QWidget *parent) :
                QWidget(parent){
    setLayout(new QHBoxLayout(this));
    
    createActions();
    createMenus(new QMenuBar(this));
    createSearchField(new QLineEdit(this),
                    new QPushButton(this));
    createHashSearchField(new QLineEdit(this),
                        new QPushButton(this));

    layout()->setContentsMargins(0, 0, 0, 0);
}


void TopBarWidget::createMenus(QMenuBar *menuBar){
    this->menuBar = menuBar;
    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(addNewFolderAct);
    fileMenu->addAction(checksumVerificationAct);
    fileMenu->addAction(propertiesAct);
    // fileMenu->addAction(renameAct);
    // fileMenu->addAction(addNewFileAct);
   
    editMenu = menuBar->addMenu(tr("&Edit"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addAction(deleteAct);
    editMenu->addSeparator();
    editMenu->addAction(renameAct);
    
    // helpMenu = menuBar->addMenu(tr("&Help"));

    menuBar->addSeparator();
    menuBar->addAction(undoAct);
    // menuBar->addAction(redoAct);

    menuBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    layout()->addWidget(menuBar);
}


void TopBarWidget::createSearchField(QLineEdit *pathField, QPushButton *goToPathButton){
    this->pathField = pathField;
    this->goToPathButton = goToPathButton;
    QString currentPath = QDir::currentPath();

    pathField->setText(currentPath);
    goToPathButton->setText("Go");
    pathField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout()->addWidget(pathField);
    goToPathButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    layout()->addWidget(goToPathButton);

    connect(goToPathButton, &QPushButton::clicked, this, &TopBarWidget::searchPath);
}

void TopBarWidget::createHashSearchField(QLineEdit *hashSearchField, QPushButton *hashSearchButton){
    this->hashSearchField = hashSearchField;
    this->hashSearchButton = hashSearchButton;

    hashSearchButton->setText("Search");
    hashSearchField->setPlaceholderText("Enter sha256 hash of file");
    hashSearchField->setFixedWidth(QFontMetrics(hashSearchField->font()).horizontalAdvance(
                                        hashSearchField->placeholderText()) + LINE_EDIT_PADDING_PX);
    layout()->addWidget(hashSearchField);
    hashSearchButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    layout()->addWidget(hashSearchButton);

    connect(hashSearchButton, &QPushButton::clicked, this, &TopBarWidget::searchByHash);
}

void TopBarWidget::searchPath(){
    emit newPathSignal(pathField->text());
    LOG_DEBUG("Got to path %s", pathField->text().toLatin1().data());
}

void TopBarWidget::searchByHash(){
    if(!hashSearchField->text().isEmpty()){
        LOG_DEBUG("Search by hash %s", hashSearchField->text().toLatin1().data());
        emit searchByHashSignal(hashSearchField->text());
    }
}

void TopBarWidget::createActions(){

    cutAct = new QAction(tr("&Cut"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setDisabled(true);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, &QAction::triggered, this, &TopBarWidget::cut);

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setDisabled(true);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, &QAction::triggered, this, &TopBarWidget::copy);

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    pasteAct->setDisabled(true);
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

    checksumVerificationAct = new QAction(tr("&Verify file checksum"), this);
    checksumVerificationAct->setStatusTip(tr("Verify file checksum"));
    checksumVerificationAct->setDisabled(true);
    connect(checksumVerificationAct, &QAction::triggered, this, &TopBarWidget::checksumVerification);

    propertiesAct = new QAction(tr("&Properties"), this);
    propertiesAct->setStatusTip(tr("Properties"));
    propertiesAct->setDisabled(true);
    connect(propertiesAct, &QAction::triggered, this, &TopBarWidget::properties);
    
    addNewFileAct = new QAction(tr("&Add new file"), this);
    addNewFileAct->setStatusTip(tr("Add new file"));
    connect(addNewFileAct, &QAction::triggered, this, &TopBarWidget::addNewFile);

    deleteAct = new QAction(tr("&Delete"), this);
    deleteAct->setStatusTip(tr("Delete item"));
    deleteAct->setShortcut(QKeySequence::Delete);
    deleteAct->setDisabled(true);
    connect(deleteAct, &QAction::triggered, this, &TopBarWidget::deleteItem);

    renameAct = new QAction(tr("&Rename"), this);
    renameAct->setStatusTip(tr("Rename item"));
    renameAct->setDisabled(true);
    connect(renameAct, &QAction::triggered, this, &TopBarWidget::renameItem);
}

void TopBarWidget::cut(){
    emit cutSignal();
}

void TopBarWidget::copy(){
    emit copySignal();
}

void TopBarWidget::paste(){
    QDir dir(pathField->text());
    emit pasteSignal(dir.absolutePath());
  
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
    QString folderName = QInputDialog::getText(this, tr("Add new folder"),
                                         tr("Folder name:"));
    emit addNewFolderSignal(folderName);
}

void TopBarWidget::addNewFile(){
    LOG_DEBUG("Add new file");
}

void TopBarWidget::deleteItem(){
    LOG_DEBUG("Delete item");
    emit deleteSignal();
}

void TopBarWidget::setPath(const QString &newPath) {
    LOG_DEBUG("path:%s", newPath.toLatin1().data());
    pathField->setText(newPath);
}

void TopBarWidget::renameItem(){
    emit renameSignal();
}

void TopBarWidget::checksumVerification(){
    emit checksumVerificationSignal();
}

void TopBarWidget::properties(){
    emit propertiesSignal();
}

void TopBarWidget::turnOnVerifyChecksumButton(bool status){
    if(status){
        if(!checksumVerificationAct->isEnabled()){
            checksumVerificationAct->setEnabled(true);
        }
    }else{
        if(checksumVerificationAct->isEnabled()){
            checksumVerificationAct->setEnabled(false);
        }
    }
}

void TopBarWidget::turnOnPropertiesButton(bool status){
    if(status){
        if(!propertiesAct->isEnabled()){
            propertiesAct->setEnabled(true);
        }
    }else{
        if(propertiesAct->isEnabled()){
            propertiesAct->setEnabled(false);
        }
    }
}

void TopBarWidget::turnOnEditButtons(bool status){
    if(status){
        if(!cutAct->isEnabled()){
            cutAct->setEnabled(true);
        }
        if(!copyAct->isEnabled()){
            copyAct->setEnabled(true);
        }
        if(!pasteAct->isEnabled()){
            pasteAct->setEnabled(true);
        }
        if(!deleteAct->isEnabled()){
            deleteAct->setEnabled(true);
        }
        if(!renameAct->isEnabled()){
            renameAct->setEnabled(true);
        }
    }else{
        if(cutAct->isEnabled()){
            cutAct->setEnabled(false);
        }
        if(copyAct->isEnabled()){
            copyAct->setEnabled(false);
        }
        if(pasteAct->isEnabled()){
            pasteAct->setEnabled(false);
        }
        if(deleteAct->isEnabled()){
            deleteAct->setEnabled(false);
        }
        if(renameAct->isEnabled()){
            renameAct->setEnabled(false);
        }
    }
}

TopBarWidget::~TopBarWidget(){
}
