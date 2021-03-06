#ifndef COLLISION_H
#define COLLISION_H

#include "globals.h"
#include "enemies.h"
#include "elements.h"
#include "player.h"

void checkCollisions()
{
  Rect helenaRect;
  helenaRect = {
    .x = helena.x + HELENA_COLLISION_X_OFFSET,
    .y = 0,
    .width = HELENA_COLLISION_WIDTH,
    .height = HELENA_COLLISION_HEIGHT
  };
  if (helena.characteristics & 0B01000000) helenaRect.y = helena.y + HELENA_COLLISION_Y_OFFSET - 2 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]);
  else helenaRect.y = helena.y + HELENA_COLLISION_Y_OFFSET + (helena.frame % 2);

  ////// Check collision weapon with enemies /////
  ////////////////////////////////////////////////

  //arduboy.collide(helenaRect,

  ////// Check collision Helena with Orcs ////////
  ////////////////////////////////////////////////
  Rect enemyRect;
  for (byte i = 0; i < MAX_ORCS_IN_WAVE; i++)
  {
    enemyRect =
    {
      .x = orc[i].x + 2,
      .y = ORC_Y - 10 + ((orcFrames + i) % 2),
      .width = ORC_COLLISION_WIDTH,
      .height = ORC_COLLISION_HEIGHT
    };
    if (((orc[i].characteristics & 0B00110000) == 0B00010000) && arduboy.collide(helenaRect, enemyRect))
    {
      if (!(helena.characteristics & 0B00100000))
      {
        helena.characteristics |= 0B00100000;
        playerScore = 0;
        helena.life--;
      }
      if (!(orc[i].characteristics & 0B01000000))
      {
        orc[i].characteristics |= 0B00100000;
      }
    }

    if ((orc[i].characteristics & 0b00000011) == ENEMY_ORC_FLAT_SPEAR)
    {
      enemyRect =
      {
        .x = orc[i].x - 14,
        .y = ORC_Y + 3 + ((orcFrames + i) % 2),
        .width = SPEAR_F_COLLISION_WIDTH,
        .height = SPEAR_F_COLLISION_HEIGHT
      };
    }
    if ((orc[i].characteristics & 0b00000011) == ENEMY_ORC_UP_SPEAR)
    {
      enemyRect =
      {
        .x = orc[i].x,
        .y = ORC_Y - 22 + ((orcFrames + i) % 2),
        .width = SPEAR_U_COLLISION_WIDTH,
        .height = SPEAR_U_COLLISION_HEIGHT
      };
    }
    if (((orc[i].characteristics & 0B00110000) == 0B00010000) && arduboy.collide(helenaRect, enemyRect))
    {
      if (!(helena.characteristics & 0B00100000))
      {
        helena.characteristics |= 0B00100000;
        playerScore = 0;
        helena.life--;
      }
    }
  }
  ////// Check collision Helena with Spikes //////
  ////////////////////////////////////////////////
  for (byte i = 0; i < MAX_SPIKES_IN_WAVE; i++)
  {
    enemyRect =
    {
      .x = spike[i].x + 4,
      .y = SPIKE_Y + 2,
      .width = SPIKE_COLLISION_WIDTH,
      .height = SPIKE_COLLISION_HEIGHT
    };
    if (((spike[i].characteristics & 0B00110000) == 0B00010000) && arduboy.collide(helenaRect, enemyRect))
    {
      if (!(helena.characteristics & 0B00100000))
      {
        helena.characteristics |= 0B00100000;
        playerScore = 0;
        //helena.life--;
      }
      if (!(spike[i].characteristics & 0B01000000))
      {
        spike[i].characteristics |= 0B00100000;
      }
    }
  }
  ////// Check collision Helena with Flames //////
  ////////////////////////////////////////////////
  enemyRect =
  {
    .x = badWalkingFlame.x + 2,
    .y = badWalkingFlame.y + 4,
    .width = BADFLAME_COLLISION_WIDTH,
    .height = BADFLAME_COLLISION_HEIGHT
  };

  if (((badWalkingFlame.characteristics & 0B00110000) == 0B00010000) && arduboy.collide(helenaRect, enemyRect))
  {
    if (!(helena.characteristics & 0B00100000))
    {

      helena.characteristics |= 0B00100000;
      playerScore = 0;
      helena.life--;
    }
    if (!(badWalkingFlame.characteristics & 0B01000000))
    {
      badWalkingFlame.characteristics |= 0B00100000;
    }
  }

  enemyRect =
  {
    .x = badFlame.x + 2,
    .y = badFlame.y + 4,
    .width = BADFLAME_COLLISION_WIDTH,
    .height = BADFLAME_COLLISION_HEIGHT
  };
  if (((badFlame.characteristics & 0B00110000) == 0B00010000) && arduboy.collide(helenaRect, enemyRect))
  {
    if (!(helena.characteristics & 0B00100000))
    {
      helena.characteristics |= 0B00100000;
      playerScore = 0;
      helena.life--;
    }
    if (!(badFlame.characteristics & 0B01000000))
    {
      badFlame.characteristics |= 0B00100000;
    }
  }
  ////// Check collision Helena with Statue //////
  ////////////////////////////////////////////////
  enemyRect =
  {
    .x = statue.x,
    .y = STATUE_Y,
    .width = STATUE_COLLISION_WIDTH,
    .height = STATUE_COLLISION_HEIGHT
  };
  if (((statue.characteristics & 0B00110000) == 0B00010000) && arduboy.collide(helenaRect, enemyRect))
  {
    if (!(helena.characteristics & 0B00100000))
    {
      helena.x--;
    }
    if (!(statue.characteristics & 0B01000000))
    {
      statue.characteristics |= 0B00100000;
    }
  }

  enemyRect =
  {
    .x = arrow.x,
    .y = ARROW_Y,
    .width = ARROW_COLLISION_WIDTH,
    .height = ARROW_COLLISION_HEIGHT
  };
  if (((arrow.characteristics & 0B00110000) == 0B00010000) && arduboy.collide(helenaRect, enemyRect))
  {
    if (!(helena.characteristics & 0B00100000))
    {
      helena.characteristics |= 0B00100000;
      playerScore = 0;
      helena.life--;
    }
    if (!(arrow.characteristics & 0B01000000))
    {
      arrow.characteristics |= 0B00100000;
    }
  }
  ////// Check collision Helena with Weed //////
  //////////////////////////////////////////////
  enemyRect =
  {
    .x = badWeed.x + 2,
    .y = badWeed.y + 8,
    .width = BADWEED_COLLISION_WIDTH,
    .height = BADWEED_COLLISION_HEIGHT
  };
  if (((badWeed.characteristics & 0B00110000) == 0B00010000) && arduboy.collide(helenaRect, enemyRect))
  {
    if (!(helena.characteristics & 0B00100000))
    {
      helena.characteristics |= 0B00100000;
      playerScore = 0;
      helena.life--;
    }
    if (!(badWeed.characteristics & 0B01000000))
    {
      badWeed.characteristics |= 0B00100000;
    }
  }
  ////// Check collision Helena with goldbars //////
  //////////////////////////////////////////////////
  for (byte i = 0; i < MAX_ONSCREEN_GOLDBARS; i++)
  {
    enemyRect =
    {
      .x = goldBar[i].x - 2,
      .y = goldBar[i].y - 2,
      .width = GOLDBAR_COLLISION_WIDTH,
      .height = GOLDBAR_COLLISION_HEIGHT
    };
    if (((goldBar[i].characteristics & 0B00110000) == 0B00010000) && arduboy.collide(helenaRect, enemyRect))
    {
      if (!(helena.characteristics & 0B00100000))
      {
        playerScore += 200;
        goldBar[i].characteristics = 0;
      }
    }
  }

  //// Check collision Helena with secret chest ////
  //////////////////////////////////////////////////
  enemyRect =
  {
    .x = secretChest.x,
    .y = secretChest.y,
    .width = SECRET_CHEST_COLLISION_WIDTH,
    .height = SECRET_CHEST_COLLISION_HEIGHT,
  };
  if (((secretChest.characteristics & 0B10010000) == 0B10010000) && arduboy.collide(helenaRect, enemyRect))
  {
    playerScore += 500;
    helena.nextHelmet = (secretChest.characteristics & 0b00000111);
    secretChest.characteristics = 0B11000000;
    helena.characteristics |= 0B00000100;
    helena.life = HELENA_HELMET;
  }

  // end of collision detection
}





#endif
