var coverLabelText = ""
var pagesAllModels = {
    ru: [
        { title: "Новые",           url: "http://bash.im",              loadMore: true  },
        { title: "Случайные",       url: "http://bash.im/random",       loadMore: true  },
        { title: "Лучшие",          url: "http://bash.im/best",         loadMore: false },
        { title: "По рейтингу",     url: "http://bash.im/byrating",     loadMore: true  },
        { title: "Бездна",          url: "http://bash.im/abyss",        loadMore: false },
        { title: "Топ Бездны",      url: "http://bash.im/abysstop",     loadMore: false },
        { title: "Лучшее Бездны",   url: "http://bash.im/abyssbest",    loadMore: false }
    ],
    eng: [
        { title: "Latest",          url: "http://bash.org/?latest",     loadMore: false },
        { title: "Browse",          url: "http://bash.org/?browse",     loadMore: true  },
        { title: "Random",          url: "http://bash.org/?random",     loadMore: true  },
        { title: "Top",             url: "http://bash.org/?top",        loadMore: false }
    ]
}


function getCoverText(text) {
    if (text.length>85) {
        return text.substring(0,85)+"..."
    } else {
        return text
    }
}

function canBeANumber(arg) {
    return !isNaN(arg)
}

function onDownloaded(data) {
    pageQuotes.downloaded = true
    loadCache.visible = false
    if (storage.lang() === "ru") {
        parser.parseRu(data);
    } else {
        parser.parseEng(data)
    }
    for (var i=0;i<parser.count();i++) {
        var color = "white"
        if (canBeANumber(parser.rating(i))) {
            color = (+parser.rating(i))>0?"green":"red"
        }

        listModelQuotes.append({  rating: parser.rating(i),
                            date: parser.date(i),
                            ident: parser.id(i),
                            color_rating: color,
                            index: i,
                            quote: parser.text(i)})
    }
    loadBtn()

    rootElement.coverText = getCoverText(parser.text(Math.floor(Math.random() * parser.count())))
}

function urlExist(url) {
    fileToSave.source = getFilepath(url)
    return fileToSave.exist()
}

function loadingFile(url) {
    if (pageQuotes.downloaded) {
        if (storage.lang()==="ru") {
            infoPopup.show("Нет интернет соединения",3)
        } else {
            infoPopup.show("No internet connection",3)
        }
        return
    }

    fileToSave.source = getFilepath(url)
    if (fileToSave.exist()) {
        if (storage.lang()==="ru") {
            infoPopup.show("Нет интернет соединения, страница загружена из кэша",3)
        } else {
            infoPopup.show("No internet connection, page was loaded from cache",3)
        }
        onDownloaded(fileToSave.read())
    } else {
        if (listModelQuotes.count===0) {
            noConnectionText.visible = true
        }
        if (storage.lang()==="ru") {
            infoPopup.show("Нет интернет соединения",3)
        } else {
            infoPopup.show("No internet connection",3)
        }
    }
}

function getFilepath(filename) {
    var str = testgetFilename(filename).replace(new RegExp("http://","g"),"").replace(new RegExp("/",'g'),".") + ".sdata"
    return str
}

function testgetFilename(filename) {
    if (filename === "") {
        return "new"
    } else if (filename[0] === "/") {
        return filename.substring(1,filename.length)
    } else {
        return filename
    }
}

function loadBtn() {
    if (pageQuotes.loadMore) {
        listView.footerItem.visible = true
    } else {
        listView.footerItem.visible = false
    }
}

function updateRating(index,action) {

    //if in ListElements
    var listModel = pageStack.currentPage.listModel
    var singleQuotePage = false
    if (!listModel) {
        listModel = pageStack.previousPage().listModel
        singleQuotePage = true
    }

    var rate_str = listModel.get(index).rating
    if (canBeANumber(rate_str)) {
        var rate = +rate_str
        if (action === "rulez") rate++
        else if (action === "sux") rate--
        listModel.setProperty(index,"rating",""+rate)
        if (singleQuotePage) {
            pageStack.currentPage.rating = ""+rate
        }
    }
}

function sendRequest(url,callback,callbackFail) {
    console.assert(typeof url === "string")
    console.assert(typeof callback === "function")
    console.assert(typeof callbackFail === "function")
    var xmlhttp = new XMLHttpRequest()

    xmlhttp.open('GET', url, true)
    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
            callback(xmlhttp.responseText)
        }
        if (xmlhttp.status !== 200) {
            callbackFail()
        }
    }
    xmlhttp.send(null);
}

function rateRU(ident, index, action) {
    if (!storage.isRatedRU(ident) ) {

        updateRating(index,action)

        storage.addRatedRU(ident)
        storage.rateRU(ident,action)

    } else {
        infoPopup.show("You are already rated that quote",3)
    }
}

function convertAction(act) {
    if (act==="rulez") {
        return "rox"
    } else if (act==="sux") {
        return "sox"
    } else if (act==="bayan") {
        return "sux"
    } else {
        console.error("convertAction err: ",act)
    }
    return "rox"
}

function rateENG(ident, index, action) {
    if (!storage.isRatedENG(ident) ) {

        updateRating(index,action);

        var url = "http://bash.org/?le="+parser.rate_key(index)+"&"+convertAction(action)+"="+ident
        storage.addRatedENG(ident)

        sendRequest(url, function(responseText) {
        }, function() {
            storage.rateLaterENG(url)
        })

    } else {
        infoPopup.show("You are already rated that quote",3)
    }
}

function rate(ident, index, action) {
    if (storage.lang() === "ru") {
        rateRU(ident,index,action)
    } else {
        rateENG(ident,index,action)
    }
}

function tryToRateUnrated() {
    for (var i=0;i<storage.rateSize();i++) {
        var url = storage.rateUrl(i)
        sendRequest(url,function(){
                storage.deleteRateElement(i)
        },function(){});
    }
}

function download(url) {
    sendRequest(url, function(responseText) {
        onDownloaded(responseText);
        tryToRateUnrated();
        fileToSave.source = getFilepath(url)
        fileToSave.write(responseText)
    }, function() {
        loadingFile(pageQuotes.urlToDownload)
    })

}
