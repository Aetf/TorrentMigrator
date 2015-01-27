#ifndef PATAPREFIXTRANSFORMER_H
#define PATAPREFIXTRANSFORMER_H

#include "irecordstransformer.h"

class QRegExp;
typedef QList<std::pair<QRegExp, QString>> ActionList;

class PathRegexTransformer : public IRecordsTransformer
{
public:
    PathRegexTransformer();
    ~PathRegexTransformer();

    virtual QString name() const;
    virtual IRecordsTransformer *allocate() const;

    virtual bool setup(QVariantMap args);
    /*!
     * \brief setup
     * \param args
     *     "#^/media/(\w)/abc#/\1/abc#g"
     *     "/john/alice/"
     * \return
     */
    virtual bool setup(QString args);
    virtual TorrentRecord transform(const TorrentRecord &input) const;
    virtual TorrentRecord transformBack(const TorrentRecord &input) const;

private:
    ActionList regexList;
};

#endif // PATAPREFIXTRANSFORMER_H
