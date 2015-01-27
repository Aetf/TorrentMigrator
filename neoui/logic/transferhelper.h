#ifndef TRANSFERHELPER_H
#define TRANSFERHELPER_H

#include <QObject>

class TransferHelper : public QObject
{
    Q_OBJECT
public:
    explicit TransferHelper(QObject *parent = 0);
    ~TransferHelper();

signals:

public slots:
};

#endif // TRANSFERHELPER_H
