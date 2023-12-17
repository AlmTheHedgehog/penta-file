#include "widget/PropertiesWindow.hpp"

PropertiesWindow::PropertiesWindow(QString objectPath, QWidget *parent):
                                    QWidget(parent), objectPath(objectPath){
    object = new QFileInfo(objectPath);                                    
   
    setWindowTitle("Properties " + nameLable.text());
    setLayout(new QVBoxLayout());

    if(object->isDir()){
        directoryProperties();
    }
    else if(object->isFile()){
        fileProperties();
    }
    else{
        LOG_DEBUG("Object is not a file or directory");
    }

    QPushButton *returnButton = new QPushButton("Return", this);
    returnButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout()->addWidget(returnButton);
    connect(returnButton, &QPushButton::clicked, this, &PropertiesWindow::close);
    
    layout()->setSpacing(8);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    adjustSize();
}

PropertiesWindow::~PropertiesWindow(){
}

void PropertiesWindow::fileProperties(){
    nameLable.setText("File name -> " + object->fileName());

    qint64 fileSizeInBytes = object->size();
    double fileSizeInMB = static_cast<double>(fileSizeInBytes) / (1024 * 1024);
    double fileSizeInGB = fileSizeInMB / 1024;

    QString sizeText;

    if (fileSizeInGB >= 0.01) {
        sizeText = "File size -> " + QString::number(fileSizeInGB, 'f', 2) + " GB";
    } else if (fileSizeInMB >= 0.01) {
        sizeText = "File size -> " + QString::number(fileSizeInMB, 'f', 2) + " MB";
    } else {
        sizeText = "File size -> " + QString::number(fileSizeInBytes) + " bytes";
    }

    sizeLable.setText(sizeText);

    typeLable.setText("File type -> " + object->suffix());
    pathLable.setText("File path -> " + object->absoluteFilePath());
    birthDateLable.setText("File birth date -> " + object->birthTime().toString("yyyy-MM-dd HH:mm:ss"));
    lastModifiedLable.setText("File last modified -> " + object->lastModified().toString("yyyy-MM-dd HH:mm:ss"));
    
    ownerLable.setText("File owner -> " + object->owner());
    QFileDevice::Permissions filePermissions = object->permissions();
    QString permissionsText = "File permissions -> ";

    if (filePermissions & QFileDevice::ReadOwner)
        permissionsText += "ReadOwner ";
    if (filePermissions & QFileDevice::WriteOwner)
        permissionsText += "WriteOwner ";
    if (filePermissions & QFileDevice::ExeOwner)
        permissionsText += "ExeOwner ";

    if (filePermissions & QFileDevice::ReadUser)
        permissionsText += "ReadUser ";
    if (filePermissions & QFileDevice::WriteUser)
        permissionsText += "WriteUser ";
    if (filePermissions & QFileDevice::ExeUser)
        permissionsText += "ExeUser ";

    if (filePermissions & QFileDevice::ReadGroup)
        permissionsText += "ReadGroup ";
    if (filePermissions & QFileDevice::WriteGroup)
        permissionsText += "WriteGroup ";
    if (filePermissions & QFileDevice::ExeGroup)
        permissionsText += "ExeGroup ";

    if (filePermissions & QFileDevice::ReadOther)
        permissionsText += "ReadOther ";
    if (filePermissions & QFileDevice::WriteOther)
        permissionsText += "WriteOther ";
    if (filePermissions & QFileDevice::ExeOther)
        permissionsText += "ExeOther ";

    permissionsLable.setText(permissionsText);
    
    layout()->addWidget(&nameLable);
    layout()->addWidget(&typeLable);
    layout()->addWidget(&pathLable);
    layout()->addItem(new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));
    layout()->addWidget(&sizeLable);
    layout()->addWidget(&birthDateLable);
    layout()->addWidget(&lastModifiedLable);
    layout()->addItem(new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));
    layout()->addWidget(&ownerLable);
    layout()->addWidget(&permissionsLable);
}

void PropertiesWindow::directoryProperties(){
    nameLable.setText("Directory name -> " + object->fileName());
    
    qint64 fileSizeInBytes = object->size();
    double fileSizeInMB = static_cast<double>(fileSizeInBytes) / (1024 * 1024);
    double fileSizeInGB = fileSizeInMB / 1024;

    QString sizeText;

    if (fileSizeInGB >= 0.01) {
        sizeText = "Directory size -> " + QString::number(fileSizeInGB, 'f', 2) + " GB";
    } else if (fileSizeInMB >= 0.01) {
        sizeText = "Directory size -> " + QString::number(fileSizeInMB, 'f', 2) + " MB";
    } else {
        sizeText = "Directory size -> " + QString::number(fileSizeInBytes) + " bytes";
    }

    sizeLable.setText(sizeText);
    
    pathLable.setText("Directory path -> " + object->absoluteFilePath());
    birthDateLable.setText("Directory birth date -> " + object->birthTime().toString("yyyy-MM-dd HH:mm:ss"));
    lastModifiedLable.setText("Directory last modified -> " + object->lastModified().toString("yyyy-MM-dd HH:mm:ss"));
    ownerLable.setText("Directory owner -> " + object->owner());

    
    ownerLable.setText("Direcotry owner -> " + object->owner());
    QFileDevice::Permissions filePermissions = object->permissions();
    QString permissionsText = "Directory permissions -> ";

    if (filePermissions & QFileDevice::ReadOwner)
        permissionsText += "ReadOwner ";
    if (filePermissions & QFileDevice::WriteOwner)
        permissionsText += "WriteOwner ";
    if (filePermissions & QFileDevice::ExeOwner)
        permissionsText += "ExeOwner ";

    if (filePermissions & QFileDevice::ReadUser)
        permissionsText += "ReadUser ";
    if (filePermissions & QFileDevice::WriteUser)
        permissionsText += "WriteUser ";
    if (filePermissions & QFileDevice::ExeUser)
        permissionsText += "ExeUser ";

    if (filePermissions & QFileDevice::ReadGroup)
        permissionsText += "ReadGroup ";
    if (filePermissions & QFileDevice::WriteGroup)
        permissionsText += "WriteGroup ";
    if (filePermissions & QFileDevice::ExeGroup)
        permissionsText += "ExeGroup ";

    if (filePermissions & QFileDevice::ReadOther)
        permissionsText += "ReadOther ";
    if (filePermissions & QFileDevice::WriteOther)
        permissionsText += "WriteOther ";
    if (filePermissions & QFileDevice::ExeOther)
        permissionsText += "ExeOther ";

    permissionsLable.setText(permissionsText);
    
    layout()->addWidget(&nameLable);
    layout()->addWidget(&pathLable);
    layout()->addItem(new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));
    layout()->addWidget(&sizeLable);
    layout()->addWidget(&birthDateLable);
    layout()->addWidget(&lastModifiedLable);
    layout()->addItem(new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));
    layout()->addWidget(&ownerLable);
    layout()->addWidget(&permissionsLable);
}