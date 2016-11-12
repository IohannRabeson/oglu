namespace oglu
{
	template <class Enum, class Int>
	Flags<Enum, Int>::Flags(Enum value) :
		m_value(value)
	{
	}

	template <class Enum, class Int>
	Flags<Enum, Int>::Flags(Int value) :
		m_value(static_cast<Enum>(value))
	{
	}

	template <class Enum, class Int>
	void	Flags<Enum, Int>::set(Enum value) noexcept
	{
		m_value |= value;
	}

	template <class Enum, class Int>
	void	Flags<Enum, Int>::unset(Enum value) noexcept
	{
		m_value &= std::numeric_limits<Int>::max() & ~value;
	}

	template <class Enum, class Int>
	bool	Flags<Enum, Int>::test(Enum value)const noexcept
	{
		return (m_value & value);
	}

	template <class Enum, class Int>
	Flags<Enum, Int>::operator Enum()const noexcept
	{
		return (static_cast<Enum>(m_value));
	}

	template <class Enum, class Int>
	Flags<Enum, Int>	operator | (Flags<Enum, Int> left, Flags<Enum, Int> right) noexcept
	{
		return (Flags<Enum, Int>(left.m_value | right.m_value));
	}

	template <class Enum, class Int>
	Flags<Enum, Int>	operator & (Flags<Enum, Int> left, Flags<Enum, Int> right) noexcept
	{
		return (Flags<Enum, Int>(left.m_value & right.m_value));
	}

	template <class Enum, class Int>
	Flags<Enum, Int>	operator ^ (Flags<Enum, Int> left, Flags<Enum, Int> right) noexcept
	{
		return (Flags<Enum, Int>(left.m_value ^ right.m_value));
	}
}
