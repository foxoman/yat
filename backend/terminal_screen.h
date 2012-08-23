/**************************************************************************************************
* Copyright (c) 2012 Jørgen Lind
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
* associated documentation files (the "Software"), to deal in the Software without restriction,
* including without limitation the rights to use, copy, modify, merge, publish, distribute,
* sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
* NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
* OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
***************************************************************************************************/

#ifndef TERMINALSCREEN_H
#define TERMINALSCREEN_H

#include <QObject>

#include "text_segment.h"
#include "color_palette.h"
#include "parser.h"
#include "yat_pty.h"
#include "update_action.h"

#include <QtCore/QPoint>
#include <QtCore/QSize>
#include <QtCore/QVector>
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>

class TextSegmentLine;

class TerminalScreen : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(qreal charWidth READ charWidth NOTIFY charWidthChanged)
    Q_PROPERTY(qreal lineHeight READ lineHeight NOTIFY lineHeightChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY screenTitleChanged)
    Q_PROPERTY(bool cursorVisible READ cursorVisible NOTIFY cursorVisibleChanged)
    Q_PROPERTY(bool cursorBlinking READ cursorBlinking NOTIFY cursorBlinkingChanged)

public:
    explicit TerminalScreen(QObject *parent = 0);
    ~TerminalScreen();
    
    Q_INVOKABLE void setHeight(int height);
    Q_INVOKABLE int height() const;
    Q_INVOKABLE void setWidth(int width);
    Q_INVOKABLE int width() const;


    QFont font() const;
    void setFont(const QFont &font);
    qreal charWidth() const;
    qreal lineHeight() const;

    void resetStyle();
    TextStyle currentTextStyle() const;
    TextStyle defaultTextStyle() const;

    Q_INVOKABLE QColor screenBackground();
    QColor defaultForgroundColor() const;
    QColor defaultBackgroundColor() const;

    QPoint cursorPosition() const;
    void moveCursorHome();
    void moveCursorTop();
    void moveCursorUp();
    void moveCursorDown();
    void moveCursorLeft();
    void moveCursorRight(int n_positions);
    void moveCursor(int x, int y);
    void setCursorVisible(bool visible);
    bool cursorVisible();
    void setBlinkingCursor(bool blinking);
    bool cursorBlinking();

    void insertAtCursor(const QString &text);

    void backspace();

    void eraseLine();
    void eraseFromCursorPositionToEndOfLine();
    void eraseFromCurrentLineToEndOfScreen();
    void eraseFromCurrentLineToBeginningOfScreen();
    void eraseToCursorPosition();
    void eraseScreen();

    void setColor(bool bold, ushort color);

    void lineFeed();

    void setTitle(const QString &title);
    QString title() const;

    Q_INVOKABLE TextSegmentLine *at(int i) const;

    Q_INVOKABLE void printScreen() const;

    Q_INVOKABLE void write(const QString &data);

    void dispatchChanges();

    void sendPrimaryDA();
    void sendSecondaryDA();

    void setCharacterMap(const QString &string);
    QString characterMap() const;

signals:
    void testSignal();

    void scrollUp(int from_line, int count);
    void scrollDown(int from_line, int count);

    void linesInserted(int count);
    void linesRemoved(int count);

    void fontChanged();
    void charWidthChanged();
    void lineHeightChanged();

    void dispatchLineChanges();
    void dispatchTextSegmentChanges();

    void screenTitleChanged();

    void cursorVisibleChanged();
    void cursorBlinkingChanged();
private:

    void readData();
    void doScrollOneLineUpAt(int line);
    void doScrollOneLineDownAt(int line);

    TextSegmentLine *line_at_cursor();

    ColorPalette m_palette;
    YatPty m_pty;
    Parser m_parser;

    QVector<TextSegmentLine *> m_screen_lines;
    QPoint m_cursor_pos;
    bool m_cursor_visible;
    bool m_cursor_blinking;

    QFont m_font;
    QFontMetricsF m_font_metrics;
    TextStyle m_current_text_style;
    QString m_title;

    QString m_character_map;

    QList<UpdateAction> m_update_actions;
};

#endif // TERMINALSCREEN_H