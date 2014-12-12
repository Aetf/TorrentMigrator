#ifndef RECORDSACCESSOROBJECT
#define RECORDSACCESSOROBJECT

#include <QObject>
#include "irecordsaccessor.h"

class RecordsAccessorObject : public QObject
{
    Q_OBJECT
public:
    RecordsAccessorObject(IRecordsAccessor *accessor = nullptr, QObject *parent = nullptr)
        : QObject(parent), m_accessor(accessor) {}

    ~RecordsAccessorObject() {
        if (m_accessor) delete m_accessor;
    }

    void set(IRecordsAccessor *accessor) { m_accessor = accessor; }
    IRecordsAccessor *get() const { return m_accessor; }
private:
    IRecordsAccessor *m_accessor;
};

#endif // RECORDSACCESSOROBJECT

