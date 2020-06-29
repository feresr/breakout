#include "GameLevel.h"

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game {
public:
    GameState State;

    std::vector<GameLevel> Levels;
    unsigned int level;
    bool Keys[1024]{};
    unsigned int Width{}, Height{};

    //constructor / destructor
    Game(unsigned int width, unsigned int height);
    ~Game();

    void DoCollisions();

    void Init();

    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
};