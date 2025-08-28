import QtQuick 2.12


Rectangle {
    color: "lightgray"
    implicitHeight: 40
    implicitWidth: 100;
    border.color: "black"
    Text{
        anchors.centerIn : parent
        font.pixelSize: 15
        font.italic: true
        text: display
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
