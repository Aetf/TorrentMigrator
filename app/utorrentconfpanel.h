#ifndef UTORRENTCONFPANEL_H
#define UTORRENTCONFPANEL_H

#include <QWidget>

namespace Ui {
class uTorrentConfPanel;
}

class IRecordsAccessor;

class uTorrentConfPanel : public QWidget
{
    Q_OBJECT

public:
    explicit uTorrentConfPanel(QWidget *parent = 0);
    ~uTorrentConfPanel();

    IRecordsAccessor *getConfigedAccessor() const;

signals:
    void accept(IRecordsAccessor*);

public slots:
    void browseAppdata();
    void browseExtraTorrents();

private slots:
    void okBtnClicked();

private:
    Ui::uTorrentConfPanel *ui;
};

#endif // UTORRENTCONFPANEL_H
