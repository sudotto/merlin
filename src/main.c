#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"

#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "particle.h"

int main(int argc, char* argv[]){
	Game game = new_game("Magus Vagus", 600, 600);
	SDL_Color color = {255, 0, 255};
	Player player = new_player(&game, "charlie", color, 5);
	Enemy enemy = new_enemy(&game, "bandit", 5);
	Bullet* bullets = malloc(sizeof(Bullet) * MAX_BULLET);
	Particle* particles = malloc(sizeof(Particle) * MAX_PARTICLE);
	while(game.running){
		game.frame_start = SDL_GetTicks();
		clear_game(&game, 65, 65, 65);
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
		update_player(&game, &player, bullets, particles);
		update_enemy(&game, &enemy, &player, bullets, particles);
		update_bullets(bullets);
		update_particles(particles);

		render_player(&game, &player);
		render_enemy(&game, &enemy);
		render_bullets(&game, bullets);
		render_particles(&game, particles);
		
		render_game_cursor(&game, 32, 32);
		
		update_game(&game);
		cap_game_framerate(&game, 60);
	}
	//destroy_bullets(bullets);
	destroy_game(&game);
}
