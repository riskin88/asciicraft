//
// Created by honza on 30.05.21.
//

/**
 * @borrowedFrom Ing. David Bernhauer
 */

#pragma once

#include <ostream>
#include "EColor.h"


class CExtendedChar {
public:
    explicit CExtendedChar(char ch, EColor color = EColor::DEFAULT, EColor bg_color = EColor::DEFAULT,
                           bool bold = false)
            : m_Char(ch), m_Color(color), m_BgColor(bg_color), m_Bold(bold) {}

    /** setter for m_Char */
    CExtendedChar &Char(char ch);

    /**
     * sends correctly formatted self into out
     * @param out
     * @param self
     * @return out
     */
    friend std::ostream &operator<<(std::ostream &out, const CExtendedChar &self);

private:
    char m_Char;
    EColor m_Color = EColor::DEFAULT;
    EColor m_BgColor = EColor::DEFAULT;
    bool m_Bold;

    /**
     * converts color to ANSI color code string
     * @param color
     * @return ANSI color code
     */
    static const char *ColorCode(EColor color);

};


