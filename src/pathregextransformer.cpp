#include <QRegExp>
#include "pathregextransformer.h"
#include "utils.h"

PathRegexTransformer::PathRegexTransformer()
{

}

PathRegexTransformer::~PathRegexTransformer()
{

}

QString PathRegexTransformer::name() const
{
    return QStringLiteral("PathRegexTransformer");
}

IRecordsTransformer *PathRegexTransformer::allocate() const
{
    return new PathRegexTransformer();
}

/*!
 * \brief setup
 * \param args
 *     "#^/media/(\w)/abc#/\1/abc#"
 *     "/john/alice/"
 * \return
 */
bool PathRegexTransformer::setup(QString args)
{
    QVariantMap argsMap;
    QStringList list = args.split('\n');
    argsMap["actionList"] = list;

    return setup(argsMap);
}

/*!
 * \brief setup
 * \param args
 *     QStringList actionList:
 *         "#^/media/(\w)/abc#/\1/abc#"
 *         "/john/alice/"
 * \return
 */
bool PathRegexTransformer::setup(QVariantMap args)
{
    QStringList list = args["actionList"].toStringList();
    if (list.isEmpty()) { return false; }

    for (auto line : list) {
        if (line.length() < 2) { continue; }

        auto mark = line[0];
        auto regex = line.section(mark, 0, 0, QString::SectionSkipEmpty);
        auto replace = line.section(mark, 1, 1, QString::SectionSkipEmpty);

        QRegExp regexp(regex);
        if (!regexp.isValid()) { continue; }

        regexList << std::make_pair(regexp, replace);

        qDebug() << "regex added:"
                 << regexp.pattern() << "=>" << replace;
    }
    return true;
}

TorrentRecord PathRegexTransformer::transform(const TorrentRecord &input) const
{
    auto result = input;
    for (auto pair : regexList) {
        result.save_path.replace(pair.first, pair.second);
    }
    return result;
}

TorrentRecord PathRegexTransformer::transformBack(const TorrentRecord &input) const
{
    auto result = input;
    qDebug() << "Warning: PathRegexTransformer::transformBack not implemented!!!";
    return result;
}
