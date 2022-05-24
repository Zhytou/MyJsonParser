#include "Number.hpp"

namespace AtomJson
{
    Number &Number::operator=(const Number &other)
    {
        ntype = other.ntype;
        num = other.num;
        return *this;
    }

    Number &Number::operator=(Number &&other)
    {
        ntype = other.ntype;
        num = other.num;
        return *this;
    }

    bool Number::operator==(const Number &other) const
    {
        if (ntype != other.ntype)
            return false;
        switch (ntype)
        {
        case NumberType::INTEGER:
            return num.l == other.num.l;
        case NumberType::UNSIGNED:
            return num.ul == other.num.ul;
        case NumberType::FLOATPOINT:
            return num.d == other.num.d;
        default:
            return true;
        }
    }

    String Number::to_str(bool scientificNotation, bool customize, size_t customPrecision) const
    {
        std::stringstream ss;
        std::string s;
        switch (ntype)
        {
        case NumberType::INTEGER:
            ss << num.l;
            s = ss.str();
            return String(s);
        case NumberType::UNSIGNED:
            ss << num.ul;
            s = ss.str();
            return String(s);
        case NumberType::FLOATPOINT:
            if (scientificNotation)
                ss << std::scientific;
            else
            {
                // TODO: how to make the big number output in fixed point format by default
                if (customize)
                {
                    ss << std::fixed;
                    ss.precision(customPrecision);
                }
            }
            ss << num.d;
            s = ss.str();
            return String(s);
        default:
            // TODO: error check
            return String();
        }
    }

    std::ostream &operator<<(std::ostream &out, const Number &number)
    {
        switch (number.ntype)
        {
        case Number::NumberType::INTEGER:
            out << number.num.l;
            break;
        case Number::NumberType::FLOATPOINT:
            out << number.num.d;
            break;
        default:;
        }
        return out;
    }
};