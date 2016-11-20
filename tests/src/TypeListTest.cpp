/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TypeListTest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 23:58:10 by irabeson          #+#    #+#             */
/*   Updated: 2016/05/28 23:59:40 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>

#include <Oglu/Generics/TypeList.hpp>

#include <iostream>

BOOST_AUTO_TEST_SUITE( type_list )

BOOST_AUTO_TEST_CASE( basic_tests )
{
    using T0 = oglu::TypeList<>;
    using T1 = oglu::TypeList<bool>;
    using T4 = oglu::TypeList<int, char, float, long>;

    static_assert( oglu::Size<T0>::value == 0u, "T0::Size == 0u failed" );
    static_assert( oglu::Size<T1>::value == 1u, "T1::Size == 1u failed" );
    static_assert( oglu::Size<T4>::value == 4u, "T4::Size == 4u failed" );
    static_assert( std::is_same< oglu::At<0, T1>, bool>::value , "T1<0> != bool" );

    static_assert( std::is_same< oglu::At<0, T4>, int>::value , "T4<0> != int" );
    static_assert( std::is_same< oglu::At<1, T4>, char>::value , "T4<1> != char" );
    static_assert( std::is_same< oglu::At<2, T4>, float>::value , "T4<2> != float" );
    static_assert( std::is_same< oglu::At<3, T4>, long>::value , "T4<3> != long" );
}

BOOST_AUTO_TEST_CASE( element_at_tests )
{
    using T1 = oglu::TypeList<bool>;
    using T4 = oglu::TypeList<int, char, float, long, bool, int>;

    static_assert( std::is_same< oglu::At<0, T1>, bool>::value , "T1<0> != bool" );
    static_assert( std::is_same< oglu::At<0, T4>, int>::value , "T4<0> != int" );
    static_assert( std::is_same< oglu::At<1, T4>, char>::value , "T4<1> != char" );
    static_assert( std::is_same< oglu::At<2, T4>, float>::value , "T4<2> != float" );
    static_assert( std::is_same< oglu::At<3, T4>, long>::value , "T4<3> != long" );
    static_assert( std::is_same< oglu::At<4, T4>, bool>::value , "T4<4> != bool" );
    static_assert( std::is_same< oglu::At<5, T4>, int>::value , "T4<5> != int" );
}

BOOST_AUTO_TEST_CASE( count_tests )
{
    using T0 = oglu::TypeList<int, char, float, long, bool, int>;

    static_assert( oglu::Count<int, T0>::value == 2u, "" );
    static_assert( oglu::Count<char, T0>::value == 1u, "" );
    static_assert( oglu::Count<bool, T0>::value == 1u, "" );
    static_assert( oglu::Count<unsigned int, T0>::value == 0u, "" );
}

BOOST_AUTO_TEST_CASE( length_tests )
{
    using T0 = oglu::TypeList<>;
    using T1 = oglu::TypeList<int>;
    using T2 = oglu::TypeList<int, char>;
    using T6 = oglu::TypeList<int, char, float, long, bool, int>;

    static_assert( oglu::Length<T0>::value == 0u, "" );
    static_assert( oglu::Length<T1>::value == 1u, "" );
    static_assert( oglu::Length<T2>::value == 2u, "" );
    static_assert( oglu::Length<T6>::value == 6u, "" );
}

BOOST_AUTO_TEST_CASE( index_of_tests )
{
    using T0 = oglu::TypeList<int, char, float, long, bool>;

    static_assert( oglu::IndexOf<int, T0>::value == 0u, "" );
    static_assert( oglu::IndexOf<char, T0>::value == 1u, "" );
    static_assert( oglu::IndexOf<float, T0>::value == 2u, "" );
    static_assert( oglu::IndexOf<long, T0>::value == 3u, "" );
}

BOOST_AUTO_TEST_CASE( contains_test )
{
    using T0 = oglu::TypeList<int, char, float, long, bool>;

    static_assert( oglu::Contains<int, T0>::value == true, "" );
    static_assert( oglu::Contains<char, T0>::value == true, "" );
    static_assert( oglu::Contains<float, T0>::value == true, "" );
    static_assert( oglu::Contains<long, T0>::value == true, "" );
    static_assert( oglu::Contains<void, T0>::value == false, "" );
    static_assert( oglu::Contains<double, T0>::value == false, "" );
    static_assert( oglu::Contains<unsigned int, T0>::value == false, "" );
}

BOOST_AUTO_TEST_CASE( concat_tests )
{
    using T1 = oglu::TypeList<bool>;
    using T4 = oglu::TypeList<int, char, float, long>;
    using TR = oglu::Concat<T1, T4>;

    static_assert( oglu::Size<TR>::value == 5u, "TR::Size == 5u failed" );
}

BOOST_AUTO_TEST_CASE( rename_tests )
{
    using T0 = oglu::TypeList<bool, int, char, float, long>;
    using TR = oglu::Rename<std::tuple, T0>;

    static_assert( oglu::Size<T0>::value == std::tuple_size<TR>::value, "T0 and TR have different size" );
    static_assert( std::is_same<TR, std::tuple<bool, int, char, float, long>>::value , "T0 and TR does not match" );
}

BOOST_AUTO_TEST_CASE( repeat_tests )
{
    using T0 = oglu::Repeat<23u, bool>;

    static_assert( oglu::Size<T0>::value == 23u, "" );
    static_assert( oglu::Count<bool, T0>::value == 23u, "" );
}

BOOST_AUTO_TEST_CASE( filter_tests )
{
    using T4 = oglu::TypeList<int, char, float, long>;
    using R = oglu::Filter<std::is_integral, T4>;

    static_assert( oglu::Size<R>::value == 3u, "");
    static_assert( oglu::Contains<int, R>::value, "" );
    static_assert( oglu::Contains<char, R>::value, "" );
    static_assert( oglu::Contains<long, R>::value, "" );
    static_assert( oglu::Contains<float, R>::value == false, "" );
    static_assert( oglu::IndexOf<int, R>::value == 0u, "");
    static_assert( oglu::IndexOf<char, R>::value == 1u, "");
    static_assert( oglu::IndexOf<long, R>::value == 2u, "");
}

namespace filterTest
{
    using T0 = oglu::TypeList<int, char, long>;
    using T1 = oglu::TypeList<float, double>;
    using TS = oglu::Concat<T0, T1>;

    template <class T>
    using IsInT0 = oglu::Contains<T, T0>;

    template <class T>
    using IsInT1 = oglu::Contains<T, T1>;
}

BOOST_AUTO_TEST_CASE( filter_tests2 )
{
    namespace ft = filterTest;
    using InT0 = oglu::Filter<ft::IsInT0, ft::TS>;
    using InT1 = oglu::Filter<ft::IsInT1, ft::TS>;

    static_assert( std::is_same<InT0, ft::T0>::value, "" );
    static_assert( std::is_same<InT1, ft::T1>::value, "" );
}

BOOST_AUTO_TEST_SUITE_END()
