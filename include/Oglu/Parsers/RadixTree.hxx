/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RadixTree.hxx                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/27 23:38:49 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/28 00:07:15 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>
#include <set>
#include <stack>

namespace oglu
{
    //
    //	class RadixTreeBase
    //
    template <class C, class T>
    RadixTreeBase<C, T>::RadixTreeBase() :
        m_root(std::make_shared<Node>(C(0)))
    {
    }

    template <class C, class T>
    RadixTreeBase<C, T>::RadixTreeBase(std::initializer_list<std::pair<String, T>>&& init) :
        m_root(std::make_shared<Node>(C(0)))
    {
        for (auto const& pair : init)
        {
            addWord(pair.first, pair.second);
        }
    }

    template <class C, class T>
    RadixTreeBase<C, T>::~RadixTreeBase()
    {
    }

    template <class C, class T>
    void RadixTreeBase<C, T>::exportDotLabel(ConstNodePtr node, OStream& os)const
    {
        os << reinterpret_cast<std::size_t>(node->get()) << " [label = \"";
        if (node == m_root)
        {
            os << "root";
        }
        else
        {
            os << node->getKey();
        }
        os << "\"";
        if (node->hasValue() && node != m_root)
        {
            os << ",style=filled,fillcolor=\"palegreen\"";
        }
        os << "];\n";
    }

    template <class C, class T>
    void RadixTreeBase<C, T>::exportDot(OStream& os, String const& graphName)const
    {
        std::set<ConstNodePtr>	nodes;

        os << "digraph " << graphName << "\n{\n";
        m_root->exportDot(os, nodes);
        for (auto node : nodes)
        {
            exportDotLabel(node, os);
        }
        os << "}\n";
    }

    template <class C, class T>
    void RadixTreeBase<C, T>::addWord(String const& word, T const& value)
    {
        if (word.empty())
            return;
        auto	it = word.cbegin();
        NodePtr	current = m_root;

        while (current && it != word.cend())
        {
            if (it + 1 == word.cend())
            {
                current = addLetter(current, *it, value);
            }
            else
            {
                current = addLetter(current, *it);
            }
            ++it;
        }
    }

    template <class C, class T>
    bool RadixTreeBase<C, T>::get(String const& str, T& value)const
    {
        ConstNodePtr previous;

        std::stack<std::pair<ConstNodePtr, decltype(str.cbegin())>> stack;

        stack.push({m_root, str.begin()});
        while (stack.empty() == false)
        {
            auto pair = stack.top();
            ConstNodePtr node = pair.first;
            auto it = pair.second;
            bool hasNexts = false;

            for (auto pair : *node)
            {
                if (pair.first == *it)
                {
                    stack.push({pair.second, it + 1});
                    hasNexts = true;
                }
            }
            if (hasNexts == false && node->hasValue())
            {
                value = node->getValue();
                return true;
            }
        }
        return false;
    }

    template <class C, class T>
    void RadixTreeBase<C, T>::completeWord(String const& beginStr, std::vector<String>& results)const
    {
        ConstNodePtr current = m_root;
        auto it = beginStr.begin();

        if (beginStr.empty())
            return;
        while (current && it != beginStr.end())
        {
            current = current->getNext(*it);
            if (current == nullptr || current->getKey() != *it)
            {
                return;
            }
            ++it;
        }
        if (current && it == beginStr.end())
        {
            for (auto p : *current)
            {
                p.second->getWords(results);
            }
        }
    }

    template <class C, class T>
    void RadixTreeBase<C, T>::getWords(std::vector<String>& results)const
    {
        m_root->getWords(results);
    }

    template <class C, class T>
    bool RadixTreeBase<C, T>::contains(String const& word)const
    {
        ConstNodePtr current = m_root;
        auto it = word.begin();

        if (it == word.end())
            return (false);
        while (current && it != word.end())
        {
            current = current->getNext(*it);
            if (current == nullptr || current->getKey() != *it)
            {
                return (false);
            }
            ++it;
        }
        return (current && current->hasValue() && it == word.end());
    }

    template <class C, class T>
    bool RadixTreeBase<C, T>::tryGetValue(RadixTreeBase::String const& word, T &value) const
    {
        ConstNodePtr current = m_root;
        auto it = word.begin();

        if (it == word.end())
            return (false);
        while (current && it != word.end())
        {
            current = current->getNext(*it);
            if (current == nullptr || current->getKey() != *it)
            {
                return (false);
            }
            ++it;
        }

        bool result = false;

        if (current && current != m_root && it == word.end())
        {
            value = current->getValue();
            result = true;
        }
        return result;
    }

    template <class C, class T>
    auto RadixTreeBase<C, T>::tryGetValue(StringIterator begin, StringIterator end, T& value)const -> std::pair<StringIterator, bool>
    {
        ConstNodePtr current = m_root;
        auto it = begin;

        if (it == end)
            return (std::make_pair(it, false));
        while (current && it != end)
        {
            current = current->getNext(*it);
            if (current == nullptr || current->getKey() != *it)
            {
                return (std::make_pair(it, false));
            }
            ++it;
        }

        bool result = false;

        if (current && current != m_root && it == end)
        {
            value = current->getValue();
            result = true;
        }
        return std::make_pair(it, result);
    }

    template <class C, class T>
    typename RadixTreeBase<C, T>::NodePtr	RadixTreeBase<C, T>::addLetter(NodePtr& current, C letter, T const& value)
    {
        NodePtr	next;

        if (current != nullptr)
        {
            next = current->getOrCreate(letter, value);
        }
        return (next);
    }

    template <class C, class T>
    auto RadixTreeBase<C, T>::addLetter(NodePtr& current, C letter) -> NodePtr
    {
        NodePtr	next;

        if (current != nullptr)
        {
            next = current->getOrCreate(letter);
        }
        return (next);
    }

    //
    //	class RadixTreeBase::Node
    //
    template <class C, class T>
    class RadixTreeBase<C, T>::Node : public std::enable_shared_from_this<Node>
    {
        static String formatDotNodeName(ConstNodePtr node)
        {
            std::basic_ostringstream<C>	os;

            os << reinterpret_cast<std::size_t>(node.get());
            return (os.str());
        }

        static void getWordsImp(ConstNodePtr const& node, String buffer, std::vector<String>& results)
        {
            C key = node->getKey();

            if (key != NullKey)
            {
                buffer.push_back(key);
            }
            if (node->hasValue() && buffer.empty() == false)
            {
                results.push_back(buffer);
            }
            if (node->hasNexts())
            {
                auto it = node->begin();

                getWordsImp(it->second, buffer, results);
                ++it;
                while (it != node->end())
                {
                    getWordsImp(it->second, buffer, results);
                    ++it;
                }
            }
        }
    public:
        using ChildIterator = typename std::map<C, NodePtr>::iterator;
        using ChildConstIterator = typename std::map<C, NodePtr>::const_iterator;

        explicit Node(C key) :
            m_key(key),
            m_hasValue(false)
        {
        }

        explicit Node(C key, T const& value) :
            m_value(value),
            m_key(key),
            m_hasValue(true)
        {
        }

        void getWords(std::vector<String>& results)const
        {
            getWordsImp(this->shared_from_this(), String(), results);
        }

        NodePtr getOrCreate(C key, T const& value)
        {
            auto it = m_nexts.find(key);
            NodePtr	result;

            if (it == m_nexts.end())
            {
                result = std::make_shared<Node>(key, value);
                m_nexts.insert(std::make_pair(key, result));
            }
            else if (it->second->hasValue() == false)
            {
                result = it->second;
                result->setValue(value);
            }
            else
            {
                throw std::runtime_error("lexical tree: duplicated entry");
            }
            return (result);
        }

        NodePtr getOrCreate(C key)
        {
            auto it = m_nexts.find(key);
            NodePtr	result;

            if (it == m_nexts.end())
            {
                result = std::make_shared<Node>(key);
                m_nexts.insert(std::make_pair(key, result));
            }
            else
            {
                result = it->second;
            }
            return (result);
        }

        void exportDot(OStream& os, std::set<ConstNodePtr>& nodes)
        {
            nodes.insert(this->shared_from_this());

            for (auto const& p : m_nexts)
            {
                os << formatDotNodeName(this->shared_from_this()) << " -> " << formatDotNodeName(p.second) << ";\n";
                p.second->exportDot(os, nodes);
            }
        }

        NodePtr getNext(C key)const
        {
            auto	it = m_nexts.find(key);
            NodePtr	result;

            if (it != m_nexts.end())
            {
                result = it->second;
            }
            return (result);
        }

        C getKey()const
        {
            return (m_key);
        }

        void setValue(T const& value)
        {
            m_value = value;
            m_hasValue = true;
        }

        T const& getValue()const
        {
            return (m_value);
        }

        bool hasValue()const
        {
            return m_hasValue;
        }

        bool hasNexts()const
        {
            return (m_nexts.empty() == false);
        }

        ChildIterator begin()
        {
            return (m_nexts.begin());
        }

        ChildIterator end()
        {
            return (m_nexts.end());
        }

        ChildConstIterator begin()const
        {
            return (m_nexts.begin());
        }

        ChildConstIterator end()const
        {
            return (m_nexts.end());
        }
    private:
        std::map<C, NodePtr> m_nexts;
        T m_value;
        C m_key;
        bool m_hasValue;
    };
}
