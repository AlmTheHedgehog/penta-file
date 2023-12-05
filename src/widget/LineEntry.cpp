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
    setCheckable(true);
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
            iconLabel->setPixmap(QPixmap(FILE_ICON_URL));
            break;
        default:
            LOG_ABNORMAL("Unknown type of LineEntry");
    }
}

void LineEntry::mouseDoubleClickEvent(QMouseEvent*){
    emit setNewPath(path);
}

void LineEntry::calculateChecksum(){
    LOG_INFO("Start sha256 checksum calculation for %s", path.toLatin1().data());
    if(lineType != FILE){
        LOG_ABNORMAL("Impossible to calculate checksum. Not a file!");
        return;
    }

    std::ifstream fileStream(path.toLatin1().data(), std::ios::in | std::ios::binary);
    if (!fileStream.good()) {
        LOG_ERROR("Can`t oppen file for hash calculation!");
        return;
    }

    char readingBuffer[FILE_READ_CHUNK] = {0};
    unsigned char hash[SHA256_DIGEST_LENGTH] = {0};
    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    while(fileStream.good()){
        fileStream.read(readingBuffer, FILE_READ_CHUNK);
        SHA256_Update(&ctx, readingBuffer, fileStream.gcount());
    }

    SHA256_Final(hash, &ctx);
    fileStream.close();

    std::ostringstream hashStringStream;
    hashStringStream << std::hex << std::setfill('0');
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        hashStringStream << std::setw(2) << static_cast<int>(hash[i]);
    }
    checksum = QString::fromStdString(hashStringStream.str());
    LOG_INFO("Calculated checksum:%s", checksum.toLatin1().data());
}

void LineEntry::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::MouseButton::LeftButton){
        emit setFilePath(path);
    }
}

void LineEntry::setSelection(bool selected) {
    if (!selected) {
        setChecked(false);
    }else{
        setChecked(true);
    }
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

QString LineEntry::getChecksum(){
    return checksum;
};
