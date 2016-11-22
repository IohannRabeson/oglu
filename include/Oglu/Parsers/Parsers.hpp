/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 00:41:58 by irabeson          #+#    #+#             */
/*   Updated: 2016/11/23 00:42:02 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if!defined PARSERS_HPP
# define PARSERS_HPP
# include <string>
# include <type_traits>

namespace oglu
{
    struct ParserState
    {
        using String = std::basic_string<char>;
        using Iterator = typename String::const_iterator;
    public:
        ParserState(Iterator begin, Iterator end, bool isOk);
        ParserState(ParserState const& other);

        char current()const;

        Iterator end()const;

        bool advance();

        bool isOk()const;
        bool canAdvance()const;
        bool matchCurrent(char c)const;

        template <typename P>
        bool matchCurrent(P&& predicate)const
        {
            // TODO: ensure m_isOk == true
            bool result = false;

            if (m_current != m_end && predicate(*m_current))
            {
                result = true;
            }
            return result;
        }

        void setError();
    private:
        Iterator m_end;
        Iterator m_current;
        bool m_isOk;
    };

    namespace details
    {
        enum class NumericType
        {
            IntegralPoint,
            FloatingPoint,
            NonNumeric
        };

        template <typename T, bool IsFloat, bool IsIntegral>
        struct NumericTypeDetector : public std::integral_constant<NumericType, NumericType::NonNumeric>{};

        template <typename T>
        struct NumericTypeDetector<T, true, false> : public std::integral_constant<NumericType, NumericType::FloatingPoint>{};

        template <typename T>
        struct NumericTypeDetector<T, false, true> : public std::integral_constant<NumericType, NumericType::IntegralPoint>{};

        template <typename T, bool Signed>
        struct IntegralNumberStringConverter;

        template <typename T>
        struct IntegralNumberStringConverter<T, false>
        {
            static_assert( std::is_integral<T>::value, "T must be an integer number");

            static inline ParserState atoi(ParserState&& state, T& value)
            {
                T result = T(0);

                if (state.canAdvance() == false || state.matchCurrent([](char c){return std::isdigit(c);}) == false)
                {
                    state.setError();
                }
                else
                {
                    while (state.canAdvance())
                    {
                        if (state.matchCurrent([](char c){return std::isdigit(c);}))
                        {
                            result = result * T(10) + (state.current() - '0');
                            state.advance();
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                value = result;
                return state;
            }
        };

        template <typename T>
        struct IntegralNumberStringConverter<T, true>
        {
            static_assert( std::is_integral<T>::value, "T must be an integer number");

            static ParserState atoi(ParserState&& state, T& value)
            {
                T result = T(0);
                auto sign = false;

                if (state.canAdvance() == false)
                {
                    return state;
                }
                if (state.matchCurrent('-'))
                {
                    sign = true;
                    state.advance();
                }
                if (state.matchCurrent([](char c){return std::isdigit(c);}))
                {
                    while (state.canAdvance())
                    {
                        if (state.matchCurrent([](char c){return std::isdigit(c);}))
                        {
                            result = result * T(10) + (state.current() - '0');
                            state.advance();
                        }
                        else
                        {
                            break;
                        }
                    }
                    if (sign)
                    {
                        result = -result;
                    }
                    value = result;
                }
                else
                {
                    state.setError();
                }
                return (state);
            }
        };

        template <typename T, details::NumericType Type>
        struct StringConverter;

        template <typename T>
        struct StringConverter<T, details::NumericType::IntegralPoint>
        {
            static ParserState parse(ParserState&& state, T& value)
            {
                return IntegralNumberStringConverter<T, std::is_signed<T>::value>::atoi(std::move(state), value);
            }
        };

        template <typename T>
        struct StringConverter<T, details::NumericType::FloatingPoint>
        {
            static ParserState parse(ParserState&& state, T& value)
            {
                static_assert( std::is_floating_point<T>::value, "T must be a floating point number");

                std::int64_t result = 0;
                std::int64_t factor = 1;
                auto dot = false;
                auto sign = false;

                if (state.canAdvance() == false)
                {
                    state.setError();
                    return state;
                }
                if (state.matchCurrent('-'))
                {
                    sign = true;
                    state.advance();
                }
                while (state.canAdvance())
                {
                    if (state.matchCurrent('.'))
                    {
                        dot = true;
                    }
                    else if (state.matchCurrent([](char c){return std::isdigit(c);}))
                    {
                        if (dot)
                        {
                            factor *= 10;
                        }
                        result = result * 10 + (state.current() - '0');
                    }
                    else
                    {
                        break;
                    }
                    state.advance();
                }
                if (sign)
                {
                    result = -result;
                }
                value = (static_cast<T>(result) / factor);
                return state;
            }
        };
    }

    class Parser
    {
        using String = std::basic_string<char>;
        using Iterator = typename String::const_iterator;
    public:
        /*! \brief Begin parsing
         *  \param text Text to parse.
         *  This string must be keept alive during the complete parsing operation.
         *  \return The new parser state
         */
        static ParserState begin(std::string const& text);

        /*!
         *  \brief Extracts a value from text.
         *  \details Currently only the following types are supported:
         *  - integral and floating point numbers
         *  - char
         *  - bool
         *  \throw FormatException
         */
        template <typename T>
        static inline ParserState parse(ParserState&& state, T& value)
        {
            static constexpr bool const IsFloat = std::is_floating_point<T>::value;
            static constexpr bool const IsInteger = std::is_integral<T>::value && std::is_same<T, bool>::value == false;
            static constexpr details::NumericType NumericType = details::NumericTypeDetector<T, IsFloat, IsInteger>::value;

            return details::StringConverter<T, NumericType>::parse(std::move(state), value);
        }

        /*!
         * \brief expect Check if the expected character is present at begin.
         * \param begin Iterator on the beginning of the string parsed.
         * \param end Iterator on the ending of the string parsed.
         * \param text Expected text.
         * \return true if text is parsed, otherwise false.
         */
        static ParserState expect(ParserState&& state, char c);

        /*!
         * \brief expect Check if the expected text is present at begin.
         * \param begin Iterator on the beginning of the string parsed.
         * \param end Iterator on the ending of the string parsed.
         * \param text Expected text.
         * \return true if text is parsed, otherwise false.
         */
        static ParserState expect(ParserState&& state, String const& expectedText);

        /*! Advance while characters parsed matchs a predicat.
         * \param predicat Something callable by passing a character as parameter and returning a boolean.
         */
        template <typename P>
        static inline ParserState skips(ParserState&& state, P&& predicat)
        {
            while (state.canAdvance() && state.matchCurrent(predicat))
            {
                state.advance();
            }
            return state;
        }

        /*! Return true if the current character is the expected character. */
        static bool is(ParserState const& state, char expectedChar);
    };
}

#endif
