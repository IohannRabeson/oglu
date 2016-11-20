/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MeshModel.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 21:59:36 by irabeson          #+#    #+#             */
/*   Updated: 2016/11/13 22:00:48 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if!defined MESHMODEL_HPP
# define MESHMODEL_HPP
# include "Oglu/OpenGl/OpenGl.hpp"
# include "Oglu/OpenGl/OpenGlTypeTraits.hpp"
# include "Oglu/Graphics/Color.hpp"
# include "Oglu/Graphics/Program.hpp"
# include "Oglu/Generics/TypeList.hpp"
# include "Oglu/Generics/LazyCast.hpp"

# include <glm/glm.hpp>
# include <tuple>
# include <cassert>
# include <iterator>
# include <vector>

namespace oglu
{
    namespace ModelComponents
    {
        struct Position
        {
            using DataType = glm::vec3;
            using BaseType = typename glm::vec3::value_type;
            static constexpr char const* const Label = "Position";
            static constexpr BufferBindingTarget const Target = BufferBindingTarget::VertexBuffer;
        };

        struct TextureUV
        {
            using DataType = glm::vec2;
            using BaseType = typename glm::vec2::value_type;
            static constexpr char const* const Label = "UV";
            static constexpr BufferBindingTarget const Target = BufferBindingTarget::VertexBuffer;
        };

        struct Color
        {
            using DataType = oglu::Color;
            using BaseType = float;
            static constexpr char const* const Label = "Color";
            static constexpr BufferBindingTarget const Target = BufferBindingTarget::VertexBuffer;
        };

        struct Index
        {
            using DataType = GLuint;
            using BaseType = GLuint;
            static constexpr char const* const Label = "Index";
            static constexpr BufferBindingTarget const Target = BufferBindingTarget::IndexBuffer;
        };
    }

    template <typename ... Components>
    class Mesh
    {
        using ComponentList = TypeList<Components...>;
        static constexpr std::size_t const ComponentCount = sizeof ... (Components);
    public:
        /*!
         * \brief Abstraction of a component data type loader.
         * \details Provide a method load() used to get datas for one component.
         */
        template <typename Component>
        class AMeshModelComponentLoader
        {
        protected:
            using ComponentType = Component;
            using DataType = typename Component::DataType;

            virtual ~AMeshModelComponentLoader()
            {
            }
        public:
            /*! Fill values with datas.
             *
             *  \param values Loaded datas should be copied into values by the concrete loader.<br>
             *  values is empty when load is called, you don't have to clean it yourself.
             */
            virtual void load(std::vector<DataType>& values) = 0;
        };

        /*!
         * \brief Abstraction of a mesh model loader.
         * \details All loaders must implements a method load() for each component data type.
         * \code
         * // Declare a Mesh with a position and a color for each vertices:
         * using Mesh = oglu::MeshModel<oglu::ModelComponents::Position, oglu::ModelComponents::Color>;
         *
         * class ExampleLoader : public Mesh::AMeshModelLoader
         * {
         *     std::vector<glm::vec3> const PositionBufferData = { ... };
         *     std::vector<oglu::Color> const ColorBufferData = { ... };
         *
         *     // Implement load() for position data type
         *     void load(std::vector<oglu::ModelComponents::Position::DataType>& positions) override
         *     {
         *         positions.assign(std::begin(PositionBufferData), std::end(PositionBufferData));
         *     }
         *
         *     // Implement load() for color data type
         *     void load(std::vector<oglu::ModelComponents::Color::DataType>& colors) override
         *     {
         *         colors = ColorBufferData;
         *     }
         * };
         * \endcode
         *
         * The order of calls to each load methods is defined by the components list.<br>
         * In the previous example, positions are loaded first, followed by colors because Position is the
         * first component passed as template parameter of MeshModel.
         */
        class AMeshModelLoader : public AMeshModelComponentLoader<Components>...
        {
            AMeshModelLoader(AMeshModelLoader const&) = delete;
            AMeshModelLoader& operator = (AMeshModelLoader const&) = delete;
        public:
            AMeshModelLoader() = default;

            virtual ~AMeshModelLoader()
            {
            }
        };
    private:
        template <typename Component>
        class Storage;
    public:
        Mesh();
        virtual ~Mesh();

        /*! Assign component datas to a program's attribute. */
        template <typename Component>
        void setAttribute(AttributeId attributeId);

        /*! Assign mesh datas using a loader.
         *
         *  \tparam Loader This class must inherits from AMeshModelLoader.
         */
        template <typename Loader>
        void load(Loader&& loader);

        void render();
    private:
        template <typename Loader>
        void loadImp(Loader&& loader);
        bool checkStoragesHaveSameVerticeCount()const;

        template <typename Component>
        Storage<Component> const& getStorage()const;

        template <typename Component>
        Storage<Component>& getStorage();
    private:
        std::tuple<Storage<Components>...> m_storages;
        std::size_t m_verticeCount = 0u;
        GLuint m_vertexArray = 0u;
    };
}

#include "Mesh.hxx"
#endif
