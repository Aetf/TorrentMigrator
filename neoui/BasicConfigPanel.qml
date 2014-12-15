import QtQuick 2.3
import QtQuick.Controls 1.2

Column {
    id: root

    default property var contentData
    property alias title: titleText.text
    signal accepted()

    function getConfigedAccessor() {
        return {};
    }

    Text {
        id: titleText
//        anchors.top : parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        text: "Config Panel"
    }

    Item {
        id: placeholder
//        anchors.top: titleText.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        data: contentData
        implicitHeight: childrenRect.height
        implicitWidth: childrenRect.width
    }

    Button {
//        anchors.top: placeholder.bottom
        anchors.right: parent.right
//        anchors.bottom: parent.bottom

        text: "OK"

        onClicked: accepted()
    }
}
