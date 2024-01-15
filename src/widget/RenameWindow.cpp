#include "widget/RenameWindow.hpp"

RenameWindow::RenameWindow(QString path, QWidget *parent):
                            PopupWindowB(parent), path(path){
    setWindowTitle("Rename");
    setLayout(new QVBoxLayout());
    nameEdit = new QLineEdit(this);
    okButton.setText("OK");
    cancelButton.setText("Cancel");
    layout()->addWidget(nameEdit);
    layout()->addWidget(&okButton);
    layout()->addWidget(&cancelButton);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    adjustSize();
    connect(&okButton, &QPushButton::clicked, this, &RenameWindow::rename);
    connect(&cancelButton, &QPushButton::clicked, this, &RenameWindow::closeWindow);
    LOG_INFO("Rename window openned. Path: \"%s\"", path.toLatin1().data());
}

RenameWindow::~RenameWindow(){
}

void RenameWindow::rename(){
    QFileInfo oldfile(path);
    QString newName = nameEdit->text();
    if(newName.isEmpty()){
        LOG_ERROR("New name is empty");
        NotificationWindow* notificationWindow = new NotificationWindow("New name is empty", NotificationWindow::NotificationType::ERROR);
        notificationWindow->show();
        closeWindow();
    }

    if(newName == oldfile.baseName()){
        LOG_ERROR("New name is the same as old name");
        NotificationWindow* notificationWindow = new NotificationWindow("New name is the same as old name", NotificationWindow::NotificationType::ERROR);
        notificationWindow->show();
    }
    else{
        if(oldfile.isDir()){
            QString newPath = oldfile.absolutePath() + QDir::separator() + newName;
            QDir dir(path);
            if(dir.rename(oldfile.absoluteFilePath(), newPath)){
                LOG_INFO("Directory renamed. Old name: \"%s\". New name: \"%s\"", oldfile.absoluteFilePath().toLatin1().data(), newName.toLatin1().data());
                closeWindow();
            } else {
                NotificationWindow* notificationWindow = new NotificationWindow("Directory not renamed", NotificationWindow::NotificationType::ERROR);
                notificationWindow->show();
            }
        } else {
            QString newPath = oldfile.absolutePath() + QDir::separator() + newName + "." + oldfile.suffix();  
            QFile file(path);
            if(file.rename(oldfile.absoluteFilePath(), newPath)){
                LOG_INFO("File renamed. Old name: \"%s\". New name: \"%s\"", oldfile.absoluteFilePath().toLatin1().data(), newName.toLatin1().data());
                closeWindow();
            } else {
                NotificationWindow* notificationWindow = new NotificationWindow("File not renamed", NotificationWindow::NotificationType::ERROR);
                notificationWindow->show();
            }
        }
        closeWindow();
    }
}

void RenameWindow::closeWindow(){
    emit renameDone();
    destroy();
    deleteLater();
}
