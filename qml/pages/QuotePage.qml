import QtQuick 2.0
import Sailfish.Silica 1.0
import "Main.js" as Main

Page {
    id: pageQuotes

    property int id
    property int rating
    property string color_rating
    property string date
    property string quote
    property int index

    InfoPopup {
        id: infoPopup
    }

    Column {
        x: Theme.paddingLarge
        y: Theme.paddingLarge + 50
        spacing: Theme.paddingMedium
        Row {
            spacing: Theme.paddingLarge
            Label {
                id: ratingLabel
                width: (Screen.width - 3*Theme.paddingLarge)/2
                text: rating
                color: color_rating
                font.pixelSize: Theme.fontSizeSmall
            }
            Label {
                id: identLabel
                width: (Screen.width - 3*Theme.paddingLarge)/2
                color: Theme.highlightColor
                text: "#"+id
                /*{
                    if (storage.lang() === "ru") {
                        return "<a href=\"http://bash.im/quote/"+id+"\">#"+id+"</a>"
                    } else {
                        return "<a href=\"http://bash.org/?"+id+"\">#"+id+"</a>"
                    }
                }*/
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (storage.lang() === "ru") {
                            Qt.openUrlExternally("http://bash.im/quote/"+id)
                        } else {
                            Qt.openUrlExternally("http://bash.org/?"+id)
                        }
                    }
                }

                horizontalAlignment: Text.AlignRight
                font.pixelSize: Theme.fontSizeSmall
            }
        }
        Label {
            id: quoteLabel
            text: quote
            wrapMode: TextEdit.WordWrap
            font.pixelSize: Theme.fontSizeMedium
            width: Screen.width - 2*Theme.paddingLarge
            MouseArea {
                anchors.fill: parent
                onPressAndHold: {
                    console.log("coping text")
                    Clipboard.text = quote
                    if (storage.lang() === "ru") {
                        infoPopup.show("Copied!",2)
                    } else {
                        infoPopup.show("Скопировано!",2)
                    }
                }
            }
        }
        Row {
            y: Theme.paddingMedium
            spacing: Theme.paddingLarge
            Button {
                width: (Screen.width - 4*Theme.paddingLarge)/3
                text: "<b>—</b>"
                onClicked: {
                    Main.rate(id, index, "sux")
                }
            }
            Button {
                width: (Screen.width - 4*Theme.paddingLarge)/3
                text: "<b>[:||||:]</b>"
                onClicked: {
                    Main.rate(id, index, "bayan")
                }
            }
            Button {
                width: (Screen.width - 4*Theme.paddingLarge)/3
                text: "<b>+</b>"
                onClicked: {
                    Main.rate(id, index, "rulez")
                }
            }
        }

    }


}
