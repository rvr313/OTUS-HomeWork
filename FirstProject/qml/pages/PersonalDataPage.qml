import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    objectName: "personalDataPage"
    allowedOrientations: Orientation.All

    Column {
        id: layout
        objectName: "layout"
        width: parent.width
        DialogHeader {
            acceptText: qsTr("Сохранить")
            cancelText: qsTr("Отменить")
        }
        PageHeader {
            objectName: "pageHeader"
            title: qsTr("Персональные данные")
        }

        TextField {
            label: qsTr("Фамилия")
            placeholderText: qsTr("Фамилия")
            width: parent.width
        }
        TextField {
            label: qsTr("Имя")
            placeholderText: qsTr("Имя")
            width: parent.width
        }
        TextField {
            label: qsTr("Отчество")
            placeholderText: qsTr("Отчество")
            width: parent.width
        }
        ComboBox {
            label: "Пол"
            description: "Укажите ваш пол"
            currentItem: null
            menu: ContextMenu {
                MenuItem { text: "Женский" }
                MenuItem { text: "Мужской" }
            }
        }
        Button {
            id: button
            width: parent.width
            text: "Укажите ваш день рождения"

            onClicked: {
                var dialog = pageStack.push(pickerComponent, {
                                                date: undefined
                                            })
                dialog.accepted.connect(function() {
                    button.text = "День рождения: " + dialog.dateText
                })
            }

            Component {
                id: pickerComponent
                DatePickerDialog {}
            }
        }
        TextField {
            id: email
            label: qsTr("Email")
            placeholderText: qsTr("Email")
            width: parent.width
            leftItem: Icon {
                source: "image://theme/icon-m-mail"
            }
            inputMethodHints: Qt.ImhEmailCharactersOnly | Qt.ImhNoPredictiveText
        }
        TextSwitch {
            text: "Подтвердите согласие на обработку персональных данных"
            checked: true
        }
        TextSwitch {
            text: "Подтвердите согласие на рассылку"
            checked: true
        }
    }
}
