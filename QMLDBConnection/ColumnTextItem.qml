import QtQuick 2.12

Rectangle {
    property alias text: itemText.text

    implicitHeight: 24
    implicitWidth: 150
    border.color: "black"
    border.width: 1

    Text {
        anchors.centerIn : parent
        anchors.leftMargin: 5
        color: model.color
        width: parent.width
        height: parent.height
        text: model.movement
        font.pixelSize: 16
        font.bold: true
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: itemText
        anchors.centerIn : parent
        anchors.leftMargin: 5
        anchors.rightMargin: 10
        width: parent.width
        height: parent.height
        text: model.text
        font.pixelSize: 14
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
