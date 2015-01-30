import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import RecordsModel 1.0

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

            function selectionToArray(sel) {
                var arr = [];
                sel.forEach(function(idx){
                    arr.push(idx);
                });

                console.log(arr.length);
                return arr;
            }

            function transfer(from, to) {
                var sel = selectionToArray(from.selection);
                TransferHelper.transfer(from.model, sel, middleColumn.model, to.model);
            }

            btnTransferToRight.onClicked: {
                transfer(leftColumn, rightColumn);
            }
            btnTransferToLeft.onClicked: {
                transfer(rightColumn, leftColumn);
            }
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
