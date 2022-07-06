#pragma once

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <vector>
#include <queue>
#include <time.h>
#include <stdio.h>
#include <string.h>

class Snake {
public:
    enum Direction {
        RIGHT, LEFT, DOWN, UP    
    };
    struct Cell {
        int x;
        int y;
    };
    Snake(const int &screenW, const int &screenH, const int &cell_dimensions);
    ~Snake();
    bool is_running();
    void update();
    void draw(SDL_Renderer *renderer);     
    void handle_events();
private:
    int m_width;
    int m_height;
    const int m_cell_pixels; // each cell in our game will be cellPixels x cellPixels big
    bool m_running;
    bool m_food_eaten;
    Cell m_food;
    std::vector<Cell> m_snake; // store cell coordinates (not scaled to screen coordinates)
    const std::vector<Cell> m_dir = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    Direction m_current_direction;
    // drawing
    SDL_Rect m_dst;
    SDL_Color m_head_color;
    SDL_Color m_food_color;
    SDL_Color m_segment_color;

    // events
    std::queue<Direction> m_events;
    SDL_Event m_ev;
    int m_key_length;
    const Uint8 *m_keyboard_state;
    Uint8 *m_prev_keyboard_state;
    // game essential functions
    void update_food();
    void move();
    void grow();
    int check_collision(Cell cell);
    void update_prev_keyboard_state();
    bool key_pressed(SDL_Scancode key);
};


