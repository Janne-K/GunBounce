#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "PlayerGun.h"
#include "ShotProjectile.h"
#include "CollectibleStar.h"

namespace gunbounce {
    class GunBounceLayer : public cocos2d::Layer
    {
    public:
        virtual bool init();
        CREATE_FUNC(GunBounceLayer);
        virtual void update(float dt) override;
    private:
        std::shared_ptr<PlayerGun> player;
        std::shared_ptr<CollectibleStar> star;
        std::queue<std::shared_ptr<ShotProjectile>> shots;
        cocos2d::Label* scoreLabel;
        cocos2d::Label* levelLabel;
        void addShotToList(std::shared_ptr<ShotProjectile> shotToAdd);
        void stageSetup();
        void updateLabels();
        void spawnPauseMenu();
        void pauseNodes();
        void handlePlayerDeath();
        void handleCollectStar();
        void addScore(int scoreToAdd);
        void randomizeStarPosition();
        void playerShoot();
        void checkMaxShots();
        void eraseOldestShot();
        void createPlayer();
        void createStar();
        int score;
        int level;
        int maxShotsOnScreen;
        float scoreTimer;
    };
}
#endif // __GAME_LAYER_H__
