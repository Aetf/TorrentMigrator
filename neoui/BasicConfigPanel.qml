import QtQuick 2.3
import QtQuick.Controls 1.2

Item {
    id: root
    implicitHeight: childrenRect.height
    implicitWidth: childrenRect.width

    signal accepted()

    function getConfigedArgs() {
        return {};
    }
}
