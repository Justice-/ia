#include "MapBuild.h"

#include "Engine.h"
#include "ActorPlayer.h"
#include "FeatureFactory.h"
#include "ActorFactory.h"
#include "ActorMonster.h"
#include "Map.h"
#include "FeatureWall.h"

void MapBuild::buildKingsTomb() {
  eng->map->clearDungeon();

  buildFromTemplate(coord(0, 0), mapTemplate_pharaohsChamber);

  eng->player->pos = coord(40, 13);

  for(int y = 0; y < MAP_Y_CELLS; y++) {
    for(int x = 0; x < MAP_X_CELLS; x++) {
      Feature* const f = eng->map->featuresStatic[x][y];
      if(f->getId() == feature_stoneWall) {
        dynamic_cast<Wall*>(f)->wallType = wall_egypt;
      }
    }
  }

  if(eng->dice.coinToss()) {
    eng->featureFactory->spawnFeatureAt(feature_stairsDown, coord(4, 2), NULL);
  } else {
    eng->featureFactory->spawnFeatureAt(feature_stairsDown, coord(4, 23), NULL);
  }


  dynamic_cast<Monster*>(eng->actorFactory->spawnActor(actor_mummy, coord(12, 12)))->isRoamingAllowed = false;
  dynamic_cast<Monster*>(eng->actorFactory->spawnActor(actor_khephren, coord(11, 13)))->isRoamingAllowed = false;
  dynamic_cast<Monster*>(eng->actorFactory->spawnActor(actor_mummy, coord(12, 14)))->isRoamingAllowed = false;

  dynamic_cast<Monster*>(eng->actorFactory->spawnActor(actor_cultist, coord(17, 11)))->isRoamingAllowed = false;
  dynamic_cast<Monster*>(eng->actorFactory->spawnActor(actor_cultist, coord(17, 15)))->isRoamingAllowed = false;

}
