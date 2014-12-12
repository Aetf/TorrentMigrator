import QtQuick 2.3

BasicConfigPanel {
    id: root

    title: "qBittorrent Config Panel"

    function getConfigedAccessor() {
        return {};
    }

    Rectangle {
        color: Qt.lighter("gray")
    }
}
