#include "widget/MainFolderWidget.hpp"

MainFolderWidget::MainFolderWidget(QWidget *parent) :
                QWidget(parent){
    
    setLayout(new QHBoxLayout(this));
    

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

    layout()->setContentsMargins(0, 0, 0, 0);

}

void MainFolderWidget::handleFolderButtonClick(const QString &path){
    emit folderButtonClicked(path);
    LOG_DEBUG("Clicked on folder: %s", path.toStdString().c_str());
}

MainFolderWidget::~MainFolderWidget() {
    for (const FolderButton &folderButton : buttonsList) {
        delete folderButton.button;
    }
}