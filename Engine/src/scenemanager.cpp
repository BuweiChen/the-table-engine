#include <iostream>

#include "gameobject.h"
#include "transform.h"
#include "resourcemanager.h"
#include "texture.h"
#include "scenemanager.h"
#include "gameobjectfactory.h"
#include <fstream>
#include <iostream>

std::atomic<uint64_t> SceneManager::m_totalObjects = 0;
std::atomic<uint64_t> SceneManager::m_aliveObjects = 0;

SceneManager& SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

SceneManager::SceneManager() {
    m_camera = new Camera();
}

void SceneManager::setRenderer(SDL_Renderer* renderer) {
    m_renderer = renderer;
}

SceneTree* SceneManager::getSceneTree() {
    return m_sceneTrees[m_currentSceneIndex];
}

void SceneManager::loadDemo() {
    m_sceneTrees.push_back(createSceneTest1());
    m_sceneTrees.push_back(createSceneTest2());
    m_sceneTrees.push_back(createSceneTest3());
}

void SceneManager::loadScenesFromJSON(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        throw std::runtime_error("Could not open JSON file: " + filePath);
    }

    nlohmann::json gameData;
    file >> gameData;

    // Parse object definitions
    std::unordered_map<std::string, nlohmann::json> objectDefinitions;
    if (gameData.contains("object_definitions")) {
        for (const auto& [type, objects] : gameData["object_definitions"].items()) {
            for (const auto& [name, definition] : objects.items()) {
                objectDefinitions[name] = definition;
            }
        }
    } else {
        std::cerr << "No object definitions found in JSON file.\n";
    }

    // Parse levels and create scenes
    if (gameData.contains("levels")) {
        for (const auto& level : gameData["levels"]) {
            SceneTree* sceneTree = new SceneTree();

            for (const auto& object : level["objects"]) {
                std::string name = object["name"];
                if (objectDefinitions.find(name) != objectDefinitions.end()) {
                    const auto& definition = objectDefinitions[name];
                    int x = object["x"];
                    int y = object["y"];

                    // Create a tile or other object based on its definition
                    if (definition["properties"].contains("type") && definition["properties"]["type"] == "Tile") {
                        std::cout << "Creating tile\n";
                        auto tile = GameObjectFactory::createTileCustom(
                            definition["file"],
                            Vec2(x, y),
                            Vec2(definition["length"], definition["width"]),
                            Vec2(definition["size_width"], definition["size_height"]),
                            Vec2(definition["top_left_x"], definition["top_left_y"])
                        );
                        std::cout << "Added tile: " << name << '\n' << " at (" << x << ", " << y << ")\n";
                        sceneTree->addChild(tile, true);
                    }

                    else if (definition["properties"].contains("type") && definition["properties"]["type"] == "Wall") {
                        std::cout << "Creating wall\n";
                        auto wall = GameObjectFactory::createWallCustom(
                            definition["file"],
                            Vec2(x, y),
                            Vec2(definition["length"], definition["width"]),
                            Vec2(definition["size_width"], definition["size_height"]),
                            Vec2(definition["top_left_x"], definition["top_left_y"])
                        );
                        std::cout << "Added wall: " << name << " at (" << x << ", " << y << ")\n";
                        sceneTree->addChild(wall, true);
                    }
                    else if (definition["properties"].contains("type") && definition["properties"]["type"] == "Table") {
                        std::cout << "Creating table\n";
                        auto table = GameObjectFactory::createTableCustom(
                            definition["file"],
                            Vec2(x, y),
                            Vec2(definition["length"], definition["width"]),
                            Vec2(definition["size_width"], definition["size_height"]),
                            Vec2(definition["top_left_x"], definition["top_left_y"])
                        );
                        std::cout << "Added table: " << name << " at (" << x << ", " << y << ")\n";
                        sceneTree->addChild(table, true);
                    }
                    // Add additional logic for other object types later...

                    else if (definition["properties"].contains("type") && definition["properties"]["type"] == "Enemy") {
                        std::cout << "Creating enemy\n";
                        auto enemy = GameObjectFactory::createEnemyWarriorCustom(
                            definition["file"],
                            definition["rows"],
                            definition["columns"],
                            definition["animation_time"],
                            x,
                            y,
                            definition["width"],
                            definition["length"]
                        );
                        std::cout << "Created enemy\n";
                        sceneTree->addChild(enemy, true);

                        std::cout << "Added enemy: " << name << " at (" << x << ", " << y << ")\n";
                    }
                } else {
                    std::cerr << "Object definition not found for: " << name << "\n";
                }
            }

            GameObject* player = GameObjectFactory::createPlayerTest();
            sceneTree->addChild(player);

            GameObject* bow = GameObjectFactory::createBow();
            player->getSceneNode()->addChild(bow);

            m_sceneTrees.push_back(sceneTree);
            std::cout<< "Loaded scene\n";

            GameObject* crosshair = GameObjectFactory::createCrosshair(); // Assuming this method exists in GameObjectFactory
            sceneTree->addChild(crosshair);
        }
    } else {
        std::cerr << "No levels found in JSON file.\n";
    }
}

SDL_Renderer* SceneManager::getRenderer() {
    return m_renderer;
}

Vec2 SceneManager::getCameraWorldPosition() {
    return m_camera->getWorldPosition();
}

void SceneManager::getNextScene() {
    int numScenes = static_cast<int>(m_sceneTrees.size());
    if (m_currentSceneIndex < static_cast<int>(m_sceneTrees.size()) - 1) {
        m_currentSceneIndex++;
    } else if (numScenes != 1) {
        std::cout << "Finished all scenes.\n";
        exit(0);
        // std::cerr << "No more scenes to transition to.\n";
    }
}

int SceneManager::getSceneIndex() {
    return m_currentSceneIndex;
}

SceneTree* SceneManager::createSceneTest1() {
    SceneTree* sceneTree = new SceneTree();

    int lenTiles = 20;
    for (int i = -lenTiles; i < lenTiles; i++) {
        for (int j = -lenTiles; j < lenTiles; j++) {
            GameObject* tile = GameObjectFactory::createTile1();
            tile->getComponent<Transform>()->setWorldPosition(i * 32, j * 32);
            sceneTree->addChild(tile, true);
        }
    }

    for (int i = 0; i < 10; i++)
    {
        int x = rand() % 1200 - 600;
        int y = rand() % 1200 - 600;
        GameObject* key = GameObjectFactory::createKey();
        key->getComponent<Transform>()->setWorldPosition(x, y);
        sceneTree->addChild(key);
    }

    GameObject* player = GameObjectFactory::createPlayerTest();
    sceneTree->addChild(player);
    GameObject* bow = GameObjectFactory::createBow();
    player->getSceneNode()->addChild(bow);

    for (int i = 0; i < 10; i++) {
        GameObject* enemy = GameObjectFactory::createEnemyWarrior();
        enemy->getComponent<Transform>()->setWorldPosition(100 + i * 50, 100);
        sceneTree->addChild(enemy);
    }

    GameObject* crosshair = GameObjectFactory::createCrosshair(); // Assuming this method exists in GameObjectFactory
    sceneTree->addChild(crosshair);

    return sceneTree;
}

SceneTree* SceneManager::createSceneTest2() {
    SceneTree* sceneTree = new SceneTree();

    int lenTiles = 20;
    for (int i = -lenTiles; i < lenTiles; i++) {
        for (int j = -lenTiles; j < lenTiles; j++) {
            GameObject* tile = GameObjectFactory::createTile1();
            tile->getComponent<Transform>()->setWorldPosition(i * 32, j * 32);
            sceneTree->addChild(tile, true);
        }
    }

    for (int i = 0; i < 20; i++)
    {
        int x = rand() % 1200 - 600;
        int y = rand() % 1200 - 600;
        GameObject* key = GameObjectFactory::createKey();
        key->getComponent<Transform>()->setWorldPosition(x, y);
        sceneTree->addChild(key);
    }

    GameObject* player = GameObjectFactory::createPlayerTest();
    sceneTree->addChild(player);
    GameObject* bow = GameObjectFactory::createBow();
    player->getSceneNode()->addChild(bow);

    for (int i = 0; i < 20; i++) {
        GameObject* enemy = GameObjectFactory::createEnemyWarrior();
        enemy->getComponent<Transform>()->setWorldPosition(100 + i * 50, 100);
        sceneTree->addChild(enemy);
    }

    GameObject* crosshair = GameObjectFactory::createCrosshair(); // Assuming this method exists in GameObjectFactory
    sceneTree->addChild(crosshair);

    return sceneTree;
}

SceneTree* SceneManager::createSceneTest3() {
    SceneTree* sceneTree = new SceneTree();

    int lenTiles = 20;
    for (int i = -lenTiles; i < lenTiles; i++) {
        for (int j = -lenTiles; j < lenTiles; j++) {
            GameObject* tile = GameObjectFactory::createTile1();
            tile->getComponent<Transform>()->setWorldPosition(i * 32, j * 32);
            sceneTree->addChild(tile, true);
        }
    }

    for (int i = 0; i < 30; i++)
    {
        int x = rand() % 1200 - 600;
        int y = rand() % 1200 - 600;
        GameObject* key = GameObjectFactory::createKey();
        key->getComponent<Transform>()->setWorldPosition(x, y);
        sceneTree->addChild(key);
    }

    GameObject* player = GameObjectFactory::createPlayerTest();
    sceneTree->addChild(player);
    GameObject* bow = GameObjectFactory::createBow();
    player->getSceneNode()->addChild(bow);

    for (int i = 0; i < 30; i++) {
        GameObject* enemy = GameObjectFactory::createEnemyWarrior();
        enemy->getComponent<Transform>()->setWorldPosition(100 + i * 50, 100);
        sceneTree->addChild(enemy);
    }

    GameObject* crosshair = GameObjectFactory::createCrosshair(); // Assuming this method exists in GameObjectFactory
    sceneTree->addChild(crosshair);

    return sceneTree;
}

void SceneManager::cleanTree()
{
    auto sceneTree = SceneManager::getInstance().getSceneTree();
    if (sceneTree == nullptr) return; 

    sceneTree->traverseTree([](SceneNode* node) {
        if (node->getGameObject() != nullptr) {
        }
        if (node->readyToDestroy()) {
            delete node;
        }
    });
}

void SceneManager::input()
{
    auto sceneTree = SceneManager::getInstance().getSceneTree();
    if (sceneTree == nullptr) return;

    sceneTree->traverseTree([](SceneNode* node) {
        if (!node->isBackground() && node->getGameObject())
            node->getGameObject()->input();
    });
}

void SceneManager::update()
{
    m_camera->update();
    auto sceneTree = SceneManager::getInstance().getSceneTree();
    if (sceneTree == nullptr) return;

    sceneTree->traverseTree([](SceneNode* node) {
        if (node->getGameObject())
            node->getGameObject()->update();
    });

    cleanTree();

    if (sceneTree->gameStatus() == -1)
        exit(0);
    else if (sceneTree->gameStatus() == 1)
        getNextScene();
}

void SceneManager::render()
{
    auto sceneTree = SceneManager::getInstance().getSceneTree();
    if (sceneTree == nullptr) return;

    sceneTree->traverseTree([](SceneNode* node) {
        if (node->getGameObject())
            node->getGameObject()->render();
    });

    sceneTree->resetCachedGameObjectsInFrame();
}
