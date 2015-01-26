#ifndef PATAPREFIXTRANSFORMER_H
#define PATAPREFIXTRANSFORMER_H

#include "irecordstransformer.h"

class QRegExp;
class PathRegexTransformer : public IRecordsTransformer
{
public:
    PathRegexTransformer();
    ~PathRegexTransformer();

    /*!
     * \brief setup
     * \param args
     *     "#^/media/(\w)/abc#/\1/abc#g"
     *     "/john/alice/"
     * \return
     */
    virtual bool setup(QVariantHash args);
    virtual bool setup(QString args);
    virtual TorrentRecord transform(const TorrentRecord &input) const;
    virtual TorrentRecord transformBack(const TorrentRecord &input) const;

private:
    QList< std::pair<QRegExp, QString>> regexList;
};

#endif // PATAPREFIXTRANSFORMER_H
