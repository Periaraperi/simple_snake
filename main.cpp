#include "snake.hpp"

int main() 
{
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0) {
        printf("Could not init SDL %s \n", SDL_GetError());
        return -1;
    }

    const int screen_width  = 640;
    const int screen_height = 640;
    SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, 
                                                   SDL_WINDOWPOS_CENTERED, 
                                                   screen_width, screen_height, 
                                                   SDL_WINDOW_SHOWN);    
    
    if(window==nullptr) {
        printf("Window error %s \n", SDL_GetError());
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 1);
    if(renderer==nullptr) {
        printf("Renderer error %s \n", SDL_GetError());
        return -1;
    }

    Snake *game = new Snake(screen_width, screen_height, 32);
    
    uint32_t prev_tick = 0;
    float dt = 0.0f;
    float accumulator = 0.0f;
    const float fixed_time_step = 0.06f;

    while(game->is_running()) {
        uint32_t current_tick = SDL_GetTicks(); // in milliseconds
        uint32_t delta_ticks = current_tick - prev_tick; // in milliseconds
        prev_tick = current_tick; // in milliseconds
        dt = delta_ticks*0.001f; // convert to seconds
        accumulator += dt;

        game->handle_events();
        while(accumulator>=fixed_time_step) {
            game->update();
            accumulator -= fixed_time_step;
        }

        SDL_SetRenderDrawColor(renderer, 50, 10, 30, 255);
        SDL_RenderClear(renderer);
        game->draw(renderer);
        SDL_RenderPresent(renderer);
    }
    SDL_Delay(500);
    printf("Game over\n");

    delete game;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
