#include "spaceinvaders.h"

void (init_game)() {
  ship = init_player();
  shield1 = init_shield(100, 1);
  shield2 = init_shield(350, 2);
  shield3 = init_shield(600, 3);
  aliens = init_aliens();
  last_alien_mov = right;
  updates = 0;
}

void (reload_aliens)() {
  aliens = init_aliens();
  shield1 = init_shield(100, 1);
  shield2 = init_shield(350, 2);
  shield3 = init_shield(600, 3);
  last_alien_mov = right;
  updates = 0;
}

Score* (load_scores)() {
  Score* array = (Score*) malloc (sizeof(Score) * 10);

  FILE* fp = fopen("/home/lcom/labs/proj/src/highscores.csv", "r");

  if (!fp) fp = fopen("/home/lcom/labs/g3/proj/src/highscores.csv", "r");
  if (!fp) {
    printf("Error opening file\n");
    return array;
  }

  char buffer[1024];

  int row = 0;
  int column = 0;

  while (fgets(buffer, 1024, fp)) {
    column = 0;

    int points;
    char datetime[17];

    char* value = strtok(buffer, ",");

    while (value) {
      switch (column) {
        case 0: points = atoi(value); break;
        case 1: value = strcpy(datetime, value); break;
        default: break;
      }
      value = strtok(NULL, ",");
      column++;
    }

    Score score;
    score.points = points;
    datetime[16] = 0;
    strcpy(score.datetime, datetime);

    array[row] = score;

    row++;
  }

  fclose(fp);

  return array;
}

Score (build_score)(int points, rtc_time* time) {
  Score score;
  score.points = points;
  char str[17];
  if (time->month < 10 && time->hour < 10) sprintf(str, "%d/0%d/20%d 0%d:%d", time->day, time->month, time->year, time->hour, time->minute);
  else if (time->month < 10) sprintf(str, "%d/0%d/20%d %d:%d", time->day, time->month, time->year, time->hour, time->minute);
  else if (time->hour < 10) sprintf(str, "%d/%d/20%d 0%d:%d", time->day, time->month, time->year, time->hour, time->minute);
  else sprintf(str, "%d/%d/20%d %d:%d", time->day, time->month, time->year, time->hour, time->minute);
  strcpy(score.datetime, str);
  return score;
}

bool (process_score)(Score score, Score* array) {
  for (size_t i = 0; i < 10; i++) {
    if (score.points > array[i].points) {
      for (size_t j = 9; j > i; j--) array[j] = array[j - 1];
      array[i] = score;
      return true;
    }
  }
  return false;
}

void (init_scores)() {
  FILE *fp = fopen("/home/lcom/labs/proj/src/highscores.csv", "w");

  for (size_t i = 0; i < 10; i++) fprintf(fp, "0,00/00/0000 00:00\n");

  fclose(fp);
}

void (store_scores)(Score* array) {
  FILE* fp = fopen("/home/lcom/labs/proj/src/highscores.csv", "w");

  if (!fp) fp = fopen("/home/lcom/labs/g3/proj/src/highscores.csv", "w");
  if (!fp) {
    printf("Error opening file\n");
    return;
  }

  for (size_t i = 0; i < 10; i++) {
    Score score = array[i];
    fprintf(fp, "%d,%s\n", score.points, score.datetime);
  }

  fclose(fp);
}

void (draw)() {
  memset(video_buffer, 0, h_res*v_res*bytes_per_pixel);

  draw_shield(shield1);
  draw_shield(shield2);
  draw_shield(shield3);

  draw_player(ship);

  draw_aliens(aliens);
  
  draw_score(ship);
  draw_lives(ship->lives);

  memcpy(video_mem, video_buffer, h_res*v_res*bytes_per_pixel);
}

void (update)(int* no_lives) {
  updates++;
  unsigned int shoot_alienTime = 0;
  unsigned int moveAlienTime = 0;

  switch(wave){
    case 1:
      shoot_alienTime = (100 - (aliens->alive_no));
      moveAlienTime = 25;
      break;
    case 2:
      shoot_alienTime = (90 - (aliens->alive_no));
      moveAlienTime = 20;
      break;
    case 3:
      shoot_alienTime = (80 - (aliens->alive_no));
      moveAlienTime = 17;
      break;
    case 4:
      shoot_alienTime = (75 - (aliens->alive_no));
      moveAlienTime = 15;
      break;
    default:
      shoot_alienTime = (70 - (aliens->alive_no));
      moveAlienTime = 15; 
      break; 
  }
  if (updates == shoot_alienTime) {
    shoot_aliens(aliens);
    updates = 0;
  }
  else if (updates % moveAlienTime == 0) {
    switch (last_alien_mov) {
      case right:
        if (!can_alien_group_move(aliens, right)) {
          move_aliens(aliens, down);
          last_alien_mov = down_after_right;
        } else move_aliens(aliens, right);
        break;
      case left:
        if (!can_alien_group_move(aliens, left)) {
          move_aliens(aliens, down);
          last_alien_mov = down_after_left;
        } else move_aliens(aliens, left);
        break;
      case down_after_right: move_aliens(aliens, left); last_alien_mov = left; break;
      case down_after_left: move_aliens(aliens, right); last_alien_mov = right; break;
      default: break;
    }
  }
  for (int i = 0; i < aliens->size; i++) {
    Alien* a = &(aliens->set[i]);
    for (int j = 0; j < a->shots_no; j++) {
      move_shot(&(a->shots[j]));
      if (a->shots[j].y_max >= (ship->y_min + 8) && (a->shots[j].x_min > ship->x_max || a->shots[j].x_max < ship->x_min)) {
        delete_alien_shot(a, j);
        return;
      } else if (shield1->lives > 0 && a->shots[j].y_max >= (shield1->y_min - 30) && a->shots[j].x_min <= shield1->x_max && a->shots[j].x_max >= shield1->x_min) {
        delete_alien_shot(a, j);
        damage(shield1, alien);
        return;
      } else if (shield2->lives > 0 && a->shots[j].y_max >= (shield2->y_min - 30) && a->shots[j].x_min <= shield2->x_max && a->shots[j].x_max >= shield2->x_min) {
        delete_alien_shot(a, j);
        damage(shield2, alien);
        return;
      } else if (shield3->lives > 0 && a->shots[j].y_max >= (shield3->y_min - 30) && a->shots[j].x_min <= shield3->x_max && a->shots[j].x_max >= shield3->x_min) {
        delete_alien_shot(a, j);
        damage(shield3, alien);
        return;
      } else if (a->shots[j].y_max >= ship->y_min && a->shots[j].x_min <= ship->x_max && a->shots[j].x_max >= ship->x_min) {
        delete_alien_shot(a, j);
        loose_life(ship);
        if(ship->lives == 0) *no_lives = 1;
        return;
      }
    }
  }
  for (int i = 0; i < ship->shots_no; i++) {
    int alien_idx;
    move_shot(&(ship->shots[i]));
    if ((ship->shots[i].y_min) <= -50) {
      delete_player_shot(ship, i);
      return;
    } else if (shield1->lives > 0 && ship->shots[i].y_min <= shield1->y_max && ship->shots[i].x_min <= shield1->x_max && ship->shots[i].x_max >= shield1->x_min) {
      delete_player_shot(ship, i);
      damage(shield1, player);
      return;
    } else if (shield2->lives > 0 && ship->shots[i].y_min <= shield2->y_max && ship->shots[i].x_min <= shield2->x_max && ship->shots[i].x_max >= shield2->x_min) {
      delete_player_shot(ship, i);
      damage(shield2, player);
      return;
    } else if (shield3->lives > 0 && ship->shots[i].y_min <= shield3->y_max && ship->shots[i].x_min <= shield3->x_max && ship->shots[i].x_max >= shield3->x_min) {
      delete_player_shot(ship, i);
      damage(shield3, player);
      return;
    } else if ((alien_idx = hit_index(aliens, &(ship->shots[i]))) != -1) {
      delete_player_shot(ship, i);
      die_alien(aliens, alien_idx);
      increment_score(ship, alien_idx);
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

extern int x_mouse;
extern int y_mouse;

void (draw_main_menu)() {
  memset(video_buffer, 0, h_res*v_res*bytes_per_pixel);
  video_draw_xpm(100, 40, "logo");
  video_draw_xpm(150, 400, "play_button");
  video_draw_xpm(800-175-150, 400, "ranking_button");
  video_draw_xpm(x_mouse, y_mouse, "mouse");
  memcpy(video_mem, video_buffer, h_res*v_res*bytes_per_pixel);
}

void (draw_high_scores)(Score* scores) {
  memset(video_buffer, 0, h_res*v_res*bytes_per_pixel);
  for (int i = 0; i < 10; i++) {
    int points = scores[i].points;
    int alg_count = 0;
    while (points != 0) {
      points /= 10;
      alg_count++;
    }
    points = scores[i].points;
    for (int j = alg_count; j > 0; j--) {
      int x = 10 + (22 * j);
      int y = 20 + (50 * i);

      switch (points % 10) {
        case 0: video_draw_xpm(x, y, "zero"); break;
        case 1: video_draw_xpm(x, y, "one"); break;
        case 2: video_draw_xpm(x, y, "two"); break;
        case 3: video_draw_xpm(x, y, "three"); break;
        case 4: video_draw_xpm(x, y, "four"); break;
        case 5: video_draw_xpm(x, y, "five"); break;
        case 6: video_draw_xpm(x, y, "six"); break;
        case 7: video_draw_xpm(x, y, "seven"); break;
        case 8: video_draw_xpm(x, y, "eight"); break;
        case 9: video_draw_xpm(x, y, "nine"); break;
        default: break;
      }
      points /= 10;
    }

    for (int j = 0; j < 16; j++) {
      char c = scores[i].datetime[j];

      int x = 278 + (32 * j);
      int y = 20 + (50 * i);

      if (c == '0') {
        video_draw_xpm(x, y, "zero");
      } else if (c == '1') {
        video_draw_xpm(x, y, "one");
      } else if (c == '2') {
        video_draw_xpm(x, y, "two");
      } else if (c == '3') {
        video_draw_xpm(x, y, "three");
      } else if (c == '4') {
        video_draw_xpm(x, y, "four");
      } else if (c == '5') {
        video_draw_xpm(x, y, "five");
      } else if (c == '6') {
        video_draw_xpm(x, y, "six");
      } else if (c == '7') {
        video_draw_xpm(x, y, "seven");
      } else if (c == '8') {
        video_draw_xpm(x, y, "eight");
      } else if (c == '9') {
        video_draw_xpm(x, y, "nine");
      } else if (c == '/') {
        video_draw_xpm(x, y, "slash");
      } else if (c == ':') {
        video_draw_xpm(x, y, "h");
      } else continue;
    }
  }
  //video_draw_xpm(x_mouse, y_mouse, "mouse");
  memcpy(video_mem, video_buffer, h_res*v_res*bytes_per_pixel);
}

void (draw_game_over_menu)() {
  memset(video_buffer, 0, h_res*v_res*bytes_per_pixel);
  video_draw_xpm(250, 200, "gameOver");
  video_draw_xpm(150, 400, "replay_button");
  video_draw_xpm(800-175-150, 400, "menu_button");
  video_draw_xpm(x_mouse, y_mouse, "mouse");
  memcpy(video_mem, video_buffer, h_res*v_res*bytes_per_pixel);
}
