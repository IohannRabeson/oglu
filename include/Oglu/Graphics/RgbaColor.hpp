/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RgbaColor.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 19:25:21 by irabeson          #+#    #+#             */
/*   Updated: 2016/11/19 19:25:25 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if!defined RGBACOLOR_HPP
# define RGBACOLOR_HPP
# include <cstdint>

namespace oglu
{
    struct RgbaColor
    {
        static RgbaColor const Transparent;
        static RgbaColor const White;
        static RgbaColor const Black;
        static RgbaColor const Red;
        static RgbaColor const Green;
        static RgbaColor const Blue;

        RgbaColor(float value) noexcept :
            r(value),
            g(value),
            b(value),
            a(1.f)
        {
        }

        RgbaColor(float red, float green, float blue, float alpha = 1.f) noexcept :
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
