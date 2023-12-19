#include "widget/EntriesWindow.hpp"

EntriesWindow::EntriesWindow(QString path, QWidget *parent):
                    QScrollArea(parent), entriesNumber(0){
    QWidget *container = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(container);
    setWidget(container);
    container->setLayout(layout);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignTop);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setWidgetResizable(true);

    setNewPath(path);
}

EntriesWindow::~EntriesWindow(){
    clearEntiesList();
}

void EntriesWindow::addNewEntry(LineEntry *newEntry){
    lineEntries.push_back(newEntry);
    widget()->layout()->addWidget(newEntry);
    connect(newEntry, &LineEntry::setNewPath, this, &EntriesWindow::setNewPath);
    connect(newEntry, &LineEntry::setFilePath, this, &EntriesWindow::selectLine);
}

void EntriesWindow::clearEntiesList(){
    for(auto eachline : lineEntries){
        delete eachline;
    }
    lineEntries.clear();
    LOG_INFO("Enties list was cleared");
}

void EntriesWindow::setNewPath(const QString &newPath){
    QFileInfo newDir(newPath);
    if(!newDir.exists()){
        LOG_ABNORMAL("A new directory(%s) doesn`t exist.",
                        newPath.toLatin1().data());
        NotificationWindow *errorWindow = new NotificationWindow("path " + newPath + " doesn`t exist", 
                                                                NotificationWindow::NotificationType::ERROR);
        initPopupWindow(errorWindow);
        return;
    }
    if(!newDir.isWritable()){
        //TODO: make possible to work with read-only dirs
        LOG_INFO("A new directory(%s) is opened in read-only", newPath.toLatin1().data());
        // LOG_ABNORMAL("Failed to set a new directory(%s). Emit wrongPath signal."
        //             " Exists:%d, isDir:%d",
        //             newPath.toLatin1().data(), newDir.exists(), newDir.isDir());
        // emit wrongPath();
    }
    if(!newDir.isDir()){
        QProcess::startDetached("xdg-open", QStringList() << newDir.filePath());
        LOG_INFO("A new directory(%s) is a file which will be opened using xdg-open",
                    newPath.toLatin1().data());
        return;
    }
    directory.setPath(newPath);
    if(selectedLine != nullptr){
        selectedLine->setSelection(false);
        selectedLine = nullptr;
    }
    clearEntiesList();
    for(auto entry:directory.entryInfoList(QDir::Filter::NoDotAndDotDot
                                            | QDir::Filter::Dirs
                                            | QDir::Filter::Files, 
                                            QDir::SortFlag::DirsFirst
                                            | QDir::SortFlag::Name
                                            | QDir::SortFlag::IgnoreCase)){
        if(entry.isDir()){
            addNewEntry(new LineEntry(LineEntry::LineType::DIRECTORY, entry.fileName(),
                                      entry.absoluteFilePath()));
        }else{
            addNewEntry(new LineEntry(LineEntry::LineType::FILE, entry.fileName(),
                                      entry.absoluteFilePath(), entry.size()));
        }
    }
    LOG_INFO("New path(%s) was set and entries were fetched", newPath.toLatin1().data());
    emit setNewPathSignal(newPath);
    deselectLine();
}


void EntriesWindow::selectLine(const QString &filePath){
    QFileInfo fileInfo(filePath);

    if(!fileInfo.exists()){
        LOG_ABNORMAL("File(%s) doesn't exist", filePath.toLatin1().data());
        return;
    }

    for(auto eachline : lineEntries){
        eachline->setSelection(false);
        if(eachline->getFilePath() == filePath){
            eachline->setSelection(true);
            selectedLine = eachline;
            if(selectedLine->getLineType() == LineEntry::LineType::DIRECTORY){
                emit turnOnChecksumVerificationForSelectedLineSignal(false);
            }else{
                emit turnOnChecksumVerificationForSelectedLineSignal(true);
            }
            emit turnOnPropertiesForSelectedLineSignal(true);
            LOG_INFO("Line(%s) was selected", filePath.toLatin1().data());
        }
    }
}

void EntriesWindow::copySelectedLine(){
    if(selectedLine == nullptr){
        LOG_ABNORMAL("No line was selected");
        return;
    }
    *isCut = false;
    copiedLine = new QFileInfo(selectedLine->getFilePath());
    LOG_INFO("Line(%s) was copied", selectedLine->getFilePath().toLatin1().data());
    selectedLine->setSelection(false);
    deselectLine();
}

void EntriesWindow::cutSelectedLine(){
    //TODO: check if not read-only
    if(selectedLine == nullptr){
        LOG_ABNORMAL("No line was selected");
        return;
    }
    copiedLine = new QFileInfo(selectedLine->getFilePath());
    *isCut = true;
    LOG_INFO("Line(%s) was cut", selectedLine->getFilePath().toLatin1().data());
    selectedLine->setSelection(false);
    deselectLine();
}

void EntriesWindow::pasteSelectedLine(const QString &destinationPath){
    //TODO: check if not read-only
    if(copiedLine == nullptr) {
        LOG_ABNORMAL("No line was copied");
        return;
    }

    if(destinationPath == ""){
        LOG_ABNORMAL("No destination directory was selected");
        return;
    }

    QDir destinationDir(destinationPath);
    if (!destinationDir.exists()) {
        LOG_ABNORMAL("Destination directory(%s) doesn't exist or is not a directory",
                    destinationPath.toLatin1().data());
        return;
    }

    QString newName = copiedLine->baseName();
    if(copiedLine->completeSuffix() != ""){
        for(int i = 1; destinationDir.exists(newName + "." + copiedLine->completeSuffix()); i++){
            newName = QString("%1_%2").arg(copiedLine->baseName()).arg(i);
        }
    }
    else{
        for(int i = 1; destinationDir.exists(newName); i++){
            newName = QString("%1_%2").arg(copiedLine->baseName()).arg(i);
        }
    }

    QString newPath = destinationPath + "/" + newName;

    if(copiedLine->isDir()){
        copyAndReplaceFolderContents(copiedLine->absoluteFilePath(), newPath, *isCut);
    }else{
        if(copiedLine->completeSuffix() != ""){
            newName = newName + "." + copiedLine->completeSuffix();
        }
        if(!QFile::copy(copiedLine->absoluteFilePath(), destinationPath + "/" + newName)){
            LOG_ABNORMAL("Failed to copy a file(%s) to a destination directory(%s)",
                        copiedLine->fileName().toLatin1().data(),
                        destinationPath.toLatin1().data());
            return;
        }
        if (*isCut) {
            QFile::remove(copiedLine->absoluteFilePath());
        }
    }
    setNewPath(destinationPath);
    LOG_INFO("Line(%s) was pasted", copiedLine->fileName().toLatin1().data());
    deselectLine();
}


void EntriesWindow::copyAndReplaceFolderContents(const QString &fromDir, const QString &toDir, bool copyAndRemove) {
    //TODO: check if not read-only
    QDirIterator it(fromDir, QDirIterator::Subdirectories);
    QDir dir(fromDir);
    const int absSourcePathLength = dir.absoluteFilePath(fromDir).length();

    while (it.hasNext()){
        it.next();
        const auto fileInfo = it.fileInfo();
        if(!fileInfo.isHidden()) { 
            const QString subPathStructure = fileInfo.absoluteFilePath().mid(absSourcePathLength);
            const QString constructedAbsolutePath = toDir + subPathStructure;
            
            if(fileInfo.isDir()){
                dir.mkpath(constructedAbsolutePath);
            } else if(fileInfo.isFile()) {
            
                QFile::remove(constructedAbsolutePath);
                QFile::copy(fileInfo.absoluteFilePath(), constructedAbsolutePath);
            }
        }
    }

    if(copyAndRemove)
        dir.removeRecursively();
}

void EntriesWindow::deleteSelectedLine(){
    //TODO: check if not read-only
    if(selectedLine == nullptr){
        LOG_ABNORMAL("No line was selected");
        return;
    }

    if(selectedLine->getLineType() == LineEntry::LineType::DIRECTORY){
        QDir dir(selectedLine->getFilePath());
        if(!dir.removeRecursively()){
            LOG_ABNORMAL("Failed to remove a directory(%s)",
                        selectedLine->getFilePath().toLatin1().data());
            return;
        }
    }else{
        QFile file(selectedLine->getFilePath());
        if(!file.remove()){
            LOG_ABNORMAL("Failed to remove a file(%s)",
                        selectedLine->getFilePath().toLatin1().data());
            return;
        }
    }
    setNewPath(directory.absolutePath());
    deselectLine();
}

void EntriesWindow::addNewFolder(const QString &folderName){
    if(folderName == ""){
        LOG_ABNORMAL("Folder name is empty");
        return;
    }

    QDir dir(directory.absolutePath());
    if(!dir.mkdir(folderName)){
        LOG_ABNORMAL("Failed to create a new folder(%s) in a directory(%s)",
                    folderName.toLatin1().data(), directory.absolutePath().toLatin1().data());
        return;
    }
    setNewPath(directory.absolutePath());
}

void EntriesWindow::renameSelectedLine(const QString &newName){
    if(selectedLine == nullptr){
        LOG_ABNORMAL("No line was selected");
        return;
    }

    if(newName == ""){
        LOG_ABNORMAL("New name is empty");
        return;
    }

    if(selectedLine->getLineType() == LineEntry::LineType::DIRECTORY){
        QDir dir(selectedLine->getFilePath());
        if(!dir.rename(selectedLine->getLineName(), newName)){
            LOG_ABNORMAL("Failed to rename a directory(%s) to a new name(%s)",
                        selectedLine->getLineName().toLatin1().data(), newName.toLatin1().data());
            return;
        }
    }else{
        QFile file(selectedLine->getFilePath());
        if(!file.rename(selectedLine->getLineName(), newName)){
            LOG_ABNORMAL("Failed to rename a file(%s) to a new name(%s)",
                        selectedLine->getLineName().toLatin1().data(), newName.toLatin1().data());
            return;
        }
    }
    setNewPath(directory.absolutePath());
    deselectLine();
}

void EntriesWindow::deletePopupWindow(PopupWindowB *windowPtr){
    bool found = false;
    std::vector<PopupWindowB*>::iterator iter = dialogWindows.begin();
    for(; iter < dialogWindows.end(); iter++){
        if(*iter == windowPtr){
            found = true;
            break;
        }
    }
    if(found){
        dialogWindows.erase(iter);
    }else{
        LOG_ABNORMAL("Didn`t find dialog window to delete from vector");
    }
}

void EntriesWindow::createNewChecksumVerificationWindow(){
    if(selectedLine == nullptr){
        LOG_ABNORMAL("Line is not selected");
        return;
    }
    if(selectedLine->getLineType() == LineEntry::LineType::DIRECTORY){
        LOG_ABNORMAL("Impossible to calculate checksum for directory");
        return;
    }
    ChecksumDialogWindow* newVerificationWindow = new ChecksumDialogWindow(selectedLine->getLineName(),
                                                                        selectedLine->getChecksum());
    initPopupWindow(newVerificationWindow);
    selectedLine->setSelection(false);
    deselectLine();
}

void EntriesWindow::initPopupWindow(PopupWindowB* window){
    dialogWindows.push_back(window);
    connect(window, &PopupWindowB::windowDestroyed,
            this, &EntriesWindow::deletePopupWindow);
    window->show();
}

void EntriesWindow::searchByHash(const QString &searchHash){
    //Find all entries which contain hash subline
    clearEntiesList();
    addFileLinesToVector(directory, searchHash.toLower());
    LOG_INFO("Search by hash \"%s\" was finished, found %ld objects",
            searchHash.toLatin1().data(), lineEntries.size());
}

void EntriesWindow::addFileLinesToVector(QDir directory, const QString &hash){
    LineEntry* lineEntry;
    for(auto entry:directory.entryInfoList(QDir::Filter::NoDotAndDotDot
                                            | QDir::Filter::Dirs
                                            | QDir::Filter::Files, 
                                            QDir::SortFlag::NoSort)){
        if(entry.isDir()){
            addFileLinesToVector(QDir(entry.absoluteFilePath()), hash);
        }else{
            lineEntry = new LineEntry(LineEntry::LineType::FILE, entry.fileName(),
                                      entry.absoluteFilePath(), entry.size());
            if(lineEntry->getChecksum().contains(hash)){
                addNewEntry(lineEntry);
                lineEntry->showChecksum();
            }else{
                delete lineEntry;
            }
        }
    }
}

void EntriesWindow::createPropertiesWindow(){
    if(selectedLine == nullptr){
        LOG_ABNORMAL("Line is not selected");
        return;
    }
    PropertiesWindow* newVerificationWindow = new PropertiesWindow(selectedLine->getFilePath());
    initPopupWindow(newVerificationWindow);
    LOG_INFO("Properties Dialog Window for %s was created", selectedLine->getLineName().toLatin1().data());
    selectedLine->setSelection(false);
    deselectLine();
}

void EntriesWindow::deselectLine(){
    emit turnOnChecksumVerificationForSelectedLineSignal(false);
    emit turnOnPropertiesForSelectedLineSignal(false);
    selectedLine = nullptr;
}