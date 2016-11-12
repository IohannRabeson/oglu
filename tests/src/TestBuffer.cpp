/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestBuffer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 20:52:03 by irabeson          #+#    #+#             */
/*   Updated: 2016/01/31 23:50:11 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <Oglu/Buffer.hpp>

BOOST_AUTO_TEST_SUITE( buffer )

typedef oglu::Buffer<float, float, float>	PositionBuffer;
typedef typename PositionBuffer::Element Position;

BOOST_AUTO_TEST_CASE( init_read )
{
	Position	positions[] =
	{
		{1, 2, 3},
		{4, 5, 6}
	};

	PositionBuffer	buffer(positions, sizeof(positions),PositionBuffer::Usage::DynamicDraw);
	auto			access = buffer.access();

	BOOST_CHECK_EQUAL( std::get<0>(access[0]), 1 );
	BOOST_CHECK_EQUAL( std::get<1>(access[0]), 2 );
	BOOST_CHECK_EQUAL( std::get<2>(access[0]), 3 );
	BOOST_CHECK_EQUAL( std::get<0>(access[1]), 4 );
	BOOST_CHECK_EQUAL( std::get<1>(access[1]), 5 );
	BOOST_CHECK_EQUAL( std::get<2>(access[1]), 6 );
}

BOOST_AUTO_TEST_SUITE_END()
