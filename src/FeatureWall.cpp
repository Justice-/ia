#include "FeatureWall.h"

#include "Engine.h"

#include "Map.h"

Wall::Wall(Feature_t id, coord pos, Engine* engine) :
  FeatureStatic(id, pos, engine), wallType(wall_common), isMossGrown(false) {
}

bool Wall::isTileAnyWallFront(const Tile_t tile) {
  return
    tile == tile_wallFront ||
    tile == tile_wallFrontAlt1 ||
    tile == tile_wallFrontAlt2 ||
    tile == tile_caveWallFront ||
    tile == tile_egyptWallFront;
}

bool Wall::isTileAnyWallTop(const Tile_t tile) {
  return
    tile == tile_wallTop ||
    tile == tile_caveWallTop ||
    tile == tile_egyptWallTop ||
    tile == tile_rubbleHigh;
}

string Wall::getDescription(const bool DEFINITE_ARTICLE) const {
  switch(wallType) {
  case wall_common:
  case wall_alt1: {
    const string modStr = isMossGrown ? "moss-grown " : "";
    return DEFINITE_ARTICLE ? "the " + modStr + "stone wall" : "a " + modStr + "stone wall";
  }
  break;
  case wall_cave: {
    const string modStr = isMossGrown ? "moss-grown " : "";
    return DEFINITE_ARTICLE ? "the " + modStr + "cavern wall" : "a " + modStr + "cavern wall";

  }
  case wall_egypt: {
    const string modStr = isMossGrown ? "moss-grown " : "";
    return DEFINITE_ARTICLE ? "the " + modStr + "stone wall" : "a " + modStr + "stone wall";

  }
  }
  return "[ERROR]";
}

SDL_Color Wall::getColor() const {
  if(isMossGrown) {
    return clrGreen;
  }

  if(wallType == wall_cave) {
    return clrBrownGray;
  }

  if(wallType == wall_egypt) {
    return clrBrownGray;
  }

  return def_->color; // clrGray;
}

char Wall::getGlyph() const {
  if(eng->config->isAsciiWallSymbolFullSquare) {
    return 10;
  } else {
    return '#';
  }
}

Tile_t Wall::getFrontWallTile() const {
  switch(wallType) {
  case wall_common:
    return tile_wallFront;
    break;
  case wall_alt1:
    return tile_wallFrontAlt1;
    break;
  case wall_cave:
    return tile_caveWallFront;
    break;
  case wall_egypt:
    return tile_egyptWallFront;
    break;
  default:
    return tile_wallFront;
    break;
  }
}

Tile_t Wall::getTopWallTile() const {
  switch(wallType) {
  case wall_common:
    return tile_wallTop;
    break;
  case wall_alt1:
    return tile_wallTop;
    break;
  case wall_cave:
    return tile_caveWallTop;
    break;
  case wall_egypt:
    return tile_egyptWallTop;
    break;
  default:
    return tile_wallTop;
    break;
  }
}

void Wall::setRandomNormalWall() {
  const int RND = eng->dice.getInRange(1, 6);
  switch(RND) {
  case 1:
    wallType = wall_alt1;
    break;
//  case 2: wallType = wall_alt2; break;
  default:
    wallType = wall_common;
    break;
  }
}

void Wall::setRandomIsMossGrown() {
  isMossGrown = eng->dice.getInRange(1, 40) == 1;
}


