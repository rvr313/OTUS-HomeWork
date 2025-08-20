import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 1.4
import Qt.labs.qmlmodels 1.0
import QtQuick.Controls.Styles 1.4

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Gold Price Table")

    property int maxHeight: 24

    function getTextColor(row, col, role) {
        if (role === "datetime" || row < 0 || col < 0) {
            return "black"
        }
        var changing = tableViewId.model.getPriceMove(row, col)

        if (changing === -1) {
            return "red"
        }
        if (changing === 1) {
            return "darkgreen"
        }

        return "black"
    }

    function getTextMoveText(row, col, role) {
        if (role === "datetime" || row < 0 || col < 0) {
            return ""
        }

        var changing = tableViewId.model.getPriceMove(row, col)

        if (changing === -1) {
            return " v "
        }
        if (changing === 1) {
            return " ^ "
        }
        return " = "
    }

    function fixedTo2(number) {
        return parseFloat(number).toFixed(2)
    }

    ColumnLayout {
        id: columnLayoutId
        anchors.fill: parent
        spacing: 5


        TableView {
            id: tableViewId
            Layout.fillHeight: true
            Layout.fillWidth: true
            alternatingRowColors : false

            model: table_model

            TableViewColumn {
                role: "datetime"
                title: "Date Time"
            }
            TableViewColumn {
                role: "purchase"
                title: "Purchase Price"
            }
            TableViewColumn {
                role: "sell"
                title: "Sell Price"
            }


            headerDelegate: Rectangle{
                color: "lightgray"
                width: 100;
                height: 40
                border.color: "black"

                Text{
                    anchors.centerIn : parent
                    text: styleData.value
                    font.pixelSize: 15
                    font.italic: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            rowDelegate: Rectangle {
                height: maxHeight // problem text protrudes out of the row
                color: "white"
                anchors.leftMargin: 2

            }
            itemDelegate: Rectangle{
                id: rectangle
                border.color: "black"
                border.width: 1

                Text {
                    anchors.centerIn : parent
                    anchors.leftMargin: 5
                    color: getTextColor(styleData.row, styleData.column, styleData.role)
                    width: parent.width
                    height: parent.height
                    text: getTextMoveText(styleData.row, styleData.column, styleData.role)
                    font.pixelSize: 16
                    font.bold: true
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter

                    onContentHeightChanged: {
                        if (contentHeight > maxHeight) maxHeight = contentHeight;
                    }
                }

                Text {
                    anchors.centerIn : parent
                    anchors.leftMargin: 5
                    anchors.rightMargin: 10
                    width: parent.width
                    height: parent.height
                    text: styleData.role === "datetime" ? styleData.value : fixedTo2(styleData.value)
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    onContentHeightChanged: {
                        if (contentHeight > maxHeight) maxHeight = contentHeight;
                    }
                }
            }
        }
        ConnectButton {
            id: connectButtonId
            Layout.fillWidth: true
        }
    }
}
