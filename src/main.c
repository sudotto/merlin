#include <stdio.h>
#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"

#include "player.h"
#include "bullet.h"

int main(int argc, char* argv[]){
	Game game = new_game("X-Caliber", 600, 600);
	SDL_Color color = {255, 0, 255};
	Player player = new_player(game.rend, "charlie", color, 5);
	Bullet bullet = new_bullet(game.rend, 100, 100, "assets/bullet/ball.png", color, 6);
	while(game.running){
		game.frame_start = SDL_GetTicks();
		clear_game(&game, 128, 128, 128);
		while(get_game_events(&game)){
			switch(game.event.type){
				case SDL_EVENT_QUIT:
					game.running = false;
					break;
			}
		}
		control_player(&player, game.keystates);
		
		update_player(&player);
		update_bullet(&bullet);
		
		render_player(game.rend, &player);
		render_bullet(game.rend, &bullet);
		
		render_game_cursor(&game, 32, 32);
		
		update_game(&game);
		cap_game_framerate(60, game.frame_start);
	}
	destroy_game(&game);
}
