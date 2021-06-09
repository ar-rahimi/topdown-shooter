//
// Created by Ahmad Rahimi on 9/25/17.
//

#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H
#include <map>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <Box2D/Box2D.h>
#include "contactlistener.h"
struct SDL_Window;
struct SDL_Renderer;

class RenderManager {
public:
    RenderManager();
    ~RenderManager();

    SDL_Surface* loadImage(const std::string &filePath);
    /* void blitSurface
     * Drawing images on a screen
     */
    void blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle, double angle = 0);

    /* void flip
     * Render everything on screen
     */
    void flip();

    /* void clear
     * Clear the screen
     */
    void clear();

    /* SDL_Renderer* getRenderer
     * Returns the renderer
     */
    SDL_Renderer* getRenderer() const;

    static RenderManager* getRenderManager();
    //world
    b2World* world;
    b2Vec2 gravity;

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    int _rendercount;
    std::map<std::string, SDL_Surface*> _spriteSheets;
    static RenderManager *renderManager;
};
#endif //GRAPHICSMANAGER_H
