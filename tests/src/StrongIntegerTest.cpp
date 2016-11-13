/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrongIntegerTest.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 21:16:26 by irabeson          #+#    #+#             */
/*   Updated: 2016/10/04 00:16:40 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include <Oglu/Generics/StrongInteger.hpp>

typedef boost::mpl::list<int,long,unsigned char, std::uint32_t> IntegralTypes;

BOOST_AUTO_TEST_SUITE(strong_integer)

BOOST_AUTO_TEST_CASE_TEMPLATE( conversion_strong_to_value, T, IntegralTypes )
{
    using StrongInt = oglu::StrongInteger<T>;

    static_assert(std::is_same<typename oglu::UnderlyingType<StrongInt>::Type, T>::value, "UnderlyingType doesn't work");
    static_assert(std::is_convertible<StrongInt, T>::value, "not convertible");
    static_assert(std::is_assignable<StrongInt, T>::value, "not assignable");
}

BOOST_AUTO_TEST_CASE( comparisons )
{
    oglu::StrongInteger<int> const v0(0);
    oglu::StrongInteger<int> const v1(1);

	BOOST_TEST(v0 == v0);
	BOOST_TEST(v1 == v1);
	BOOST_TEST(v0 != v1);
	BOOST_TEST(v0 < v1);
	BOOST_TEST(v1 > v0);
	BOOST_TEST(v0 <= v1);
	BOOST_TEST(v1 >= v0);
	BOOST_TEST(v0 <= v0);
	BOOST_TEST(v1 >= v1);
}

BOOST_AUTO_TEST_CASE( arithmetic )
{
    oglu::StrongInteger<int> const v0(0);
    oglu::StrongInteger<int> const v1(1);
    oglu::StrongInteger<int> const v2(2);

	BOOST_TEST( v0 + v1 == 1 );
	BOOST_TEST( v0 - v1 == -1 );
	BOOST_TEST( v2 * v2 == 4 );
	BOOST_TEST( v2 / v2 == 1 );
	BOOST_TEST( (v1 & v2) == (1 & 2) );
	BOOST_TEST( (v1 | v2) == (1 | 2) );
	BOOST_TEST( (v1 ^ v2) == (1 ^ 2) );
	BOOST_TEST( ~v2 == ~2 );

    oglu::StrongInteger<int> t(123);
    oglu::StrongInteger<int> t_pre = t++;

	BOOST_TEST(t_pre == 123);
	BOOST_TEST(t == 124);
}

BOOST_AUTO_TEST_SUITE_END()
