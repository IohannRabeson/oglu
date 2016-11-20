/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Color.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 19:25:21 by irabeson          #+#    #+#             */
/*   Updated: 2016/11/19 19:25:25 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if!defined COLOR_HPP
# define COLOR_HPP
# include <cstdint>

namespace oglu
{
    struct Color
    {
        static Color const Transparent;
        static Color const White;
        static Color const Black;
        static Color const Red;
        static Color const Green;
        static Color const Blue;

        Color(float red, float green, float blue, float alpha = 1.f) noexcept :
            r(red),
            g(green),
            b(blue),
            a(alpha)
        {
        }

        float r;
        float g;
        float b;
        float a;
    };
}

#endif
