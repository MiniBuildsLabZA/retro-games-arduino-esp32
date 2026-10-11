#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#include <ESP_I2S.h>
#include "cow_b_assets.h"
#include "sfx_data.h"

#define SFX_SWORD()       PLAY_SFX(sfx_jan_strikei)        // shared: George + ninja
#define SFX_ROJA_SHOOT()  PLAY_SFX(sfx_roja_shoot)
#define SFX_ARROW_SHOOT() PLAY_SFX(bow)
#define SFX_ROJA_DIE()    PLAY_SFX(sfx_roja_death)
#define SFX_JAN_DIE()     PLAY_SFX(sfx_jan_death)

#define TFT_CS   D1
#define TFT_RST  D2
#define TFT_DC   D3

#define I2S_BCLK   D6
#define I2S_LRC    D7
#define I2S_DIN    D9
#define SFX_RATE   16000
#define MAX_VOICES 4
#define SFX_VOLUME 1.0f      // 0.0 - 1.0, lower if it distorts when sounds overlap

#define swordStrike2Left swordStrike2Right

#define DRAW_FRAMES    15
#define STRIKE1_FRAMES 12
#define STRIKE2_FRAMES 44

// Size of the sword/strike frames. If any are bigger than 16x16, change these
// (and see the note on x offsets for left-facing frames).
#define ACT_W 16
#define ACT_H 16

#define LONG_PRESS_MS  500
#define DEBOUNCE_MS     25
#define SWORD_ANIM_MS   50

//NINJA SWORD
#define NINJA_W 16
#define NINJA_H 16
#define NINJA_MAX_HEALTH 3
#define NINJA_SPEED 0.9f
#define NINJA_MIN_Y 20
#define NINJA_MAX_Y (128 - NINJA_H)
#define NINJA_ATTACK_RANGE 22      // horizontal distance (center to center) to start a strike
#define NINJA_ALIGN_TOL 8
#define NINJA_THINK_MIN 150
#define NINJA_THINK_MAX 300
#define NINJA_WALK_MS 110
#define NINJA_ATTACK_MS 60         // 12 frames * 60ms = 720ms per strike
#define NINJA_HIT_START 4          // active frames (of 12)
#define NINJA_HIT_END   8
#define NINJA_REACH 18
#define NINJA_HURT_MS 350
#define NINJA_DEAD_MS 900
#define NINJA_BAR_W 16
#define NINJA_BAR_H 3

//NINJA ARROW (archer: IDLE / RUN / SHOOT)
#define NINJA_ARROW_W 16
#define NINJA_ARROW_H 16
#define NINJA_ARROW_MAX_HEALTH 5
#define NINJA_ARROW_SPEED 0.8f
#define NINJA_ARROW_MIN_Y 20
#define NINJA_ARROW_MAX_Y (128 - NINJA_ARROW_H)
#define NINJA_ARROW_TOO_CLOSE 30        // closer than this (px) -> back away
#define NINJA_ARROW_FAR 70              // farther than this -> chase
#define NINJA_ARROW_ALIGN_TOL 8         // vertical tolerance to count as "lined up"
#define NINJA_ARROW_THINK_MIN 500
#define NINJA_ARROW_THINK_MAX 1000
#define NINJA_ARROW_HURT_MS 350         // hit-flash duration
#define NINJA_ARROW_ANIM_FRAME_MS 100
#define NINJA_ARROW_FIRE_FRAME_STAND 3  // shoot frame index (0-4) the arrow leaves on
#define NINJA_ARROW_MUZZLE_Y 7          // hand height inside the 16x16 sprite
#define NINJA_ARROW_MUZZLE_RIGHT_X 14   // arrow spawn x offset when facing right
#define NINJA_ARROW_MUZZLE_LEFT_X 2     // and when facing left
#define NINJA_ARROW_BAR_W 16
#define NINJA_ARROW_BAR_H 3

#define ARROW_W 8               // <-- ARROW bitmap size
#define ARROW_H 3
#define ARROW_SPEED 3.0f
#define MAX_ARROWS 4
#define ARROW_KEY 0xF81F
// Right-facing arrow bitmap. If you don't have arrowrv in your assets,
// change this to arrowlv for now.
#define ARROW_BMP_RIGHT arrowrv
#define ARROW_BMP_LEFT  arrowlv

enum NinjaState : uint8_t { N_IDLE, N_WALK, N_ATTACK, N_HURT, N_DEAD };
NinjaState nState = N_IDLE;
float ninjaHealth = NINJA_MAX_HEALTH;
bool ninjaFacingLeft = true;
int8_t ninjaMoveX = 0, ninjaMoveY = 0;
float ninjaKnockVX = 0;
uint8_t ninjaAnimStep = 0;
bool ninjaStrikeHit = false, ninjaDrawn = false;
unsigned long ninjaLastFrameTime = 0, ninjaNextThink = 0, ninjaNextAttackOk = 1200;
unsigned long ninjaHurtUntil = 0, ninjaDeadStart = 0;
int16_t ninjaprevX = 96, ninjaprevY = 97;

bool swingHitRoja = false, swingHitNinja = false;
bool swingHitNinjaArrow = false;

#define ROJA_W 32
#define ROJA_H 32
#define ROJA_MAX_HEALTH 5
#define ROJA_SPEED 0.8f
#define ROJA_MIN_Y 20
#define ROJA_MAX_Y (128 - ROJA_H)
#define ROJA_TOO_CLOSE 30        // closer than this (px) -> back away
#define ROJA_FAR 90              // farther than this -> chase
#define ROJA_ALIGN_TOL 8         // vertical tolerance to count as "lined up"
#define ROJA_THINK_MIN 1000
#define ROJA_THINK_MAX 2000
#define ROJA_HURT_MS 350
#define ROJA_DEAD_MS 900
#define ROJA_FIRE_FRAME_STAND 3  // attack frame index (0-4) the bullet leaves on
#define ROJA_FIRE_FRAME_WALK  2  // attack-walk frame index (0-5)
#define ROJA_MUZZLE_Y 14         // hand height inside the 32x32 sprite
#define ROJA_MUZZLE_RIGHT_X 28   // bullet spawn x offset when facing right
#define ROJA_MUZZLE_LEFT_X 4     // and when facing left
#define ROJA_BAR_W 20
#define ROJA_BAR_H 3

#define BULLET_W 7               // <-- SET to your rojasbullet bitmap size
#define BULLET_H 8
#define BULLET_SPEED 3.0f
#define MAX_BULLETS 4
#define BULLET_KEY 0xF81F

#define HEALTH_PX_PER_POINT 2    // 2 health * 13 = your 26px bar
#define GEORGE_INVULN_MS 700

#define SWORD_REACH 10           // how far George's blade reaches in front of him
#define S1_HIT_START 4           // strike 1 active frames (of 12)
#define S1_HIT_END   8
#define S2_HIT_START 8           // strike 2 active frames (of 25)
#define S2_HIT_END   18
#define STRIKE_ANIM_MS 30
enum RojaState : uint8_t { R_IDLE, R_RUN, R_RUN_SHOOT, R_SHOOT, R_HURT, R_DEAD };
RojaState rState = R_IDLE;
float rojaHealth = ROJA_MAX_HEALTH;
bool rojaFacingLeft = true;
int8_t rojaMoveX = 0, rojaMoveY = 0;
float rojaKnockVX = 0;
uint8_t rojaShotsLeft = 0;
bool rojaFired = false, rojaDrawn = false;
unsigned long rojaNextThink = 0, rojaNextBurstOk = 1500, rojaHurtUntil = 0, rojaDeadStart = 0;

struct Bullet { float x, y; int8_t dir; bool active; bool drawn; int16_t px, py; };
Bullet bullets[MAX_BULLETS];

//NINJA_ARROW_GLOBALS (3 states; hurt = flash, dead = NinjaArrowAlive false)
enum NinjaArrowState : uint8_t { NA_IDLE, NA_RUN, NA_SHOOT };
NinjaArrowState naState = NA_IDLE;
float NinjaArrowHealth = NINJA_ARROW_MAX_HEALTH;
bool NinjaArrowAlive = true;
bool NinjaArrowFacingLeft = true;
int8_t NinjaArrowMoveX = 0, NinjaArrowMoveY = 0;
bool NinjaArrowFired = false, NinjaArrowDrawn = false;
uint8_t NinjaArrowAnimStep = 0;
unsigned long NinjaArrowLastFrameTime = 0, NinjaArrowNextThink = 0;
unsigned long NinjaArrowNextShotOk = 1500, NinjaArrowFlashUntil = 0;

struct Arrow { float x, y; int8_t dir; bool active; bool drawn; int16_t px, py; };
Arrow arrows[MAX_ARROWS];
///////////////////////////////////////////////////////////////////////////////////////////////


unsigned long georgeInvulnUntil = 0;
bool gameOver = false, gameOverShown = false;
unsigned long gameOverAt = 0;
bool hudDirty = false;
bool janRedraw = false;
enum FaceDir : uint8_t { FACE_SIDE, FACE_UP, FACE_DOWN };
FaceDir faceDir = FACE_SIDE;
// ---------- State ----------
enum PlayerState : uint8_t { PS_NORMAL, PS_DRAWING, PS_SHEATHING, PS_ARMED, PS_STRIKE1, PS_STRIKE2 };
PlayerState pState = PS_NORMAL;

int8_t actFrame = 0;
unsigned long actLastTime = 0;
bool comboQueued = false;
bool forceRedraw = false;

// ---------- Button (active LOW, INPUT_PULLUP) ----------
enum BtnEvent : uint8_t { BTN_NONE, BTN_SHORT, BTN_LONG };
bool btnStable = HIGH, btnLastRead = HIGH, longFired = false;
unsigned long btnChangeTime = 0, btnPressStart = 0;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
float georgeX = 29;
float georgeY = 89;
float georgeHealthX = 5;
float georgeHealthY = 6;
float georgeHealth = 8;
float georgeHealthBarWidthpx = 26;
float georgeHealthBarHightpx= 4;
int16_t prevX = (int)georgeX;
int16_t prevY = (int)georgeY;


float rojaX = 117;
float rojaY = 83;
int16_t rojaprevX = (int)rojaX;
int16_t rojaprevY = (int)rojaY;

float NinjaArrowX = 96;
float NinjaArrowY = 77;
int16_t NinjaArrowprevX = (int)NinjaArrowX;
int16_t NinjaArrowprevY = (int)NinjaArrowY;

float ninjaX = 96;
float ninjaY = 97;

//scroll

#define WORLD_W        320                       // two 160px backgrounds
#define MAX_CAM        (WORLD_W - SCREEN_W)      // 160
#define SCROLL_TRIGGER (SCREEN_W / 2 - SPRITE_W / 2)   // George's screen x where scrolling starts (72)
#define HEALTH_SCROLLS 0                         // 1 = health bar scrolls with the world, 0 = fixed HUD

int16_t camX = 0;          // camera for this frame
int16_t drawnCamX = 0;     // camera the screen currently shows
bool sceneDirty = false;   // true on frames where the whole background was redrawn
bool janMoving = false;
////
#define SPRITE_W 16
#define SPRITE_H 16
#define SCREEN_W 160
#define TRACTOR_W 50
#define TRACTOR_H 40
#define MAX_SPRITE_W 50   // must fit largest sprite erased (roja is 32 wide)

#define JOY_X_PIN D0
#define JOY_Y_PIN D4
#define JOY_HIGH_THRESH 3000
#define JOY_LOW_THRESH  1000
#define MOVE_SPEED   1.0f
#define ANIM_FRAME_MS 120
#define RUN_SPEED 1.8f
#define RUN_ANIM_FRAME_MS 60

// Run thresholds PER DIRECTION (raw ADC 0-4095). Tune these using JOY_DEBUG below.
// Rules: HIGH values must stay well above JOY_HIGH_THRESH (3000),
//        LOW values well below JOY_LOW_THRESH (1000).
#define JOY_RUN_X_HIGH 3600     // right
#define JOY_RUN_X_LOW   500     // left
#define JOY_RUN_Y_HIGH 3600     // up
#define JOY_RUN_Y_LOW   500     // down
#define JOY_RUN_HYST    250     // stays running until the stick eases back this far

#define JOY_DEBUG 1             // 1 = print raw stick values to Serial, 0 = off

bool xRun = false, yRun = false;
bool joyRunning = false;        // true if either axis is running (drives animation speed)
#define SWAP_BTN_PIN D5
#define RIDE_DISTANCE 25

#define ROJA_ANIM_FRAME_MS 80
//Background frames
const uint16_t* backgroudFrames[2] = {Farmland1, Farmland2};
uint16_t frameBuf[SCREEN_W * 128];   // 40KB off-screen frame
uint16_t* gBuf = nullptr;            // non-null = draw into frameBuf instead of the TFT

// George walk frames
const uint16_t* walkFramesRight[3] =        { janrv1, janrv2, janrv3 };
const uint16_t* walkFramesLeft[3]  =        { janlv1, janlv2, janlv3 };
const uint16_t* walkSwordFramesRight[3] =   { janswordwalkrv1, janswordwalkrv2, janswordwalkrv3 };
const uint16_t* walkSwordFramesLeft[3]  =   { janswordwalklv1, janswordwalklv2, janswordwalklv3 };
const uint16_t* walkUpFrames[2]   = { janback1,  janback2  };
const uint16_t* walkDownFrames[2] = { janfront1, janfront2 };

const uint16_t* idleFrameRight     = jan;
const uint16_t* idleFrameLeft      = janlv;

const uint16_t* drawSwordFramesRight[15] = {
  jansword1, jansword2, jansword3, jansword4, jansword5,
  jansword6, jansword7, jansword8, jansword9, jansword10,
  jansword11, jansword12, jansword13, jansword14, jansword15 };

const uint16_t* drawSwordFramesLeft[15] = {
  janswordlv1, janswordlv2, janswordlv3, janswordlv4, janswordlv5,
  janswordlv6, janswordlv7, janswordlv8, janswordlv9, janswordlv10,
  janswordlv11, janswordlv12, janswordlv13, janswordlv14, janswordlv15 };

const uint16_t* swordStrike1Right[12] = {
  janswordstrikei1, janswordstrikei2, janswordstrikei3, janswordstrikei4,
  janswordstrikei5, janswordstrikei6, janswordstrikei7, janswordstrikei8,
  janswordstrikei9, janswordstrikei10, janswordstrikei11, janswordstrikei12 };

const uint16_t* swordStrike1Left[12] = {
  janswordstrikeilv1, janswordstrikeilv2, janswordstrikeilv3, janswordstrikeilv4,
  janswordstrikeilv5, janswordstrikeilv6, janswordstrikeilv7, janswordstrikeilv8,
  janswordstrikeilv9, janswordstrikeilv10, janswordstrikeilv11, janswordstrikeilv12 };

const uint16_t* swordStrike3Right[25] = {
  janswordstrikeii1, janswordstrikeii2, janswordstrikeii3, janswordstrikeii4, janswordstrikeii5,
  janswordstrikeii6, janswordstrikeii7, janswordstrikeii8, janswordstrikeii9, janswordstrikeii10,
  janswordstrikeii11, janswordstrikeii12, janswordstrikeii13, janswordstrikeii14, janswordstrikeii15,
  janswordstrikeii16, janswordstrikeii17, janswordstrikeii18, janswordstrikeii19, janswordstrikeii20,
  janswordstrikeii21, janswordstrikeii22, janswordstrikeii23, janswordstrikeii24, janswordstrikeii25 };

const uint16_t* SwordStrike3Left[25]  = {janswordstrikeiilv1, janswordstrikeiilv2, janswordstrikeiilv3, janswordstrikeiilv4 ,janswordstrikeiilv5,
                                               janswordstrikeiilv6, janswordstrikeiilv7, janswordstrikeiilv8, janswordstrikeiilv9 ,janswordstrikeiilv10,
                                               janswordstrikeiilv11, janswordstrikeiilv12, janswordstrikeiilv13, janswordstrikeiilv14 ,janswordstrikeiilv15,
                                               janswordstrikeiilv16, janswordstrikeiilv17, janswordstrikeiilv18, janswordstrikeiilv19 ,janswordstrikeiilv20,
                                               janswordstrikeiilv21, janswordstrikeiilv22, janswordstrikeiilv23, janswordstrikeiilv24 ,janswordstrikeiilv25
                                              };

const uint16_t* SwordStrike2Left[44] = {
                                               janswordspinstrikelv1, janswordspinstrikelv2, janswordspinstrikelv3, janswordspinstrikelv4 ,janswordspinstrikelv5,
                                               janswordspinstrikelv6, janswordspinstrikelv7, janswordspinstrikelv8, janswordspinstrikelv9 ,janswordspinstrikelv10,
                                               janswordspinstrikelv11, janswordspinstrikelv12, janswordspinstrikelv13, janswordspinstrikelv14 ,janswordspinstrikelv15,
                                               janswordspinstrikelv16, janswordspinstrikelv17, janswordspinstrikelv18, janswordspinstrikelv19 ,janswordspinstrikelv20,
                                               janswordspinstrikelv21, janswordspinstrikelv22, janswordspinstrikelv23, janswordspinstrikelv24 ,janswordspinstrikelv25,
                                               janswordspinstrikelv7, janswordspinstrikelv8, janswordspinstrikelv9 ,janswordspinstrikelv10,
                                               janswordspinstrikelv11, janswordspinstrikelv12, janswordspinstrikelv13, janswordspinstrikelv14 ,janswordspinstrikelv15,
                                               janswordspinstrikelv16, janswordspinstrikelv17, janswordspinstrikelv18, janswordspinstrikelv19 ,janswordspinstrikelv20,
                                               janswordspinstrikelv21, janswordspinstrikelv22, janswordspinstrikelv23, janswordspinstrikelv24 ,janswordspinstrikelv25

};
const uint16_t* SwordStrike2Right[44] = {
  janswordspinstrikerv1, janswordspinstrikerv2, janswordspinstrikerv3, janswordspinstrikerv4, janswordspinstrikerv5,
  janswordspinstrikerv6, janswordspinstrikerv7, janswordspinstrikerv8, janswordspinstrikerv9, janswordspinstrikerv10,
  janswordspinstrikerv11, janswordspinstrikerv12, janswordspinstrikerv13, janswordspinstrikerv14, janswordspinstrikerv15,
  janswordspinstrikerv16, janswordspinstrikerv17, janswordspinstrikerv18, janswordspinstrikerv19, janswordspinstrikerv20,
  janswordspinstrikerv21, janswordspinstrikerv22, janswordspinstrikerv23, janswordspinstrikerv24, janswordspinstrikerv25,
  janswordspinstrikerv7, janswordspinstrikerv8, janswordspinstrikerv9, janswordspinstrikerv10,
  janswordspinstrikerv11, janswordspinstrikerv12, janswordspinstrikerv13, janswordspinstrikerv14, janswordspinstrikerv15,
  janswordspinstrikerv16, janswordspinstrikerv17, janswordspinstrikerv18, janswordspinstrikerv19, janswordspinstrikerv20,
  janswordspinstrikerv21, janswordspinstrikerv22, janswordspinstrikerv23, janswordspinstrikerv24, janswordspinstrikerv25
};

const uint8_t animSequence[6] = {0, 1, 2, 2, 1, 0};      // 3-frame walk cycle (George, ninja, archer)
uint8_t animStep = 0;
unsigned long lastFrameTime = 0;

bool facingLeft =   false;
bool wasMoving  =   true;
bool lastBtnState = HIGH;

//roja
uint8_t rojaAnimStep = 0;
unsigned long rojalastFrameTime = 0;
const uint8_t rojaIdleAnimSequence[10] = {0, 1, 2, 3, 4, 4, 3, 2, 1, 0};


const uint16_t* rojaWalkFramesRight[6] = {rojawalkrv1,rojawalkrv2,rojawalkrv3,rojawalkrv4,rojawalkrv5,rojawalkrv6 };
const uint16_t* rojaWalkFramesLeft[6]  = {rojawalk1,rojawalk2,rojawalk3,rojawalk4,rojawalk5,rojawalk6 };
const uint16_t* rojaIdleFramesRight[5] = { rojarv1, rojarv2, rojarv3, rojarv4, rojarv5 };
const uint16_t* rojaIdleFramesLeft[5]  = { roja1, roja2, roja3, roja4, roja5 };
const uint16_t* rojaAttackWalkFramesRight[6] = {rojaattackwalkrv1,rojaattackwalkrv2,rojaattackwalkrv3,rojaattackwalkrv4,rojaattackwalkrv5,rojaattackwalkrv6};
const uint16_t* rojaAttackWalkFramesLeft[6] = {rojaattackwalk1,rojaattackwalk2,rojaattackwalk3,rojaattackwalk4,rojaattackwalk5,rojaattackwalk6};
const uint16_t* rojaAttackFramesRight[5] = {rojaattackwalkrv1, rojaattackwalkrv2,rojaattackwalkrv3,rojaattackwalkrv4,rojaattackwalkrv5};
const uint16_t* rojaAttackFramesLeft[5] = {rojaattackwalk1, rojaattackwalk2,rojaattackwalk3,rojaattackwalk4,rojaattackwalk5};

const uint16_t* ninjaWalkLeft[]    = {ninjaswordwalklv1, ninjaswordwalklv2, ninjaswordwalklv3};
const uint16_t* ninjaWalkRight[]   = {ninjaswordwalkrv1, ninjaswordwalkrv2, ninjaswordwalkrv3};
const uint16_t* ninjaIdleLeft[]    = {ninjaswordstrikeilv1};
const uint16_t* ninjaIdleRight[]   = {ninjaswordstrikeirv1};

const uint16_t* ninjaAttackLeft[]  = {ninjaswordstrikeilv1, ninjaswordstrikeilv2, ninjaswordstrikeilv3, ninjaswordstrikeilv4,
                                      ninjaswordstrikeilv5, ninjaswordstrikeilv6, ninjaswordstrikeilv7, ninjaswordstrikeilv8,
                                      ninjaswordstrikeilv9, ninjaswordstrikeilv10, ninjaswordstrikeilv11, ninjaswordstrikeilv12,
                                      };

const uint16_t* ninjaAttackRight[] = {ninjaswordstrikeirv1, ninjaswordstrikeirv2, ninjaswordstrikeirv3, ninjaswordstrikeirv4,
                                      ninjaswordstrikeirv5, ninjaswordstrikeirv6, ninjaswordstrikeirv7, ninjaswordstrikeirv8,
                                      ninjaswordstrikeirv9, ninjaswordstrikeirv10, ninjaswordstrikeirv11, ninjaswordstrikeirv12,
                                      };

// Ninja archer frames
const uint16_t* ninjaArrowIdleLeft[]  = {ninjaarrowidlelv1, ninjaarrowidlelv2};
const uint16_t* ninjaArrowIdleRight[] = {ninjaarrowidlerv1, ninjaarrowidlerv2};

const uint16_t* ninjaArrowWalkLeft[]  = {ninjaarrowwalklv1, ninjaarrowwalklv2, ninjaarrowwalklv3};
const uint16_t* ninjaArrowWalkRight[] = {ninjaarrowwalkrv1, ninjaarrowwalkrv2, ninjaarrowwalkrv3};

const uint16_t* ninjaArrowAttackLeft[] = {
ninjaarrowshootlv1, ninjaarrowshootlv2, ninjaarrowshootlv3, ninjaarrowshootlv4, ninjaarrowshootlv5
};
const uint16_t* ninjaArrowAttackRight[] = {
ninjaarrowshootrv1, ninjaarrowshootrv2, ninjaarrowshootrv3, ninjaarrowshootrv4, ninjaarrowshootrv5
};

//////////working with sound
I2SClass i2s;

struct Voice {
  const uint8_t* data;
  uint32_t len;
  volatile uint32_t pos;
  volatile bool on;
};
Voice voices[MAX_VOICES];

void playSfx(const uint8_t* d, uint32_t len) {
  for (auto &v : voices) {
    if (v.on) continue;
    v.data = d;
    v.len = len;
    v.pos = 0;
    v.on = true;
    return;
  }
}

void audioTask(void*) {
  int16_t buf[256];
  const int32_t vol = (int32_t)(SFX_VOLUME * 128.0f);   // 128 = full scale
  for (;;) {
    for (int i = 0; i < 256; i++) {
      int32_t s = 0;
      for (auto &v : voices) {
        if (!v.on) continue;
        s += ((int8_t)v.data[v.pos++]) << 7;            // 8-bit signed -> 16-bit
        if (v.pos >= v.len) v.on = false;
      }
      s = (s * vol) >> 7;
      buf[i] = constrain(s, -32768, 32767);
    }
    i2s.write((uint8_t*)buf, sizeof(buf));              // blocks, so it paces itself
  }
}

void audioBegin() {
  i2s.setPins(I2S_BCLK, I2S_LRC, I2S_DIN);
  if (!i2s.begin(I2S_MODE_STD, SFX_RATE, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO)) {
    Serial.println("I2S init failed");
    return;
  }
  xTaskCreatePinnedToCore(audioTask, "audio", 4096, NULL, 1, NULL, 0);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

void composeBackground() {                       // world -> frameBuf at current camX
  int16_t split = SCREEN_W - camX;
  for (int16_t y = 0; y < 128; y++) {
    memcpy(&frameBuf[y * SCREEN_W],         &Farmland1[y * SCREEN_W + camX], split * 2);
    memcpy(&frameBuf[y * SCREEN_W + split], &Farmland2[y * SCREEN_W],        camX * 2);
  }
}

void pushFrame() {                               // one SPI burst for the whole screen
  tft.startWrite();
  tft.setAddrWindow(0, 0, SCREEN_W, 128);
  tft.writePixels(frameBuf, SCREEN_W * 128, true, false);
  tft.endWrite();
}


static void blitTransparent(int16_t x, int16_t y, const uint16_t *bm,
                            int16_t w, int16_t h, uint16_t key) {
  for (int16_t j = 0; j < h; j++) {
    int16_t sy = y + j;
    if (sy < 0 || sy >= 128) continue;
    for (int16_t i = 0; i < w; i++) {
      int16_t sx = x + i;
      if (sx < 0 || sx >= SCREEN_W) continue;
      uint16_t c = bm[j * w + i];
      if (c != key) frameBuf[sy * SCREEN_W + sx] = c;
    }
  }
}

static void fillRectTarget(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  if (!gBuf) { tft.fillRect(x, y, w, h, color); return; }
  for (int16_t j = max((int16_t)0, y); j < min((int16_t)128, (int16_t)(y + h)); j++)
    for (int16_t i = max((int16_t)0, x); i < min((int16_t)SCREEN_W, (int16_t)(x + w)); i++)
      frameBuf[j * SCREEN_W + i] = color;
}

void eraseSpriteRect(int16_t x, int16_t y, int16_t w, int16_t h) {
   if (gBuf) return;
  int16_t xStart = max((int16_t)0, x);
  int16_t yStart = max((int16_t)0, y);
  int16_t xEnd = min((int16_t)SCREEN_W, (int16_t)(x + w));
  int16_t yEnd = min((int16_t)128, (int16_t)(y + h));
  if (xStart >= xEnd || yStart >= yEnd) return;
  int16_t copyW = xEnd - xStart;

  static uint16_t rowBuf[MAX_SPRITE_W];
  tft.startWrite();
  for (int16_t yy = yStart; yy < yEnd; yy++) {
    int16_t wx = xStart + camX;                       // world x of first pixel
    for (int16_t i = 0; i < copyW; i++) {
      int16_t px = wx + i;
      rowBuf[i] = (px < SCREEN_W) ? Farmland1[yy * SCREEN_W + px]
                                  : Farmland2[yy * SCREEN_W + (px - SCREEN_W)];
    }
    tft.setAddrWindow(xStart, yy, copyW, 1);
    tft.writePixels(rowBuf, copyW, true, false);
  }
  tft.endWrite();
}

static void writeRunClipped(int16_t sx, int16_t sy, const uint16_t *buf, int16_t len) {
  if (sy < 0 || sy >= 128) return;
  int16_t skip = 0;
  if (sx < 0) { skip = -sx; sx = 0; }
  int16_t n = len - skip;
  if (sx + n > SCREEN_W) n = SCREEN_W - sx;
  if (n <= 0) return;
  tft.setAddrWindow(sx, sy, n, 1);
  tft.writePixels((uint16_t *)(buf + skip), n, true, false);
}

void drawSpriteTransparent(int16_t x, int16_t y, const uint16_t *bitmap,
                           int16_t w, int16_t h, uint16_t transparentColor) {
  if (x >= SCREEN_W || x + w <= 0 || y >= 128 || y + h <= 0) return;   // fully off-screen
  if (gBuf) { blitTransparent(x, y, bitmap, w, h, transparentColor); return; }
  uint16_t rowBuf[64];
  tft.startWrite();
  for (int16_t j = 0; j < h; j++) {
    int16_t runStart = -1;
    int16_t runLen = 0;
    for (int16_t i = 0; i <= w; i++) {
      uint16_t color = (i < w) ? bitmap[j * w + i] : transparentColor;
      bool opaque = (color != transparentColor);
      if (opaque) {
        if (runStart == -1) runStart = i;
        rowBuf[runLen++] = color;
      } else if (runStart != -1) {
        writeRunClipped(x + runStart, y + j, rowBuf, runLen);
        runStart = -1;
        runLen = 0;
      }
    }
  }
  tft.endWrite();
}

bool rectsOverlap(int16_t ax, int16_t ay, int16_t aw, int16_t ah,
                   int16_t bx, int16_t by, int16_t bw, int16_t bh) {
  return !(ax + aw <= bx || bx + bw <= ax || ay + ah <= by || by + bh <= ay);
}

// Moved up here so erasePhase() and friends can see it
bool janRectHit(int16_t wx, int16_t wy, int16_t w, int16_t h) {
  return rectsOverlap(wx, wy, w, h, prevX, prevY, ACT_W, ACT_H);
}



void setRojaState(RojaState s) {
  rState = s;
  rojaAnimStep = 0;
  rojalastFrameTime = millis();
  rojaFired = false;
}

void enterRoja(RojaState s) { if (rState != s) setRojaState(s); }

void startBurst() {
  rojaMoveX = 0; rojaMoveY = 0;
  rojaShotsLeft = random(1, 4);                  // 1-3 shots
  setRojaState(R_SHOOT);
}

void fireRojaBullet() {
  for (auto &b : bullets) {
    if (b.active) continue;
    b.dir = rojaFacingLeft ? -1 : 1;
    b.x = rojaFacingLeft ? rojaX + ROJA_MUZZLE_LEFT_X - BULLET_W : rojaX + ROJA_MUZZLE_RIGHT_X;
    b.y = rojaY + ROJA_MUZZLE_Y;
    b.active = true;
    SFX_ROJA_SHOOT();
    return;
  }
}

void rojaThink(unsigned long now, float gc, float rc) {
  rojaNextThink = now + random(ROJA_THINK_MIN, ROJA_THINK_MAX);

  float dx = gc - rc;
  float dist = fabsf(dx);
  int8_t toward = (dx < 0) ? -1 : 1;
  float dy = (georgeY + SPRITE_H / 2.0f) - (rojaY + ROJA_MUZZLE_Y);   // muzzle vs George's body
  bool aligned = fabsf(dy) <= ROJA_ALIGN_TOL;
  int8_t vert = aligned ? 0 : (dy > 0 ? 1 : -1);
  bool shotReady = now >= rojaNextBurstOk;

  rojaMoveX = 0; rojaMoveY = 0;

  if (dist < ROJA_TOO_CLOSE) {                   // George is in sword range
    int8_t away = -toward;
    bool blocked = (away < 0 && rojaX <= 2) || (away > 0 && rojaX >= WORLD_W - ROJA_W - 2);
    if (!blocked && random(100) < 70) {
      rojaMoveX = away;
      enterRoja((aligned && shotReady && random(100) < 40) ? R_RUN_SHOOT : R_RUN);
    } else if (shotReady) {
      startBurst();                              // cornered -> fight back
    } else {
      enterRoja(R_IDLE);
    }
  } else if (dist > ROJA_FAR) {                  // chase
    rojaMoveX = toward; rojaMoveY = vert;
    enterRoja((aligned && shotReady) ? R_RUN_SHOOT : R_RUN);
  } else {                                       // mid range: line up and shoot
    if (!aligned)                               { rojaMoveY = vert; enterRoja(R_RUN); }
    else if (shotReady && random(100) < 80)     { startBurst(); }
    else if (random(100) < 35)                  { rojaMoveX = random(2) ? 1 : -1; enterRoja(R_RUN); }  // strafe
    else                                        { enterRoja(R_IDLE); }
  }
}

void updateRoja() {
  if (rState == R_DEAD) return;
  unsigned long now = millis();

  float gc = georgeX + SPRITE_W / 2.0f;
  float rc = rojaX + ROJA_W / 2.0f;
  if (rState != R_HURT) rojaFacingLeft = (gc < rc);   // always faces George

  // movement
  if (rState == R_RUN || rState == R_RUN_SHOOT) {
    rojaX += rojaMoveX * ROJA_SPEED;
    rojaY += rojaMoveY * ROJA_SPEED;
  } else if (rState == R_HURT) {
    rojaX += rojaKnockVX;
    rojaKnockVX *= 0.8f;
    if (now >= rojaHurtUntil) { setRojaState(R_IDLE); rojaNextThink = now + random(100, 250); }
  }
  rojaX = constrain(rojaX, 0.0f, (float)(WORLD_W - ROJA_W));
  rojaY = constrain(rojaY, (float)ROJA_MIN_Y, (float)ROJA_MAX_Y);

  // animation + shooting on specific frames
  if (now - rojalastFrameTime >= ROJA_ANIM_FRAME_MS) {
    rojalastFrameTime = now;
    switch (rState) {
      case R_IDLE:
        rojaAnimStep = (rojaAnimStep + 1) % 10;
        break;
      case R_RUN:
        rojaAnimStep = (rojaAnimStep + 1) % 6;
        break;
      case R_RUN_SHOOT:
        rojaAnimStep = (rojaAnimStep + 1) % 6;
        if (rojaAnimStep == 0) rojaFired = false;
        if (rojaAnimStep == ROJA_FIRE_FRAME_WALK && !rojaFired && now >= rojaNextBurstOk) {
          fireRojaBullet();
          rojaFired = true;
          rojaNextBurstOk = now + random(700, 1200);
        }
        break;
      case R_SHOOT:
        rojaAnimStep++;
        if (rojaAnimStep == ROJA_FIRE_FRAME_STAND && !rojaFired) { fireRojaBullet(); rojaFired = true; }
        if (rojaAnimStep >= 5) {
          if (rojaShotsLeft > 0) rojaShotsLeft--;
          if (rojaShotsLeft > 0) { rojaAnimStep = 0; rojaFired = false; }     // next shot in burst
          else {
            rojaNextBurstOk = now + random(900, 1800);                         // cooldown
            setRojaState(R_IDLE);
            rojaNextThink = now + random(150, 300);                            // short recovery
          }
        }
        break;
      default: break;
    }
  }

  // decide (only when not committed to shooting/hurt)
  bool canThink = (rState == R_IDLE || rState == R_RUN || rState == R_RUN_SHOOT);
  if (canThink && now >= rojaNextThink) rojaThink(now, gc, rc);
}

void hurtRoja(int dmg) {
  unsigned long now = millis();
  rojaHealth -= dmg;
  rojaShotsLeft = 0;
  rojaMoveX = 0; rojaMoveY = 0;
  if (rojaHealth <= 0) {
    rojaHealth = 0;
    setRojaState(R_DEAD);
    rojaDeadStart = now;
    SFX_ROJA_DIE();
    return;
  }
  setRojaState(R_HURT);
  rojaHurtUntil = now + ROJA_HURT_MS;
  rojaKnockVX = ((georgeX + SPRITE_W / 2.0f) < (rojaX + ROJA_W / 2.0f)) ? 3.0f : -3.0f;  // pushed away
}

////// Ninja Arrow (archer) functions: IDLE / RUN / SHOOT
void setNinjaArrowState(NinjaArrowState s) {
  naState = s;
  NinjaArrowAnimStep = 0;
  NinjaArrowLastFrameTime = millis();
  NinjaArrowFired = false;
}

void enterNinjaArrow(NinjaArrowState s) { if (naState != s) setNinjaArrowState(s); }

void startNinjaArrowShoot() {
  NinjaArrowMoveX = 0; NinjaArrowMoveY = 0;
  setNinjaArrowState(NA_SHOOT);
}

void fireNinjaArrow() {
  for (auto &a : arrows) {
    if (a.active) continue;
    a.dir = NinjaArrowFacingLeft ? -1 : 1;
    a.x = NinjaArrowFacingLeft ? NinjaArrowX + NINJA_ARROW_MUZZLE_LEFT_X - ARROW_W
                               : NinjaArrowX + NINJA_ARROW_MUZZLE_RIGHT_X;
    a.y = NinjaArrowY + NINJA_ARROW_MUZZLE_Y;
    a.active = true;
    SFX_ARROW_SHOOT();
    return;
  }
}

void NinjaArrowThink(unsigned long now, float gc, float nc) {
  NinjaArrowNextThink = now + random(NINJA_ARROW_THINK_MIN, NINJA_ARROW_THINK_MAX);

  float dx = gc - nc;
  float dist = fabsf(dx);
  int8_t toward = (dx < 0) ? -1 : 1;
  float dy = (georgeY + SPRITE_H / 2.0f) - (NinjaArrowY + NINJA_ARROW_MUZZLE_Y);
  bool aligned = fabsf(dy) <= NINJA_ARROW_ALIGN_TOL;
  int8_t vert = aligned ? 0 : (dy > 0 ? 1 : -1);
  bool ready = now >= NinjaArrowNextShotOk;

  NinjaArrowMoveX = 0; NinjaArrowMoveY = 0;

  if (dist < NINJA_ARROW_TOO_CLOSE) {                 // too close: back away
    int8_t away = -toward;
    bool blocked = (away < 0 && NinjaArrowX <= 2) ||
                   (away > 0 && NinjaArrowX >= WORLD_W - NINJA_ARROW_W - 2);
    if (!blocked && random(100) < 70)  { NinjaArrowMoveX = away; enterNinjaArrow(NA_RUN); }
    else if (ready && aligned)         { startNinjaArrowShoot(); }   // cornered
    else                               { enterNinjaArrow(NA_IDLE); }
  } else if (dist > NINJA_ARROW_FAR) {                // too far: chase
    NinjaArrowMoveX = toward; NinjaArrowMoveY = vert;
    enterNinjaArrow(NA_RUN);
  } else {                                            // sweet spot
    if (!aligned)      { NinjaArrowMoveY = vert; enterNinjaArrow(NA_RUN); }
    else if (ready)    { startNinjaArrowShoot(); }
    else               { enterNinjaArrow(NA_IDLE); }
  }
}

void updateNinjaArrow() {
  if (!NinjaArrowAlive) return;
  unsigned long now = millis();

  float gc = georgeX + SPRITE_W / 2.0f;
  float nc = NinjaArrowX + NINJA_ARROW_W / 2.0f;
  if (naState != NA_SHOOT) NinjaArrowFacingLeft = (gc < nc);   // locked while aiming

  if (naState == NA_RUN) {
    NinjaArrowX += NinjaArrowMoveX * NINJA_ARROW_SPEED;
    NinjaArrowY += NinjaArrowMoveY * NINJA_ARROW_SPEED;
  }
  NinjaArrowX = constrain(NinjaArrowX, 0.0f, (float)(WORLD_W - NINJA_ARROW_W));
  NinjaArrowY = constrain(NinjaArrowY, (float)NINJA_ARROW_MIN_Y, (float)NINJA_ARROW_MAX_Y);

  if (now - NinjaArrowLastFrameTime >= NINJA_ARROW_ANIM_FRAME_MS) {
    NinjaArrowLastFrameTime = now;
    if (naState == NA_RUN) {
      NinjaArrowAnimStep = (NinjaArrowAnimStep + 1) % 6;
    } else if (naState == NA_SHOOT) {
      NinjaArrowAnimStep++;
      if (NinjaArrowAnimStep == NINJA_ARROW_FIRE_FRAME_STAND && !NinjaArrowFired) {
        fireNinjaArrow();
        NinjaArrowFired = true;
      }
      if (NinjaArrowAnimStep >= 5) {
        NinjaArrowNextShotOk = now + random(1200, 2200);   // cooldown
        setNinjaArrowState(NA_IDLE);
        NinjaArrowNextThink = now + random(150, 300);
      }
    }
  }

  if (naState != NA_SHOOT && now >= NinjaArrowNextThink) NinjaArrowThink(now, gc, nc);
}

void hurtNinjaArrow(int dmg) {
  unsigned long now = millis();
  NinjaArrowHealth -= dmg;
  NinjaArrowFlashUntil = now + NINJA_ARROW_HURT_MS;     // flash, not a state
  if (NinjaArrowHealth <= 0) { NinjaArrowHealth = 0; NinjaArrowAlive = false; return; }
  NinjaArrowX += ((georgeX < NinjaArrowX) ? 4 : -4);    // small shove away from George
  setNinjaArrowState(NA_IDLE);                          // flinch cancels the shot
  NinjaArrowNextThink = now + 200;
}



///////////////////////////////
void hurtGeorge(int dmg) {
  georgeHealth -= dmg;
  if (georgeHealth < 0) georgeHealth = 0;
  georgeHealthBarWidthpx = georgeHealth * HEALTH_PX_PER_POINT;
  hudDirty = true;
  georgeInvulnUntil = millis() + GEORGE_INVULN_MS;
  if (georgeHealth <= 0 && !gameOver) {
  gameOver = true;
  gameOverAt = millis();
  SFX_JAN_DIE();
  }
}
void setNinjaState(NinjaState s) {
  nState = s;
  ninjaAnimStep = 0;
  ninjaLastFrameTime = millis();
  ninjaStrikeHit = false;
}

void enterNinja(NinjaState s) { if (nState != s) setNinjaState(s); }

void ninjaThink(unsigned long now, float gc, float nc) {
  ninjaNextThink = now + random(NINJA_THINK_MIN, NINJA_THINK_MAX);

  float dx = gc - nc;
  float dist = fabsf(dx);
  int8_t toward = (dx < 0) ? -1 : 1;
  float dy = (georgeY + SPRITE_H / 2.0f) - (ninjaY + NINJA_H / 2.0f);
  bool aligned = fabsf(dy) <= NINJA_ALIGN_TOL;
  int8_t vert = aligned ? 0 : (dy > 0 ? 1 : -1);
  bool ready = now >= ninjaNextAttackOk;

  ninjaMoveX = 0; ninjaMoveY = 0;

  if (dist <= NINJA_ATTACK_RANGE && aligned) {
    if (ready) {
    if (random(100) < 85) { setNinjaState(N_ATTACK); SFX_SWORD(); }
    else enterNinja(N_IDLE);
    } else if (random(100) < 50) {                       // cooling down: step back or hold guard
      ninjaMoveX = -toward;
      enterNinja(N_WALK);
    } else {
      enterNinja(N_IDLE);
    }
    return;
  }

  // approach: close the gap, line up vertically
  ninjaMoveX = (dist > NINJA_ATTACK_RANGE - 4) ? toward : 0;
  ninjaMoveY = vert;
  if (ninjaMoveX == 0 && ninjaMoveY == 0) enterNinja(N_IDLE);
  else enterNinja(N_WALK);
}

void updateNinja() {
  if (nState == N_DEAD) return;
  unsigned long now = millis();

  float gc = georgeX + SPRITE_W / 2.0f;
  float nc = ninjaX + NINJA_W / 2.0f;
  if (nState != N_HURT && nState != N_ATTACK) ninjaFacingLeft = (gc < nc);   // facing locks during a strike

  if (nState == N_WALK) {
    ninjaX += ninjaMoveX * NINJA_SPEED;
    ninjaY += ninjaMoveY * NINJA_SPEED;
  } else if (nState == N_HURT) {
    ninjaX += ninjaKnockVX;
    ninjaKnockVX *= 0.8f;
    if (now >= ninjaHurtUntil) { setNinjaState(N_IDLE); ninjaNextThink = now + random(100, 250); }
  }
  ninjaX = constrain(ninjaX, 0.0f, (float)(WORLD_W - NINJA_W));
  ninjaY = constrain(ninjaY, (float)NINJA_MIN_Y, (float)NINJA_MAX_Y);

  // animation
  unsigned long frameMs = (nState == N_ATTACK) ? NINJA_ATTACK_MS : NINJA_WALK_MS;
  if (now - ninjaLastFrameTime >= frameMs) {
    ninjaLastFrameTime = now;
    if (nState == N_WALK) {
      ninjaAnimStep = (ninjaAnimStep + 1) % 6;
    } else if (nState == N_ATTACK) {
      ninjaAnimStep++;
      if (ninjaAnimStep >= 12) {
        ninjaNextAttackOk = now + random(700, 1400);       // cooldown before next strike
        setNinjaState(N_IDLE);
        ninjaNextThink = now + random(300, 600);           // recovery: window for George to punish
      }
    }
  }

  // sword damage: active frames only, once per strike, respects George's i-frames
  if (nState == N_ATTACK && !ninjaStrikeHit &&
      ninjaAnimStep >= NINJA_HIT_START && ninjaAnimStep <= NINJA_HIT_END &&
      now >= georgeInvulnUntil) {
    int16_t sx = ninjaFacingLeft ? (int)ninjaX - NINJA_REACH : (int)ninjaX + NINJA_W;
    if (rectsOverlap(sx, (int)ninjaY - 2, NINJA_REACH, NINJA_H + 4,
                     (int)georgeX + 3, (int)georgeY + 2, 10, 13)) {
      ninjaStrikeHit = true;
      hurtGeorge(1);
    }
  }

  bool canThink = (nState == N_IDLE || nState == N_WALK);
  if (canThink && now >= ninjaNextThink) ninjaThink(now, gc, nc);
}

void hurtNinja(int dmg) {
  unsigned long now = millis();
  ninjaHealth -= dmg;
  ninjaMoveX = 0; ninjaMoveY = 0;
  if (ninjaHealth <= 0) {
    ninjaHealth = 0;
    setNinjaState(N_DEAD);
    ninjaDeadStart = now;
    return;
  }
  setNinjaState(N_HURT);                                   // interrupts his strike
  ninjaHurtUntil = now + NINJA_HURT_MS;
  ninjaKnockVX = ((georgeX + SPRITE_W / 2.0f) < (ninjaX + NINJA_W / 2.0f)) ? 3.0f : -3.0f;
}

// George's blade can hit Roja, Ninja and the archer, once each per swing
void checkSwordHit() {
  bool s1 = (pState == PS_STRIKE1 && actFrame >= S1_HIT_START && actFrame <= S1_HIT_END);
  bool s2 = (pState == PS_STRIKE2 && actFrame >= S2_HIT_START && actFrame <= S2_HIT_END);
  if (!s1 && !s2) return;

  int16_t sx = facingLeft ? (int)georgeX - SWORD_REACH : (int)georgeX + SPRITE_W;
  int16_t sy = (int)georgeY - 4;
  int dmg = s2 ? 2 : 1;                                    // strike 2 hits harder

  if (rState != R_DEAD && !swingHitRoja &&
      rectsOverlap(sx, sy, SWORD_REACH, SPRITE_H + 8, (int)rojaX + 6, (int)rojaY + 4, 20, 28)) {
    swingHitRoja = true;
    hurtRoja(dmg);
  }
  if (nState != N_DEAD && !swingHitNinja &&
      rectsOverlap(sx, sy, SWORD_REACH, SPRITE_H + 8, (int)ninjaX + 2, (int)ninjaY + 2, 12, 14)) {
    swingHitNinja = true;
    hurtNinja(dmg);
  }
  if (NinjaArrowAlive && !swingHitNinjaArrow &&
      rectsOverlap(sx, sy, SWORD_REACH, SPRITE_H + 8, (int)NinjaArrowX + 2, (int)NinjaArrowY + 2, 12, 14)) {
    swingHitNinjaArrow = true;
    hurtNinjaArrow(dmg);
  }
}
const uint16_t* ninjaFrame() {
  bool L = ninjaFacingLeft;
  switch (nState) {
    case N_WALK:   return (L ? ninjaWalkLeft   : ninjaWalkRight)[animSequence[ninjaAnimStep % 6]];
    case N_ATTACK: return (L ? ninjaAttackLeft : ninjaAttackRight)[ninjaAnimStep % 12];
    default:       return (L ? ninjaIdleLeft   : ninjaIdleRight)[0];       // guard pose, sword out
  }
}

void drawNinja() {
  unsigned long now = millis();
  bool visible = true;
  if (nState == N_HURT) visible = !((now / 70) & 1);
  if (nState == N_DEAD) visible = (now - ninjaDeadStart < NINJA_DEAD_MS) && !((now / 90) & 1);

  ninjaprevX = (int)ninjaX;
  ninjaprevY = (int)ninjaY;
  if (!visible) return;

  drawSpriteTransparent((int)ninjaX - camX, (int)ninjaY, ninjaFrame(), NINJA_W, NINJA_H, 0xF81F);

  if (nState != N_DEAD) {                                  // health above head
    int16_t bx = (int)ninjaX - camX + (NINJA_W - NINJA_BAR_W) / 2;
    int16_t by = (int)ninjaY - 5;
    int16_t fillW = (int)ceilf(NINJA_BAR_W * ninjaHealth / NINJA_MAX_HEALTH);
    fillRectTarget(bx, by, NINJA_BAR_W, NINJA_BAR_H, 0x4208);
    fillRectTarget(bx, by, fillW, NINJA_BAR_H, ninjaHealth <= 1 ? ST77XX_RED : ST77XX_GREEN);
  }
  ninjaDrawn = true;
}

// Erases everything that moved last frame (bullets, arrows, Roja, Ninja, archer, HUD, George)
void erasePhase() {
  janRedraw = janMoving || wasMoving || forceRedraw || sceneDirty ||
              (millis() < georgeInvulnUntil + 100);

  for (auto &b : bullets) {
    if (b.drawn) {
      eraseSpriteRect(b.px - camX, b.py, BULLET_W, BULLET_H);
      if (janRectHit(b.px, b.py, BULLET_W, BULLET_H)) janRedraw = true;
    }
    if (b.active && janRectHit((int)b.x, (int)b.y, BULLET_W, BULLET_H)) janRedraw = true;
  }

  for (auto &a : arrows) {
    if (a.drawn) {
      eraseSpriteRect(a.px - camX, a.py, ARROW_W, ARROW_H);
      if (janRectHit(a.px, a.py, ARROW_W, ARROW_H)) janRedraw = true;
    }
    if (a.active && janRectHit((int)a.x, (int)a.y, ARROW_W, ARROW_H)) janRedraw = true;
  }

  if (rojaDrawn) {
    eraseSpriteRect(rojaprevX - camX, rojaprevY - 6, ROJA_W, ROJA_H + 6);
    if (janRectHit(rojaprevX, rojaprevY - 6, ROJA_W, ROJA_H + 6)) janRedraw = true;
  }
  if (janRectHit((int)rojaX, (int)rojaY - 6, ROJA_W, ROJA_H + 6)) janRedraw = true;
  rojaDrawn = false;

  if (ninjaDrawn) {
    eraseSpriteRect(ninjaprevX - camX, ninjaprevY - 6, NINJA_W, NINJA_H + 6);
    if (janRectHit(ninjaprevX, ninjaprevY - 6, NINJA_W, NINJA_H + 6)) janRedraw = true;
  }
  if (janRectHit((int)ninjaX, (int)ninjaY - 6, NINJA_W, NINJA_H + 6)) janRedraw = true;
  ninjaDrawn = false;

  if (NinjaArrowDrawn) {
    eraseSpriteRect(NinjaArrowprevX - camX, NinjaArrowprevY - 6, NINJA_ARROW_W, NINJA_ARROW_H + 6);
    if (janRectHit(NinjaArrowprevX, NinjaArrowprevY - 6, NINJA_ARROW_W, NINJA_ARROW_H + 6)) janRedraw = true;
  }
  if (janRectHit((int)NinjaArrowX, (int)NinjaArrowY - 6, NINJA_ARROW_W, NINJA_ARROW_H + 6)) janRedraw = true;
  NinjaArrowDrawn = false;

  if (hudDirty) {
    int16_t off = HEALTH_SCROLLS ? camX : 0;
    eraseSpriteRect((int)georgeHealthX - off, (int)georgeHealthY, 41, 14);
  }

  if (janRedraw) eraseSpriteRect(prevX - camX, prevY, ACT_W, ACT_H);
}

void drawPhase() {
  drawRoja();
  drawNinja();
  drawNinjaArrow();
  drawPlayerhealth();
  drawJan();
  drawBullets();
  drawArrows();
}

void updateBullets() {
  unsigned long now = millis();
  for (auto &b : bullets) {
    if (!b.active) continue;
    b.x += b.dir * BULLET_SPEED;
    if (b.x < -BULLET_W || b.x > WORLD_W) { b.active = false; continue; }
    if (now >= georgeInvulnUntil &&
        rectsOverlap((int)b.x, (int)b.y, BULLET_W, BULLET_H,
                     (int)georgeX + 3, (int)georgeY + 2, 10, 13)) {   // George's hurtbox
      b.active = false;
      hurtGeorge(1);
    }
  }
}

void updateArrows() {
  unsigned long now = millis();
  for (auto &a : arrows) {
    if (!a.active) continue;
    a.x += a.dir * ARROW_SPEED;
    if (a.x < -ARROW_W || a.x > WORLD_W) { a.active = false; continue; }
    if (now >= georgeInvulnUntil &&
        rectsOverlap((int)a.x, (int)a.y, ARROW_W, ARROW_H,
                     (int)georgeX + 3, (int)georgeY + 2, 10, 13)) {
      a.active = false;
      hurtGeorge(1);
    }
  }
}

const uint16_t* rojaFrame() {
  bool L = rojaFacingLeft;
  switch (rState) {
    case R_RUN:       return (L ? rojaWalkFramesLeft       : rojaWalkFramesRight)[rojaAnimStep % 6];
    case R_RUN_SHOOT: return (L ? rojaAttackWalkFramesLeft : rojaAttackWalkFramesRight)[rojaAnimStep % 6];
    case R_SHOOT:     return (L ? rojaAttackFramesLeft     : rojaAttackFramesRight)[rojaAnimStep % 5];
    case R_IDLE:      return (L ? rojaIdleFramesLeft       : rojaIdleFramesRight)[rojaIdleAnimSequence[rojaAnimStep % 10]];
    default:          return (L ? rojaIdleFramesLeft       : rojaIdleFramesRight)[0];
  }
}

const uint16_t* NinjaArrowFrame() {
  bool L = NinjaArrowFacingLeft;
  switch (naState) {
    case NA_RUN:   return (L ? ninjaArrowWalkLeft : ninjaArrowWalkRight)[animSequence[NinjaArrowAnimStep % 6]];
    case NA_SHOOT: return (L ? ninjaArrowAttackLeft : ninjaArrowAttackRight)[NinjaArrowAnimStep % 5];
    default:       return (L ? ninjaArrowIdleLeft : ninjaArrowIdleRight)[(millis() / 400) & 1];
  }
}

void drawRoja() {
  unsigned long now = millis();
  bool visible = true;
  if (rState == R_HURT) visible = !((now / 70) & 1);                                   // flash when hit
  if (rState == R_DEAD) visible = (now - rojaDeadStart < ROJA_DEAD_MS) && !((now / 90) & 1);  // blink out

  rojaprevX = (int)rojaX;
  rojaprevY = (int)rojaY;
  if (!visible) return;

  drawSpriteTransparent((int)rojaX - camX, (int)rojaY, rojaFrame(), ROJA_W, ROJA_H, 0xF81F);

  if (rState != R_DEAD) {                                                              // health above head
    int16_t bx = (int)rojaX - camX + (ROJA_W - ROJA_BAR_W) / 2;
    int16_t by = (int)rojaY - 5;
    int16_t fillW = (int)ceilf(ROJA_BAR_W * rojaHealth / ROJA_MAX_HEALTH);
    fillRectTarget(bx, by, ROJA_BAR_W, ROJA_BAR_H, 0x4208);
    fillRectTarget(bx, by, fillW, ROJA_BAR_H, rojaHealth <= 1 ? ST77XX_RED : ST77XX_GREEN);
  }
  rojaDrawn = true;
}

void drawNinjaArrow() {
  unsigned long now = millis();
  NinjaArrowprevX = (int)NinjaArrowX;
  NinjaArrowprevY = (int)NinjaArrowY;
  if (!NinjaArrowAlive) return;
  if (now < NinjaArrowFlashUntil && ((now / 70) & 1)) return;   // hit flash

  drawSpriteTransparent((int)NinjaArrowX - camX, (int)NinjaArrowY,
                        NinjaArrowFrame(), NINJA_ARROW_W, NINJA_ARROW_H, 0xF81F);

  int16_t bx = (int)NinjaArrowX - camX + (NINJA_ARROW_W - NINJA_ARROW_BAR_W) / 2;
  int16_t by = (int)NinjaArrowY - 5;
  int16_t fillW = (int)ceilf(NINJA_ARROW_BAR_W * NinjaArrowHealth / NINJA_ARROW_MAX_HEALTH);
  fillRectTarget(bx, by, NINJA_ARROW_BAR_W, NINJA_ARROW_BAR_H, 0x4208);
  fillRectTarget(bx, by, fillW, NINJA_ARROW_BAR_H, NinjaArrowHealth <= 1 ? ST77XX_RED : ST77XX_GREEN);
  NinjaArrowDrawn = true;
}

void drawBullets() {
  for (auto &b : bullets) {
    if (b.active) {
      b.px = (int)b.x; b.py = (int)b.y;
      drawSpriteTransparent(b.px - camX, b.py, rojasbullet, BULLET_W, BULLET_H, BULLET_KEY);
      b.drawn = true;
    } else {
      b.drawn = false;
    }
  }
}

void drawArrows() {
  for (auto &a : arrows) {
    if (a.active) {
      a.px = (int)a.x; a.py = (int)a.y;
      drawSpriteTransparent(a.px - camX, a.py, a.dir < 0 ? ARROW_BMP_LEFT : ARROW_BMP_RIGHT,
                            ARROW_W, ARROW_H, ARROW_KEY);
      a.drawn = true;
    } else {
      a.drawn = false;
    }
  }
}

// rojaX/rojaY, ninjaX/ninjaY and rojaprevX/Y are WORLD coords.
void moveRoja() {
  if (millis() - rojalastFrameTime >= ROJA_ANIM_FRAME_MS) {
    rojalastFrameTime = millis();
    rojaAnimStep = (rojaAnimStep + 1) % 10;
  }
  eraseSpriteRect(rojaprevX - camX, rojaprevY, 32, 32);
  drawSpriteTransparent((int)rojaX - camX, (int)rojaY,
                        rojaIdleFramesLeft[rojaIdleAnimSequence[rojaAnimStep]], 32, 32, 0xF81F);
  rojaprevX = rojaX;
  rojaprevY = rojaY;
}


void drawPlayerhealth() {
  int16_t off = HEALTH_SCROLLS ? camX : 0;
  drawSpriteTransparent((int)georgeHealthX - off, (int)georgeHealthY, janhealth, 41, 14, 0xF81F);
  fillRectTarget(19 - off, 11, georgeHealthBarWidthpx, georgeHealthBarHightpx, ST77XX_RED);
  hudDirty = false;
}

BtnEvent readButton() {
  BtnEvent ev = BTN_NONE;
  unsigned long now = millis();
  bool r = digitalRead(SWAP_BTN_PIN);

  if (r != btnLastRead) { btnLastRead = r; btnChangeTime = now; }

  if (now - btnChangeTime >= DEBOUNCE_MS && r != btnStable) {
    btnStable = r;
    if (btnStable == LOW) { btnPressStart = now; longFired = false; }
    else if (!longFired)  { ev = BTN_SHORT; }       // released before long-press threshold
  }

  // Long press fires while still held, once
  if (btnStable == LOW && !longFired && now - btnPressStart >= LONG_PRESS_MS) {
    longFired = true;
    ev = BTN_LONG;
  }
  return ev;
}

// ---------- State transitions ----------
void beginState(PlayerState s, int8_t startFrame) {

  if (s == PS_STRIKE1 || s == PS_STRIKE2) SFX_SWORD();   // delete "|| s == PS_STRIKE2" for strike 1 only
  pState = s;
  actFrame = startFrame;
  actLastTime = millis();
  comboQueued = false;
  forceRedraw = true;
  faceDir = FACE_SIDE;
  swingHitRoja = false;
  swingHitNinja = false;
  swingHitNinjaArrow = false;
}

void handleSwordInput(BtnEvent ev) {
  if (ev == BTN_NONE) return;
  switch (pState) {
    case PS_NORMAL:
      if (ev == BTN_SHORT) beginState(PS_DRAWING, 0);
      break;
    case PS_ARMED:
      if (ev == BTN_SHORT)     beginState(PS_STRIKE1, 0);
      else if (ev == BTN_LONG) beginState(PS_SHEATHING, DRAW_FRAMES - 1);  // draw frames in reverse
      break;
    case PS_STRIKE1:
      if (ev == BTN_SHORT) comboQueued = true;   // successive press -> strike 2 when strike 1 ends
      break;
    default: break;   // ignore input mid draw/sheathe/strike 2
  }
}

void advanceAction() {
  if (pState == PS_NORMAL || pState == PS_ARMED) return;

  unsigned long frameMs = (pState == PS_STRIKE1 || pState == PS_STRIKE2)
                          ? STRIKE_ANIM_MS : SWORD_ANIM_MS;
  if (millis() - actLastTime < frameMs) return;
  actLastTime = millis();
  forceRedraw = true;

  switch (pState) {
    case PS_DRAWING:
      if (++actFrame >= DRAW_FRAMES) beginState(PS_ARMED, 0);
      break;
    case PS_SHEATHING:
      if (--actFrame < 0) beginState(PS_NORMAL, 0);
      break;
    case PS_STRIKE1:
      if (++actFrame >= STRIKE1_FRAMES) {
        if (comboQueued) beginState(PS_STRIKE2, 0);
        else             beginState(PS_ARMED, 0);
      }
      break;
    case PS_STRIKE2:
      if (++actFrame >= STRIKE2_FRAMES) beginState(PS_ARMED, 0);
      break;
    default: break;
  }
}

const uint16_t* actionFrame() {
  switch (pState) {
    case PS_DRAWING:
    case PS_SHEATHING: return facingLeft ? drawSwordFramesLeft[actFrame] : drawSwordFramesRight[actFrame];
    case PS_STRIKE1:   return facingLeft ? swordStrike1Left[actFrame]    : swordStrike1Right[actFrame];
    case PS_STRIKE2:   return facingLeft ? SwordStrike2Left[actFrame]    : SwordStrike2Right[actFrame];
    default:           return nullptr;
  }
}
void updateJan() {
  handleSwordInput(readButton());
  advanceAction();

  bool canMove = (pState == PS_NORMAL || pState == PS_ARMED);
  bool moving = false;

  if (canMove) {
    int rawX = analogRead(JOY_X_PIN);
    int rawY = analogRead(JOY_Y_PIN);

#if JOY_DEBUG
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint > 200) {
      lastPrint = millis();
      Serial.printf("joy X=%d Y=%d  xRun=%d yRun=%d\n", rawX, rawY, xRun, yRun);
    }
#endif

    bool xMove = (rawX > JOY_HIGH_THRESH || rawX < JOY_LOW_THRESH);
    bool yMove = (rawY > JOY_HIGH_THRESH || rawY < JOY_LOW_THRESH);

    // Each axis decides on its own, so one can never latch the other
    xRun = xRun ? (rawX > JOY_RUN_X_HIGH - JOY_RUN_HYST || rawX < JOY_RUN_X_LOW + JOY_RUN_HYST)
                : (rawX > JOY_RUN_X_HIGH || rawX < JOY_RUN_X_LOW);
    yRun = yRun ? (rawY > JOY_RUN_Y_HIGH - JOY_RUN_HYST || rawY < JOY_RUN_Y_LOW + JOY_RUN_HYST)
                : (rawY > JOY_RUN_Y_HIGH || rawY < JOY_RUN_Y_LOW);

    if (!xMove) xRun = false;     // an axis can only run while it is actually moving
    if (!yMove) yRun = false;
    joyRunning = xRun || yRun;

    float speedX = xRun ? RUN_SPEED : MOVE_SPEED;
    float speedY = yRun ? RUN_SPEED : MOVE_SPEED;
    int8_t dx = 0, dy = 0;

    if (rawX > JOY_HIGH_THRESH)     { georgeX += speedX; facingLeft = false; dx = 1; }
    else if (rawX < JOY_LOW_THRESH) { georgeX -= speedX; facingLeft = true;  dx = -1; }
    if (rawY > JOY_HIGH_THRESH)     { georgeY -= speedY; dy = -1; }
    else if (rawY < JOY_LOW_THRESH) { georgeY += speedY; dy = 1; }

    moving = (dx != 0 || dy != 0);

    if (pState == PS_NORMAL) {
      if (dx != 0)      faceDir = FACE_SIDE;
      else if (dy < 0)  faceDir = FACE_UP;
      else if (dy > 0)  faceDir = FACE_DOWN;
    }

    if (moving) {
      if (georgeX < 0) georgeX = 0;
      if (georgeX > WORLD_W - SPRITE_W) georgeX = WORLD_W - SPRITE_W;
      if (georgeY < 0) georgeY = 0;
      if (georgeY > 128 - SPRITE_H) georgeY = 128 - SPRITE_H;

      unsigned long animMs = joyRunning ? RUN_ANIM_FRAME_MS : ANIM_FRAME_MS;
      if (millis() - lastFrameTime >= animMs) {
        lastFrameTime = millis();
        animStep = (animStep + 1) % 6;
      }
    } else {
      animStep = 0;
    }
  } else {
    xRun = false;                 // no running during draw / strike / sheathe
    yRun = false;
    joyRunning = false;
  }

  janMoving = moving;
  camX = constrain((int)georgeX - SCROLL_TRIGGER, 0, MAX_CAM);
}

void drawJan() {
  bool moving = janMoving;
  bool canMove = (pState == PS_NORMAL || pState == PS_ARMED);

  if (janRedraw) {
    const uint16_t* frame;
    if (!canMove) {
      frame = actionFrame();
    } else if (pState == PS_ARMED) {
      const uint16_t** walkSet = facingLeft ? walkSwordFramesLeft : walkSwordFramesRight;
      const uint16_t*  idleSet = facingLeft ? drawSwordFramesLeft[DRAW_FRAMES - 1]
                                            : drawSwordFramesRight[DRAW_FRAMES - 1];
      frame = moving ? walkSet[animSequence[animStep]] : idleSet;
    } else if (faceDir == FACE_UP || faceDir == FACE_DOWN) {
      const uint16_t** set = (faceDir == FACE_UP) ? walkUpFrames : walkDownFrames;
      frame = set[moving ? (animStep & 1) : 0];
    } else {
      const uint16_t** walkSet = facingLeft ? walkFramesLeft : walkFramesRight;
      const uint16_t*  idleSet = facingLeft ? idleFrameLeft  : idleFrameRight;
      frame = moving ? walkSet[animSequence[animStep]] : idleSet;
    }

    bool blinkOff = (millis() < georgeInvulnUntil) && ((millis() / 80) & 1);
    if (!blinkOff) drawSpriteTransparent((int)georgeX - camX, (int)georgeY, frame, ACT_W, ACT_H, 0xF81F);
    prevX = (int)georgeX;
    prevY = (int)georgeY;
    forceRedraw = false;
  }
  wasMoving = moving;
}

void setup() {
  Serial.begin(115200);
  SPI.begin(D8, -1, D10, -1);   // SCK, MISO (none), MOSI, SS (none)
  audioBegin();
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.drawRGBBitmap(0, 0, Farmland1, 160, 128);
  pinMode(SWAP_BTN_PIN, INPUT_PULLUP);
}

void loop() {
  //playSfx(sword_4_raw, sword_4_raw_len);
  if (gameOver) {
    if (!gameOverShown) {
      gameOverShown = true;
      tft.setTextSize(2);
      tft.setTextColor(ST77XX_RED);
      tft.setCursor(26, 56);
      tft.print("GAME OVER");
    }
    if (millis() - gameOverAt > 1000 && digitalRead(SWAP_BTN_PIN) == LOW) ESP.restart();
    delay(50);
    return;
  }

  updateJan();
  updateRoja();
  updateNinjaArrow();
  updateNinja();
  checkSwordHit();
  updateBullets();
  updateArrows();

  bool scrolled = (camX != drawnCamX);
  if (scrolled) {
    drawnCamX = camX;
    sceneDirty = true;
    composeBackground();
    gBuf = frameBuf;
  }

  erasePhase();
  drawPhase();

  if (scrolled) {
    gBuf = nullptr;
    pushFrame();
  }

  sceneDirty = false;
  delay(30);
}
