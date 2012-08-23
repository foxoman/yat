import QtQuick 2.0

import org.yat 1.0

TerminalItem {
    id: terminal
    width: 800
    height: 600
    property font font: screen.font;

    property real fontWidth: screen.charWidth;
    property real fontHeight: screen.lineHeight;

    onWidthChanged: {
        setTerminalWidth();
    }
    onHeightChanged: {
        setTerminalHeight();
    }

    onFontHeightChanged: {
        setTerminalHeight();
    }
    onFontWidthChanged: {
        setTerminalWidth();
    }

    function setTerminalWidth() {
        if (fontWidth > 0) {
            var pty_width = width / fontWidth;
            terminal.screen.setWidth(pty_width);
        } else {
            terminal.screen.setWidth(10);
        }
    }

    function setTerminalHeight() {
        if (fontHeight > 0) {
            var pty_height = height / fontHeight;
            terminal.screen.setHeight(pty_height);
        }
    }
    Rectangle {
        anchors.fill: parent
        color: "black"

        TerminalScreen {
            anchors.fill: parent
            terminalScreen: terminal.screen
        }
    }

}