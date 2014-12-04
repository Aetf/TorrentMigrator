#ifndef UTORRENTCONFPANEL_H
#define UTORRENTCONFPANEL_H

#include <QWidget>

namespace Ui {
class uTorrentConfPanel;
}

class uTorrentConfPanel : public QWidget
{
    Q_OBJECT

public:
    explicit uTorrentConfPanel(QWidget *parent = 0);
    ~uTorrentConfPanel();

private:
    Ui::uTorrentConfPanel *ui;
};

#endif // UTORRENTCONFPANEL_H
