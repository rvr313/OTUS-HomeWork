import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls
import Qt.labs.qmlmodels 1.0

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Gold Price Table")

    ColumnLayout {
        id: columnLayoutId
        spacing: 0
        anchors.fill: parent

        HorizontalHeaderView {
            id: hHeaderId
            syncView: tableViewId
            clip: true
            delegate: HorizontalHeaderDelegate {}
        }

        TableView {
            id: tableViewId
            Layout.fillHeight: true
            Layout.fillWidth: true

            model: table_model

            // delegate: DelegateChooser {
            //     DelegateChoice {
            //         delegate: ColumnTextItem {}
            //     }
            // }
            delegate: ColumnTextItem {}
        }
        ConnectButton {
            id: connectButtonId
            Layout.fillWidth: true
        }
    }
}
