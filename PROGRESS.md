# Create my first C game

## Progress

### 31-12-2024

- 10:18. SDL2 library instalation on my debian distribution. Check it is working with a simple print app.

## TODOS
- [x] Configuration of development enviroment.
    - Install SDL2 library on your project.
    - You can install the package from [SDL2 2.30.10 repository](https://github.com/libsdl-org/SDL/releases/tag/release-2.30.10)
    - Add configuration for your text editor.
    - Test your installation with a basic main.c file.
- [ ] Create a basic windows 800x600.
- [ ] Implemente the main game loop.
    - Run a game loop until the player close the game.
    - Handle player events (like close the windows)
    - Update game renderization.
    - Render.
    - Use a clock to keep the speed constantly.
- [ ] Draw a square in the windows.
    - Should clean the windows before redraw the square.
- [ ] Add movements to the square.
    - The player can move the square with arrows or WASD.
- [ ] Handle the edge of the screen.
- [ ] Add collision detections.
    - You can draw another square blue square for example.
    - Implement a logic that handle red square and blue square collision.
    - You can use *AABB collision detection* tecnique (Axis-Aligned Bounding Box)
    - Compare the coords of both squares.
- [ ] Add visual feedbacks.
    - Show any message on screen.
    - Add restart button or something like that.
- [ ] Add your first basic mechanic to the game.
    - Add a yellow circle and increase points value on screen every time the red square collide with the circle.
- [ ] Add some sound to the game.
    - Use SDL_mixer or SDL_Audio.
    - Play any sound when squares collides.
- [ ] Add a starting o finish screen.
    - Use SDL_tff to show any text on screen.
    - Show "Game Over" text on screen when both squares collides.
- [ ] Add a better performance for the game loop.
    - Add FPS control system.
- [ ] Add sprites on your current game.
- [ ] Test you game.
