/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AShaderLoader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 12:25:00 by irabeson          #+#    #+#             */
/*   Updated: 2016/11/13 12:25:12 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Oglu/Graphics/AShaderLoader.hpp"
#include <fstream>
#include <sstream>

namespace oglu
{
    AShaderLoader::~AShaderLoader()
    {
    }

    LoadShaderFromFile::LoadShaderFromFile(const std::string &filePath) :
        m_filePath(filePath)
    {
    }

    std::string LoadShaderFromFile::getShaderContent()
    {
        std::stringstream content;
        std::ifstream file(m_filePath.c_str(), std::ios_base::in);

        file.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        content << file.rdbuf();
        return content.str();
    }
}
