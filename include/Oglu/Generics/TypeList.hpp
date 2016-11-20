/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TypeList.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 23:42:35 by irabeson          #+#    #+#             */
/*   Updated: 2016/05/28 23:42:37 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if!defined TYPELIST_HPP
#define TYPELIST_HPP
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <functional>

#include "Type.hpp"

// TODO: move theses helpers to a dedicated file
namespace oglu
{
    template <std::size_t N>
    using SizeTypeConstant = std::integral_constant<std::size_t, N>;
}

namespace oglu
{
    template <class ... TS>
    struct TypeList
    {
    };

    // *****************************************************
    // SizeHelper
    template <class>
    struct SizeHelper : public SizeTypeConstant<0u>
    {
    };

    template <class ... TS>
    struct SizeHelper<TypeList<TS...>> : public SizeTypeConstant<sizeof...(TS)>
    {
    };

    /*! Get the type list size. */
    template <class ... TS>
    using Size = SizeHelper<TS...>;

    // *****************************************************
    // ConcatHelper
    template <class ... >
    struct ConcatHelper
    {
        using Type = TypeList<>;
    };

    template <class ... TS>
    struct ConcatHelper<TypeList<TS...>>
    {
        using Type = TypeList<TS...>;
    };

    template <class ... TS0, class ... TS1, class ... TSR>
    struct ConcatHelper<TypeList<TS0...>, TypeList<TS1...>, TSR...>
    {
        using Type = typename ConcatHelper<TypeList<TS0..., TS1...>, TSR...>::Type;
    };

    /*!
     *  \brief Concatenate serveral types lists
     *  \code
     *  using MyTypeList0 = oglu::TypeList<int, float, bool>;
     *  using MyTypeList1 = oglu::TypeList<int, std::string>;
     *
     *  using Result = Concat<MyTypeList0, MyTypeList1>;
     *  \endcode
     */
    template <class ... TS>
    using Concat = typename ConcatHelper<TS...>::Type;

    // *****************************************************
    // RenameHelper
    template <template <class...> class TN, class T>
    struct RenameHelper;

    // Here TS must be not defined by the user since
    // the compiler can deduce it. When we specialize RenameHelper
    // we pass for the type T T0<TS...>, this is here compiler deduce
    // TS.
    template <template <class...> class TN, template <class...> class T0, class ... TS>
    struct RenameHelper<TN, T0<TS...>>
    {
        using Type = TN<TS...>;
    };

    /*!
     *  \brief Rename a type list
     *
     *  \code
     *  using MyTypeList = oglu::TypeList<int, float, bool>;
     *  using MyTuple = oglu::Rename<std::tuple, MyTypeList>
     *  \endcode
     */
    template <template <class...> class TN, class T>
    using Rename = typename RenameHelper<TN, T>::Type;

    /*!
     *  \brief Convert a type list to a tuple
     */
    template <class TS>
    using Tuple = Rename<std::tuple, TS>;

    template <class>
    struct TupleTypeHelper;

    template <class ... TS>
    struct TupleTypeHelper<TypeList<TS...>>
    {
        using Type = std::tuple<Type<TS>...>;
    };

    /*!
     *  \brief Convert a type list to a tuple
     */
    template <class TS>
    using TupleType = typename TupleTypeHelper<TS>::Type;

    // *****************************************************
    // AtHelper
    template <std::size_t I, class TL>
    struct AtHelper;

    template <std::size_t I, template <class...> class TL, class ... TS>
    struct AtHelper<I, TL<TS...>>
    {
        using Type = typename std::tuple_element<I, std::tuple<TS...>>::type;
    };

    /*!
     *  \brief Get Ith type in a type list TL
     */
    template <std::size_t I, class TL>
    using At = typename AtHelper<I, TL>::Type;

    /*!
     *  \brief Get index of a type in a type list.
     */
    template <class, class>
    struct IndexOf;

    template <class T, class ... TS>
    struct IndexOf<T, TypeList<T, TS...>> : public SizeTypeConstant<0u>
    {
    };

    template <class T, class T0, class ... TS>
    struct IndexOf<T, TypeList<T0, TS...>> : public SizeTypeConstant<IndexOf<T, TypeList<TS...>>::value + 1u>
    {
    };

    // *****************************************************
    // CountHelper
    template <class T, class TS>
    struct CountHelper : public SizeTypeConstant<0u>
    {
    };

    template <class T, class T0, class ... TS>
    struct CountHelper<T, TypeList<T0, TS...>> : public SizeTypeConstant
            <
                CountHelper<T, TypeList<TS...>>::value + (std::is_same<T, T0>::value ? 1u : 0u)
            >
    {
    };

    /*!
     *  \brief Get the count of a particular type in a type list.
     */
    template <class T, class TS>
    using Count = typename CountHelper<T, TS>::type;

    template <class>
    struct Length;

    /*!
     *  \brief Get the length of a type list.
     */
    template <class ... TS>
    struct Length<TypeList<TS...>> : public SizeTypeConstant<sizeof ... (TS)>
    {
    };

    /*!
     *  \brief Get true if T has been found in TS type list.
     *  \tparam T The type list
     */
    template <class T, class TS>
    using Contains = std::integral_constant<bool, (Count<T, TS>::value > 0u)>;

    template <std::size_t C, class T>
    struct RepeatHelper
    {
        using Type = Concat<typename RepeatHelper<C - 1u, T>::Type, TypeList<T>>;
    };

    template <class T>
    struct RepeatHelper<0u, T>
    {
        using Type = TypeList<>;
    };

    template <std::size_t C, class T>
    using Repeat = typename RepeatHelper<C, T>::Type;

    template <class TS, std::size_t I, std::size_t N>
    struct ForEachHelper
    {
        using T = At<I, TS>;

        template <class L>
        inline static void apply(L&& lambda)
        {
            lambda(Type<T>{});
            ForEachHelper<TS, I + 1u, N>::apply(std::forward<L>(lambda));
        }
    };

    template <class S, std::size_t N>
    struct ForEachHelper<S, N, N>
    {
        template <class L>
        inline static void apply(L&&){}
    };

    /*!
     *  \brief Generate successive call for each types in type list TS
     *  \tparam TS Type list
     *  \tparam L Lambda type
     *
     *  The current type is passed to the lamda by a parameter of type oglu::Type<T>
     *  with T the current type in TS.
     *  The lambda used must take one parameter of type auto which will be used
     *  to get the type:
     *  \code
     *
     *  using MyTypeList = oglu::TypeList<int, std::string, int, long, bool>;
     *
     *  oglu::forEach<MyTypeList>([this](auto t)
     *  {
     *      // This lambda will be called 5 times, with a t of type oglu::Type<int>, oglu::Type<std::string>, etc...
     *      using TType = decltype(t);
     *      using CurrentType = typename TType::TType;
     *
     *      // Do something with CurrentType...
     *  });
     *
     *  \endcode
     */
    template <class TS, class L>
    inline static void forEach(L&& lambda)
    {
        ForEachHelper<TS, 0u, Size<TS>::value>::apply(std::forward<L>(lambda));
    }

    template <class TS, std::size_t I, std::size_t N>
    struct ForEachTupleHelper
    {
        using T = typename std::tuple_element<I, TS>::type;

        template <class L>
        inline static void apply(L&& lambda)
        {
            lambda(Type<T>{});
            ForEachHelper<TS, I + 1u, N>::apply(std::forward<L>(lambda));
        }
    };

    template <class TS, std::size_t N>
    struct ForEachTupleHelper<TS, N, N>
    {
        template <class L>
        inline static void apply(L&&){}
    };

    template <class TS, class L>
    inline static void forEachTuple(L&& lambda)
    {
        ForEachHelper<TS, 0u, std::tuple_size<TS>::value>::apply(std::forward<L>(lambda));
    }

    template <template <class> class P, class ... TS>
    struct FilterHelper
    {
        using Type = TypeList<>;
    };

    template <template <class> class P, class T>
    struct FilterHelper<P, TypeList<T>>
    {
        using Type = typename std::conditional<P<T>::value, TypeList<T>, TypeList<>>::type;
    };

    template <template <class> class P, class T, class ... TS>
    struct FilterHelper<P, TypeList<T, TS...>>
    {
        using Next = typename FilterHelper<P, TypeList<TS...>>::Type;
        using Type = typename std::conditional<P<T>::value, Concat<TypeList<T>, Next>, Next>::type;
    };

    template <template <class> class P, class TS>
    using Filter = typename FilterHelper<P, TS>::Type;
}

#endif
