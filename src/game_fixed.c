#include "game.h"
#include "framebuffer.h"
#include "gpio.h"
#include "timer.h"

#define MAX_BULLETS 10
#define MAX_ENEMIES 5

typedef struct {
    int x, y;
    int active;
} GameObject;

static GameObject player;
static GameObject bullets[MAX_BULLETS];
static GameObject enemies[MAX_ENEMIES];
static int score = 0;
static int frame_counter = 0;

void game_init(void) {
    player.x = get_screen_width() / 2;
    player.y = get_screen_height() - 50;
    player.active = 1;
    
    for (int i = 0; i < MAX_BULLETS; i++)
        bullets[i].active = 0;
    
    for (int i = 0; i < MAX_ENEMIES; i++)
        enemies[i].active = 0;
    
    score = 0;
    frame_counter = 0;
}

void spawn_enemy(void) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) {
            enemies[i].x = (frame_counter * 37) % (get_screen_width() - 40) + 20;
            enemies[i].y = 0;
            enemies[i].active = 1;
            break;
        }
    }
}

void fire_bullet(void) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) {
            bullets[i].x = player.x;
            bullets[i].y = player.y - 10;
            bullets[i].active = 1;
            break;
        }
    }
}

int check_collision(GameObject *a, GameObject *b, int size) {
    return (a->x < b->x + size && a->x + size > b->x &&
            a->y < b->y + size && a->y + size > b->y);
}

void game_update(void) {
    frame_counter++;
    
    // Player input (disabled for now)
    if (button_left() && player.x > 0)
        player.x -= 5;
    if (button_right() && player.x < get_screen_width() - 20)
        player.x += 5;
    if (button_up() && player.y > 0)
        player.y -= 5;
    if (button_down() && player.y < get_screen_height() - 20)
        player.y += 5;
    if (button_fire())
        fire_bullet();
    
    // Update bullets
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].y -= 8;
            if (bullets[i].y < 0)
                bullets[i].active = 0;
        }
    }
    
    // Update enemies
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            enemies[i].y += 3;
            if (enemies[i].y > get_screen_height())
                enemies[i].active = 0;
        }
    }
    
    // Check collisions
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) continue;
        
        for (int j = 0; j < MAX_ENEMIES; j++) {
            if (!enemies[j].active) continue;
            
            if (check_collision(&bullets[i], &enemies[j], 20)) {
                bullets[i].active = 0;
                enemies[j].active = 0;
                score += 10;
            }
        }
    }
    
    // Spawn enemy every 60 frames (~1 second at 60 FPS)
    if (frame_counter % 60 == 0) {
        spawn_enemy();
    }
}

void game_render(void) {
    clear_screen(COLOR_BLACK);
    
    draw_rect(player.x, player.y, 20, 20, COLOR_GREEN);
    
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active)
            draw_rect(bullets[i].x, bullets[i].y, 5, 10, COLOR_YELLOW);
    }
    
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active)
            draw_rect(enemies[i].x, enemies[i].y, 20, 20, COLOR_RED);
    }
}
