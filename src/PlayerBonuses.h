#ifndef PLAYER_BONUSES_H
#define PLAYER_BONUSES_H

#include <string>
#include <vector>

#include "AbilityValues.h"
#include "Converters.h"
#include "Engine.h"

#include <math.h>

using namespace std;

// *************************************************** //
// Keep the following values lexicographically sorted! //
// *************************************************** //
enum PlayerBonuses_t {
  playerBonus_adeptMeleeCombatant,
//playerBonus_aggressive,
//  playerBonus_athletic,
//playerBonus_clearThinker,
  playerBonus_coolHeaded,
//playerBonus_courageous,
  playerBonus_curer,
//playerBonus_deadlyThrower,
  playerBonus_dexterous,
//  playerBonus_elusive,
  playerBonus_healthy,
  playerBonus_imperceptible,
  playerBonus_lithe,
  playerBonus_marksman,
  playerBonus_masterfulMeleeCombatant,
  playerBonus_mobile,
//  playerBonus_nimbleHanded,
  playerBonus_observant,
  playerBonus_occultist,
  playerBonus_rapidRecoverer,
  playerBonus_rugged,
  playerBonus_selfAware,
  playerBonus_sharpshooter,
  playerBonus_skillfulWoundTreater,
  playerBonus_steadyAimer,
  playerBonus_stealthy,
  playerBonus_strongBacked,
  playerBonus_strongMinded,
//playerBonus_swiftAssailant,
//playerBonus_swiftRetaliator,
  playerBonus_tough,
  playerBonus_treasureHunter,
//playerBonus_tumbler,
  playerBonus_unyielding,
  playerBonus_vigilant,
  playerBonus_vigorous,
//playerBonus_wakeful,
  playerBonus_warlock,
  endOfPlayerBonuses
};

class PlayerBonus {
public:
  PlayerBonus(string title, string description, vector<PlayerBonuses_t> prereqs) :
    title_(title), description_(description), prereqs_(prereqs), isPicked_(false) {
  }
  PlayerBonus() {
  }
  string title_;
  string description_;
  vector<PlayerBonuses_t> prereqs_;
  bool isPicked_;
protected:
};

class PlayerBonusHandler {
public:
  PlayerBonusHandler(Engine* engine);

  void addSaveLines(vector<string>& lines) {
    for(unsigned int i = 0; i < endOfPlayerBonuses; i++) {
      lines.push_back(bonuses_[i].isPicked_ ? intToString(1) : intToString(0));
    }
  }

  void setParametersFromSaveLines(vector<string>& lines) {
    for(unsigned int i = 0; i < endOfPlayerBonuses; i++) {
      bonuses_[i].isPicked_ = lines.front() == intToString(0) ? false : true;
      lines.erase(lines.begin());
    }
  }

  bool isBonusPicked(const PlayerBonuses_t bonus) {
    return bonuses_[bonus].isPicked_;
  }

  void setAllToUnpicked() {
    for(unsigned int i = 0; i < endOfPlayerBonuses; i++) {
      bonuses_[i].isPicked_ = false;
    }
  }

  vector<PlayerBonuses_t> getBonusChoices() const;

  string getBonusTitle(const PlayerBonuses_t bonus) const {
    return bonuses_[bonus].title_;
  }

  void getAllPickedBonusTitlesList(vector<string>& titles);
  void getAllPickedBonusTitlesLine(string& str);

  string getBonusDescription(const PlayerBonuses_t bonus) const {
    return bonuses_[bonus].description_;
  }

  void pickBonus(const PlayerBonuses_t bonus);

  void setAllBonusesToPicked() {
    for(unsigned int i = 0; i < endOfPlayerBonuses; i++) {
      bonuses_[i].isPicked_ = true;
    }
  }

  vector<PlayerBonuses_t> getBonusPrereqs(const PlayerBonuses_t bonusId) const;

private:
  Engine* eng;

  void setBonus(const PlayerBonuses_t bonus, const string title,
                const string description,
                const PlayerBonuses_t prereq1 = endOfPlayerBonuses,
                const PlayerBonuses_t prereq2 = endOfPlayerBonuses,
                const PlayerBonuses_t prereq3 = endOfPlayerBonuses);

  PlayerBonus bonuses_[endOfPlayerBonuses];
};

#endif
