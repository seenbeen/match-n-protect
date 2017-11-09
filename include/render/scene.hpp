#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <set>

#include <core/math.hpp>
#include <render/image-atlas.hpp>
#include <render/batcherizer.hpp>

namespace MNPRender {
    class SceneObject;

    class Scene {
        std::set<SceneObject*> m_objects;
        Batcherizer m_batcherizer;
        ImageAtlas &m_imageAtlas;

    public:
        /*
            Note: Scene does not take ownership of imageAtlas;
            In other words, the caller is still responsible for
            freeing any allocated memory by the ImageAtlas.
        */
        Scene(ImageAtlas &imageAtlas);
        ~Scene();
        bool addObject(SceneObject *object);
        bool removeObject(SceneObject *object);
        void update(const sf::Time &deltaTime);
        void render(sf::RenderTarget &renderTarget);
    };

    class SceneObject {
    public:
        std::string resource;

        MNPCore::Transform transform;

        SceneObject(const std::string &resource);
        virtual ~SceneObject();
        virtual void update(const sf::Time &deltaTime);
    };
}
