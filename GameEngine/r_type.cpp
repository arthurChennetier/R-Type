#include <iostream>
#include <utility>
#include <TacosEngine.h>
#include <Sprite/Sprite.hpp>

namespace TacosEngine
{
    class Behaviour;

    class PlayerBehaviour : public Behaviour
    {
    public:
        PlayerBehaviour(const std::string &name, std::shared_ptr<Sprite> sprite)
                : Behaviour(name, std::move(sprite))
        {
        }

        ~PlayerBehaviour() override = default;

        void    Start()
        {
            std::cout << "In Start()" << std::endl;
        }

        void update(const Input &input) override {
            Vector2 dir(input.getAxis("Horizontal"), input.getAxis("Vertical"));
            auto rb = getComponent<Rigidbody>();

            if (input.getAxis("Horizontal") != 0 && input.getAxis("Vertical") != 0)
                dir = dir / 2;
            _object->getTransform().setDirection(dir);
            _object->getTransform().setSpeed(0.5f);
            rb->addForce(dir * _object->getTransform().getSpeed());
        }

        void PlayerBehaviour::onCollide(GameObject &other) override {
            std::cout << "OnCollide() => " << other.getInstanceName() << std::endl;
            if (other.getInstanceName() == "Obs")
            {
                if (auto obs2 = _object->findByName("Obs2"))
                    obs2->getTransform().setPosition(Vector2(10, 10));
                setDestroy(true);
            }
        }
    };
}

using namespace TacosEngine;

int main()
{
    Engine engine;
    std::shared_ptr <Scene> scene = std::make_shared<Scene>("Scene1");

    engine.initRessources("ressources.txt");

    // Scene
    engine.addScene(scene);

    // Sprite background
    std::shared_ptr<Sprite> back = std::make_shared<Sprite>("Background", scene, Layout::BACKGROUND);
    back->setTexture(scene->getTexture("back"));
    back->setSize(Vector2(800, 400));
    scene->addGameObject(back);

    // Sprite ship
    std::shared_ptr <Sprite> player = std::make_shared<Sprite>("Player", scene, Layout::SCENE);
    player->setTexture(scene->getTexture("ship"));
    player->setSize(Vector2(20, 20));
    std::shared_ptr<PlayerBehaviour> playerBeha = std::make_shared<PlayerBehaviour>("playerBeh", player);
    std::shared_ptr<Collider> coll = std::make_shared<Collider>("ok", player, Vector2(20, 20), player->getTransform().getPosition(), true);
    std::shared_ptr<Rigidbody> rig = std::make_shared<Rigidbody>("Rb", player);
    scene->addGameObject(player);
    scene->addComponent(playerBeha);
    scene->addComponent(coll);
    scene->addComponent(rig);

    // Sprite obstacle
    std::shared_ptr <Sprite> obs = std::make_shared<Sprite>("Obs", scene, Layout::SCENE);
    obs->setTexture(scene->getTexture("ship"));
    obs->setSize(Vector2(20, 20));
    obs->getTransform().setPosition(Vector2(400, 200));
    std::shared_ptr<Collider> collObs = std::make_shared<Collider>("Collider", obs, obs->getSize(), obs->getTransform().getPosition(), false);
    std::shared_ptr<Rigidbody> rigObs = std::make_shared<Rigidbody>("Rigidbody", obs);
    scene->addGameObject(obs);
    scene->addComponent(collObs);
    scene->addComponent(rigObs);

    // Sprite obstacle 2
    std::shared_ptr <Sprite> obs2 = std::make_shared<Sprite>("Obs2", scene, Layout::SCENE);
    obs2->setTexture(scene->getTexture("ship"));
    obs2->setSize(Vector2(20, 20));
    obs2->getTransform().setPosition(Vector2(400, 100));
    std::shared_ptr<Collider> collObs2 = std::make_shared<Collider>("Collider", obs2, obs2->getSize(), obs2->getTransform().getPosition(), true);
    std::shared_ptr<Rigidbody> rigObs2 = std::make_shared<Rigidbody>("Rigidbody", obs2);
    scene->addGameObject(obs2);
    scene->addComponent(collObs2);
    scene->addComponent(rigObs2);

    // Load and run scene
    engine.loadScene(scene);
    engine.run();
    return 0;
}