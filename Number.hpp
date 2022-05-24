#ifndef ATOMJSON_NUMBER_HPP
#define ATOMJSON_NUMBER_HPP

#include <iostream>
#include <sstream>
#include <cstring>

#include "String.hpp"

namespace AtomJson
{
    class Number
    {
        union SubNum
        {
            unsigned long ul;
            long l;
            double d;

            SubNum() { std::memset(this, 0, sizeof(SubNum)); }

            SubNum(const int &ii)
            {
                std::memset(this, 0, sizeof(SubNum));
                this->l = ii;
            }

            SubNum(const long &ll)
            {
                std::memset(this, 0, sizeof(SubNum));
                this->l = ll;
            }

            SubNum(const unsigned &uu)
            {
                std::memset(this, 0, sizeof(SubNum));
                this->ul = uu;
            }

            SubNum(const unsigned long &ull)
            {
                std::memset(this, 0, sizeof(SubNum));
                this->ul = ull;
            }

            SubNum(const double &dd)
            {
                std::memset(this, 0, sizeof(SubNum));
                this->d = dd;
            }

            SubNum(const SubNum &other) { std::memcpy(this, &other, sizeof(SubNum)); }

            SubNum(SubNum &&other) { std::memcpy(this, &other, sizeof(SubNum)); }

            SubNum &
            operator=(const SubNum &other)
            {
                std::memcpy(this, &other, sizeof(SubNum));
                return *this;
            }

            SubNum &operator=(SubNum &&other) = delete;

            ~SubNum() {}
        };

        enum NumberType
        {
            _NULL,
            INTEGER,
            UNSIGNED,
            FLOATPOINT,
        };

    public:
        /**
         * @brief Construct a new Number object
         *
         */
        Number() : ntype(NumberType::_NULL) {}

        /**
         * @brief Construct a new Number object
         *
         * @param ii
         */
        Number(const int &ii) : num(ii), ntype(NumberType::INTEGER) {}

        /**
         * @brief Construct a new Number object
         *
         * @param ll
         */
        Number(const long &ll) : num(ll), ntype(NumberType::INTEGER) {}

        /**
         * @brief Construct a new Number object
         *
         * @param uu
         */
        Number(const unsigned &uu) : num(uu), ntype(NumberType::UNSIGNED) {}

        /**
         * @brief Construct a new Number object
         *
         * @param ul
         */
        Number(const unsigned long &ul) : num(ul), ntype(NumberType::UNSIGNED) {}

        /**
         * @brief Construct a new Number object
         *
         * @param ff
         */
        Number(const float &ff) : num(ff), ntype(NumberType::INTEGER) {}

        /**
         * @brief Construct a new Number object
         *
         * @param dd
         */
        Number(const double &dd) : num(dd), ntype(NumberType::FLOATPOINT) {}

        /**
         * @brief Construct a new Number object
         *
         * @param other
         */
        Number(const Number &other) : num(other.num), ntype(other.ntype) {}

        /**
         * @brief Construct a new Number object
         *
         * @param other
         */
        Number(Number &&other) : num(other.num), ntype(other.ntype) {}

        /**
         * @brief
         *
         * @param other
         * @return Number&
         */
        Number &operator=(const Number &other);

        /**
         * @brief
         *
         * @param other
         * @return Number&
         */
        Number &operator=(Number &&other);

        /**
         * @brief Destroy the Number object
         *
         */
        ~Number() {}

        /**
         * @brief Check if the Number objects are the same
         *
         * @param other
         * @return bool
         */
        bool operator==(const Number &other) const;

        /**
         * @brief
         *
         * @param scientificNotation
         * @param customize
         * @param customPrecision
         * @return String
         */
        String to_str(bool scientificNotation, bool customize, size_t customPrecision = 0) const;

        /**
         * *Overload the output operator
         * @brief Insert the Number object into the standard template library outstream
         *
         * @param out
         * @param num
         * @return std::ostream&
         */
        friend std::ostream &operator<<(std::ostream &out, const Number &number);

    private:
        SubNum num;
        NumberType ntype;
    };
}; // namespace AtomJson

#endif