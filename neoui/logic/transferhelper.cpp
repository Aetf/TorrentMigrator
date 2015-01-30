#include <QDebug>
#include "transferhelper.h"
#include "models/recordsmodel.h"
#include "models/transformermodel.h"
#include "models/recordstransformerfactory.h"
#include "utils.h"

TransferHelper::TransferHelper(QObject *parent) : QObject(parent)
{ }

QObject *TransferHelper::TransferHelperProvider(QQmlEngine *engine,
                                                QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return new TransferHelper();
}

bool TransferHelper::transfer(RecordsModel *sourceModel, QList<int> selection,
                              TransformerModel *transModel, RecordsModel *targetModel)
{
    AutoList<IRecordsTransformer> transList(createTransformersFromModel(transModel));
    for (auto row : selection) {
        qDebug() << "Selected row:" << row;

        auto idx = sourceModel->index(row, 0);
        auto record = sourceModel->data(idx,
                                        BasicTorrentModel::RecordDataRole).value<TorrentRecord>();
        qDebug() << "Processing record:" << record.name << "with save_path" << record.save_path;

        qDebug() << "Applying" << transList.list.length() << "transformers";
        for (auto t : transList.list) {
            record = t->transform(record);
        }
        qDebug() << "After transform:" << record.name << "with save_path" << record.save_path;

        auto target = reinterpret_cast<BasicTorrentModel *>(targetModel->sourceModel());
        if (!target->insertRecord(-1, record)) {
            qDebug() << "Insertion failed on record" << record.name;
        }
    }

    return true;
}

QList<IRecordsTransformer *> TransferHelper::createTransformersFromModel(TransformerModel *model)
{
    QList<IRecordsTransformer *> list;
    RecordsTransformerFactory factory;
    for (int i = 0; i != model->rowCount(); i++) {
        auto idx = model->index(i, 0);
        auto argsStr = model->data(idx, TransformerModel::ArgsStrRole).toString();
        auto args = model->data(idx, TransformerModel::ArgsRole).toMap();
        auto name = model->data(idx, Qt::DisplayRole).toString();
        list << (argsStr.isEmpty() ?
                 factory.createTransformer(name, args)
                 : factory.createTransformer(name, argsStr));
        qDebug() << "Craeted transformer with argument" << argsStr << "and" << args;
    }
    return list;
}
