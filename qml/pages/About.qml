import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: aboutPage

    width: Screen.width
    height: Screen.height
/*
    IconTextSwitch {
        y: 200
        width: Screen.width
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Big text"
        //icon.source: "image://theme/icon-m-gps"
        description: "Use bigger font size"
        //onCheckedChanged: locationSettings.locationEnabled = checked
    }
*/
    Label {
        id: aboutPageLabel
        width: Screen.width
        height: Screen.height
        wrapMode: Text.WordWrap
        anchors.fill: parent
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        Component.onCompleted: {
            if (storage.lang()==="eng") {
                aboutPageLabel.text = "Simple Bash Reader<br>by Fedor Zaytsev<br><br>Source code can be found at<br><a href=\"https://github.com/rusphantom/bashReaderSailfish/\">Github</a>"
            } else {
                aboutPageLabel.text = "Bash Reader<br>Автор Федор Зайцев<br><br>Исходный код можно найти на <br><a href=\"https://github.com/rusphantom/bashReaderSailfish/\">Github</a>"
            }
        }
        onLinkActivated: {
            Qt.openUrlExternally(link)
        }
    }
}
