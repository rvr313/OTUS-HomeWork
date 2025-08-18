import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 1.4
import Qt.labs.qmlmodels 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Gold Price Table")

    ColumnLayout {
        id: columnLayoutId
        anchors.fill: parent
        spacing: 5

        TableView {
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

            id: tableViewId
            Layout.fillHeight: true
            Layout.fillWidth: true

            model: table_model
        }

        ConnectButton {
            id: connectButtonId
            Layout.fillWidth: true
        }
    }
}
