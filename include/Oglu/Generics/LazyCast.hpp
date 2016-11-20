/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LazyCast.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 23:37:54 by irabeson          #+#    #+#             */
/*   Updated: 2016/11/16 23:38:47 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if!defined LAZYCAST_HPP
# define LAZYCAST_HPP
# include <type_traits>

namespace oglu
{
    template <class T>
    static inline typename std::underlying_type<T>::type lazyCast(T enumValue) noexcept
    {
        return static_cast<typename std::underlying_type<T>::type>(enumValue);
    }
}

#endif
