namespace oglu
{
    template <typename ... Components>
    Mesh<Components...>::Mesh()
    {
        glGenVertexArrays(1, &m_vertexArray);
    }

    template <typename ... Components>
    Mesh<Components...>::~Mesh()
    {
        glDeleteVertexArrays(1, &m_vertexArray);
    }

    template <typename ... Components>
    template <typename Component>
    auto Mesh<Components...>::getStorage()const -> Storage<Component> const&
    {
        static constexpr std::size_t const ComponentIndex = IndexOf<Component, ComponentList>::value;

        return std::get<ComponentIndex>(m_storages);
    }

    template <typename ... Components>
    template <typename Component>
    auto Mesh<Components...>::getStorage() -> Storage<Component>&
    {
        static constexpr std::size_t const ComponentIndex = IndexOf<Component, ComponentList>::value;

        return std::get<ComponentIndex>(m_storages);
    }

    template <typename ... Components>
    template <typename Component>
    void Mesh<Components...>::setAttribute(AttributeId attributeId)
    {
        static constexpr std::size_t const ComponentIndex = IndexOf<Component, ComponentList>::value;

        std::get<ComponentIndex>(m_storages).setAttribute(attributeId);
    }

    template <typename ... Components>
    template <typename Loader>
    void Mesh<Components...>::load(Loader&& loader)
    {
        loadImp(std::forward<AMeshModelLoader>(loader));
    }

    template <typename ... Components>
    void Mesh<Components...>::render()
    {
        glBindVertexArray(m_vertexArray);

        // Call enableVertexAttribute() for each storage in m_storages
        oglu::forEach<ComponentList>([this](auto t)
        {
            using ComponentType = typename decltype(t)::TType;
            auto& storage = getStorage<ComponentType>();

            storage.enableVertexAttribute();
        });

        glDrawArrays(GL_TRIANGLES, 0, m_verticeCount);

        // Call disableVertexAttribute() for each storage in m_storages
        oglu::forEach<ComponentList>([this](auto t)
        {
            using ComponentType = typename decltype(t)::TType;
            auto& storage = getStorage<ComponentType>();

            storage.disableVertexAttribute();
        });

        glBindVertexArray(0);
    }

    template <typename ... Components>
    bool Mesh<Components...>::checkStoragesHaveSameVerticeCount()const
    {
        bool result = true;

        oglu::forEach<ComponentList>([this, &result](auto t)
        {
            using ComponentType = typename decltype(t)::TType;
            auto const& storage = getStorage<ComponentType>();

            result &= (storage.size() == m_verticeCount);
        });

        return result;
    }

    template <typename ... Components>
    template <typename Loader>
    void Mesh<Components...>::loadImp(Loader&& loader)
    {
        glBindVertexArray(m_vertexArray);

        oglu::forEach<ComponentList>([this, &loader](auto t)
        {
            using ComponentType = typename decltype(t)::TType;
            auto& storage = getStorage<ComponentType>();

            storage.load(loader);
        });

        m_verticeCount = getStorage<ModelComponents::Position>().size();

        assert( checkStoragesHaveSameVerticeCount() );

        oglu::forEach<ComponentList>([this](auto t)
        {
            using ComponentType = typename decltype(t)::TType;
            auto& storage = getStorage<ComponentType>();

            storage.prepareRender();
        });

        glBindVertexArray(0);
    }

    /*!
     *  Handle a Vertex Buffer dedicated to a particular Component.
     */
    template <typename ... Components>
    template <typename Component>
    class Mesh<Components...>::Storage
    {
    public:
        Storage()
        {
            GL_CHECK( glGenBuffers(1, &m_buffer) );
        }

        ~Storage()
        {
            GL_CHECK( glDeleteBuffers(1, &m_buffer) );
        }

        std::size_t size()const
        {
            return m_components.size();
        }

        void setAttribute(AttributeId attributeId)
        {
            m_attribute = attributeId;
        }

        std::size_t load(AMeshModelComponentLoader<Component>& loader)
        {
            using DataType = typename Component::DataType;
            loader.template load(m_components);

            GL_CHECK( glBindBuffer(oglu::lazyCast(Component::Target), m_buffer) );
            GL_CHECK( glBufferData(oglu::lazyCast(Component::Target), sizeof(DataType) * m_components.size(), m_components.data(), GL_STATIC_DRAW) );
            return m_components.size();
        }

        void prepareRender()
        {
            using ComponentDataType = typename Component::DataType;
            using ComponentBaseType = typename Component::BaseType;
            using ComponentDataTraits = OpenGlTypeTraits<ComponentBaseType>;

            static constexpr std::size_t const ValuePerVertex = sizeof(ComponentDataType) / sizeof(ComponentBaseType);

            enableVertexAttribute();

            GL_CHECK( glBindBuffer(oglu::lazyCast(Component::Target), m_buffer) );
            GL_CHECK( glVertexAttribPointer(oglu::get(m_attribute), ValuePerVertex, ComponentDataTraits::Enum, GL_FALSE, 0, 0) );

            disableVertexAttribute();
        }

        void enableVertexAttribute()
        {
            GL_CHECK( glEnableVertexAttribArray(oglu::get(m_attribute)) );
        }

        void disableVertexAttribute()
        {
            GL_CHECK( glDisableVertexAttribArray(oglu::get(m_attribute)) );
        }
    private:
        std::vector<typename Component::DataType> m_components;
        GLuint m_buffer;
        AttributeId m_attribute;
    };
}