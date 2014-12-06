#ifndef QBITTORRENTCONFPANEL_H
#define QBITTORRENTCONFPANEL_H

#include "abstractconfpanel.h"

namespace Ui {
class qBittorrentConfPanel;
}

class IRecordsAccessor;

class qBittorrentConfPanel : public AbstractConfPanel
{
    Q_OBJECT

public:
    explicit qBittorrentConfPanel(QWidget *parent = 0);
    ~qBittorrentConfPanel();

    virtual IRecordsAccessor *configedAccessor() const;

public slots:
    void browseConfigDir();
    void browseBackupDir();

private:
    Ui::qBittorrentConfPanel *ui;
};

#endif // QBITTORRENTCONFPANEL_H
