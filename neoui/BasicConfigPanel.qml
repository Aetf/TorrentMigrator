import QtQuick 2.3
import QtQuick.Controls 1.2

Item {
    id: root

    default property alias contentData: placeholder.data
    property alias title: titleText.text
    signal accepted()

    function getConfigedAccessor() {
        return {};
    }

    Text {
        id: titleText
        anchors.top : parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        text: "Config Panel"
    }

    Item {
        id: placeholder
        anchors.top: titleText.bottom
        anchors.left: parent.left
        anchors.right: parent.right

    }

    Button {
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        text: "OK"

        onClicked: accepted()
    }
}
