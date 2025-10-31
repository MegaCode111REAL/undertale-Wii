#include <gccore.h>
#include <wiiuse/wpad.h>
#include <fat.h>
#include <grrlib.h>

#include "input.h"
#include "game.h"
#include "render.h"

static void init_wii() {
    VIDEO_Init();
    WPAD_Init();
    PAD_Init();
    fatInitDefault(); // initialize FAT (SD)
    GRRLIB_Init();
    GRRLIB_SetBackgroundColour(0,0,0,0xFF);
}

int main(int argc, char **argv) {
    init_wii();

    // Initialize systems
    Render_Init();
    Game_Init();

    // Main loop
    while(1) {
        WPAD_ScanPads();
        PAD_ScanPads();

        InputState input = GetInputState();

        Game_Update(&input);
        Render_BeginFrame();
        Game_Render();
        Render_EndFrame();

        VIDEO_WaitVSync();
    }

    // Cleanup (never reached in homebrew main loop)
    Game_Shutdown();
    Render_Shutdown();
    GRRLIB_Exit();
    return 0;
}