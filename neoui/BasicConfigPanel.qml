import QtQuick 2.3
import QtQuick.Controls 1.2

Item {
    id: root

    default property Component content
    property alias title: titleText.text
    signal accepted()

    function getConfigedAccessor() {
        return {};
    }

    Column {
        anchors.centerIn: parent
        Text {
            id: titleText
            anchors.horizontalCenter: parent.horizontalCenter

            text: "Config Panel"
        }

        Loader {
            anchors.horizontalCenter: parent.horizontalCenter

            sourceComponent: content
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter

            text: "OK"

            onClicked: accepted()
        }
    }
}
