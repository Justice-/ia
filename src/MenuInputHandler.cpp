#include "MenuInputHandler.h"

#include "Engine.h"
#include "Input.h"

MenuAction_t MenuInputHandler::getAction(MenuBrowser& browser) {
  while(true) {
    KeyboardReadReturnData d = eng->input->readKeysUntilFound();

    if(d.sdlKey_ == SDLK_RIGHT || d.key_ == '6') {
      browser.navigate(direction_right);
      return menuAction_browsed;
    }
    else if(d.sdlKey_ == SDLK_LEFT || d.key_ == '4') {
      browser.navigate(direction_left);
      return menuAction_browsed;
    }
    else if(d.sdlKey_ == SDLK_UP || d.key_ == '8') {
      browser.navigate(direction_up);
      return menuAction_browsed;
    }
    else if(d.sdlKey_ == SDLK_DOWN || d.key_ == '2') {
      browser.navigate(direction_down);
      return menuAction_browsed;
    }
    else if(d.sdlKey_ == SDLK_RETURN) {
      d.key_ = browser.enter();
      if(d.isShiftHeld_) {
        d.key_ = d.key_ - 'a' + 'A';
      }
    }
    else if(d.sdlKey_ == SDLK_SPACE || d.sdlKey_ == SDLK_ESCAPE) {
      return menuAction_canceled;
    }

    const int SIZE_OF_FIRST_LIST = browser.getNrOfItemsInFirstList();
    const int SIZE_OF_SECOND_LIST = browser.getNrOfItemsInSecondList();

    const int TOT_SIZE_OF_LISTS = SIZE_OF_FIRST_LIST + SIZE_OF_SECOND_LIST;

////    const int NR_LETTERS_A_TO_Z = int('z' - 'a');

    if((d.key_ >= 'a' && int(d.key_ - 'a') < TOT_SIZE_OF_LISTS)) {
      browser.navigate(d.key_);
      return menuAction_selected;
    }
    if((d.key_ >= 'A' && int(d.key_ - 'A') < TOT_SIZE_OF_LISTS)) {
      browser.navigate(d.key_ - 'A' + 'a');
      return menuAction_selectedWithShift;
    }
  }
  return menuAction_canceled;
}

