/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.bashreader.htmlparse 1.0
import harbour.bashreader.FileIO 1.0
import "Main.js" as Main


Page {
    id: pageQuotes
    property string pageName
    property string urlToDownload
    property bool loadMore
    property bool downloaded: false
    property Item contextMenu
    property bool retryCurl : true
    property alias listModel : listModelQuotes

    HtmlParse {
        id: parser
    }

    FileIO {
        id: fileToSave
        onError: console.log(msg)
    }

    InfoPopup {
        id: infoPopup
    }

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        running: downloaded === false
        size: BusyIndicatorSize.Large
    }

    Button {
        id: loadCache
        anchors.centerIn: parent
        anchors.verticalCenterOffset: 200
        visible: false
        opacity: 0.0
        text: storage.lang() === "eng" ? "Load from cache" : "Загрузить из кэша"
        NumberAnimation on opacity {
            id: animation
            to: 1.0
            duration: 1000
            running: false
        }

        Component.onCompleted: timer.showBtnLoadCache.connect(function() {
            if (!pageQuotes.downloaded && Main.urlExist(urlToDownload)) {
                loadCache.visible = true
                animation.start()
            }
        })
        onClicked: Main.loadingFile(urlToDownload)
    }

    Timer {
        id: timer
        interval: 3000
        running: true
        onTriggered: showBtnLoadCache()
        signal showBtnLoadCache()
    }

    Label {
        id: noConnectionText
        visible: false
        y: Screen.height*0.75
        width: Screen.width
        horizontalAlignment: Text.AlignHCenter

        text: storage.lang() === "eng" ? "No internet connection" : "Нет интернет соединения"
    }

    SilicaListView {
        id: listView
        visible: downloaded === true
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: storage.lang() === "eng" ? "About" : "О программе"
                onClicked: pageStack.push(Qt.resolvedUrl("About.qml"))
            }
            MenuItem {
                text: storage.lang() === "eng" ? "Change language" : "Сменить язык"
                onClicked: {
                    storage.changleLang()

                    pageStack.previousPage().pagesModel = Main.pagesAllModels[storage.lang()]

                    pageStack.pop()
                }
            }
        }
        ListModel {
            id: listModelQuotes
        }
        model: listModelQuotes
        spacing: Theme.paddingLarge
        header: PageHeader {
            title: pageName
        }
        footer: LoadMoreButton{}
        delegate: QuoteComponent{}
        VerticalScrollDecorator {}

        Component.onCompleted: {
            Main.download(urlToDownload)
        }
    }

    Component {
        id: contextComponent
        ContextMenu {
            id: contextContexMenuComponent
            property string ident
            property int index
            MenuItem {
                text: storage.lang() === "ru" ? "Нравится" : "Like"
                onClicked: {
                    Main.rate(ident, index, "rulez")
                }
            }

            MenuItem {
                text: storage.lang() === "ru" ? "Баян" : "Send to review"
                onClicked: {
                    Main.rate(ident, index, "bayan")
                }
            }

            MenuItem {
                text: storage.lang() === "ru" ? "Не нравится" : "Dislike"
                onClicked: {
                    Main.rate(ident, index, "sux")
                }
            }
        }
    }
}


