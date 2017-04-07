/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RadixTree.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/27 03:42:11 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/28 00:30:50 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <iterator>
#include <random>
#include <algorithm>
#include <chrono>

#include <Oglu/Parsers/RadixTree.hpp>

BOOST_AUTO_TEST_SUITE( lexical_tree )

BOOST_AUTO_TEST_CASE( add_word_tests0 )
{
        oglu::RadixTreeBase<char, int> tree;
        std::vector<std::string> result;
        std::vector<std::string> expected
        {
            "a",
            "aa",
            "ab",
            "aba",
            "abab",
            "abc",
            "abcd",
            "b",
            "bc",
            "bcd",
            "abracadra"
        };

        std::shuffle(expected.begin(), expected.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
        for (auto str : expected)
        {
                tree.addWord(str, 1);
        }
        tree.getWords(result);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected.begin(), expected.end() );
}

BOOST_AUTO_TEST_CASE( add_word_tests1 )
{
        oglu::RadixTreeBase<char, int> tree;
        std::vector<std::string> result;
        std::vector<std::string> expected
        {
            "a",
            "a.a",
            "a.b",
            "az"
        };

        std::shuffle(expected.begin(), expected.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
        for (auto str : expected)
        {
            tree.addWord(str, 1);
        }
        tree.getWords(result);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected.begin(), expected.end() );
}

BOOST_AUTO_TEST_CASE( add_word_tests2 )
{
        oglu::RadixTreeBase<char, int>	tree;
        std::vector<std::string>			result;
        std::vector<std::string> 			expected
        {
                "a",
                "aa",
                "ab",
                "aba",
                "abab",
                "abc",
                "abcd",
                "b",
                "bc",
                "bcd"
        };

        std::shuffle(expected.begin(), expected.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
        for (auto str : expected)
        {
                tree.addWord(str, 1);
        }
        tree.getWords(result);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected.begin(), expected.end() );
}

BOOST_AUTO_TEST_CASE( get_words_tests0 )
{
        oglu::RadixTreeBase<char, int>	tree;
        std::vector<std::string>			result;
        std::vector<std::string> 			expected
        {
                "a",
                "aa",
                "ab",
                "aba",
                "abab",
                "abc",
                "abcd",
                "b",
                "bc",
                "bcd"
        };

        for (auto str : expected)
        {
                tree.addWord(str, 1);
        }
        tree.getWords(result);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected.begin(), expected.end() );
}

BOOST_AUTO_TEST_CASE( add_word_error )
{
        oglu::RadixTreeBase<char, int>	tree;
        std::vector<std::string>			result;

        BOOST_REQUIRE_NO_THROW( tree.addWord("a", 1) );
        BOOST_REQUIRE_NO_THROW( tree.addWord("b", 1) );
        BOOST_REQUIRE_NO_THROW( tree.addWord("c", 1) );
        BOOST_REQUIRE_NO_THROW( tree.addWord("01", 1) );
        BOOST_REQUIRE_NO_THROW( tree.addWord("01ZZ", 1) );
        BOOST_REQUIRE_NO_THROW( tree.addWord("10", 1) );

        BOOST_CHECK_THROW (tree.addWord("a", 1), std::runtime_error);
        BOOST_CHECK_THROW (tree.addWord("a", 1), std::runtime_error);
        BOOST_CHECK_THROW (tree.addWord("b", 1), std::runtime_error);
        BOOST_CHECK_THROW (tree.addWord("c", 1), std::runtime_error);
        BOOST_CHECK_THROW (tree.addWord("01", 1), std::runtime_error);
        BOOST_CHECK_THROW (tree.addWord("10", 1), std::runtime_error);
        BOOST_CHECK_NO_THROW( tree.addWord("01Z", 1) );
        BOOST_CHECK_NO_THROW( tree.addWord("ab", 1) );
        BOOST_CHECK_NO_THROW( tree.addWord("bc", 1) );
        BOOST_CHECK_NO_THROW( tree.addWord("cd", 1) );
}

BOOST_AUTO_TEST_CASE( get_words_tests1 )
{
        oglu::RadixTreeBase<char, int>	tree;
        std::vector<std::string>			result;
        std::vector<std::string> 			expected
        {
                "a",
                "aa",
                "ab",
                "abab",
                "abc",
                "abcd",
                "b",
                "bc",
                "bcd"
        };

        for (auto str : expected)
        {
                tree.addWord(str, 1);
        }
        tree.getWords(result);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected.begin(), expected.end() );
}

BOOST_AUTO_TEST_CASE( get_words_tests2 )
{
        oglu::RadixTreeBase<char, int>	tree;
        std::vector<std::string>			result;
        std::vector<std::string> 			expected
        {
                "a",
                "aa",
                "ab",
                "abab",
                "abababa"
                "abc",
                "abcc",
                "abcd",
                "b",
                "bc",
                "bcd"
        };

        for (auto str : expected)
        {
                tree.addWord(str, 1);
        }
        tree.getWords(result);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected.begin(), expected.end() );
}

BOOST_AUTO_TEST_CASE( get_words_tests3 )
{
        oglu::RadixTreeBase<char, int>	tree;
        std::vector<std::string>			result;
        std::vector<std::string> 			expected
        {
                "a",
                "ab",
                "abc",
                "abcd",
                "b",
                "bc",
                "bcd",
                "demo.a",
                "demo.ab",
                "demo.abc",
                "demoabc"
                "demoab"
        };

        for (auto str : expected)
        {
                tree.addWord(str, 1);
        }
        tree.getWords(result);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected.begin(), expected.end() );
}

BOOST_AUTO_TEST_CASE( complete_words_tests )
{
        oglu::RadixTreeBase<char, int>	tree;
        std::vector<std::string> 			words
        {
                "a",
                "ab",
                "abc",
                "abcd",
                "b",
                "bc",
                "bcd"
        };
        std::vector<std::string>			expected_a =
        {
                "b",
                "bc",
                "bcd"
        };
        std::vector<std::string>			result;

        for (auto str : words)
        {
                tree.addWord(str, 1);
        }
        tree.completeWord("a", result);
        std::sort(expected_a.begin(), expected_a.end());
        std::sort(result.begin(), result.end());
        BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected_a.begin(), expected_a.end() );
}

BOOST_AUTO_TEST_CASE( complete_words_tests2 )
{
        oglu::RadixTreeBase<char, int>	tree;
        std::vector<std::string> 			words
        {
                "a",
                "aa",
                "ab",
                "abab",
                "abc",
                "abcd",
                "b",
                "bc",
                "bcd"
        };
        std::vector<std::string>			expected_a =
        {
                "a",
                "b",
                "bab",
                "bc",
                "bcd"
        };
        std::vector<std::string>			expected_ab =
        {
                "ab",
                "c",
                "cd"
        };
        std::vector<std::string>			expected_b =
        {
                "c",
                "cd"
        };
        std::vector<std::string>			expected_c =
        {
        };
        std::vector<std::string>			result;

        for (auto str : words)
        {
                tree.addWord(str, 1);
        }
        std::sort(expected_a.begin(), expected_a.end());
        std::sort(expected_ab.begin(), expected_ab.end());
        std::sort(expected_b.begin(), expected_b.end());
        std::sort(expected_c.begin(), expected_c.end());
        tree.completeWord("a", result);
        std::sort(result.begin(), result.end());
        BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected_a.begin(), expected_a.end() );
        result.clear();
        tree.completeWord("ab", result);
        std::sort(result.begin(), result.end());
        BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected_ab.begin(), expected_ab.end() );
        result.clear();
        tree.completeWord("b", result);
        std::sort(result.begin(), result.end());
        BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected_b.begin(), expected_b.end() );
        result.clear();
        tree.completeWord("c", result);
        std::sort(result.begin(), result.end());
        BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected_c.begin(), expected_c.end() );
}

BOOST_AUTO_TEST_CASE( complete_words_tests3 )
{
        oglu::RadixTreeBase<char, int>	tree;
        std::vector<std::string> 			words
        {
                "a",
                "ab",
                "abc",
                "abcd",
                "b",
                "bc",
                "bcd"
        };
        std::vector<std::string>			expected_a =
        {
                "c",
                "cd"
        };
        std::vector<std::string>			result;

        for (auto str : words)
        {
                tree.addWord(str, 1);
        }
        tree.completeWord("b", result);
        std::sort(expected_a.begin(), expected_a.end());
        std::sort(result.begin(), result.end());
        BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected_a.begin(), expected_a.end() );
}

BOOST_AUTO_TEST_CASE( complete_words_tests4 )
{
        oglu::RadixTreeBase<char, int>	tree;
        std::vector<std::string> 			words
        {
                "a",
                "ab",
                "abc",
                "abcd",
                "b",
                "bc",
                "bcd",
                "demoabc",
                "demo.a",
                "demo.ab",
                "demo.abc"
        };
        std::vector<std::string>			expected_demo =
        {
                "a",
                "ab",
                "abc"
        };
        std::vector<std::string>			result;

        for (auto str : words)
        {
                tree.addWord(str, 1);
        }
        tree.completeWord("demo.", result);
        std::sort(expected_demo.begin(), expected_demo.end());
        std::sort(result.begin(), result.end());
        BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected_demo.begin(), expected_demo.end() );
}

BOOST_AUTO_TEST_CASE( complete_words_tests5 )
{
        oglu::RadixTreeBase<char, int>	tree;
        std::vector<std::string> 			words
        {
                "a",
                "ab",
                "abc",
                "abcd",
                "b",
                "bc",
                "bcd",
                "demo.a",
                "demo.ab",
                "demo.abc",
                "demoabc",
                "demoab",
                "demo.demo"
        };
        std::vector<std::string>			expected_demo_dot =
        {
                "a",
                "ab",
                "abc",
                "demo"
        };
        std::vector<std::string>			expected_demo =
        {
                "ab",
                "abc",
                ".a",
                ".ab",
                ".abc",
                ".demo"
        };
        std::vector<std::string>			result;

        for (auto str : words)
        {
                tree.addWord(str, 1);
        }
        std::sort(expected_demo_dot.begin(), expected_demo_dot.end());
        std::sort(expected_demo.begin(), expected_demo.end());
        tree.completeWord("demo.", result);
        std::sort(result.begin(), result.end());
        BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected_demo_dot.begin(), expected_demo_dot.end() );
        result.clear();
        tree.completeWord("demo", result);
        std::sort(result.begin(), result.end());
        BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected_demo.begin(), expected_demo.end() );
}

BOOST_AUTO_TEST_CASE( contains_word_tests0 )
{
        oglu::RadixTreeBase<char, int>	tree;
        std::vector<std::string> 			words
        {
                "a",
                "aa",
                "ab",
                "aba",
                "abab",
                "abc",
                "abcd",
                "b",
                "bc",
                "bcd",
                "abracadra"
        };

        for (auto word : words)
        {
                tree.addWord(word, 1);
        }
        for (auto word : words)
        {
                BOOST_CHECK( tree.contains(word) == true );
        }
}

BOOST_AUTO_TEST_CASE( not_contains_word_test )
{
        oglu::RadixTreeBase<char, int>	tree;
        std::vector<std::string> 			words
        {
                "a",
                "aa",
                "ab",
                "aba",
                "abab",
                "abc",
                "abcd",
                "b",
                "bc",
                "bcd",
                "abracadra",
                "phuqk"
        };

        std::vector<std::string>			notContained =
        {
                "0",
                "123",
                "aac",
                "c",
                "p"
        };

        for (auto word : words)
        {
                tree.addWord(word, 1);
        }
        for (auto word : notContained)
        {
                BOOST_CHECK( tree.contains(word) == false );
        }
}

BOOST_AUTO_TEST_SUITE_END()
