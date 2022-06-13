#include <iostream>
#include <SDL.h>

SDL_Surface* image = NULL;
SDL_Window* window = NULL;

int main(int argc, char* args[])
{
    if(SDL_Init( SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL failed to initialize!");
        SDL_Quit();
        return 0;
    }
    
    window = SDL_CreateWindow("SDL!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 32);
    //Load the image
    image = SDL_LoadBMP("graphics/image.bmp");
    if(image == NULL)
    {
        printf("Image failed to load!\n");
        SDL_Quit();
        return 0;
    }
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (render == nullptr) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    //Draw the image
    SDL_Texture *texture = SDL_CreateTextureFromSurface(render, image);
    SDL_FreeSurface(image);
    if (texture == nullptr){
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    /* Draw the render on window */
    SDL_RenderClear(render); // Fill render with color
    SDL_RenderCopy(render, texture, NULL, NULL); // Copy the texture into render
    SDL_RenderPresent(render); // Show render on window
    //Wait
    SDL_Delay(3000);
    //Finish
    SDL_FreeSurface(image);
    SDL_Quit();
    return 1;
}