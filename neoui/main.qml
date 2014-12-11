import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: root
    visible: true
    width: 1090
    height: 320
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Item {
        id: mainRow
        anchors.fill: parent

        TorrentsColumn {
            id: leftColumn
            anchors {
                top: parent.top; bottom: parent.bottom;
                left: parent.left; leftMargin: 5;
                right: middleColumn.left; rightMargin: 5
            }
            title: "From:"
        }

        TransferButtonBox {
            id: middleColumn
            anchors.centerIn: parent
        }

        TorrentsColumn {
            id: rightColumn
            anchors {
                top: parent.top; bottom: parent.bottom;
                left: middleColumn.right; leftMargin: 5;
                right: parent.right; rightMargin: 5
            }
            title: "To:"
        }
    }
}
