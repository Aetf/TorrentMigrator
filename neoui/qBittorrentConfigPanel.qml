import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import RecordsModel 1.0

BasicConfigPanel {
    id: root

//    title: "qBittorrent Config Panel"
    property string name: "libtorrent"

    function getConfigedArgs() {
        return {
            "configDir" : configDirEdit.path,
            "backupDir" : backupDirEdit.path
        };
    }

    GridLayout {
        anchors { left: parent.left; right: parent.right }
        columns: 2
        rowSpacing: 5
        columnSpacing: 10

        Text {
            Layout.alignment: Qt.AlignRight

            text: "Config Directory:"
        }
        FilePathField { id: configDirEdit }

        Text {
            Layout.alignment: Qt.AlignRight

            text: "Backup Directory:"
        }
        FilePathField { id: backupDirEdit }

        Item {
            Layout.columnSpan: 2
            Layout.fillWidth: true
            implicitHeight: childrenRect.height

            Button {
                anchors.right: parent.right
                text: "OK"

                onClicked: accepted()
            }
        }
    }
}
