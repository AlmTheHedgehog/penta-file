#include "widget/ChecksumDialogWindow.hpp"

ChecksumDialogWindow::ChecksumDialogWindow(QString fileName, QString checksum, QWidget *parent):
                                        QWidget(parent), fileName(fileName), checksum(checksum){
    nameLable.setText("SHA256 checksum for \"" + fileName + "\":");
    checksumLine.setText(checksum);
    checksumLine.setReadOnly(true);
    checksumLine.setFixedWidth(20 + QFontMetrics(checksumLine.font()).horizontalAdvance(checksumLine.text()));
    compareToLable.setText("Compare to checksum:");
    verifyButton.setText("Verify");

    setWindowTitle(fileName + " checksum");
    setLayout(new QVBoxLayout());
    nameLable.setAlignment(Qt::AlignCenter);
    compareToLable.setAlignment(Qt::AlignCenter);
    verifyButton.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout()->addWidget(&nameLable);
    layout()->addWidget(&checksumLine);
    layout()->addWidget(&compareToLable);
    layout()->addWidget(&lineInput);
    layout()->addWidget(&verifyButton);
    layout()->setSpacing(8);
    checksumLine.setFixedHeight(32);
    lineInput.setFixedHeight(32);
    verifyButton.setFixedHeight(48);
    setFixedHeight(224);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    layout()->setAlignment(&verifyButton, Qt::AlignHCenter);

    adjustSize();

    connect(&verifyButton, &QPushButton::clicked,
            this, &ChecksumDialogWindow::verifyChecksum);
}

ChecksumDialogWindow::~ChecksumDialogWindow(){
    emit destroyedSignal(this);
}

void ChecksumDialogWindow::verifyChecksum(bool){
    if(lineInput.text().isEmpty()){
        LOG_INFO("Filed for input checksum for verification %s file is empty", 
                fileName.toLatin1().data());
        //TODO: add pop-up window with message
    }
    if(checksum == lineInput.text()){
        verifyButton.setIcon(QIcon(QPixmap(VERIFIED_ICON_URL)));
        LOG_INFO("Checkum verification successful");
    }else{
        verifyButton.setIcon(QIcon(QPixmap(NOT_VERIFIED_ICON_URL)));
        LOG_INFO("Checkum verification unsuccessful");
    }
}
