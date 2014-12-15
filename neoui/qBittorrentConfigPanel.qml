import QtQuick 2.3
import RecordsModel 1.0

BasicConfigPanel {
    id: root

    title: "qBittorrent Config Panel"

    function getConfigedAccessor() {
        return RecordsAccessorFactory.createLibTorrentAccessor(configDirEdit.path, backupDirEdit.path);
    }

//    ColumnLayout {
    Column {
        FilePathField {
            id: configDirEdit
//            Layout.fillWidth: true

            label: "Config Directory:"
        }
        FilePathField {
            id: backupDirEdit
//            Layout.fillWidth: true

            label: "Backup Directory:"
        }
    }
}
