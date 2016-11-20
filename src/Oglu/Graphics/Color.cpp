/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Color.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 19:25:34 by irabeson          #+#    #+#             */
/*   Updated: 2016/11/19 19:25:43 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Oglu/Graphics/Color.hpp"

namespace oglu
{
    Color const Color::Transparent = Color{0.f, 0.f, 0.f, 0.f};
    Color const Color::White = Color{1.f, 1.f, 1.f, 1.f};
    Color const Color::Black = Color{0.f, 0.f, 0.f, 1.f};
    Color const Color::Red = Color{1.f, 0.f, 0.f, 1.f};
    Color const Color::Green = Color{0.f, 1.f, 0.f, 1.f};
    Color const Color::Blue = Color{0.f, 0.f, 1.f, 1.f};
}