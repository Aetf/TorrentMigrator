import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import RecordsModel 1.0

BasicConfigPanel {
    id: root

    title: "uTorrent Config Panel"

    function getConfigedAccessor() {
        return RecordsAccessorFactory.createUTorrentAccessor(appdataEdit.path, extraEdit.path);
    }

//    ColumnLayout {
    Column {
        FilePathField {
            id: appdataEdit
//            Layout.fillWidth: true

            label: "APPDATA Directory:"
        }
        FilePathField {
            id: extraEdit
//            Layout.fillWidth: true

            label: "Extra Torrents Directory:"
        }
    }
}
