#ifndef UTORRENTCONFPANEL_H
#define UTORRENTCONFPANEL_H

#include "abstractconfpanel.h"

namespace Ui {
class uTorrentConfPanel;
}

class IRecordsAccessor;

class uTorrentConfPanel : public AbstractConfPanel
{
    Q_OBJECT

public:
    explicit uTorrentConfPanel(QWidget *parent = 0);
    ~uTorrentConfPanel();

    virtual IRecordsAccessor *configedAccessor() const;

public slots:
    void browseAppdata();
    void browseExtraTorrents();

private:
    Ui::uTorrentConfPanel *ui;
};

#endif // UTORRENTCONFPANEL_H
