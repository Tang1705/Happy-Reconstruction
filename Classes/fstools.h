#ifndef FSTOOLS_H
#define FSTOOLS_H


class QString;

namespace fstools
{
    bool delDir(const QString &path);
    bool mkDir(const QString &path, const QString &dirName);
}

#endif // FSTOOLS_H
