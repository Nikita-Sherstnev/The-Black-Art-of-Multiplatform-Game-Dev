#include <iostream>
#include <SDL.h>

SDL_Surface* background = NULL;
SDL_Surface* sprite = NULL;
SDL_Window* window = NULL;

bool ProgramIsRunning();
bool LoadImages();
void FreeImages();


int main(int argc, char* args[])
{
    if(SDL_Init( SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL failed to initialize!");
        SDL_Quit();
        return 0;
    }
    
    window = SDL_CreateWindow("SDL!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 32);

    if(!LoadImages())
    {
        printf("Images failed to load!\n");
        FreeImages();
        SDL_Quit();
        return 0;
    }

    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (render == nullptr) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Texture *backTexture = SDL_CreateTextureFromSurface(render, background);
    if (backTexture == nullptr){
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Rect backPos;
    backPos.x = 0;
    backPos.y = 0;
    backPos.w = 800;
    backPos.h = 600;

    SDL_RenderCopy(render, backTexture, NULL, &backPos);
    SDL_RenderPresent(render);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(render, sprite);

    while(ProgramIsRunning())
    {
        SDL_Rect spritePos;
        spritePos.x = rand()%800;
        spritePos.y = rand()%600;
        spritePos.w = 100;
        spritePos.h = 100;

        SDL_RenderCopy(render, texture, NULL, &spritePos);
        SDL_RenderPresent(render);
        SDL_Delay(100);
    }
    
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(backTexture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 1;
}

bool ProgramIsRunning() {
    SDL_Event event;
    bool running = true;

    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT)
        running = false;
    }
    return running;
}

bool LoadImages()
{
    background = SDL_LoadBMP("../graphics/download.bmp");
    if(background == NULL)
        return false;
    sprite = SDL_LoadBMP("../graphics/sprite.bmp");
    if(sprite == NULL)
        return false;
    return true;
}

void FreeImages()
{
    if(background != NULL)
    {
        SDL_FreeSurface(background);
        background = NULL;
    }
    if(sprite != NULL)
    {
        SDL_FreeSurface(sprite);
        sprite = NULL;
    }
}