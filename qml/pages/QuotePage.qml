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
    property int pageMargin: 50

    InfoPopup {
        id: infoPopup
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height + 2 * pageMargin
        contentWidth: Screen.width

        Column {
            x: Theme.paddingLarge
            y: Theme.paddingLarge + pageMargin
            spacing: Theme.paddingMedium
            id: column
            Row {
                id: rowTop
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
                    font.underline: true
                    text: "#"+id
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
}
