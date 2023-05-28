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

Score* (loadScores)() {
  Score* array = (Score*) malloc (sizeof(Score) * 10);

  FILE* fp = fopen("/home/lcom/labs/proj/src/highscores.csv", "r");

  if (!fp) fp = fopen("/home/lcom/labs/g3/proj/src/highscore.csv", "r");
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

Score (buildScore)(int points, rtc_time* time) {
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

bool (processScore)(Score score, Score* array) {
  for (size_t i = 0; i < 10; i++) {
    if (score.points > array[i].points) {
      for (size_t j = 9; j > i; j--) array[j] = array[j - 1];
      array[i] = score;
      return true;
    }
  }
  return false;
}

void (initScores)() {
  FILE *fp = fopen("/home/lcom/labs/proj/src/highscores.csv", "w");

  for (size_t i = 0; i < 10; i++) fprintf(fp, "0,00/00/0000 00:00\n");

  fclose(fp);
}

void (storeScores)(Score* array) {
  FILE* fp = fopen("/home/lcom/labs/proj/src/highscores.csv", "w");

  if (!fp) fp = fopen("/home/lcom/labs/g3/proj/src/highscore.csv", "w");
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
      moveAlienTime = 20;
      break;
    case 2:
      shootAlienTime = 40;
      moveAlienTime = 15;
      break;
    case 3:
      shootAlienTime = 30;
      moveAlienTime = 12;
      break;
    case 4:
      shootAlienTime = 20;
      moveAlienTime = 10;
      break;
    default:
      shootAlienTime = 20;
      moveAlienTime = 10; 
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

extern int x_mouse;
extern int y_mouse;

void (drawMainMenu)() {
  memset(video_buffer, 0, h_res*v_res*bytes_per_pixel);
  video_draw_xpm(100, 40, "logo");
  video_draw_xpm(150, 400, "play_button");
  video_draw_xpm(800-175-150, 400, "ranking_button");
  video_draw_xpm(x_mouse, y_mouse, "mouse");
  memcpy(video_mem, video_buffer, h_res*v_res*bytes_per_pixel);
}

void (drawHighscores)(Score* scores) {
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

void (drawGameOverMenu)() {
  memset(video_buffer, 0, h_res*v_res*bytes_per_pixel);
  video_draw_xpm(250, 250, "gameOver");
  video_draw_xpm(x_mouse, y_mouse, "mouse");
  memcpy(video_mem, video_buffer, h_res*v_res*bytes_per_pixel);
}
