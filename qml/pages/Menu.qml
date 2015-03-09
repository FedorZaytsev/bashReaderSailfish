
import QtQuick 2.0
import Sailfish.Silica 1.0
import "Main.js" as Main

Page {
    id: pageMenu
    property var pagesModel: Main.pagesAllModels[storage.lang()]

    SilicaListView {
        id: menuListView
        anchors.fill: parent
        model: pagesModel
        delegate: BackgroundItem {
            width: menuListView.width
            height: Screen.height / pagesModel.length
            Label {
                id: firstName

                property var modelData: model.modelData ? model.modelData : model

                text: modelData.title
                color: highlighted ? Theme.highlightColor : Theme.primaryColor
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignHCenter
                x: Theme.paddingLarge
                width: Screen.width - 2* Theme.paddingLarge
                font.pixelSize: Theme.fontSizeExtraLarge
            }
            onClicked: pageStack.push(Qt.resolvedUrl("ListElements.qml"),{pageName: modelData.title, urlToDownload: modelData.url, loadMore: modelData.loadMore})
        }
        PullDownMenu {
            MenuItem {
                id: menuItem1

                function updateLang() {
                    menuItem1.text = storage.lang() === "eng" ? "About" : "О программе"
                }
                Component.onCompleted: {
                    updateLang();
                }

                text: "About"
                onClicked: pageStack.push(Qt.resolvedUrl("About.qml"))
            }
            MenuItem {
                id: menuItem2

                function updateLang() {
                    menuItem2.text = storage.lang() === "eng" ? "Change language" : "Сменить язык"
                }
                Component.onCompleted: {
                    updateLang();
                }
                text: "Change language"
                onClicked: {
                    storage.changleLang()

                    pagesModel = Main.pagesAllModels[storage.lang()]

                    menuItem1.updateLang()
                    menuItem2.updateLang()
                }
            }
        }
    }
}


