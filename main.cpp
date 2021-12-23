#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 729;

const int BALL_WIDTH = 15;
const int BALL_HEIGHT = 15;

const int PADDLE_WIDTH = 15;
const int PADDLE_HEIGHT = 30;

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

class Ball {
    public:
        Ball(Vec2 position) : position(position) {
                rect.x = static_cast<int>(position.x);
                rect.y = static_cast<int>(position.y);
                rect.w = BALL_WIDTH;
                rect.h = BALL_HEIGHT;
            }

        void Draw(SDL_Renderer* renderer) {
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);

            SDL_RenderFillRect(renderer, &rect);
        }

        Vec2 position;
        SDL_Rect rect;
};

class Paddle {
    public:
        Paddle(Vec2 position) : position(position) {
                rect.x = static_cast<int>(position.x);
                rect.y = static_cast<int>(position.y);
                rect.w = PADDLE_WIDTH;
                rect.h = PADDLE_HEIGHT;
            }

        void Draw(SDL_Renderer* renderer) {
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);

            SDL_RenderFillRect(renderer, &rect);
        }


        Vec2 position;
        SDL_Rect rect;
};

int main() {
    // Init
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Pong", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    TTF_Font* scoreFont = TTF_OpenFont("DejaVuSansMono.ttf", 40);

    Ball ball(Vec2((WINDOW_WIDTH / 2.0f) - (BALL_WIDTH / 2.0f),
	(WINDOW_HEIGHT / 2.0f) - (BALL_WIDTH / 2.0f)));

    Paddle paddleOne(Vec2(50.0f, (WINDOW_HEIGHT / 2.0f) - (PADDLE_HEIGHT / 2.0f)));
    Paddle paddleTwo(Vec2(WINDOW_WIDTH - 50.0f, (WINDOW_HEIGHT / 2.0f) - (PADDLE_HEIGHT / 2.0f)));

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

            ball.Draw(renderer);

            paddleOne.Draw(renderer);
            paddleTwo.Draw(renderer);

            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(scoreFont);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
