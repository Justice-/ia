#ifndef PLAYER_POWERS_HANDLER_H
#define PLAYER_POWERS_HANDLER_H

/*
 * Responsible for providing a user interface for selecting spells to cast,
 * gathered from all sources (scrolls, memorised scrolls, etc), and also for
 * ending the turn when the spell was cast.
 *
 */

#include <vector>

#include "MenuBrowser.h"

using namespace std;

class Engine;
class Scroll;

class PlayerPowersHandler {
public:
	PlayerPowersHandler(Engine* engine);
	~PlayerPowersHandler();

	void run();

	inline unsigned int getNrOfSpells() const {
	  return scrollsToReadFromPlayerMemory.size();
	}

  Scroll* getScrollAt(const unsigned int SCROLL_VECTOR_ELEMENT) const;

private:
	void draw(MenuBrowser& browser, const vector<unsigned int> memorizedScrollsToShow);

	vector<Scroll*> scrollsToReadFromPlayerMemory;

	Engine* eng;

};

#endif
