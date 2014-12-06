#ifndef ABSTRACTCONFPANEL_H
#define ABSTRACTCONFPANEL_H

#include <QWidget>

class IRecordsAccessor;

class AbstractConfPanel : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractConfPanel(QWidget *parent = nullptr) : QWidget(parent) { }
    virtual IRecordsAccessor *configedAccessor() const { return nullptr; }
    int id() const { return m_id; }
    void setId(int id) { m_id = id; }

signals:
    void accept(int, IRecordsAccessor *);

protected slots:
    void emitAccept() { emit accept(id(), configedAccessor()); }

private:
    int m_id = 0;
};

#endif // ABSTRACTCONFPANEL_H
