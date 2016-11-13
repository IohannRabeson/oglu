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

        constexpr StrongInteger() :
            m_value(T{0})
        {
        }

        constexpr StrongInteger(T value) :
			m_value(value)
		{
		}

        template <class U>
        constexpr explicit StrongInteger(U value) :
            m_value(value)
        {
            static_assert(std::is_floating_point<U>::value == false, "U can't be floating point type");
        }

        constexpr StrongInteger<T, Tag>& operator = (T value)
		{
			m_value = value;
			return *this;
		}

        //////////////////////////////////////////////////////////////
		operator T()
		{
			return m_value;
		}

		operator T() const
		{
			return m_value;
		}

        //////////////////////////////////////////////////////////////
        friend bool operator == (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right)
		{
			return left.m_value == right.m_value;
		}

        friend bool operator != (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right)
		{
			return left.m_value != right.m_value;
		}

        friend bool operator <= (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right)
		{
			return left.m_value <= right.m_value;
		}

        friend bool operator >= (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right)
		{
			return left.m_value >= right.m_value;
		}

        friend bool operator == (StrongInteger<T, Tag> left, T right)
        {
            return left.m_value == right;
        }

        friend bool operator != (StrongInteger<T, Tag> left, T right)
        {
            return left.m_value != right;
        }

        friend bool operator <= (StrongInteger<T, Tag> left, T right)
        {
            return left.m_value <= right;
        }

        friend bool operator >= (StrongInteger<T, Tag> left, T right)
        {
            return left.m_value >= right;
        }

        //////////////////////////////////////////////////////////////
        StrongInteger<T, Tag>& operator ++ ()
        {
            ++m_value;
            return *this;
        }

        StrongInteger<T, Tag> operator ++ (int)
        {
            auto copy = *this;

            ++m_value;
            return copy;
        }

        StrongInteger<T, Tag>& operator -- ()
        {
            --m_value;
            return *this;
        }

        StrongInteger<T, Tag> operator -- (int)
        {
            auto copy = *this;

            --m_value;
            return copy;
        }

        //////////////////////////////////////////////////////////////
        StrongInteger<T, Tag>& operator += (StrongInteger<T, Tag> right)
        {
            m_value += right.m_value;
            return *this;
        }

        StrongInteger<T, Tag>& operator -= (StrongInteger<T, Tag> right)
        {
            m_value -= right.m_value;
            return *this;
        }

        StrongInteger<T, Tag>& operator *= (StrongInteger<T, Tag> right)
        {
            m_value *= right.m_value;
            return *this;
        }

        StrongInteger<T, Tag>& operator /= (StrongInteger<T, Tag> right)
        {
            m_value /= right.m_value;
            return *this;
        }

        StrongInteger<T, Tag>& operator %= (StrongInteger<T, Tag> right)
        {
            m_value %= right.m_value;
            return *this;
        }

        StrongInteger<T, Tag>& operator &= (StrongInteger<T, Tag> right)
        {
            m_value &= right.m_value;
            return *this;
        }

        StrongInteger<T, Tag>& operator |= (StrongInteger<T, Tag> right)
        {
            m_value |= right.m_value;
            return *this;
        }

        StrongInteger<T, Tag>& operator ^= (StrongInteger<T, Tag> right)
        {
            m_value ^= right.m_value;
            return *this;
        }

        //////////////////////////////////////////////////////////////
        StrongInteger<T, Tag>& operator += (T right)
        {
            m_value += right;
            return *this;
        }

        StrongInteger<T, Tag>& operator -= (T right)
        {
            m_value -= right;
            return *this;
        }

        StrongInteger<T, Tag>& operator *= (T right)
        {
            m_value *= right;
            return *this;
        }

        StrongInteger<T, Tag>& operator /= (T right)
        {
            m_value /= right;
            return *this;
        }

        StrongInteger<T, Tag>& operator %= (T right)
        {
            m_value %= right;
            return *this;
        }

        StrongInteger<T, Tag>& operator &= (T right)
        {
            m_value &= right;
            return *this;
        }

        StrongInteger<T, Tag>& operator |= (T right)
        {
            m_value |= right;
            return *this;
        }

        StrongInteger<T, Tag>& operator ^= (T right)
        {
            m_value ^= right;
            return *this;
        }

        //////////////////////////////////////////////////////////////
        friend StrongInteger<T, Tag> operator + (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right)
        {
            return StrongInteger<T, Tag>{left.m_value + right.m_value};
        }

        friend StrongInteger<T, Tag> operator - (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right)
        {
            return StrongInteger<T, Tag>{left.m_value - right.m_value};
        }

        friend StrongInteger<T, Tag> operator * (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right)
		{
            return StrongInteger<T, Tag>{left.m_value * right.m_value};
		}

        friend StrongInteger<T, Tag> operator / (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right)
		{
            return StrongInteger<T, Tag>{left.m_value / right.m_value};
		}

        friend StrongInteger<T, Tag> operator % (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right)
		{
            return StrongInteger<T, Tag>{left.m_value / right.m_value};
		}

        friend StrongInteger<T, Tag> operator & (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right)
		{
            return StrongInteger<T, Tag>{left.m_value & right.m_value};
		}

        friend StrongInteger<T, Tag> operator | (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right)
		{
            return StrongInteger<T, Tag>{left.m_value | right.m_value};
		}

        friend StrongInteger<T, Tag> operator ^ (StrongInteger<T, Tag> left, StrongInteger<T, Tag> right)
		{
            return StrongInteger<T, Tag>{left.m_value ^ right.m_value};
		}

        //////////////////////////////////////////////////////////////
        friend StrongInteger<T, Tag> operator + (StrongInteger<T, Tag> left, T right)
        {
            return StrongInteger<T, Tag>{left.m_value + right};
        }

        friend StrongInteger<T, Tag> operator - (StrongInteger<T, Tag> left, T right)
        {
            return StrongInteger<T, Tag>{left.m_value - right};
        }

        friend StrongInteger<T, Tag> operator * (StrongInteger<T, Tag> left, T right)
        {
            return StrongInteger<T, Tag>{left.m_value * right};
        }

        friend StrongInteger<T, Tag> operator / (StrongInteger<T, Tag> left, T right)
        {
            return StrongInteger<T, Tag>{left.m_value / right};
        }

        friend StrongInteger<T, Tag> operator % (StrongInteger<T, Tag> left, T right)
        {
            return StrongInteger<T, Tag>{left.m_value / right};
        }

        friend StrongInteger<T, Tag> operator & (StrongInteger<T, Tag> left, T right)
        {
            return StrongInteger<T, Tag>{left.m_value & right};
        }

        friend StrongInteger<T, Tag> operator | (StrongInteger<T, Tag> left, T right)
        {
            return StrongInteger<T, Tag>{left.m_value | right};
        }

        friend StrongInteger<T, Tag> operator ^ (StrongInteger<T, Tag> left, T right)
        {
            return StrongInteger<T, Tag>{left.m_value ^ right};
        }

        StrongInteger<T, Tag> operator ~ ()
		{
            return StrongInteger<T, Tag>{~m_value};
		}
	private:
		T m_value;
	};

    template <class T>
    struct UnderlyingTypeImp;

    template <class T>
    struct UnderlyingTypeImp<StrongInteger<T>>
    {
        using Type = T;
    };

    template <class T>
    struct UnderlyingType : public UnderlyingTypeImp<T>
    {
    };
}

#endif
