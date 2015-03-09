/*
    Copyright (C) 2012 Dickson Leong
    This file is part of Tweetian.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.1
import Sailfish.Silica 1.0
import "Main.js" as Main

Item {
    id: root

    implicitWidth: parent.width
    height: visible ? 75 + 2*Theme.paddingMedium : Theme.paddingMedium

    Loader {
        id: buttonLoader
        anchors.centerIn: parent
        sourceComponent: visible ? loadMoreButton : undefined
    }

    Component {
        id: loadMoreButton

        Button {
            id: loadMoreBtn
            width: root.width * 0.75
            text: storage.lang() === "ru" ? "Хочу еще!" : "Load more"
            onClicked: {
                if (pageQuotes.pageName === "Random") {
                    Main.download("http://bash.org/?random")
                } else {
                    Main.download(parser.wantMore())
                }
            }
        }
    }
}
