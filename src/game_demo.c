#include "game.h"
#include "framebuffer.h"
#include "gpio.h"
#include "timer.h"

#define MAX_BULLETS 10
#define MAX_ENEMIES 5

// Set to 1 for auto-demo mode (Pi 5 without GPIO)
#define AUTO_DEMO_MODE 0

typedef struct {
    int x, y;
    int active;
} GameObject;

static GameObject player;
static GameObject bullets[MAX_BULLETS];
static GameObject enemies[MAX_ENEMIES];
static int score = 0;
static unsigned long last_enemy_spawn = 0;

void game_init(void) {
    player.x = get_screen_width() / 2;
    player.y = get_screen_height() - 50;
    player.active = 1;
    
    for (int i = 0; i < MAX_BULLETS; i++)
        bullets[i].active = 0;
    
    for (int i = 0; i < MAX_ENEMIES; i++)
        enemies[i].active = 0;
    
    score = 0;
}

void spawn_enemy(void) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) {
            enemies[i].x = (get_timer_count() % (get_screen_width() - 40)) + 20;
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
#if AUTO_DEMO_MODE
    // Auto-demo mode for Raspberry Pi 5 (no GPIO input)
    static int auto_move_counter = 0;
    static int move_direction = 1;
    
    // Move player left and right automatically
    player.x += move_direction * 3;
    
    // Bounce at screen edges
    if (player.x <= 0) {
        move_direction = 1;
    } else if (player.x >= get_screen_width() - 20) {
        move_direction = -1;
    }
    
    // Auto-fire periodically
    if (auto_move_counter % 15 == 0) {
        fire_bullet();
    }
    
    auto_move_counter++;
#else
    // Normal GPIO input mode
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
#endif
    
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].y -= 8;
            if (bullets[i].y < 0)
                bullets[i].active = 0;
        }
    }
    
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            enemies[i].y += 3;
            if (enemies[i].y > get_screen_height())
                enemies[i].active = 0;
        }
    }
    
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
    
    unsigned long now = get_timer_count();
    if (now - last_enemy_spawn > 1000000) {
        spawn_enemy();
        last_enemy_spawn = now;
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
    
#if AUTO_DEMO_MODE
    // Visual indicator that demo mode is active
    // Draw a cyan border
    draw_rect(0, 0, get_screen_width(), 5, COLOR_CYAN);
    draw_rect(0, get_screen_height() - 5, get_screen_width(), 5, COLOR_CYAN);
    draw_rect(0, 0, 5, get_screen_height(), COLOR_CYAN);
    draw_rect(get_screen_width() - 5, 0, 5, get_screen_height(), COLOR_CYAN);
#endif
}
