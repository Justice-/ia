#ifndef DUNGEON_MASTER_H
#define DUNGEON_MASTER_H

#include <iostream>
#include <math.h>

#include "CommonSettings.h"
#include "AbilityValues.h"
#include "Colors.h"
#include "Converters.h"
#include "PlayerCreateCharacter.h"
#include "BasicUtils.h"

class Engine;

class DungeonMaster
{
public:
  DungeonMaster(Engine* engine) : eng(engine) {
    init();
  }
  ~DungeonMaster() {
  }

  int getXp() const {
    return playerExp;
  }

  int getLevel() const {
    return playerLvl;
  }

  int getXpToNextLvl() const {
    return expTable[playerLvl];
  }

  int getXpToNextLvlAtLvl(int lvl) const {
    return expTable[lvl];
  }

  void monsterKilled(Actor* monster);

  void playerGainsExp(int exp);

  void playerGainsXpPercent(const int PERCENT, const int PLUS_XP) {
    const int XP_GAINED = PLUS_XP + int((float(PERCENT) / 100) * float(playerExp));
    playerGainsExp(XP_GAINED);
  }

  void playerLoseXpPercent(const int PERCENT) {
    playerExp = int((float(100 - PERCENT) / 100) * float(playerExp));
  }

  void addSaveLines(vector<string>& lines) const;
  void setParametersFromSaveLines(vector<string>& lines);

  void winGame();

  TimeData getTimeStarted() const {
    return timeStarted;
  }
  void setTimeStartedToNow();

private:
  void init();

  int playerExp, playerLvl;
  void initExpTable();
  int expTable[PLAYER_CLVL_MAX + 1];

  TimeData timeStarted;

  Engine* const eng;
};

#endif
