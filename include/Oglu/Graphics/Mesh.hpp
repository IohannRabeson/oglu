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
# include "Oglu/OpenGl/OpenGlError.hpp"
# include "Oglu/OpenGl/OpenGlTypeTraits.hpp"
# include "Oglu/Graphics/RgbaColor.hpp"
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

        struct Normal
        {
            using DataType = glm::vec3;
            using BaseType = typename glm::vec3::value_type;
            static constexpr char const* const Label = "Normal";
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
            using DataType = oglu::RgbaColor;
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

    /*!
     * \brief Abstraction of a component data type loader.
     * \details Provide a method load() used to get datas for one component.
     *You should not use this class directly but AMeshModelLoader.
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
        virtual void load(ComponentType, std::vector<typename ComponentType::DataType>& values) = 0;
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
    template <typename ... Components>
    class AMeshModelLoader : public AMeshModelComponentLoader<Components>...
    {
        AMeshModelLoader(AMeshModelLoader const&) = delete;
        AMeshModelLoader& operator = (AMeshModelLoader const&) = delete;
    public:
        AMeshModelLoader() = default;

        virtual ~AMeshModelLoader()
        {
        }

        virtual void beginLoading()
        {
        }

        virtual void endLoading()
        {
        }
    };

    template <typename ... Components>
    class Mesh;

    struct RenderModes
    {
        static void line(std::size_t verticeCount)
        {
            GL_CHECK( glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) );
            GL_CHECK( glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(verticeCount)) );
        }

        static void fill(std::size_t verticeCount)
        {
            GL_CHECK( glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) );
            GL_CHECK( glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(verticeCount)) );
        }
    };

    /*!
     *  \brief Allow to take an oglu::Mesh as template parameter.
     *  \code
     *  using MyMesh = oglu::Mesh<Nanani, Nanana>;
     *
     *  class NanaLoader : public oglu::AMeshModelLoader<MyMesh> // MyMesh instead of Nanani, Nanana
     *  {
     *      ...
     *  };
     *  \endcode
     */
    template <typename ... Components>
    class AMeshModelLoader<Mesh<Components...>> : public AMeshModelLoader<Components...>
    {
    };

    template <typename ... Components>
    class Mesh
    {
        using ComponentList = TypeList<Components...>;
        static constexpr std::size_t const ComponentCount = sizeof ... (Components);
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

        void render(std::function<void(std::size_t)>&& mode = RenderModes::fill)const;
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
