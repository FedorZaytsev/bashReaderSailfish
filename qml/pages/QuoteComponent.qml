import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: delegate
    property bool menuOpen: contextMenu != null && contextMenu.parent === delegate
    height: menuOpen ? contextMenu.height + topRow.height + quoteText.height : topRow.height + quoteText.height
    Item  {
        Column {
            Row {
                id: topRow
                x: Theme.paddingLarge
                width: Screen.width - 2*Theme.paddingLarge

                Label {
                    x: 0
                    width: parent.width/2
                    font.pixelSize: Theme.fontSizeTiny
                    color: color_rating
                    text: rating
                }
                Label {
                    horizontalAlignment: Text.AlignRight
                    x: parent.width/2
                    width: parent.width/2
                    font.pixelSize: Theme.fontSizeTiny
                    text: date
                }
            }

            Label {
                id: quoteText
                x: Theme.paddingLarge
                width: Screen.width - 2*Theme.paddingLarge
                text: quote
                wrapMode: TextEdit.WordWrap
                font.pixelSize: Theme.fontSizeSmall
            }
        }
    }

    onClicked: {
        pageStack.push(Qt.resolvedUrl("QuotePage.qml"),{
                           quote: quote,
                           date: date,
                           rating: rating,
                           id: ident,
                           color_rating: color_rating,
                           index: index
                       })
    }


    onPressAndHold: {
        contextMenu = contextComponent.createObject(listView,{ident:ident, index: index})

        contextMenu.show(delegate);
    }
}
