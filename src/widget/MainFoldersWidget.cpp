#include "widget/MainFolderWidget.hpp"

MainFolderWidget::MainFolderWidget(QWidget *parent) :
                QWidget(parent){
    
    setLayout(new QHBoxLayout(this));


    QHBoxLayout *newlayout = new QHBoxLayout(this);

    // Get the list of directories in /mnt/ 
    QDir mntDir("/mnt/");
    QStringList diskList = mntDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QString &diskName : diskList) {
        FolderButton folderButton;
        folderButton.name = diskName;
        folderButton.path = mntDir.absoluteFilePath(diskName);
        folderButton.button = new QPushButton(diskName, this);

        connect(folderButton.button, &QPushButton::clicked, this, [=]() {
            handleFolderButtonClick(folderButton.path);
        });

        newlayout->addWidget(folderButton.button);

        buttonsList.append(folderButton);
    }

    layout()->addItem(newlayout);
}

void MainFolderWidget::handleFolderButtonClick(const QString &path) {
    // Handle the button click, for example, emit a signal with the selected path
   // emit folderButtonClicked(path);
    LOG_DEBUG("Clicked on folder: %s", path.toStdString().c_str());
}

MainFolderWidget::~MainFolderWidget() {
    for (const FolderButton &folderButton : buttonsList) {
        delete folderButton.button;
    }
}