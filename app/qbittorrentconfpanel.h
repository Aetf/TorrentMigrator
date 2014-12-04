#ifndef QBITTORRENTCONFPANEL_H
#define QBITTORRENTCONFPANEL_H

#include <QWidget>

namespace Ui {
class qBittorrentConfPanel;
}

class qBittorrentConfPanel : public QWidget
{
    Q_OBJECT

public:
    explicit qBittorrentConfPanel(QWidget *parent = 0);
    ~qBittorrentConfPanel();

private:
    Ui::qBittorrentConfPanel *ui;
};

#endif // QBITTORRENTCONFPANEL_H
