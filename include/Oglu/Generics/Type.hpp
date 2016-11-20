/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Type.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 03:12:28 by irabeson          #+#    #+#             */
/*   Updated: 2016/05/29 03:13:03 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if!defined TYPE_HPP
# define TYPE_HPP

namespace oglu
{
	template <class T>
	struct Type
	{
        using TType = T;
	};
}

#endif
