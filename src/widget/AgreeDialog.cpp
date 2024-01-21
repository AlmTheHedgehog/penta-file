#include "widget/AgreeDialog.hpp"

AgreeDialog::AgreeDialog(QString message, QWidget *parent): QDialog(parent){
    setWindowTitle("Confirmation");
    msgLabel.setText(message);
    agreeButton.setText("Agree");
    cancelButton.setText("Cancel");
    QGridLayout* dialoglayout = new QGridLayout();
    dialoglayout->addWidget(&msgLabel, 0, 0, 1, 2);
    dialoglayout->addWidget(&agreeButton, 1, 0);
    dialoglayout->addWidget(&cancelButton, 1, 1);
    connect(&agreeButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(&cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    setLayout(dialoglayout);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

AgreeDialog::~AgreeDialog(){
}
