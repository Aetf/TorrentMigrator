import QtQuick 2.3
import RecordsModel 1.0

BasicConfigPanel {
    id: root

    title: "qBittorrent Config Panel"

    function getConfigedAccessor() {
        return RecordsAccessorFactory.createLibTorrentAccessor("", "");
    }

    Rectangle {
        color: Qt.lighter("gray")
    }
}
