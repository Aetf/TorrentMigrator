#ifndef TRANSFERLOGIC_H
#define TRANSFERLOGIC_H

#include <QList>
#include <QObject>

class BasicTorrentModel;
class IRecordsTransformer;

class TransferManager : public QObject
{
    Q_OBJECT
public:
    TransferManager();
    ~TransferManager();

    bool transfer(BasicTorrentModel *source, const QList<int> &selection,
                  BasicTorrentModel *target);

private:
    QList<IRecordsTransformer*> transformations;
};

#endif // TRANSFERLOGIC_H
