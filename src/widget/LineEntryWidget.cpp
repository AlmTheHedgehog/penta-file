#include "widget/LineEntryWidget.hpp"

LineEntryWidget::LineEntryWidget(LineType lineType, QString name, qint64 size, QWidget *parent):
                QWidget(parent), lineType(lineType), name(name), size(size){
    setLayout(new QHBoxLayout(this));
    iconLabel = new QLabel();
    setIcon(lineType);
    nameLabel = new QLabel(name);
    sizeLabel = new QLabel(QString::number(size));

    iconLabel->setFixedSize(16, 16);
    nameLabel->setFixedHeight(16);
    sizeLabel->setFixedSize(50, 16);

    layout()->addWidget(iconLabel);
    layout()->addWidget(nameLabel);
    layout()->addWidget(sizeLabel);
    layout()->setMargin(0);
}

LineEntryWidget::~LineEntryWidget(){
    delete iconLabel;
    delete nameLabel;
    delete sizeLabel;
}

void LineEntryWidget::setIcon(LineType lineType){
    switch(lineType){
        case LineType::DIRECTORY:
            iconLabel->setPixmap(QPixmap(DIRECTORY_ICON_URL));
            break;
        case LineType::FILE:
            //TODO: add icon for files
            LOG_DEBUG("TODO: add file icon");
            break;
        default:
            LOG_ABNORMAL("Unknown type of LineEntryWidget");
    }
}