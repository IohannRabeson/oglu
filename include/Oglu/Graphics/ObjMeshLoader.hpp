/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjMeshLoader.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 22:50:44 by irabeson          #+#    #+#             */
/*   Updated: 2016/11/20 22:50:46 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if!defined OBJMESHLOADER_HPP
# define OBJMESHLOADER_HPP
# include "Oglu/Graphics/Mesh.hpp"
# include "Oglu/Parsers/Parsers.hpp"
# include <list>
# include <fstream>
# include <sstream>
# include <iostream>

namespace oglu
{
    template <typename ... Components>
    class ObjMeshLoader;

    template <typename ... Components>
    class ObjMeshLoader<Mesh<Components...>> : public AMeshLoader<Components...>
    {
        using MyType = ObjMeshLoader<Mesh<Components...>>;
    public:
        ObjMeshLoader(std::string const& filePath) :
            m_filePath(filePath)
        {
            m_loadingFunctions["#"] = std::bind(&MyType::noOp, this, std::placeholders::_1);
            m_loadingFunctions["v"] = std::bind(&MyType::readPosition, this, std::placeholders::_1);
            m_loadingFunctions["vn"] = std::bind(&MyType::readNormal, this, std::placeholders::_1);
            m_loadingFunctions["vt"] = std::bind(&MyType::readTexture, this, std::placeholders::_1);
            m_loadingFunctions["f"] = std::bind(&MyType::readFace, this, std::placeholders::_1);
        }

        void beginLoading() override
        {
            std::ifstream file(m_filePath.c_str(), std::ios_base::in);
            std::string line;
            bool isOk = true;
            auto lineId = 0u;

            file.exceptions(std::ios_base::badbit);
            m_positions.reserve(256u);
            while (isOk && std::getline(file, line))
            {
                if (line.empty())
                    continue;
                auto const keySize = line.find_first_of(" ");

                if (keySize != std::string::npos)
                {
                    auto const key = line.substr(0u, keySize);
                    auto const loaderIt = m_loadingFunctions.find(key);

                    if (loaderIt != m_loadingFunctions.end())
                    {
                        isOk &= loaderIt->second(line);
                    }
                    if (isOk == false)
                    {
                        std::cout << "Failed at line " << lineId << ": " << line << std::endl;
                    }
                    ++lineId;
                }
            }
        }

        void load(oglu::MeshComponents::Position, std::vector<oglu::MeshComponents::Position::DataType>& positions)
        {
            for (auto const index : m_positionIndexes)
            {
                if (index < m_positions.size())
                {
                    positions.push_back(m_positions.at(index));
                }
            }
        }

        void load(oglu::MeshComponents::Normal, std::vector<oglu::MeshComponents::Normal::DataType>& normals)
        {
            for (auto const index : m_normalIndexes)
            {
                if (index < m_normals.size())
                {
                    normals.push_back(m_normals.at(index));
                }
            }
        }

        void load(oglu::MeshComponents::TextureUV, std::vector<oglu::MeshComponents::TextureUV::DataType>& textures)
        {
            for (auto const index : m_textureIndexes)
            {
                if (index < m_textures.size())
                {
                    textures.push_back(m_textures.at(index));
                }
            }
        }
    private:
        using LoadingFunction = std::function<bool(std::string const&)>;
        using FunctionMap = std::map<std::string, LoadingFunction>;
        using Vec2List = std::vector<glm::vec2>;
        using Vec3List = std::vector<glm::vec3>;
        using Vec4List = std::vector<glm::vec4>;
        using IndexList = std::vector<GLuint>;

        void skipSpaces(std::string const& line, std::string::size_type& pos)const
        {
            while (std::isspace(line[pos]))
                ++pos;
        }

        bool noOp(std::string const&)
        {
            return true;
        }

        bool readPosition(std::string const& line)
        {
            auto state = Parser::begin(line);
            glm::vec3 vertex;

            state = Parser::expect(std::move(state), 'v');
            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
            state = Parser::parse<float>(std::move(state), vertex.x);
            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
            state = Parser::parse<float>(std::move(state), vertex.y);
            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
            state = Parser::parse<float>(std::move(state), vertex.z);
            m_positions.emplace_back(std::move(vertex));
            return state.isOk();
        }

        bool readTexture(std::string const& line)
        {
            auto state = Parser::begin(line);
            glm::vec3 vertex;

            state = Parser::expect(std::move(state), 'v');
            state = Parser::expect(std::move(state), 't');
            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
            state = Parser::parse<float>(std::move(state), vertex.x);
            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
            state = Parser::parse<float>(std::move(state), vertex.y);
            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
            state = Parser::parse<float>(std::move(state), vertex.z);
            m_textures.emplace_back(std::move(vertex));
            return state.isOk();
        }

        bool readNormal(std::string const& line)
        {
            auto state = Parser::begin(line);
            glm::vec3 vertex;

            state = Parser::expect(std::move(state), 'v');
            state = Parser::expect(std::move(state), 'n');
            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
            state = Parser::parse<float>(std::move(state), vertex.x);
            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
            state = Parser::parse<float>(std::move(state), vertex.y);
            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
            state = Parser::parse<float>(std::move(state), vertex.z);
            m_normals.emplace_back(std::move(vertex));
            return state.isOk();
        }

        bool readFace(std::string const& line)
        {
            auto state = Parser::begin(line);

            state = Parser::expect(std::move(state), 'f');
            for (auto i = 0u; i < 3u && state.canAdvance(); ++i)
            {
                state = readFaceTriplet(std::move(state));
            }
            return state.isOk();
        }

        ParserState readFaceTriplet(ParserState&& state)
        {
            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
            state = readFaceTripletComponent(std::move(state), m_positionIndexes);

            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
            state = readFaceTripletComponent(std::move(state), m_textureIndexes);

            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
            state = readFaceTripletComponent(std::move(state), m_normalIndexes);
            return state;
        }

        ParserState readFaceTripletComponent(ParserState&& state, std::vector<GLuint>& indexes)
        {
            if (state.canAdvance())
            {
                if (Parser::is(state, '/'))
                {
                    state.advance();
                    if (Parser::is(state, '/'))
                    {
                        state.advance();
                    }
                }
                else
                {
                    GLuint index = std::numeric_limits<GLuint>::max();

                    state = Parser::parse(std::move(state), index);
                    indexes.emplace_back(index - 1u);
                }
            }
            return state;
        }

    private:
        FunctionMap m_loadingFunctions;

        Vec3List m_positions;
        Vec3List m_normals;
        Vec3List m_textures;

        IndexList m_positionIndexes;
        IndexList m_textureIndexes;
        IndexList m_normalIndexes;
        std::string m_filePath;
    };
}

#endif
