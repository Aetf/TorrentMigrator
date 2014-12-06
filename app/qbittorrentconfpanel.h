#ifndef QBITTORRENTCONFPANEL_H
#define QBITTORRENTCONFPANEL_H

#include <QWidget>

namespace Ui {
class qBittorrentConfPanel;
}

class IRecordsAccessor;

class qBittorrentConfPanel : public QWidget
{
    Q_OBJECT

public:
    explicit qBittorrentConfPanel(QWidget *parent = 0);
    ~qBittorrentConfPanel();

    IRecordsAccessor *getConfigedAccessor() const;

signals:
    void accept(IRecordsAccessor*);

public slots:
    void browseConfigDir();
    void browseBackupDir();

protected slots:
    void okBtnClicked();

private:
    Ui::qBittorrentConfPanel *ui;
};

#endif // QBITTORRENTCONFPANEL_H
