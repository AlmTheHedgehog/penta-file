#include <QtWidgets>
#include "../include/mainwidget.h"

// Constructor for main window
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent) {
  button_       = new QPushButton(tr("Push Me!"));
  textBrowser_  = new QTextBrowser();

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->addWidget(button_,0,0);
  mainLayout->addWidget(textBrowser_,1,0);
  setLayout(mainLayout);
  setWindowTitle(tr("Connecting buttons to processes.."));

  connect(button_, SIGNAL(released()), this, SLOT(onButtonReleased()));
  connect(&process_, SIGNAL(readyReadStandardOutput()), this, SLOT(onCaptureProcessOutput()));
}

// Destructor
MainWidget::~MainWidget() {
  delete button_;
  delete textBrowser_;
}

// Handler for button click
void MainWidget::onButtonReleased() {
  // clear the text in the textBrowser and start the process
  textBrowser_->clear();

  // Set up our process to write to stdout and run our command
  process_.setCurrentWriteChannel(QProcess::StandardOutput); // Set the write channel
  process_.start(QString("ls -alh ").append(QDir::homePath()).append("/Desktop")); // Start a terminal command
}


// This is called whenever the QProcess::readyReadStandardOutput() signal is received
void MainWidget::onCaptureProcessOutput() {
  // Determine whether the object that sent the signal was a pointer to a process
  QProcess* process = qobject_cast<QProcess*>(sender());
  // If so, append the output to the textbrowser
  if (process){
    textBrowser_->append(process->readAllStandardOutput());
  }
}
