import QtQuick 2.0

Item {
    property QtObject terminalScreen: null

    anchors.fill: parent

    ListView {
        anchors.fill: parent
        model:  screenModel
        delegate: TerminalLine {
            id: lineDelegate
            height: terminal.fontHeight
            width: parent.width
            textLine: line
        }
        snapMode: ListView.SnapOneItem
    }

    Connections {
        id: connections

        target: terminal.screen

        onScrollUp: {
            screenModel.move(0,from_line - (count -1), count);
        }

        onScrollDown: {
            console.log("FIXME SCROLLDOWN TerminalScreen.qml");
        }

        onLinesInserted: {
            console.log("lines inserted");
            var model_size = screenModel.count;
            for (var i = 0; i < count; i++) {
                screenModel.append({
                                       "line": terminal.screen.at(model_size + i)
                                   });
            }

            resetModel();
        }

        onLinesRemoved: {
            for (var i = 0; i < count; i++) {
                screenModel.remove(0)
            }
        }
    }


    ListModel {
        id: screenModel
        Component.onCompleted:  resetModel();
    }


    function resetModel() {
        screenModel.clear();
        for (var i = 0; i < terminal.screen.height(); i++) {
            screenModel.append({
                                   "line": terminal.screen.at(i)
                               });
        }
    }

    Item {
        id: keyHandler
        focus: true
        Keys.onPressed: {
            terminal.screen.write(event.text)
            if (event.text === "?") {
                terminal.screen.printScreen()
            }
        }
    }
}