import QtQuick 2.3
import QtQuick.Controls 1.2
import RecordsModel 1.0

Item {
    id: root
    implicitHeight: inner.implicitHeight
    implicitWidth: inner.implicitWidth

    property alias label: label.text
    property alias browseButtonText: browseBtn.text
    property alias path: pathField.text

    Row {
        id: inner
        anchors.fill: parent

        Text {
            id: label
        }
        TextField {
            id: pathField
        }
        Button {
            id: browseBtn
            text: "Browse..."

            onClicked: {
                root.path = DialogHelper.getExistingDirectory("Choose Directory", root.path);
            }
        }
    }
}
