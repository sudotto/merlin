#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"

#include "player.h"
#include "bullet.h"

int main(int argc, char* argv[]){
	Game game = new_game("X-Caliber", 600, 600);
	SDL_Color color = {255, 255, 0};
	Player player = new_player(&game, "charlie", color, 5);
	Bullet* bullets = malloc(sizeof(Bullet) * MAX_BULLET);
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
		if(game.keystates[SDL_SCANCODE_P]){
			print_bullets(bullets);
		}
		control_player(&game, &player, bullets);

		update_player(&player);
		update_bullets(bullets);

		render_player(&game, &player);
		render_bullets(&game, bullets);
		
		render_game_cursor(&game, 32, 32);
		
		update_game(&game);
		cap_game_framerate(&game, 60);
	}
	//destroy_bullets(bullets);
	destroy_game(&game);
}
