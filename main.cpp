#include <SDL2/SDL.h>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 729;

class Vec2 {
    public:
        Vec2()
            : x(0.0f), y(0.0f)
        {}

        Vec2(float x, float y)
            : x(x), y(y)
        {}

        Vec2 operator+(Vec2 const& rhs) {
            return Vec2(x + rhs.x, y + rhs.y);
        }

        Vec2& operator+=(Vec2 const& rhs) {
            x += rhs.x;
            y += rhs.y;
            
            return *this;
        }

        Vec2 operator*(float rhs) {
            return Vec2(x * rhs, y * rhs);
        }

        float x, y;
};

int main() {
    // Init
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Pong", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Logic
    {
        bool running = true;

        while (running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
                }
            }

            SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

            for (int y = 0; y < WINDOW_HEIGHT; y++) {
                if (y % 5) {
                    SDL_RenderDrawPoint(renderer, WINDOW_WIDTH / 2, y);
                }
            }

            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
