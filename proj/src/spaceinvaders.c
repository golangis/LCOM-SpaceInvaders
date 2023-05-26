#include "spaceinvaders.h"

void (init_game)() {
  ship = initPlayer();
  shield1 = initShield(100, 1);
  shield2 = initShield(350, 2);
  shield3 = initShield(600, 3);
  aliens = initAliens();
  last_alien_mov = right;
  updates = 0;
}

void (reload_aliens)() {
  aliens = initAliens();
  last_alien_mov = right;
  updates = 0;
}

void (draw)() {
  memset(video_buffer, 0, h_res*v_res*bytes_per_pixel);

  drawShield(shield1);
  drawShield(shield2);
  drawShield(shield3);

  drawPlayer(ship);

  drawAliens(aliens);

  drawScore(ship);
  drawLives(ship->lives);

  memcpy(video_mem, video_buffer, h_res*v_res*bytes_per_pixel);
}

void (update)(int* no_lives) {
  updates++;
  unsigned int shootAlienTime = 0;
  unsigned int moveAlienTime = 0;

  switch(wave){
    case 1:
      shootAlienTime = 50;
      moveAlienTime = 30;
      break;
    case 2:
      shootAlienTime = 40;
      moveAlienTime = 25;
      break;
    case 3:
      shootAlienTime = 30;
      moveAlienTime = 22;
      break;
    case 4:
      shootAlienTime = 20;
      moveAlienTime = 20;
      break;
    default:
      shootAlienTime = 20;
      moveAlienTime = 20; 
      break; 
  }
  if (updates == shootAlienTime) {
    shootAliens(aliens);
    updates = 0;
  }
  else if (updates % moveAlienTime == 0) {
    switch (last_alien_mov) {
      case right:
        if (!canAlienGroupMove(aliens, right)) {
          moveAliens(aliens, down);
          last_alien_mov = down_after_right;
        } else moveAliens(aliens, right);
        break;
      case left:
        if (!canAlienGroupMove(aliens, left)) {
          moveAliens(aliens, down);
          last_alien_mov = down_after_left;
        } else moveAliens(aliens, left);
        break;
      case down_after_right: moveAliens(aliens, left); last_alien_mov = left; break;
      case down_after_left: moveAliens(aliens, right); last_alien_mov = right; break;
      default: break;
    }
  }
  for (int i = 0; i < aliens->size; i++) {
    Alien* a = &(aliens->set[i]);
    for (int j = 0; j < a->shots_no; j++) {
      moveShot(&(a->shots[j]));
      if ((a->shots[j].y_max) >= 650) {
        deleteAlienShot(a, j);
        return;
      } else if (shield1->lives > 0 && a->shots[j].y_max >= shield1->y_min && a->shots[j].x_min <= shield1->x_max && a->shots[j].x_max >= shield1->x_min) {
        deleteAlienShot(a, j);
        damage(shield1, alien);
        return;
      } else if (shield2->lives > 0 && a->shots[j].y_max >= shield2->y_min && a->shots[j].x_min <= shield2->x_max && a->shots[j].x_max >= shield2->x_min) {
        deleteAlienShot(a, j);
        damage(shield2, alien);
        return;
      } else if (shield3->lives > 0 && a->shots[j].y_max >= shield3->y_min && a->shots[j].x_min <= shield3->x_max && a->shots[j].x_max >= shield3->x_min) {
        deleteAlienShot(a, j);
        damage(shield3, alien);
        return;
      } else if (a->shots[j].y_max >= ship->y_min && a->shots[j].x_min <= ship->x_max && a->shots[j].x_max >= ship->x_min) {
        deleteAlienShot(a, j);
        looseLife(ship);
        if(ship->lives == 0) *no_lives = 1;
        return;
      }
    }
  }
  for (int i = 0; i < ship->shots_no; i++) {
    int alien_idx;
    moveShot(&(ship->shots[i]));
    if ((ship->shots[i].y_min) <= -50) {
      deletePlayerShot(ship, i);
      return;
    } else if (shield1->lives > 0 && ship->shots[i].y_min <= shield1->y_max && ship->shots[i].x_min <= shield1->x_max && ship->shots[i].x_max >= shield1->x_min) {
      deletePlayerShot(ship, i);
      damage(shield1, player);
      return;
    } else if (shield2->lives > 0 && ship->shots[i].y_min <= shield2->y_max && ship->shots[i].x_min <= shield2->x_max && ship->shots[i].x_max >= shield2->x_min) {
      deletePlayerShot(ship, i);
      damage(shield2, player);
      return;
    } else if (shield3->lives > 0 && ship->shots[i].y_min <= shield3->y_max && ship->shots[i].x_min <= shield3->x_max && ship->shots[i].x_max >= shield3->x_min) {
      deletePlayerShot(ship, i);
      damage(shield3, player);
      return;
    } else if ((alien_idx = hitIndex(aliens, &(ship->shots[i]))) != -1) {
      deletePlayerShot(ship, i);
      dieAlien(aliens, alien_idx);
      incrementScore(ship, alien_idx);
      return;
    }
  }
  if (aliens->alive_no == 0) {
    int score = ship->score;
    wave++;
    reload_aliens();
    ship->score = score;
  }
}

void (drawMenu)() {
  memset(video_buffer, 0, h_res*v_res*bytes_per_pixel);
  video_draw_xpm(20, 20, play_button_xpm);
  memcpy(video_mem, video_buffer, h_res*v_res*bytes_per_pixel);
}
