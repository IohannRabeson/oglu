/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrongInteger.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 21:06:58 by irabeson          #+#    #+#             */
/*   Updated: 2016/10/04 00:17:10 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if!defined STRONGINTEGER_HPP
# define STRONGINTEGER_HPP
# include <type_traits>

namespace oglu
{
    /*!
        \class StrongInteger
        \brief An integer with a strong type
     */
    template <class T, class Tag = void>
    class StrongInteger
    {
        static_assert(std::is_integral<T>::value, "T must be integral");
    public:
        using IntegerType = T;

        constexpr StrongInteger() noexcept :
            m_value(T{0})
        {
        }

        constexpr StrongInteger(T const& value) noexcept :
            m_value(value)
        {
        }

        constexpr StrongInteger(T const&& value) noexcept :
            m_value(std::move(value))
        {
        }

        template <class U>
        constexpr explicit StrongInteger(U value) noexcept :
            m_value(value)
        {
            static_assert(std::is_floating_point<U>::value == false, "U can't be floating point type");
        }

        constexpr StrongInteger<T, Tag> & operator = (T value) noexcept
        {
            m_value = value;
            return *this;
        }

        //////////////////////////////////////////////////////////////
        /*!
         * \brief Allow to cast to T.
         * \code
         * auto a = oglu::StrongInteger<int>{234};
         * int underlying0 = static_cast<int>(a);
         * \endcode
         */
        explicit operator T() noexcept
        {
            return m_value;
        }

        /*!
         * \brief Allow to cast to T.
         * \code
         * auto const a = oglu::StrongInteger<int>{234};
         * int const underlying0 = static_cast<int>(a);
         * \endcode
         */
        constexpr explicit operator T() const noexcept
        {
            return m_value;
        }

        //////////////////////////////////////////////////////////////
        friend bool operator == (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right) noexcept
        {
            return left.m_value == right.m_value;
        }

        friend bool operator != (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right) noexcept
        {
            return left.m_value != right.m_value;
        }

        friend bool operator < (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right) noexcept
        {
            return left.m_value < right.m_value;
        }

        friend bool operator > (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right) noexcept
        {
            return left.m_value > right.m_value;
        }

        friend bool operator <= (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right) noexcept
        {
            return left.m_value <= right.m_value;
        }

        friend bool operator >= (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right) noexcept
        {
            return left.m_value >= right.m_value;
        }

        friend bool operator == (StrongInteger<T, Tag> left, T right) noexcept
        {
            return left.m_value == right;
        }

        friend bool operator != (StrongInteger<T, Tag> left, T right) noexcept
        {
            return left.m_value != right;
        }

        friend bool operator <= (StrongInteger<T, Tag> left, T right) noexcept
        {
            return left.m_value <= right;
        }

        friend bool operator >= (StrongInteger<T, Tag> left, T right) noexcept
        {
            return left.m_value >= right;
        }

        //////////////////////////////////////////////////////////////
        StrongInteger<T, Tag>& operator ++ () noexcept
        {
            ++m_value;
            return *this;
        }

        StrongInteger<T, Tag> operator ++ (int) noexcept
        {
            auto copy = *this;

            ++m_value;
            return copy;
        }

        StrongInteger<T, Tag>& operator -- () noexcept
        {
            --m_value;
            return *this;
        }

        StrongInteger<T, Tag> operator -- (int) noexcept
        {
            auto copy = *this;

            --m_value;
            return copy;
        }

        //////////////////////////////////////////////////////////////
        StrongInteger<T, Tag>& operator += (StrongInteger<T, Tag> right) noexcept
        {
            m_value += right.m_value;
            return *this;
        }

        StrongInteger<T, Tag>& operator -= (StrongInteger<T, Tag> right) noexcept
        {
            m_value -= right.m_value;
            return *this;
        }

        StrongInteger<T, Tag>& operator *= (StrongInteger<T, Tag> right) noexcept
        {
            m_value *= right.m_value;
            return *this;
        }

        StrongInteger<T, Tag>& operator /= (StrongInteger<T, Tag> right) noexcept
        {
            m_value /= right.m_value;
            return *this;
        }

        StrongInteger<T, Tag>& operator %= (StrongInteger<T, Tag> right) noexcept
        {
            m_value %= right.m_value;
            return *this;
        }

        StrongInteger<T, Tag>& operator &= (StrongInteger<T, Tag> right) noexcept
        {
            m_value &= right.m_value;
            return *this;
        }

        StrongInteger<T, Tag>& operator |= (StrongInteger<T, Tag> right) noexcept
        {
            m_value |= right.m_value;
            return *this;
        }

        StrongInteger<T, Tag>& operator ^= (StrongInteger<T, Tag> right) noexcept
        {
            m_value ^= right.m_value;
            return *this;
        }

        //////////////////////////////////////////////////////////////
        StrongInteger<T, Tag>& operator += (T right) noexcept
        {
            m_value += right;
            return *this;
        }

        StrongInteger<T, Tag>& operator -= (T right) noexcept
        {
            m_value -= right;
            return *this;
        }

        StrongInteger<T, Tag>& operator *= (T right) noexcept
        {
            m_value *= right;
            return *this;
        }

        StrongInteger<T, Tag>& operator /= (T right) noexcept
        {
            m_value /= right;
            return *this;
        }

        StrongInteger<T, Tag>& operator %= (T right) noexcept
        {
            m_value %= right;
            return *this;
        }

        StrongInteger<T, Tag>& operator &= (T right) noexcept
        {
            m_value &= right;
            return *this;
        }

        StrongInteger<T, Tag>& operator |= (T right) noexcept
        {
            m_value |= right;
            return *this;
        }

        StrongInteger<T, Tag>& operator ^= (T right) noexcept
        {
            m_value ^= right;
            return *this;
        }

        //////////////////////////////////////////////////////////////
        friend StrongInteger<T, Tag> operator + (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right) noexcept
        {
            return StrongInteger<T, Tag>{left.m_value + right.m_value};
        }

        friend StrongInteger<T, Tag> operator - (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right) noexcept
        {
            return StrongInteger<T, Tag>{left.m_value - right.m_value};
        }

        friend StrongInteger<T, Tag> operator * (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right) noexcept
        {
            return StrongInteger<T, Tag>{left.m_value * right.m_value};
        }

        friend StrongInteger<T, Tag> operator / (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right) noexcept
        {
            return StrongInteger<T, Tag>{left.m_value / right.m_value};
        }

        friend StrongInteger<T, Tag> operator % (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right) noexcept
        {
            return StrongInteger<T, Tag>{left.m_value / right.m_value};
        }

        friend StrongInteger<T, Tag> operator & (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right) noexcept
        {
            return StrongInteger<T, Tag>{left.m_value & right.m_value};
        }

        friend StrongInteger<T, Tag> operator | (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right) noexcept
        {
            return StrongInteger<T, Tag>{left.m_value | right.m_value};
        }

        friend StrongInteger<T, Tag> operator ^ (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right) noexcept
        {
            return StrongInteger<T, Tag>{left.m_value ^ right.m_value};
        }

        //////////////////////////////////////////////////////////////
        friend StrongInteger<T, Tag> operator + (StrongInteger<T, Tag> left, T right) noexcept
        {
            return StrongInteger<T, Tag>{left.m_value + right};
        }

        friend StrongInteger<T, Tag> operator - (StrongInteger<T, Tag> left, T right) noexcept
        {
            return StrongInteger<T, Tag>{left.m_value - right};
        }

        friend StrongInteger<T, Tag> operator * (StrongInteger<T, Tag> left, T right) noexcept
        {
            return StrongInteger<T, Tag>{left.m_value * right};
        }

        friend StrongInteger<T, Tag> operator / (StrongInteger<T, Tag> left, T right) noexcept
        {
            return StrongInteger<T, Tag>{left.m_value / right};
        }

        friend StrongInteger<T, Tag> operator % (StrongInteger<T, Tag> left, T right) noexcept
        {
            return StrongInteger<T, Tag>{left.m_value / right};
        }

        friend StrongInteger<T, Tag> operator & (StrongInteger<T, Tag> left, T right) noexcept
        {
            return StrongInteger<T, Tag>{left.m_value & right};
        }

        friend StrongInteger<T, Tag> operator | (StrongInteger<T, Tag> left, T right) noexcept
        {
            return StrongInteger<T, Tag>{left.m_value | right};
        }

        friend StrongInteger<T, Tag> operator ^ (StrongInteger<T, Tag> left, T right) noexcept
        {
            return StrongInteger<T, Tag>{left.m_value ^ right};
        }

        friend StrongInteger<T, Tag> operator~ (StrongInteger<T, Tag> value) noexcept
        {
            return StrongInteger<T, Tag>{~value.m_value};
        }
    private:
        T m_value;
    };

    template <class ST>
    using UnderlyingType = typename ST::IntegerType;

    /*!
     *  Return the underlying value of a StrongInteger.
     *
     * \code
     * auto a = oglu::StrongInteger<int>{234};
     * int underlying0 = oglu::get(a);
     * \endcode
     */
    template <class ST>
    static inline UnderlyingType<ST> get(ST const& value) noexcept
    {
        return static_cast<UnderlyingType<ST>>(value);
    }
}

#endif
