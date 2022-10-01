#include "context/GameContext.hpp"
#include "utils/Logger.hpp"

namespace arcana {
    GameContext::GameContext() {
        window.setEventData(events.get());
        keyboard.setEventData(events.get());
        mouse.setEventData(events.get());
    }

    Vector2 GameContext::CtxWindow::getWindowSize() {return window->getWindowSize();}
    void GameContext::CtxWindow::setMinWindowSize(int min_width, int min_height) {window->setMinSize(Vector2(min_width, min_height));}
    void GameContext::CtxWindow::setMaxWindowSize(int max_width, int max_height) {window->setMaxSize(Vector2(max_width, max_height));}
    void GameContext::CtxWindow::setWindowPos(int x, int y) {setWindowPos(Vector2(x, y));}
    void GameContext::CtxWindow::setWindowPos(Vector2 pos) {window->setWindowPos(pos);}
    void GameContext::CtxWindow::restoreWindow() {window->restore();}
    void GameContext::CtxWindow::minimizeWindow() {window->minimize();}
    void GameContext::CtxWindow::maximizeWindow() {window->maximize();}
    void GameContext::CtxWindow::updateTitle(const char* title) {
        window->updateTitle(title);
    }

    GameContext::~GameContext() {

    }   

}