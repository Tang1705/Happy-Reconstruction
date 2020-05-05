#include "fstools.h"
#include <QtCore/qdir.h>

namespace fstools{
    bool delDir(const QString &path) {
        if (path.isEmpty()){
            return false;
        }
        QDir dir(path);
        if(!dir.exists()){
            return true;
        }
        dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
        QFileInfoList fileList = dir.entryInfoList();
        foreach (QFileInfo file, fileList){
            if (file.isFile()) {
                file.dir().remove(file.fileName());
            }
            else {
                delDir(file.absoluteFilePath());
            }
        }
        return dir.rmpath(dir.absolutePath());
    }
    bool mkDir(const QString &path, const QString &dirName) {
        QDir dir(path);
        dir.cd(path);
        bool ok = dir.mkdir(dirName);
        return ok;
    }
}
