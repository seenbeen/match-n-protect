#include <render/batcherizer.hpp>

namespace MNPRender {
    Batcherizer::BatchBundle::BatchBundle(const sf::FloatRect &imageRect, const sf::FloatRect &textureRect, float depth) {
        _imageRect = imageRect;
        _textureRect = textureRect;
        _depth = depth;
        _layersInfrontOf = 0;
    }

    Batcherizer::Batcherizer() {}
    Batcherizer::~Batcherizer() {
        std::list<BatchBundle*>::iterator it;
        for (it = m_batchBundles.begin(); it != m_batchBundles.end(); ++it) {
            delete *it;
        }
    }

    void Batcherizer::push(const sf::FloatRect &imageRect, const sf::FloatRect &textureRect, float depth) {
        m_batchBundles.push_back(new BatchBundle(imageRect,textureRect,depth));
    }

    bool Batcherizer::BatchBundle::batchBundleDepthCmp(const BatchBundle *a, const BatchBundle *b) {
        return a->_depth < b->_depth;
    }

    void Batcherizer::batcherize() {
        m_batchBundles.sort(BatchBundle::batchBundleDepthCmp);
        std::list<BatchBundle*>::iterator it;
        std::list<BatchBundle*>::iterator it2;
        BatchBundle *bundle1, *bundle2;
        m_batches.clear();
        for (it = m_batchBundles.begin(); it != m_batchBundles.end(); ++it) {
            bundle1 = *it;
            for (it2 = m_batchBundles.begin(); it2 != it; ++it2) {
                bundle2 = *it2;
                if (bundle1->_imageRect.intersects(bundle2->_imageRect)) {
                    bundle1->_layersInfrontOf = std::max(bundle1->_layersInfrontOf,bundle2->_layersInfrontOf + 1);
                }
            }
            if (bundle1->_layersInfrontOf >= m_batches.size()) {
                m_batches.push_back (sf::VertexArray(sf::Quads));
            }
            int layerIndex = bundle1->_layersInfrontOf;
            m_batches[layerIndex].append(sf::Vertex(sf::Vector2f(bundle1->_imageRect.left,
                                                                 bundle1->_imageRect.top),
                                                    sf::Vector2f(bundle1->_textureRect.left,
                                                                 bundle1->_textureRect.top)));
            m_batches[layerIndex].append(sf::Vertex(sf::Vector2f(bundle1->_imageRect.left+
                                                                 bundle1->_imageRect.width,
                                                                 bundle1->_imageRect.top),
                                                    sf::Vector2f(bundle1->_textureRect.left+
                                                                 bundle1->_textureRect.width,
                                                                 bundle1->_textureRect.top)));
            m_batches[layerIndex].append(sf::Vertex(sf::Vector2f(bundle1->_imageRect.left+
                                                                 bundle1->_imageRect.width,
                                                                 bundle1->_imageRect.top+
                                                                 bundle1->_imageRect.height),
                                                    sf::Vector2f(bundle1->_textureRect.left+
                                                                 bundle1->_textureRect.width,
                                                                 bundle1->_textureRect.top+
                                                                 bundle1->_textureRect.height)));
            m_batches[layerIndex].append(sf::Vertex(sf::Vector2f(bundle1->_imageRect.left,
                                                                 bundle1->_imageRect.top+
                                                                 bundle1->_imageRect.height),
                                                    sf::Vector2f(bundle1->_textureRect.left,
                                                                 bundle1->_textureRect.top+
                                                                 bundle1->_textureRect.height)));
        }
        for (it = m_batchBundles.begin(); it != m_batchBundles.end(); ++it) {
            delete *it;
        }
        m_batchBundles.clear();
    }

    std::vector<sf::VertexArray> &Batcherizer::getBatches() {
        return m_batches;
    }
}

