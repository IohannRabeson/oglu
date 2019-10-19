/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringConverterTest.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 00:16:09 by irabeson          #+#    #+#             */
/*   Updated: 2016/11/22 00:16:11 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include <Oglu/Parsers/Parsers.hpp>

#include <vector>
#include <cstdint>
#include <utility>

class FormatException : public std::runtime_error
{
public:
    FormatException() : std::runtime_error("FUCK")
    {
    }
};

BOOST_AUTO_TEST_SUITE ( string_converter )

/*!
 *  \brief Extract a value from a string and test if:
 *  - the parser is ok
 *  - the parser has consumed each character of text
 *  \throw FormatException if one of theses checks fails.
 */
template <typename T>
static inline T parse(std::string const& text)
{
    T value;
    auto parser = oglu::Parser::begin(text);

    parser = oglu::Parser::parse<T>(std::move(parser), value);
    if (parser.isOk() == false || parser.canAdvance())
    {
        throw FormatException();
    }
    return value;
}

typedef boost::mpl::list<
                         std::uint8_t,
                         std::uint16_t,
                         std::uint32_t,
                         std::uint64_t,
                         std::int8_t,
                         std::int16_t,
                         std::int32_t,
                         std::int64_t
                         > AtoiTestTypes;

typedef boost::mpl::list<
                         std::int8_t,
                         std::int16_t,
                         std::int32_t,
                         std::int64_t
                         > AtoiSignedTestTypes;

typedef boost::mpl::list<
                        float,
                        double
                         > AtofTestTypes;

/*!
 * \brief Test StringConverter::parse<T>() with unsigned integer types
 */
BOOST_AUTO_TEST_CASE_TEMPLATE( atoi, T, AtoiTestTypes )
{
    typedef std::pair<std::string, T>	StrNumPair;

    std::vector<StrNumPair>	tests =
    {
        {"0", 0},
        {"1", 1},
        {"2", 2},
        {"10", 10},
        {"42", 42},
        {"100", 100},
        {"0100", 100},
        {std::to_string(std::numeric_limits<T>::min()), std::numeric_limits<T>::min()},
        {std::to_string(std::numeric_limits<T>::max()), std::numeric_limits<T>::max()}
    };

    for (auto i = 0u; i < tests.size(); ++i)
    {
        BOOST_TEST_CHECKPOINT( "atoi iteration " << i );
        BOOST_TEST( parse<T>(tests[i].first) == tests[i].second );
    }
}

/*!
 * \brief Test StringConverter::parse<T>() with signed integer types
 */
BOOST_AUTO_TEST_CASE_TEMPLATE( atoi_signed, T, AtoiSignedTestTypes )
{
    typedef std::pair<std::string, T>	StrNumPair;

    std::vector<StrNumPair>	tests =
    {
        {"0", 0},
        {"-0", 0},
        {"-1", -1},
        {"-2", -2},
        {"-10", -10},
        {"-42", -42},
        {"-100", -100},
        {"-0100", -100},
        {std::to_string(std::numeric_limits<T>::min()), std::numeric_limits<T>::min()}
    };

    for (auto i = 0u; i < tests.size(); ++i)
    {
        BOOST_TEST_CHECKPOINT( "atoi iteration " << i );
        BOOST_TEST( parse<T>(tests[i].first) == tests[i].second );
    }
}

/*!
 * \brief Test StringConverter::parse<T>() with floating point types
 */
BOOST_AUTO_TEST_CASE_TEMPLATE( atof, T, AtofTestTypes )
{
    typedef std::pair<std::string, T>	StrNumPair;

    std::vector<StrNumPair>	tests =
    {
        {"0", 0},
        {"-0", 0},
        {"0.", 0},
        {".0", 0},
        {"-1", -1},
        {"-2", -2},
        {"-10", -10},
        {"-42", -42},
        {"-042", -42},
        {"-100", -100},
        {".3", 0.3},
        {"0.3", 0.3},
        {"00.3", 0.3},
        {"00.30", 0.3},
        {"-.3", -0.3},
        {"-0.3", -0.3},
        {"-00.3", -0.3},
        {"-00.30", -0.3},
        {"3423523.4555", 3423523.4555},
        {"0.00004", 0.00004},
        {"-0.00004", -0.00004},
        {"-0.00004000", -0.00004},
        {"-2.876", -2.876}
    };

    for (auto i = 0u; i < tests.size(); ++i)
    {
        BOOST_TEST_CHECKPOINT( "atoi iteration " << i );
        BOOST_CHECK_CLOSE( parse<T>(tests[i].first), tests[i].second, 0.000001 );
    }
}

/*!
 *  \brief Test exception when signed number is parsed when an unsigned is requested.
 */
BOOST_AUTO_TEST_CASE( unsigned_errors )
{
    BOOST_CHECK_THROW( parse<unsigned int>("-1"), FormatException );
}

/*!
 * \brief Test monkey values.
 */
BOOST_AUTO_TEST_CASE_TEMPLATE( int_error_tests, T, AtoiTestTypes )
{
    BOOST_CHECK_THROW( parse<T>(""), FormatException );
    BOOST_CHECK_THROW( parse<T>("asd"), FormatException );
    BOOST_CHECK_THROW( parse<T>("-d123"), FormatException );
    BOOST_CHECK_THROW( parse<T>("9(*&"), FormatException );
    BOOST_CHECK_THROW( parse<T>(" 8 "), FormatException );
    BOOST_CHECK_THROW( parse<T>("9.0"), FormatException );
    BOOST_CHECK_THROW( parse<T>(".981."), FormatException );
}

/*!
 * \brief Test monkey values.
 */
BOOST_AUTO_TEST_CASE_TEMPLATE( float_error_tests, T, AtoiTestTypes )
{
    BOOST_CHECK_THROW( parse<T>(""), FormatException );
    BOOST_CHECK_THROW( parse<T>("asd"), FormatException );
    BOOST_CHECK_THROW( parse<T>("-d123"), FormatException );
    BOOST_CHECK_THROW( parse<T>("9(*&"), FormatException );
    BOOST_CHECK_THROW( parse<T>(" 8 "), FormatException );
    BOOST_CHECK_THROW( parse<T>(".981."), FormatException );
    BOOST_CHECK_THROW( parse<T>("."), FormatException );
}

BOOST_AUTO_TEST_CASE( bool_test )
{
//    TODO: Boolean parser (using the radix tree)
//    BOOST_TEST( oglu::Parser::parse<bool>("true") == true );
//    BOOST_TEST( oglu::Parser::parse<bool>("false") == false );
//    BOOST_CHECK_THROW( oglu::Parser::parse<bool>(""), FormatException );
//    BOOST_CHECK_THROW( oglu::Parser::parse<bool>("veut pas aller dormir"), FormatException );
}

BOOST_AUTO_TEST_SUITE_END()

