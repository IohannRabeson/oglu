/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PlyMeshLoader.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 00:28:53 by irabeson          #+#    #+#             */
/*   Updated: 2017/03/01 00:29:33 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if!defined PLYMESHLOADER_HPP
# define PLYMESHLOADER_HPP
# include "Oglu/Graphics/Mesh.hpp"
# include "Oglu/Parsers/Parsers.hpp"
# include "Oglu/Parsers/RadixTree.hpp"
# include <functional>
# include <fstream>
# include <sstream>
# include <iostream>
# include <map>
# include <vector>

namespace oglu
{
    template <typename ... Components>
    class PlyMeshLoader;

    template <typename ... Components>
    class PlyMeshLoader<Mesh<Components...>> : public AMeshLoader<Components...>
    {
        using MyType = PlyMeshLoader<Mesh<Components...>>;
    public:
        PlyMeshLoader(std::string const& filePath) :
            m_filePath(filePath)
        {
            m_loadingFunctions.addWord("format", std::bind(&MyType::noOp, this, std::placeholders::_1));
            m_loadingFunctions.addWord("comment", std::bind(&MyType::noOp, this, std::placeholders::_1));
            m_loadingFunctions.addWord("end_header", std::bind(&MyType::noOp, this, std::placeholders::_1));
            m_loadingFunctions.addWord("property", std::bind(&MyType::noOp, this, std::placeholders::_1));
            m_loadingFunctions.addWord("element vertex", std::bind(&MyType::readVertexCount, this, std::placeholders::_1));
            m_loadingFunctions.addWord("element face", std::bind(&MyType::readFaceCount, this, std::placeholders::_1));

//            m_loadingFunctions[""] = std::bind(&MyType::readPosition, this, std::placeholders::_1);
//            m_loadingFunctions["vn"] = std::bind(&MyType::readNormal, this, std::placeholders::_1);
//            m_loadingFunctions["vt"] = std::bind(&MyType::readTexture, this, std::placeholders::_1);
//            m_loadingFunctions["f"] = std::bind(&MyType::readFace, this, std::placeholders::_1);
        }

        void beginLoading() override
        {
            std::ifstream file(m_filePath.c_str(), std::ios_base::in);
            std::string line;
            bool isOk = true;
            auto lineId = 0u;

            if (file.is_open() == false)
            {
                throw std::runtime_error("File not found: '" + m_filePath + "'");
            }
            file.exceptions(std::ios_base::badbit);
            while (isOk && std::getline(file, line))
            {
                if (line.empty() == false)
                {
                    auto const keySize = line.find_last_of(" ");

                    if (keySize != std::string::npos)
                    {
                        auto const key = line.substr(0u, keySize);
                        LoadingFunction function;

                        if (m_loadingFunctions.get(key, function))
                        {
                            function(line);
                        }
                        else
                        {
                            isOk = false;
                        }
                        if (isOk == false)
                        {
                            std::ostringstream oss;

                            oss << m_filePath << ": failed at line " << lineId << ": " << line << std::endl;
                            throw std::runtime_error(oss.str());
                        }
                    }
                }
                ++lineId;
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
        using FunctionMap = RadixTree<LoadingFunction>;
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

        bool readVertexCount(std::string const& line)
        {
            auto state = Parser::begin(line);
            std::size_t count = 0u;

            state = Parser::expect(std::move(state), "element vertex");
            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
            state = Parser::parse<std::size_t>(std::move(state), count);
            m_positions.reserve(count);
            m_textures.reserve(count);
            m_colors.reserve(count);
            m_normals.reserve(count);
            return state.isOk();
        }

        bool readFaceCount(std::string const& line)
        {
            auto state = Parser::begin(line);
            std::size_t count = 0u;

            state = Parser::expect(std::move(state), "element edge");
            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
            state = Parser::parse<std::size_t>(std::move(state), count);
            m_positionIndexes.reserve(count);
            m_normalIndexes.reserve(count);
            m_textureIndexes.reserve(count);
            m_colorIndexes.reserve(count);
            return state.isOk();
        }

        void checkoutRow()
        {
            for (auto it : m_rowElements)
            {

            }
        }

//        bool readPosition(std::string const& line)
//        {
//            auto state = Parser::begin(line);
//            glm::vec3 vertex;

//            state = Parser::expect(std::move(state), 'v');
//            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
//            state = Parser::parse<float>(std::move(state), vertex.x);
//            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
//            state = Parser::parse<float>(std::move(state), vertex.y);
//            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
//            state = Parser::parse<float>(std::move(state), vertex.z);
//            m_positions.emplace_back(std::move(vertex));
//            return state.isOk();
//        }

//        bool readTexture(std::string const& line)
//        {
//            auto state = Parser::begin(line);
//            glm::vec3 vertex;

//            state = Parser::expect(std::move(state), 'v');
//            state = Parser::expect(std::move(state), 't');
//            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
//            state = Parser::parse<float>(std::move(state), vertex.x);
//            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
//            state = Parser::parse<float>(std::move(state), vertex.y);
//            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
//            state = Parser::parse<float>(std::move(state), vertex.z);
//            m_textures.emplace_back(std::move(vertex));
//            return state.isOk();
//        }

//        bool readNormal(std::string const& line)
//        {
//            auto state = Parser::begin(line);
//            glm::vec3 vertex;

//            state = Parser::expect(std::move(state), 'v');
//            state = Parser::expect(std::move(state), 'n');
//            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
//            state = Parser::parse<float>(std::move(state), vertex.x);
//            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
//            state = Parser::parse<float>(std::move(state), vertex.y);
//            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
//            state = Parser::parse<float>(std::move(state), vertex.z);
//            m_normals.emplace_back(std::move(vertex));
//            return state.isOk();
//        }

//        bool readFace(std::string const& line)
//        {
//            auto state = Parser::begin(line);

//            state = Parser::expect(std::move(state), 'f');
//            for (auto i = 0u; i < 3u && state.canAdvance(); ++i)
//            {
//                state = readFaceTriplet(std::move(state));
//            }
//            return state.isOk();
//        }

//        ParserState readFaceTriplet(ParserState&& state)
//        {
//            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
//            state = readFaceTripletComponent(std::move(state), m_positionIndexes);

//            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
//            state = readFaceTripletComponent(std::move(state), m_textureIndexes);

//            state = Parser::skips(std::move(state), [](char c){return std::isspace(c);});
//            state = readFaceTripletComponent(std::move(state), m_normalIndexes);
//            return state;
//        }

//        ParserState readFaceTripletComponent(ParserState&& state, std::vector<GLuint>& indexes)
//        {
//            if (state.canAdvance())
//            {
//                if (Parser::is(state, '/'))
//                {
//                    state.advance();
//                    if (Parser::is(state, '/'))
//                    {
//                        state.advance();
//                    }
//                }
//                else
//                {
//                    GLuint index = std::numeric_limits<GLuint>::max();

//                    state = Parser::parse(std::move(state), index);
//                    // Index readed is 1-based, our stored vertices are 0-based indexed.
//                    indexes.emplace_back(index - 1u);
//                }
//            }
//            return state;
//        }

    private:
        struct Row
        {

        };

        using AssignFunction = std::function<void(float, Row)>;
        FunctionMap m_loadingFunctions;

        Vec3List m_positions;
        Vec3List m_normals;
        Vec3List m_textures;
        Vec4List m_colors;

        IndexList m_positionIndexes;
        IndexList m_textureIndexes;
        IndexList m_normalIndexes;
        IndexList m_colorIndexes;
        std::string m_filePath;

        std::map<std::string, std::size_t> m_rowElements;
        std::vector<float> m_row;
    };
}

#endif
