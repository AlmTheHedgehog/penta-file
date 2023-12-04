#include "widget/LineEntry.hpp"

LineEntry::LineEntry(LineType lineType, QString name, QString path, qint64 size, QWidget *parent):
                QPushButton(parent), lineType(lineType), name(name), size(size), path(path){
    setLayout(new QHBoxLayout(this));
    iconLabel = new QLabel();
    setIcon(lineType);
    nameLabel = new QLabel(name);
    if(lineType == LineType::DIRECTORY){
        sizeLabel = new QLabel("");
    }else{
        sizeLabel = new QLabel(QString::number(size));
    }

    iconLabel->setFixedSize(16, 16);
    nameLabel->setFixedHeight(32);
    sizeLabel->setFixedSize(50, 32);
    setFixedHeight(32);

    layout()->addWidget(iconLabel);
    layout()->addWidget(nameLabel);
    layout()->addWidget(sizeLabel);
    layout()->setContentsMargins(8, 0, 0, 0);
    setStyleSheet("padding: 0px");
    setFlat(true);
}

LineEntry::~LineEntry(){
}

void LineEntry::setIcon(LineType lineType){
    switch(lineType){
        case LineType::DIRECTORY:
            iconLabel->setPixmap(QPixmap(DIRECTORY_ICON_URL));
            break;
        case LineType::FILE:
            //TODO: add icon for files
            LOG_DEBUG("TODO: add file icon");
            break;
        default:
            LOG_ABNORMAL("Unknown type of LineEntry");
    }
}

void LineEntry::mouseDoubleClickEvent(QMouseEvent*){
    emit setNewPath(path);
}

void LineEntry::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::MouseButton::LeftButton){
        emit setFilePath(path);
    }
}

void LineEntry::setSelection(bool selected) {
    if (!selected) {
        setStyleSheet("");
        return;
    }

    setStyleSheet("background-color: grey; color: white;");
}

QString LineEntry::getFilePath(){
    return path;
}

LineEntry::LineType LineEntry::getLineType(){
    return lineType;
}

QString LineEntry::getLineName(){
    return name;
}