import QtQuick 2.0
import Sailfish.Silica 1.0

Component {
    id: contextMenuComponent
    ContextMenu {
        property string ident
        MenuItem {
            text: storage.lang() === "ru" ? "Нравится" : "Like"
            onClicked: {
                console.log("ident is")
                console.log(ident)
                Main.rate("123", "rulez")
            }
        }

        MenuItem {
            text: storage.lang() === "ru" ? "Баян" : "Send to review"
            onClicked: {

            }
        }

        MenuItem {
            text: storage.lang() === "ru" ? "Не нравится" : "Dislike"
            onClicked: {

            }
        }
    }
}
