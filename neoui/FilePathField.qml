import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import RecordsModel 1.0

RowLayout {
    id: root
    spacing: 5

    property alias browseButtonText: browseBtn.text
    property alias path: pathField.text

    TextField {
        id: pathField
        Layout.fillWidth: true
    }

    Button {
        id: browseBtn
        Layout.maximumWidth: implicitWidth
        text: "Browse..."

        onClicked: {
            root.path = DialogHelper.getExistingDirectory("Choose Directory", root.path);
        }
    }
}
