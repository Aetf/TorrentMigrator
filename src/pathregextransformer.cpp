#include <QRegExp>
#include "pathregextransformer.h"
#include "utils.h"

PathRegexTransformer::PathRegexTransformer()
{

}

PathRegexTransformer::~PathRegexTransformer()
{

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
    QVariantHash argsHash;
    for (auto line : args.split('\n')) {
        if (line.isEmpty()) continue;

        auto mark = line[0];
        auto regex = line.section(mark, 0, 0, QString::SectionSkipEmpty);
        auto replace = line.section(mark, 1, 1, QString::SectionSkipEmpty);
        if (!regex.isEmpty()) {
            argsHash[regex] = replace;
        }
    }
    return setup(argsHash);
}

/*!
 * \brief setup
 * \param args
 *     "#^/media/(\w)/abc#/\1/abc#"
 *     "/john/alice/"
 * \return
 */
bool PathRegexTransformer::setup(QVariantHash args)
{
    for (auto key : args.keys()) {
        QRegExp regexp(key);
        if (!regexp.isValid()) { continue; }
        if (!args[key].canConvert<QString>()) { continue; }

        auto replacement = args[key].toString();
        regexList << std::make_pair(regexp, replacement);

        qDebug() << "regex added:"
                 << regexp.pattern() << "=>" << replacement;
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
