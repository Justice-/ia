#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>

#include "Actor.h"
#include "CommonTypes.h"

const int MIN_SHOCK_WHEN_OBSESSION = 35;

enum InsanityPhobia_t {
  insanityPhobia_rat,
  insanityPhobia_spider,
  insanityPhobia_dog,
  insanityPhobia_undead,
  insanityPhobia_openPlace,
  insanityPhobia_closedPlace,
  insanityPhobia_deepPlaces,
  endOfInsanityPhobias
};

enum InsanityObsession_t {
  insanityObsession_sadism,
  insanityObsession_masochism,
  endOfInsanityObsessions
};

class Monster;

class Player: public Actor {
public:
  Player();
  ~Player() {}

  int getHpMax(const bool WITH_MODIFIERS) const;

  void updateFov();

  void moveDirection(const coord& dir) {moveDirection(dir.x, dir.y);}
  void moveDirection(const int X_DIR, int Y_DIR);

  void actorSpecific_init() {}

  void actorSpecific_spawnStartItems();

  void act();

  void hearSound(const Sound& sound);

  void explosiveThrown();

  int firstAidTurnsLeft;
  int waitTurnsLeft;

  void incrShock(const ShockValues_t shockValue);
  void incrShock(const int VAL);
  void restoreShock(const int amountRestored, const bool IS_TEMP_SHOCK_RESTORED);
  int getShockTotal() {return int(floor(shock_ + shockTemp_));}
  int getShockTmp() {return shockTemp_;}
  int getInsanity() const {return min(100, insanity_);}
  void incrMth(const int VAL);
  int getMth() const {return mth;}
  void setTempShockFromFeatures();

  int getShockResistance() const;

  int getCarryWeightLimit() const;

  int dynamiteFuseTurns;
  int molotovFuseTurns;
  int flareFuseTurns;

  void addSaveLines(vector<string>& lines) const;
  void setParametersFromSaveLines(vector<string>& lines);

  bool insanityPhobias[endOfInsanityPhobias];
  bool insanityObsessions[endOfInsanityObsessions];

  const Actor* target;

  void autoMelee();

  void kick(Actor& actorToKick);
  void punch(Actor& actorToPunch);

  void updateColor();

  int getHealingTimeTotal() const;

  void actorSpecific_addLight(bool light[MAP_X_CELLS][MAP_Y_CELLS]) const;

  void grantMthPower() const;

private:
  friend class DungeonMaster;
  friend class GameTime;
  friend class MessageLog;

  void incrInsanity();
  void tryIdentifyItems();
  void testPhobias();
  void actorSpecific_hit(const int DMG);
  void FOVhack();
  void interruptActions(const bool PROMPT_FOR_ABORT);
  bool isStandingInOpenSpace() const;
  bool isStandingInCrampedSpace() const;

  int insanity_;
  double shock_, shockTemp_;

  int mth;

  int nrMovesUntilFreeAction;

  const int carryWeightBase;
};


#endif
