import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import RecordsModel 1.0

BasicConfigPanel {
    id: root

//    title: "uTorrent Config Panel"
    property string name: "uTorrent"

    function getConfigedArgs() {
        return {
            "appdata" : appdataEdit.path,
            "extratorrent" : extraEdit.path
        };
    }

    GridLayout {
        anchors { left: parent.left; right: parent.right }
        columns: 2
        rowSpacing: 5
        columnSpacing: 10

        Text {
            Layout.alignment: Qt.AlignRight

            text: qsTr("APPDATA Directory:")
        }
        FilePathField { id: appdataEdit }

        Text {
            Layout.alignment: Qt.AlignRight

            text: qsTr("Extra Torrents Directory:")
        }
        FilePathField { id: extraEdit }

        Item {
            Layout.columnSpan: 2
            Layout.fillWidth: true
            implicitHeight: childrenRect.height

            Button {
                anchors.right: parent.right
                text: qsTr("OK")

                onClicked: accepted()
            }
        }
    }
}
