/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 22:56:33 by irabeson          #+#    #+#             */
/*   Updated: 2017/01/27 22:56:35 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Oglu/Parsers/Parsers.hpp"
#include <cassert>

namespace oglu
{
    ///////////////////////////////////////////////////////
    /// class ParserState

    ParserState::ParserState(ParserState::Iterator begin, ParserState::Iterator end, bool isOk) :
        m_end(end),
        m_current(begin),
        m_isOk(isOk)
    {
    }

    ParserState::ParserState(const ParserState &other) :
        m_end(other.m_end),
        m_current(other.m_current),
        m_isOk(other.m_isOk)
    {
    }

    char ParserState::current() const
    {
        return *m_current;
    }

    ParserState::Iterator ParserState::end() const
    {
        return m_end;
    }

    bool ParserState::advance()
    {
        assert(m_isOk == true);

        return ++m_current != m_end;
    }

    bool ParserState::isOk() const
    {
        return m_isOk;
    }

    bool ParserState::canAdvance() const
    {
        return m_isOk && m_current != m_end;
    }

    bool ParserState::matchCurrent(char c) const
    {
        assert(m_isOk == true);

        bool result = false;

        if (m_current != m_end && c == *m_current)
        {
            result = true;
        }
        return result;
    }

    void ParserState::setError()
    {
        m_isOk = false;
    }

    ///////////////////////////////////////////////////////
    /// class Parser

    ParserState Parser::begin(const std::string &text)
    {
        return ParserState(text.begin(), text.end(), text.empty() == false);
    }

    ParserState Parser::expect(ParserState &&state, char c)
    {
        if (state.canAdvance() == false || state.matchCurrent(c) == false)
        {
            state.setError();
        }
        state.advance();
        return state;
    }

    ParserState Parser::expect(ParserState &&state, const Parser::String &expectedText)
    {
        auto checkIt = expectedText.begin();

        while (state.canAdvance() && checkIt != expectedText.end())
        {
            if (state.matchCurrent(*checkIt) == false)
            {
                state.setError();
                return state;
            }
            state.advance();
            ++checkIt;
        }
        return state;
    }

    bool Parser::is(const ParserState &state, char expectedChar)
    {
        bool result = false;

        if (state.canAdvance() && state.matchCurrent(expectedChar))
        {
            result = true;
        }
        return result;
    }
}