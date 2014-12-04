#include "qbittorrentconfpanel.h"
#include "ui_qbittorrentconfpanel.h"

qBittorrentConfPanel::qBittorrentConfPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qBittorrentConfPanel)
{
    ui->setupUi(this);
}

qBittorrentConfPanel::~qBittorrentConfPanel()
{
    delete ui;
}
