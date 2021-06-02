//
// Created by honza on 30.05.21.
//

#include "CExtendedChar.h"

using namespace std;

const char *CExtendedChar::ColorCode(EColor color) {
    switch (color) {
        case EColor::BLACK:
            return "\u001b[30m";
        case EColor::RED:
            return "\u001b[31m";
        case EColor::GREEN:
            return "\u001b[32m";
        case EColor::YELLOW:
            return "\u001b[33m";
        case EColor::BLUE:
            return "\u001b[34m";
        case EColor::MAGENTA:
            return "\u001b[35m";
        case EColor::CYAN:
            return "\u001b[36m";
        case EColor::WHITE:
            return "\u001b[37m";
        case EColor::BG_BLACK:
            return "\u001b[40m";
        case EColor::BG_RED:
            return "\u001b[41m";
        case EColor::BG_GREEN:
            return "\u001b[42m";
        case EColor::BG_YELLOW:
            return "\u001b[43m";
        case EColor::BG_BLUE:
            return "\u001b[44m";
        case EColor::BG_MAGENTA:
            return "\u001b[45m";
        case EColor::BG_CYAN:
            return "\u001b[46m";
        case EColor::BG_WHITE:
            return "\u001b[47m";
        default:
            return "\u001b[0m";
    }
}

CExtendedChar &CExtendedChar::Char(char ch) {
    m_Char = ch;
    return *this;
}

ostream &operator<<(ostream &out, const CExtendedChar &self) {
    if (self.m_BgColor != EColor::DEFAULT)
        out << CExtendedChar::ColorCode(self.m_BgColor);
    if (self.m_Color != EColor::DEFAULT)
        out << CExtendedChar::ColorCode(self.m_Color);
    if (self.m_Bold)
        out << "\u001b[1m";
    return out << self.m_Char << "\u001b[0m";
}
