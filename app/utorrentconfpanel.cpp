#include <QFileDialog>
#include <QVariantHash>
#include "utorrentconfpanel.h"
#include "ui_utorrentconfpanel.h"
#include "utorrentaccessor.h"

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

void uTorrentConfPanel::browseAppdata()
{
    auto path = ui->appdataPathEdit->text();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Set APPDATA Directory"),
                                                    path.isEmpty() ? QDir::home().path() : path,
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        ui->appdataPathEdit->setText(dir);
    }
}

void uTorrentConfPanel::browseExtraTorrents()
{
    auto path = ui->extraTorrentsPathEdit->text();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Set Extra torrents Directory"),
                                                    path.isEmpty() ? QDir::home().path() : path,
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        ui->extraTorrentsPathEdit->setText(dir);
    }
}

IRecordsAccessor *uTorrentConfPanel::getConfigedAccessor() const
{
    auto accessor = new uTorrentAccessor;
    QVariantHash args;
    args["appdata"] = ui->appdataPathEdit->text();
    args["extratorrent"] = ui->extraTorrentsPathEdit->text();
    accessor->setup(args);
    return accessor;
}

void uTorrentConfPanel::okBtnClicked()
{
    emit accept(getConfigedAccessor());
}
