/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RgbaColor.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 19:25:34 by irabeson          #+#    #+#             */
/*   Updated: 2016/11/19 19:25:43 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Oglu/Graphics/RgbaColor.hpp"

namespace oglu
{
    RgbaColor const RgbaColor::Transparent = RgbaColor{0.f, 0.f, 0.f, 0.f};
    RgbaColor const RgbaColor::White = RgbaColor{1.f, 1.f, 1.f, 1.f};
    RgbaColor const RgbaColor::Black = RgbaColor{0.f, 0.f, 0.f, 1.f};
    RgbaColor const RgbaColor::Red = RgbaColor{1.f, 0.f, 0.f, 1.f};
    RgbaColor const RgbaColor::Green = RgbaColor{0.f, 1.f, 0.f, 1.f};
    RgbaColor const RgbaColor::Blue = RgbaColor{0.f, 0.f, 1.f, 1.f};
}