# Create my first C game

## Progress

### 04/01/2025

- 12:35:23. Add reset button.
    - Create rect element to place the reset button.
    - Create text and texture surface for the "Reset" label.
    - Handle reset logic on click button.
    ```c
    posX = 100;
    posY = 100;
    red_rect.x = posX;
    red_rect.y = posY;
    show_reset_button = false;
    ```
    - Add `show_reset_button` flag to handle render reset button.
    ```c
    if (show_reset_button) {
        // Colorize white reset button.
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &reset_button);
        SDL_RenderCopy(renderer, reset_text_texture, NULL, &reset_text_rect);
    } else {
        // Change to green of red_rect.
        // Render on screen the red_rect.
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &red_rect);
    }
    ```

### 03-01-2025

- 23:47:17. Create build script to compile the game.
    ```bash
    gcc -o output main.c -lSDL2 -lSDL2_ttf
    ./output
    ```
- 23:35:16. Add feedback text on screen.
    - When main square collide with obstacle (second square) the program will show a "Game Over" text on screen, then after 3 seconds will close the app.
    - Had to install the ttf library `sudo apt install libsdl2-ttf-dev` so we can import the necesary modules.
        - `#include <SDL2/SDL_ttf.h>`
    - Had to create a surface and texture for the feedback text.
        - The text should render on squares collition.
        - Set delay of 3 seconds.
        - After the 3 second the app should close.
    - Had to add a `fonts` folder and use `arcade_classic.ttf` custom font.
    - Had to link the `ttf_LSD2` header so we can compile the app.
        - `gcc -o output main.c -lSDL2 -lSDL2_ttf`
- 21:36:42. Add collision.
    - Create a function to check the collision between two squares.
    ```c
    return (a.x + a.w >= b.x) && // A's right edge >= B's left edge.
    (a.x <= b.x + b.w) &&    // A's left edge <= B's right edge.
    (a.y + a.h >= b.y) &&    // A's botton edge >= B's top edge.
    (a.y <= b.y + b.h);      // A's top edge <= B's botton edge.
    ```
    - If the condition return `true` means that both square are collide, so the main square turn red.
    - Otherwise, the main square keeps the main color that is green.
- 21:20:47. Add blue square.
    - We create a blue square the same way as red square.
    ```c
    SDL_Rect blue_rect = { bPosX, bPosY, BLUE_SQUARE_WIDTH, BLUE_SQUARE_HEIGHT };
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &blue_rect);
    ```
- 15:04:01. Increase the `speed` movement to 10 becuase was to slow.
- 15:02:56. Add red square width and height constant values.
- 15:01:34. Add validation to prevent the red square go outsite the screen.
    - Validate with screen width and height minus square width and height.
- 14:47:44. Move keydowns event handler inside `SDL_PollEvent(&event)` and update `speed` value to `5`.
    - Something happends after I restart my computer that everything was broken.
- 14:46:03. Re install SDL2 library.
    - I use this command `sudo apt update` then `sudo apt install --reinstall libsdl2-dev`
    - Looks like the drive cannot be finded.

### 31-12-2024

- 15:30. Add movements to the square.
    - Create variables for square position x and y.
    - Create `speed` variables for the movement of square to 1. (5 is very fast, maybe depends on screen width?)
    - Add conditional if to ask is `event.type` is equal to `SDL_KEYDOWN`.
        - Use a switch case to handle Key type.
            - `SDL_UP` decrease the y position by `speed`.
            - `SDL_DOWN` increase the y position by `speed`.
            - `SDL_LEFT` decrease the x position by `speed`.
            - `SDL_RIGHT` increase the x position by `speed`.
    - Add `WINDOW_WIDTH` and `WINDOW_HEIGHT` to make this values reusables.
- 15:02. Add red square on screen.
    - [SDL Rect Docs](https://wiki.libsdl.org/SDL2/SDL_Rect)
    - Create the square size properties `SDL_Rect red_rect = { 100, 100, 50, 50 };`
    - Update the square background color to red `SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);`
    - Now the red square is renderer on the windows `SDL_RenderFillRect(renderer, &red_rect);`
- 13:39. Add loop that check users inputs events.
    - Check is the event type is equal to `SDL_QUIT`. Then run the next code to close the app.
    ```c
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            is_running = false;
        }
    }
    ```
- 13:31. Create my first windows.
    - [SDL_CreateWindow Docs](https://wiki.libsdl.org/SDL2/SDL_CreateWindow)
    - Save the return function a `window` variable, set the arguments for positions and size.
    - Check if the windows was created successfully otherwise close the app with [SDL_Quit()](https://wiki.libsdl.org/SDL2/SDL_Quit).
    - Create a `renderer` variable to draw the windows, also check if the renderer was created successfully.
    - Keep the windows open, I create a while loop that checks is the boolean variable `is_running` is `true`.
        - If is true, I run this code.
        ```c
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Negro
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        ```
        - This code above clean and render the background color.
        - If is false, I run this code.
        ```c
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        ```
        - Clean all the resources and close SDL successfully.
- 10:18. SDL2 library instalation on my debian distribution. Check it is working with a simple print app.
    - [SDL2 Library Docs](https://wiki.libsdl.org/wiki/index)

## Todos
- [x] Configuration of development enviroment.
    - Install SDL2 library on your project.
    - You can install the package from [SDL2 2.30.10 repository](https://github.com/libsdl-org/SDL/releases/tag/release-2.30.10)
    - Add configuration for your text editor.
    - Test your installation with a basic main.c file.
- [x] Create a basic windows 800x600.
- [x] Implemente the main game loop.
    - Run a game loop until the player close the game.
    - Handle player events (like close the windows)
    - Update game renderization.
    - Render.
    - Use a clock to keep the speed constantly.
- [x] Draw a square in the windows.
    - Should clean the windows before redraw the square.
- [x] Add movements to the square.
    - The player can move the square with arrows or WASD.
- [x] Handle the edge of the screen.
- [x] Add collision detections.
    - You can draw another square blue square for example.
    - Implement a logic that handle red square and blue square collision.
    - You can use *AABB collision detection* tecnique (Axis-Aligned Bounding Box)
    - Compare the coords of both squares.
- [x] Add visual feedbacks.
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
