/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AShaderLoader.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 12:14:58 by irabeson          #+#    #+#             */
/*   Updated: 2016/11/13 12:15:13 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if!defined ASHADERLOADER_HPP
# define ASHADERLOADER_HPP
# include "Oglu/OpenGl/OpenGl.hpp"
# include <string>

namespace oglu
{
    class AShaderLoader
    {
    public:
        virtual ~AShaderLoader();

        virtual std::string getShaderContent() = 0;
    };

    class LoadShaderFromFile : public AShaderLoader
    {
    public:
        explicit LoadShaderFromFile(std::string const& filePath);

        virtual std::string getShaderContent();
    private:
        std::string const m_filePath;
    };
}

#endif
