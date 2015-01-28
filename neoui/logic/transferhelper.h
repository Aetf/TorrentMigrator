#ifndef TRANSFERHELPER_H
#define TRANSFERHELPER_H

#include <QObject>
#include "irecordstransformer.h"

class QQmlEngine;
class QJSEngine;
class RecordsModel;
class TransformerModel;

class TransferHelper : public QObject
{
    Q_OBJECT
public:
    explicit TransferHelper(QObject *parent = 0);

    Q_INVOKABLE
    bool transfer(RecordsModel *sourceModel, QList<int> selection,
                  const TransformerModel *transModel, RecordsModel *targetModel);

    static QObject *TransferHelperProvider(QQmlEngine *engine, QJSEngine *scriptEngine);
private:
    QList<IRecordsTransformer *> createTransformersFromModel(const TransformerModel *model);
};

#endif // TRANSFERHELPER_H
