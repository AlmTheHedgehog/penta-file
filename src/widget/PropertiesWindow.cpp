#include "widget/PropertiesWindow.hpp"

PropertiesWindow::PropertiesWindow(QString objectPath, QWidget *parent):
                                    QWidget(parent), objectPath(objectPath){
    object = new QFileInfo(objectPath);                                    
   
    setWindowTitle("Properties " + nameLabel.text());
    setLayout(new QVBoxLayout());

    createProperties();

    layout()->setSpacing(8);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    adjustSize();
}

PropertiesWindow::~PropertiesWindow(){
}

void PropertiesWindow::createProperties(){
    QWidget* nameWidget = new QWidget(this);
    QHBoxLayout *nameLayout = new QHBoxLayout(nameWidget);
    nameEdit = new QLineEdit(nameWidget);

    nameLabel.setTextFormat(Qt::RichText);
    nameLabel.setText("<b>Name:</b> ");
    nameLayout->addWidget(&nameLabel);
    nameEdit->setText(object->baseName());
    nameLayout->addWidget(nameEdit);
    if(!object->isDir()){
        nameLayout->addWidget(new QLabel("." + object->suffix(), nameWidget));
    }
    nameWidget->setLayout(nameLayout);
   
    createInfoWidget();
    createPermissionsWidget();
   
    layout()->addWidget(nameWidget);
    layout()->addWidget(infoWidget);
    layout()->addWidget(&permissionsLabel);
    layout()->addWidget(permissionsWidget);
}

qint64 PropertiesWindow::dirSize(QString dirPath) {
    qint64 size = 0;
    QDir dir(dirPath);
    //calculate total size of current directories' files
    QDir::Filters fileFilters = QDir::Files|QDir::System|QDir::Hidden;
    for(QString filePath : dir.entryList(fileFilters)) {
        QFileInfo fi(dir, filePath);
        size+= fi.size();
    }
    //add size of child directories recursively
    QDir::Filters dirFilters = QDir::Dirs|QDir::NoDotAndDotDot|QDir::System|QDir::Hidden;
    for(QString childDirPath : dir.entryList(dirFilters))
        size+= dirSize(dirPath + QDir::separator() + childDirPath);
    return size;
}

QString PropertiesWindow::formatSize(qint64 size) {
    QStringList units = {"Bytes", "KB", "MB", "GB", "TB", "PB"};
    int i;
    double outputSize = size;
    for(i=0; i<units.size()-1; i++) {
        if(outputSize<1024) break;
        outputSize= outputSize/1024;
    }
    return QString("%0 %1").arg(outputSize, 0, 'f', 2).arg(units[i]);
}

void PropertiesWindow::createInfoWidget(){
     infoWidget = new QWidget(this);
    infoLayout = new QVBoxLayout(infoWidget);

    typeLabel.setTextFormat(Qt::RichText);
    sizeLabel.setTextFormat(Qt::RichText);
    pathLabel.setTextFormat(Qt::RichText);
    birthDateLabel.setTextFormat(Qt::RichText);
    lastModifiedLabel.setTextFormat(Qt::RichText);
    ownerLabel.setTextFormat(Qt::RichText);

    if(object->isDir()){
        typeLabel.setText("<b>Type:</b> Directory");
        sizeLabel.setText("<b>Size:</b> " + formatSize(dirSize(object->absoluteFilePath())));
    }else{
        typeLabel.setText("<b>Type:</b> File");
        sizeLabel.setText("<b>Size:</b> " + formatSize(object->size()));
    }
    pathLabel.setText("<b>Path:</b> " + object->absoluteFilePath());
    birthDateLabel.setText("<b>Created:</b> " + object->birthTime().toString("dd-MM-yyyy HH:mm:ss"));
    lastModifiedLabel.setText("<b>Modified:</b> " + object->lastModified().toString("dd-MM-yyyy HH:mm:ss"));
    ownerLabel.setText("<b>Owner:</b> " + object->owner());

    infoLayout->addWidget(&pathLabel);
    infoLayout->addWidget(&typeLabel);
    infoLayout->addWidget(&sizeLabel);
    infoLayout->addWidget(&ownerLabel);
    infoLayout->addWidget(&birthDateLabel);
    infoLayout->addWidget(&lastModifiedLabel);
    infoLayout->addWidget(&permissionsLabel);
    infoWidget->setLayout(infoLayout);
}

void PropertiesWindow::createPermissionsWidget(){
     permissionsLabel.setTextFormat(Qt::RichText);
    permissionsLabel.setText("<b>Permissions</b> ");
    permissionsLabel.setAlignment(Qt::AlignCenter);

    QFileDevice::Permissions filePermissions = object->permissions();
    permissionsWidget = new QWidget(this);
    permissionsLayout = new QHBoxLayout(permissionsWidget);

    QString option = "Option\t\nRead\t\nWrite\t\nExecute\t";

    QString ownerPermissions = "Owner:\t";
    if (filePermissions & QFileDevice::ReadOwner)
        ownerPermissions += "\n+";
    else
        ownerPermissions += "\n-";
    if (filePermissions & QFileDevice::WriteOwner)
        ownerPermissions += "\n+";
    else
        ownerPermissions += "\n-";
    if (filePermissions & QFileDevice::ExeOwner)
        ownerPermissions += "\n+";
    else
        ownerPermissions += "\n-";

    QString groupPermissions = "Group:\t";
    if (filePermissions & QFileDevice::ReadGroup)
        groupPermissions += "\n+";
    else
        groupPermissions += "\n-";
    if (filePermissions & QFileDevice::WriteGroup)
        groupPermissions += "\n+";
    else
        groupPermissions += "\n-";
    if (filePermissions & QFileDevice::ExeGroup)
        groupPermissions += "\n+";
    else
        groupPermissions += "\n-";

    QString otherPermissions = "Other:\t";
    if (filePermissions & QFileDevice::ReadOther)
        otherPermissions += "\n+";
    else
        otherPermissions += "\n-";
    if (filePermissions & QFileDevice::WriteOther)
        otherPermissions += "\n+";
    else
        otherPermissions += "\n-";
    if (filePermissions & QFileDevice::ExeOther)
        otherPermissions += "\n+";
    else
        otherPermissions += "\n-";

    QString userPermissions = "User:\t";
    if (filePermissions & QFileDevice::ReadUser)
        userPermissions += "\n+";
    else
        userPermissions += "\n-";
    if (filePermissions & QFileDevice::WriteUser)
        userPermissions += "\n+";
    else
        userPermissions += "\n-";
    if (filePermissions & QFileDevice::ExeUser)
        userPermissions += "\n+";
    else
        userPermissions += "\n-";

    permissionsLayout->addWidget(new QLabel(option, permissionsWidget));
    permissionsLayout->addWidget(new QLabel(ownerPermissions, permissionsWidget));
    permissionsLayout->addWidget(new QLabel(userPermissions, permissionsWidget));
    permissionsLayout->addWidget(new QLabel(groupPermissions, permissionsWidget));
    permissionsLayout->addWidget(new QLabel(otherPermissions, permissionsWidget));
    permissionsWidget->setLayout(permissionsLayout);
}

