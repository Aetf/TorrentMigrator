#include "utorrentconfpanel.h"
#include "ui_utorrentconfpanel.h"

uTorrentConfPanel::uTorrentConfPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::uTorrentConfPanel)
{
    ui->setupUi(this);
}

uTorrentConfPanel::~uTorrentConfPanel()
{
    delete ui;
}
