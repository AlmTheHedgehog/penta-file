#include "widget/MainFolderWidget.hpp"

MainFolderWidget::MainFolderWidget(QWidget *parent) :
                QWidget(parent){
    
    setLayout(new QHBoxLayout(this));
    
    // QDir mntDir;
    // QStringList diskList = mntDir.entryList(QDir::Drives);
    
    // for (const QString &diskName : diskList) {
    //     FolderButton folderButton;
    //     folderButton.name = diskName;
    //     folderButton.path = mntDir.absoluteFilePath(diskName);
    //     folderButton.button = new QPushButton(diskName, this);
    //     LOG_DEBUG("Disk name: %s", diskName.toStdString().c_str());
    //     connect(folderButton.button, &QPushButton::clicked, this, [=]() {
    //         handleFolderButtonClick(folderButton.path);
    //     });

    //     layout()->addWidget(folderButton.button);

    //     buttonsList.append(folderButton);
    // }

    QList<QStorageInfo> drives = QStorageInfo::mountedVolumes();

    for (const QStorageInfo &drive : drives) {
        FolderButton folderButton;
        folderButton.name = drive.displayName();
        folderButton.path = drive.rootPath();
        folderButton.button = new QPushButton(folderButton.name, this);

        connect(folderButton.button, &QPushButton::clicked, this, [=]() {
            handleFolderButtonClick(folderButton.path);
        });

        layout()->addWidget(folderButton.button);

        buttonsList.append(folderButton);
    }

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