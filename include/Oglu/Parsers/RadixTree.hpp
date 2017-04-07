/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RadixTree.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/27 03:07:56 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/28 00:07:45 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICALTREE_HPP
# define LEXICALTREE_HPP
# include <string>
# include <vector>
# include <map>
# include <memory>
# include <ostream>

namespace oglu
{
    template <typename C, typename T>
    class RadixTreeBase
    {
        class Node;
        // shared_ptr works since they're no loop
        // TODO: replace shared_ptr by unique_ptr?
        using NodePtr = std::shared_ptr<Node>;
        using ConstNodePtr = std::shared_ptr<Node const>;
        using String = std::basic_string<C>;
        using OStream = std::basic_ostream<C>;

        using StringIterator = typename String::const_iterator;
        void exportDotLabel(ConstNodePtr node, OStream& os)const;
    public:
        static constexpr C NullKey = C(0);

        RadixTreeBase();
        RadixTreeBase(std::initializer_list<std::pair<String, T>>&& init);
        ~RadixTreeBase();

        void exportDot(OStream& os, String const& graphName)const;
        void addWord(String const& word, T const& value);
        void completeWord(String const& beginStr, std::vector<String>& results)const;
        bool get(String const& str, T& value)const;
        void getWords(std::vector<String>& results)const;
        bool tryGetValue(String const& word, T& value)const;
        std::pair<StringIterator, bool> tryGetValue(StringIterator begin, StringIterator end, T& value)const;
        bool contains(String const& word)const;
    private:
        static auto addLetter(NodePtr& current, C letter, T const& value) -> NodePtr;
        static auto addLetter(NodePtr& current, C letter) -> NodePtr;
    private:
        NodePtr	m_root;
    };

    template <typename T>
    using RadixTree = RadixTreeBase<char, T>;
}

#include "RadixTree.hxx"
#endif
