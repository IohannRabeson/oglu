/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Buffer.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 14:42:27 by irabeson          #+#    #+#             */
/*   Updated: 2016/02/01 00:32:30 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if!defined OGLU_BUFFER_HPP
# define OGLU_BUFFER_HPP
# include <Oglu/OpenGl.hpp>
# include <Oglu/OpenGlError.hpp>

# include <tuple>

# include <iostream>
namespace oglu
{
	template <class H, class ... T>
	struct	SizeOfTuple
	{
		static constexpr std::size_t const	Size = sizeof(H) + SizeOfTuple<T...>::Size;
	};

	template <class H>
	struct	SizeOfTuple<H>
	{
		static constexpr std::size_t const	Size = sizeof(H);
	};

	template <class ... T>
	class Buffer
	{
		static constexpr std::size_t ElementSize = SizeOfTuple<T...>::Size;
	public:
		typedef std::tuple<T...>	Element;

		enum class Usage : GLenum
		{
			StreamDraw = GL_STREAM_DRAW,
			StreamRead = GL_STREAM_READ,
			StreamCopy = GL_STREAM_COPY,
			StaticDraw = GL_STATIC_DRAW,
			StaticRead = GL_STATIC_READ,
			StaticCopy = GL_STATIC_COPY,
			DynamicDraw = GL_DYNAMIC_DRAW,
			DynamicRead = GL_DYNAMIC_READ,
			DynamicCopy = GL_DYNAMIC_COPY
		};

		enum class Behavior : GLbitfield
		{
			MapRead = GL_MAP_READ_BIT,
			MapWrite = GL_MAP_WRITE_BIT,
			DynamicStorage = GL_DYNAMIC_STORAGE_BIT,
			Persitent = GL_MAP_PERSISTENT_BIT,
			Coherent = GL_MAP_COHERENT_BIT,
			ClientStorage = GL_CLIENT_STORAGE_BIT
		};

		Buffer(std::size_t count, const Element& defaultElement, Usage usage) :
			m_bufferId(0u),
			m_count(count)
		{
			Element*			dataPtr = nullptr;

			GL_CHECK( glGenBuffers(1, &m_bufferId) );
			GL_CHECK( glBindBuffer(GL_ARRAY_BUFFER, m_bufferId) );
			GL_CHECK( glBufferData(GL_ARRAY_BUFFER, count * ElementSize, nullptr, static_cast<GLenum>(usage)) );
			GL_CHECK( dataPtr = reinterpret_cast<Element*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY)) );
			std::fill(dataPtr, dataPtr + count, defaultElement);
			GL_CHECK( glUnmapBuffer(GL_ARRAY_BUFFER) );
		}

		Buffer(Element const* elements, std::size_t byteSize, Usage usage) :
			m_bufferId(0u),
			m_count(byteSize / ElementSize)
		{
			GL_CHECK( glGenBuffers(1, &m_bufferId) );
			GL_CHECK( glBindBuffer(GL_ARRAY_BUFFER, m_bufferId) );
			GL_CHECK( glBufferData(GL_ARRAY_BUFFER, byteSize, elements, static_cast<GLenum>(usage)) );
		}

		Buffer(const std::vector<Element>& elements, Usage usage) :
			m_bufferId(0u),
			m_count(elements.size())
		{
			std::size_t const	TotalByteSize = ElementSize * elements.size();

			GL_CHECK( glGenBuffers(1, &m_bufferId) );
			GL_CHECK( glBindBuffer(GL_ARRAY_BUFFER, m_bufferId) );
			GL_CHECK( glBufferData(GL_ARRAY_BUFFER, TotalByteSize, elements.data(), static_cast<GLenum>(usage)) );
		}

		~Buffer()
		{
			if (m_bufferId != 0u)
			{
				GL_CHECK( glDeleteBuffers(1, &m_bufferId) );
			}
		}

		GLuint	getId()const
		{
			return (m_bufferId);
		}

		void	bind()const
		{
			GL_CHECK( glBindBuffer(GL_ARRAY_BUFFER, m_bufferId) );
		}

		class ConstAccess
		{
		public:
			ConstAccess(GLuint arrayId, std::size_t count) :
				m_bufferId(arrayId),
				m_elements(nullptr),
				m_count(count)
			{
				GL_CHECK( m_elements = static_cast<Element const*>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY)) );
			}

			~ConstAccess()
			{
				GL_CHECK( glUnmapBuffer(GL_ARRAY_BUFFER) );
			}

			Element const&	operator[](std::size_t index)const
			{
				if (index >= m_count)
				{
					throw std::range_error("oglu::Buffer::ConstAccess::operator[]: index of of range");
				}
				return (m_elements[ElementSize * index]);
			}
		private:
			GLuint const		m_bufferId;
			Element const*		m_elements;
			std::size_t const	m_count;
		};

		ConstAccess	access()const
		{
			bind();
			return (ConstAccess(m_bufferId, m_count));
		}
	private:
		GLuint												m_bufferId;
		std::size_t											m_count;
	};
}

#endif
