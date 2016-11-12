/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flags.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 01:27:08 by irabeson          #+#    #+#             */
/*   Updated: 2016/02/01 02:00:47 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if!defined FLAGS_HPP
# define FLAGS_HPP
# include <limits>

namespace oglu
{
	/*!
		\brief Helper for enum type

		This template allows to combine serveral enum value with boolean operator such
		operator AND, OR, XOR.
		\code
		enum Foo
		{
			A = 0x1,
			B = 0x2,
			C = 0x4
		};

		typedef Flags<Foo, short>	Bar;

		Bar	v0 = A | B;

		if (v0.test(A))
			std::cout << " - A enabled\n";
		if (v0.test(B))
			std::cout << " - B enabled\n";
		if (v0.test(C))
			std::cout << " - C enabled\n";
		\endcode
	*/
	template <class Enum, class Int>
	class Flags
	{
		static_assert(sizeof(Enum) <= sizeof(Int), "Int type is too small to handle Enum");
	public:
		/*!
			Allow implicit conversion between Enum to Flags.
		*/
		Flags(Enum value);

		/*!	Allow implicit conversion between Int to Flags. */
		Flags(Int value);

		/*!	Set a flag without changing the others. */
		void	set(Enum value) noexcept;

		/*!	Unset a flag without changing the others. */
		void	unset(Enum value) noexcept;

		/*!	Test a flag. */
		bool	test(Enum value)const noexcept;

		/*!	Allow implicit conversion to Enum type. */
		operator Enum()const noexcept;

		/*!	Operator OR. */
		friend Flags<Enum, Int>	operator | (Flags<Enum, Int> left, Flags<Enum, Int> right) noexcept;

		/*!	Operator AND. */
		friend Flags<Enum, Int>	operator & (Flags<Enum, Int> left, Flags<Enum, Int> right) noexcept;

		/*!	Operator XOR. */
		friend Flags<Enum, Int>	operator ^ (Flags<Enum, Int> left, Flags<Enum, Int> right) noexcept;

		/*!	Equal operator. */
		friend bool operator == (Flags<Enum, Int> left, Flags<Enum, Int> right);

		/*!	Not equal operator. */
		friend bool operator != (Flags<Enum, Int> left, Flags<Enum, Int> right);
	private:
		Int	m_value;
	};
}

#include "Oglu/Flags.hxx"
#endif
