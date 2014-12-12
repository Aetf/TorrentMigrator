import QtQuick 2.3
import RecordsModel 1.0

BasicConfigPanel {
    id: root

    title: "uTorrent Config Panel"

    function getConfigedAccessor() {
        return RecordsAccessorFactory.createUTorrentAccessor("", "");
    }

    Rectangle {
        color: Qt.lighter("gray")
    }
}
