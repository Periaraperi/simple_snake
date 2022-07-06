#include "snake.h"

Snake::Snake(const int& screenW, const int& screenH, const int& cell_dimensions) 
:m_cell_pixels(cell_dimensions)
{
    m_width  = screenW / m_cell_pixels;
    m_height = screenH / m_cell_pixels;
    m_current_direction = RIGHT;
    m_dst = {0,0,m_cell_pixels, m_cell_pixels};

    m_snake.push_back({m_width/2, m_height/2}); // snake head
    m_snake.push_back({m_snake[0].x-1, m_snake[0].y});
    
    m_head_color    = {83,90,44,255};
    m_segment_color = {83,122,44,255};
    m_food_color    = {255,20,0,255};

    m_running = true;
    
    m_keyboard_state = SDL_GetKeyboardState(&m_key_length);
    m_prev_keyboard_state = new Uint8[m_key_length];
    memcpy(m_prev_keyboard_state, m_keyboard_state, m_key_length);

    srand(time(NULL)); // need to randomly generate food
    update_food(); // set location of first food
}

Snake::~Snake() 
{
    delete[] m_prev_keyboard_state;
}

void Snake::update() 
{
    if(!m_events.empty()) {
        m_current_direction = m_events.front();
        m_events.pop();
    }
    move();
}

void Snake::move() 
{
    for(int i=m_snake.size()-1; i>0; --i) {
        m_snake[i] = m_snake[i-1];
    }
    
    m_snake[0].x = (((m_snake[0].x + m_dir[m_current_direction].x) % m_width)  + m_width)  % m_width;
    m_snake[0].y = (((m_snake[0].y + m_dir[m_current_direction].y) % m_height) + m_height) % m_height;
    int collision = check_collision(m_snake[0]);
    
    if(collision==1) { // eat food
        grow();
        update_food();
    } else if(collision==2) { // hit itself so game over
        m_running = false; 
        return;
    }
}

void Snake::grow() 
{
    int oldTail = m_snake.size()-1;
    Cell newTail = {(((m_snake[oldTail].x - m_dir[m_current_direction].x) % m_width)  + m_width)  % m_width,
                    (((m_snake[oldTail].y - m_dir[m_current_direction].y) % m_height) + m_height) % m_height};
    m_snake.push_back(newTail);
}

int Snake::check_collision(Cell cell) 
{
    if(cell.x == m_food.x && cell.y == m_food.y) return 1; // collision with food
    else {
        for(int segment=1; segment<(int)m_snake.size(); ++segment) {
            if(m_snake[segment].x == cell.x && m_snake[segment].y == cell.y) 
                return 2; // game over, snake colliding with itself
        }
    }

    return 0; // no collision
} 

void Snake::update_food()
{
    bool freeCell = false;
    while(!freeCell) {
        m_food = {rand()%m_width, rand()%m_height};
        freeCell = true;
        for(auto segment:m_snake) {
            if(segment.x == m_food.x && segment.y == m_food.y) {
                freeCell = false;
                break;
            }
        }
    } 
    m_food_eaten = false;
}

void Snake::draw(SDL_Renderer *renderer) 
{
    m_dst.x = m_snake[0].x*m_cell_pixels;
    m_dst.y = m_snake[0].y*m_cell_pixels;
    SDL_SetRenderDrawColor(renderer,m_head_color.r,m_head_color.g,m_head_color.b,255);
    SDL_RenderFillRect(renderer,&m_dst);
    for(int segment=1; segment<(int)m_snake.size(); ++segment) {
        m_dst.x = m_snake[segment].x*m_cell_pixels;
        m_dst.y = m_snake[segment].y*m_cell_pixels;
        SDL_SetRenderDrawColor(renderer,m_segment_color.r,m_segment_color.g,m_segment_color.b,255);
        SDL_RenderFillRect(renderer,&m_dst);
    } 

    m_dst.x = m_food.x*m_cell_pixels;
    m_dst.y = m_food.y*m_cell_pixels;
    SDL_SetRenderDrawColor(renderer,m_food_color.r,m_food_color.g,m_food_color.b,255);
    SDL_RenderFillRect(renderer,&m_dst);
}

void Snake::handle_events() 
{
    while(SDL_PollEvent(&m_ev)) {
        if(m_ev.type == SDL_QUIT) {
            m_running = 0;
            break;
        } 
    }
    
    if(key_pressed(SDL_SCANCODE_A)) {
        if(m_current_direction!=RIGHT) { 
            m_events.push(LEFT);
        }
    } else if(key_pressed(SDL_SCANCODE_D)) {
        if(m_current_direction!=LEFT) {
            m_events.push(RIGHT);
        }
    } else if(key_pressed(SDL_SCANCODE_W)) {
        if(m_current_direction!=DOWN) {
            m_events.push(UP);
        }
    } else if(key_pressed(SDL_SCANCODE_S)) {
        if(m_current_direction!=UP) { 
            m_events.push(DOWN);
        }
    }
    update_prev_keyboard_state();
}

bool Snake::key_pressed(SDL_Scancode key) 
{
    return (m_prev_keyboard_state[key]==0 &&  m_keyboard_state[key]!=0);
}

void Snake::update_prev_keyboard_state()
{
    memcpy(m_prev_keyboard_state, m_keyboard_state, m_key_length);
}

bool Snake::is_running() 
{
    return m_running;
}
