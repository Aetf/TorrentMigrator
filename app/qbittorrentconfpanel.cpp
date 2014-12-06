#include <QFileDialog>
#include "qbittorrentconfpanel.h"
#include "ui_qbittorrentconfpanel.h"
#include "libtorrentaccessor.h"

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

void qBittorrentConfPanel::browseConfigDir()
{
    auto path = ui->configDirPathEdit->text();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Set APPDATA Directory"),
                                                    path.isEmpty() ? QDir::home().path() : path,
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        ui->configDirPathEdit->setText(dir);
    }
}

void qBittorrentConfPanel::browseBackupDir()
{
    auto path = ui->backupDirPathEdit->text();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Set APPDATA Directory"),
                                                    path.isEmpty() ? QDir::home().path() : path,
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        ui->backupDirPathEdit->setText(dir);
    }
}

IRecordsAccessor *qBittorrentConfPanel::getConfigedAccessor() const
{
    auto accessor = new LibtorrentAccessor;
    QVariantHash args;
    args["configDir"] = ui->configDirPathEdit->text();
    args["backupDir"] = ui->backupDirPathEdit->text();
    accessor->setup(args);
    return accessor;
}

void qBittorrentConfPanel::okBtnClicked()
{
    emit accept(getConfigedAccessor());
}
