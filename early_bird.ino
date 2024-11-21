#include <Arduino.h>
#include <avr/pgmspace.h>  // PROGMEM 사용

byte digits[10][7] = {
  { 0, 0, 0, 0, 0, 0, 1 },  // 0
  { 1, 0, 0, 1, 1, 1, 1 },  // 1
  { 0, 0, 1, 0, 0, 1, 0 },  // 2
  { 0, 0, 0, 0, 1, 1, 0 },  // 3
  { 1, 0, 0, 1, 1, 0, 0 },  // 4
  { 0, 1, 0, 0, 1, 0, 0 },  // 5
  { 0, 1, 0, 0, 0, 0, 0 },  // 6
  { 0, 0, 0, 1, 1, 1, 1 },  // 7
  { 0, 0, 0, 0, 0, 0, 0 },  // 8
  { 0, 0, 0, 1, 1, 0, 0 },  // 9
  // A,B,C,D,E,F,G
};
struct Melody {
  uint16_t pitch;
  uint16_t beat;

  Melody& operator=(uint16_t value) {
    pitch = value;
    beat = value;
    return *this;
  }
};

// 기본 음계
const uint16_t G = 392;   // G (솔)
const uint16_t A = 440;   // A (라)
const uint16_t B = 494;   // B (시)
const uint16_t C = 262;   // C (도)
const uint16_t D = 294;   // D (레)
const uint16_t E = 330;   // E (미)
const uint16_t F = 349;   // F (파)
const uint16_t Fs = 370;  // F♯ (파♯)
const uint16_t Fb = 330;  // F♭ (파♭)
const uint16_t Cs = 277;  // C♯ (도♯)
const uint16_t Cb = 247;  // C♭ (도♭)
const uint16_t Gs = 415;  // G♯ (솔♯)
const uint16_t Gb = 370;  // G♭ (솔♭)
const uint16_t Ds = 311;  // D♯ (레♯)
const uint16_t Db = 277;  // D♭ (레♭)
const uint16_t As = 466;  // A♯ (라♯)
const uint16_t Ab = 415;  // A♭ (라♭)
const uint16_t Bb = 466;  // B♭ (시♭)

// 높은 1단계
const uint16_t HC = 523;   // 높은 C (도)
const uint16_t HCs = 554;  // 높은 C♯ (도♯)
const uint16_t HCb = 494;  // 높은 C♭ (도♭)
const uint16_t HD = 587;   // 높은 D (레)
const uint16_t HDs = 622;  // 높은 D♯ (레♯)
const uint16_t HDb = 554;  // 높은 D♭ (레♭)
const uint16_t HE = 659;   // 높은 E (미)
const uint16_t HEb = 622;  // 높은 E♭ (미♭)
const uint16_t HF = 698;   // 높은 F (파)
const uint16_t HFs = 740;  // 높은 F♯ (파♯)
const uint16_t HFb = 659;  // 높은 F♭ (파♭)
const uint16_t HG = 784;   // 높은 G (솔)
const uint16_t HGs = 830;  // 높은 G♯ (솔♯)
const uint16_t HGb = 740;  // 높은 G♭ (솔♭)
const uint16_t HA = 880;   // 높은 A (라)
const uint16_t HAs = 932;  // 높은 A♯ (라♯)
const uint16_t HAb = 830;  // 높은 A♭ (라♭)
const uint16_t HB = 988;   // 높은 B (시)
const uint16_t HBb = 932;  // 높은 B♭ (시♭)

// 높은 2단계
const uint16_t HHC = 1047;   // 두 단계 높은 C (도)
const uint16_t HHCs = 1109;  // 두 단계 높은 C♯ (도♯)
const uint16_t HHCb = 988;   // 두 단계 높은 C♭ (도♭)
const uint16_t HHD = 1175;   // 두 단계 높은 D (레)
const uint16_t HHDs = 1245;  // 두 단계 높은 D♯ (레♯)
const uint16_t HHDb = 1109;  // 두 단계 높은 D♭ (레♭)
const uint16_t HHE = 1319;   // 두 단계 높은 E (미)
const uint16_t HHEb = 1245;  // 두 단계 높은 E♭ (미♭)
const uint16_t HHF = 1397;   // 두 단계 높은 F (파)
const uint16_t HHFs = 1480;  // 두 단계 높은 F♯ (파♯)
const uint16_t HHFb = 1319;  // 두 단계 높은 F♭ (파♭)
const uint16_t HHG = 1568;   // 두 단계 높은 G (솔)
const uint16_t HHGs = 1661;  // 두 단계 높은 G♯ (솔♯)
const uint16_t HHGb = 1480;  // 두 단계 높은 G♭ (솔♭)
const uint16_t HHA = 1760;   // 두 단계 높은 A (라)
const uint16_t HHAs = 1865;  // 두 단계 높은 A♯ (라♯)
const uint16_t HHAb = 1661;  // 두 단계 높은 A♭ (라♭)
const uint16_t HHB = 1976;   // 두 단계 높은 B (시)
const uint16_t HHBb = 1865;  // 두 단계 높은 B♭ (시♭)

// 낮은 1단계
const uint16_t LC = 131;   // 낮은 C (도)
const uint16_t LCs = 139;  // 낮은 C♯ (도♯)
const uint16_t LCb = 123;  // 낮은 C♭ (도♭)
const uint16_t LD = 147;   // 낮은 D (레)
const uint16_t LDs = 156;  // 낮은 D♯ (레♯)
const uint16_t LDb = 139;  // 낮은 D♭ (레♭)
const uint16_t LE = 165;   // 낮은 E (미)
const uint16_t LEb = 156;  // 낮은 E♭ (미♭)
const uint16_t LF = 175;   // 낮은 F (파)
const uint16_t LFs = 185;  // 낮은 F♯ (파♯)
const uint16_t LFb = 165;  // 낮은 F♭ (파♭)
const uint16_t LG = 196;   // 낮은 G (솔)
const uint16_t LGs = 208;  // 낮은 G♯ (솔♯)
const uint16_t LGb = 185;  // 낮은 G♭ (솔♭)
const uint16_t LA = 220;   // 낮은 A (라)
const uint16_t LAs = 233;  // 낮은 A♯ (라♯)
const uint16_t LAb = 208;  // 낮은 A♭ (라♭)
const uint16_t LB = 247;   // 낮은 B (시)
const uint16_t LBb = 233;  // 낮은 B♭ (시♭)

// 낮은 2단계
const uint16_t LLC = 65;    // 두 단계 낮은 C (도)
const uint16_t LLCs = 69;   // 두 단계 낮은 C♯ (도♯)
const uint16_t LLCb = 62;   // 두 단계 낮은 C♭ (도♭)
const uint16_t LLD = 73;    // 두 단계 낮은 D (레)
const uint16_t LLDs = 78;   // 두 단계 낮은 D♯ (레♯)
const uint16_t LLDb = 69;   // 두 단계 낮은 D♭ (레♭)
const uint16_t LLE = 82;    // 두 단계 낮은 E (미)
const uint16_t LLEb = 78;   // 두 단계 낮은 E♭ (미♭)
const uint16_t LLF = 87;    // 두 단계 낮은 F (파)
const uint16_t LLFs = 93;   // 두 단계 낮은 F♯ (파♯)
const uint16_t LLFb = 82;   // 두 단계 낮은 F♭ (파♭)
const uint16_t LLG = 98;    // 두 단계 낮은 G (솔)
const uint16_t LLGs = 104;  // 두 단계 낮은 G♯ (솔♯)
const uint16_t LLGb = 93;   // 두 단계 낮은 G♭ (솔♭)
const uint16_t LLA = 110;   // 두 단계 낮은 A (라)
const uint16_t LLAs = 117;  // 두 단계 낮은 A♯ (라♯)
const uint16_t LLAb = 104;  // 두 단계 낮은 A♭ (라♭)
const uint16_t LLB = 123;   // 두 단계 낮은 B (시)
const uint16_t LLBb = 117;  // 두 단계 낮은 B♭ (시♭)

const uint16_t Wh = 48;
const uint16_t Dh = 36;
const uint16_t Half = 24;
const uint16_t Dq = 18;
const uint16_t Qt = 12;
const uint16_t QE = 9;
const uint16_t Ei = 6;
const uint16_t Ei_3_of_one = 4;
const uint16_t Si = 3;

// zero - imagine dragon
const Melody melody0[] PROGMEM = {
  // 1,1
  { 0, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  // 1,2
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { C, Qt },
  // 1,3
  { 0, Ei },
  { 0, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  // 1,4
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Qt },
  { C, Qt },
  // 1,5
  { 0, Ei },
  { 0, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },

  // 2,1
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Qt },
  { C, Qt },
  // 2,2
  { F, Ei },
  { F, Ei },
  { C, Qt },
  { F, Ei },
  { F, Ei },
  { C, Qt },
  // 2,3
  { F, Ei },
  { F, Ei },
  { C, Ei },
  { C, Ei },
  { F, Ei },
  { F, Ei },
  { C, Ei },
  { F, Ei },
  // 2,4
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  // 2,5
  { D, Ei },
  { D, Ei },
  { D, Ei },
  { C, Qt },
  { C, Qt },
  { F, Ei },
  // 3,1
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  // 3,2
  { D, Ei },
  { D, Ei },
  { D, Ei },
  { C, Qt },
  { C, Qt },
  { F, Ei },
  // 3,3
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { E, Qt },
  { E, Ei },
  { E, Ei },
  // 3,4
  { D, Ei },
  { D, Ei },
  { D, Ei },
  { C, Qt },
  { C, Qt },
  { F, Ei },
  // 3,5
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { E, Qt },
  { E, Ei },
  { E, Ei },
  // 4,1
  { D, Ei },
  { D, Qt },
  { C, Qt },
  { C, Qt },
  { LB, Ei },
  // 4,2
  { LB, Ei },
  { LB, Ei },
  { LB, Ei },
  { LB, Ei },
  { D, Qt },
  { D, Ei },
  { D, Ei },
  // 4,3
  { F, Qt },
  { F, Ei },
  { B, Qt },
  { B, Qt },
  { LB, Ei },
  // 4,4
  { LB, Ei },
  { LB, Ei },
  { LB, Ei },
  { LB, Ei },
  { D, Qt },
  { D, Ei },
  { D, Ei },
  //4,5
  { D, Ei },
  { D, Ei },
  { D, Ei },
  { C, Ei },
  { D, Dq },
  { 0, Ei },
  // 5,1
  { F, Qt },
  { F, Ei },
  { B, Qt },
  { A, Qt },
  { F, Ei },
  // 5,2
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { E, Ei },
  { E, Ei },
  { E, Qt },
  //5,3
  { D, Qt },
  { D, Ei },
  { C, Ei },
  { C, Qt },
  { F, Ei },
  //5,4
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  // 4,5
  { D, Ei },
  { D, Ei },
  { D, Ei },
  { C, Ei },
  { D, Dq },
  { 0, Ei },

  // 6,1
  { A, Ei },
  { F, Qt },
  { A, Ei },
  { F, Qt },
  { A, Ei },
  { A, Ei },
  // 6,2
  { A, Ei },
  { A, Ei },
  { A, Ei },
  { A, Ei },
  { A, Ei },
  { A, Ei },
  { A, Ei },
  { A, Ei },
  // 6,3
  { A, Ei },
  { E, Qt },
  { A, Ei },
  { E, Qt },
  { E, Ei },
  { E, Ei },
  // 6, 4
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  //7,1
  { F, Ei },
  { D, Qt },
  { F, Ei },
  { D, Qt },
  { E, Ei },
  { E, Ei },
  //7,2
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  //7,3
  { F, Ei },
  { D, Qt },
  { F, Ei },
  { D, Dq },
  { F, Ei },
  //7,4
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { B, Qt },
  { A, Qt },
  // 8,1
  { A, Ei },
  { F, Qt },
  { A, Ei },
  { F, Qt },
  { A, Ei },
  { A, Ei },
  // 8,2
  { A, Ei },
  { A, Ei },
  { A, Ei },
  { A, Ei },
  { A, Ei },
  { A, Ei },
  { A, Ei },
  { A, Ei },
  // 8,3
  { A, Ei },
  { E, Qt },
  { A, Ei },
  { E, Qt },
  { E, Ei },
  { E, Ei },
  // 8,4
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  // 9,1
  { F, Ei },
  { D, Qt },
  { F, Ei },
  { D, Qt },
  { E, Ei },
  { E, Ei },
  //9,2
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  { E, Ei },
  //9,3
  { F, Ei },
  { D, Qt },
  { F, Ei },
  { D, Dq },
  { F, Ei },
  // 9,4
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { F, Ei },
  { B, Qt },
  { A, Qt },

};

// 전선을 간다 - 군가
const Melody melody1[] PROGMEM = {
  //1,3
  { E, Qt },
  { E, Dq },
  { E, Qt },
  { A, Qt },
  //1,4
  { G, Wh },
  //2,1
  { E, Dq },
  { F, Ei },
  { E, Dq },
  { D, Ei },
  { E, Qt },
  { HC, Qt },
  //2,2
  { B, Dh },
  { A, Dq },
  { B, Ei },
  //2,3
  { HC, Dh },
  { B, Ei },
  { HC, Ei },
  { G, Ei },
  //2,4
  { A, Dh },
  { A, Qt },
  //3,1
  { G, Dq },
  { G, Ei },
  { B, Qt },
  { G, Qt },
  //3,2
  { A, Wh },
  //3,3
  { LA, Qt },
  { LA, Qt },
  { C, Qt },
  { LB, Ei },
  { LA, Ei },
  //3,4
  { E, Dh },
  { E, Ei },
  { E, Qt },
  //4,1
  { G, Dh },
  { A, Qt },
  //4,2
  { E, Dh },
  { 0, Ei },
  //4,3
  { D, Qt },
  { D, Qt },
  { F, Qt },
  { E, Ei },
  { D, Ei },
  //4,4
  { E, Dh },
  { D, Ei },
  { C, Ei },
  // 5,1
  { LB, Dh },
  { E, Qt },
  //5,2
  { LA, Dh },
  { 0, Qt },
  //5,3
  { A, Qt },
  { A, Qt },
  { A, Half },
  //5,4
  { A, Ei },
  { G, Qt },
  { F, Ei },
  { E, Half },
  //6,1
  { D, Qt },
  { E, Qt },
  { F, Qt },
  { G, Qt },
  //6,2
  { E, Dh },
  { 0, Qt },
  //6,3
  { A, Qt },
  { A, Qt },
  { A, Half },
  //6,4
  { A, Ei },
  { G, Qt },
  { F, Ei },
  { E, Half },
  //7,1
  { E, Qt },
  { B, Qt },
  { B, Qt },
  { A, Qt },
  //7,2
  { B, Dq },
  { A, Qt },
  { B, Qt },
  //7,3
  { HC, Dh },
  { B, Ei_3_of_one },
  { B, Ei_3_of_one },
  { B, Ei_3_of_one },
  //7,4
  { G, Dh },
  { A, Qt },
  //8,1
  { G, Dq },
  { G, Ei },
  { A, Qt },
  { A, Qt },
  //8,2
  { E, Dh },
  { A, Ei },
  { B, Ei },
  //8,3
  { HC, Dh },
  { B, Ei_3_of_one },
  { B, Ei_3_of_one },
  { B, Ei_3_of_one },
  //8,4
  { G, Dh },
  { G, Qt },
  //9,1
  { G, Dq },
  { G, Ei },
  { B, Qt },
  { G, Qt },
  //9,2
  { A, Dh },
  { 0, Qt },
  //9,3
  { E, Qt },
  { E, Ei },
  { D, Ei },
  { E, Qt },
  { A, Qt },
  //9,4
  { G, Wh },
  //10,1
  { E, Ei },
  { F, Ei },
  { E, Ei },
  { D, Ei },
  { E, Qt },
  { HC, Qt },
  //10,2
  { B, Dh },
  { A, Ei },
  { B, Ei },
  //10,3
  { HC, Dh },
  { B, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { G, Ei_3_of_one },
  //10,4
  { A, Dh },
  { A, Qt },
  //11,1
  { A, Dh },
  { A, Qt },
  //11,2
  { E, Dh },
  { 0, Qt },
};
// 여우비 - 이선희
const Melody melody2[] PROGMEM = {
  //1,1
  { D, Dq },
  { A, Ei },
  { A, Ei },
  { A, Ei_3_of_one },
  { G, Ei_3_of_one },
  { Fb, Ei_3_of_one },
  //1,2
  { G, Qt },
  { E, Ei_3_of_one },
  { E, Qt },
  { D, Ei_3_of_one },
  { C, Ei_3_of_one },
  //1,3
  { D, Ei_3_of_one },
  { E, Ei_3_of_one },
  { Fb, Ei_3_of_one },
  { G, Qt },
  { Fb, Ei },
  { A, Ei },
  //1,4
  { A, Dq },
  { 0, Ei },
  { Fb, Ei },
  { G, Ei },
  //1,5
  { A, Qt },
  { A, Ei },
  { A, Ei },
  { G, Ei },
  { Fb, Ei },
  //1,6
  { E, Ei },
  { Fb, Ei },
  { G, Ei },
  { Fb, Dq },
  //2,1
  { Fb, Ei },
  { D, Ei },
  { E, Ei },
  { Fb, Ei },
  { G, Si },
  { Fb, Si },
  //2,2
  { Fb, Dq },
  { 0, Ei },
  { C, Ei },
  //2,3
  { D, Ei },
  { A, Si },
  { A, Si },
  { A, Ei_3_of_one },
  { G, Ei_3_of_one },
  { Fb, Ei_3_of_one },
  //2,4
  { HC, Qt },
  { G, Ei },
  { G, Qt },
  { Fb, Si },
  { E, Si },
  //3,5
  { D, Ei },
  { E, Ei },
  { Fb, Ei },
  { G, Qt },
  { HC, Si },
  { A, Si },
  //3,6
  { A, Dq },
  { 0, Ei },
  { Fb, Ei },
  { G, Ei },
  //4,1
  { HC, Ei },
  { B, Ei },
  { B, Ei },
  { A, Ei },
  { G, Ei },
  { F, Ei },
  //4,2
  { G, Qt },
  { HC, Si },
  { A, Si },
  { A, Qt },
  { A, Ei },
  //4,3
  { A, Ei },
  { G, Ei },
  { Fs, Si },
  { G, Si },
  { G, Qt },
  { 0, Si },
  { G, Si },
  //4,4
  { G, Ei },
  { F, Ei },
  { E, Ei },
  { F, Ei },
  { G, Ei },
  { F, Ei },
  //4,5
  { A, Qt },
  { A, Ei },
  { G, Ei },
  { A, Ei },
  { HC, Si },
  { G, Si },
  //4,6
  { G, Dq },
  { 0, Dq },
  //5,1
  { Fb, Dq },
  { 0, Dq },
  //5,2
  { 0, Ei },
  { Fb, Dq },
  { E, Ei },
  { Fb, Ei },
  { A, Ei },
  { F, Ei },
  //5,3
  { 0, Ei },
  { Fb, Dq },
  { E, Ei },
  { Fb, Ei },
  { A, Ei },
  { Fb, Ei },
  //5,4
  { 0, Ei },
  { Fb, Si },
  { E, Si },
  { Fb, Si },
  { G, Si },
  { A, Ei },
  { Fb, Si },
  { E, Si },
  { Fb, Si },
  { G, Si },
  //5,5
  { A, Ei },
  { Fb, Si },
  { E, Si },
  { Fb, Si },
  { G, Si },
  { A, Ei },
  { HC, Ei },
  { Fb, Ei },
  //5,6
  { 0, Ei },
  { Fb, Dq },
  { E, Ei },
  { Fb, Ei },
  { A, Ei },
  { Fb, Ei },
  //6,1
  { 0, Ei },
  { Fb, Dq },
  { E, Ei },
  { Fb, Ei },
  { HC, Ei },
  { A, Ei },
  //6,2
  { 0, Ei },
  { Fb, Si },
  { E, Si },
  { Fb, Si },
  { G, Si },
  { A, Ei },
  { Fb, Si },
  { E, Si },
  { Fb, Si },
  { G, Si },
  //6,3
  { A, Qt },
  { 0, Ei },
  { Fb, Ei },
  { G, Ei },
  { A, Ei },
  //6,4
  { A, Qt },
  { A, Si },
  { G, Si },
  { G, Ei },
  { Fb, Ei },
  { E, Ei },
  //6,5
  { G, Qt },
  { G, Si },
  { Fb, Si },
  { Fb, Qt },
  { 0, Si },
  { Fb, Si },
  //6,6
  { HC, Ei },
  { B, Ei },
  { B, Ei },
  { A, Ei },
  { G, Ei },
  { Fb, Ei },
  //7,1
  { G, Qt },
  { HC, Si },
  { A, Si },
  { A, Qt },
  { A, Ei },
  //7,2
  { A, Ei },
  { G, Ei },
  { Fs, Si },
  { G, Si },
  { G, Qt },
  { 0, Si },
  { A, Si },
  //7,3
  { G, Ei },
  { Fb, Ei },
  { E, Ei },
  { Fb, Ei },
  { G, Ei },
  { Fb, Ei },
  //7,4
  { A, Qt },
  { A, Si },
  { G, Si },
  { G, Ei },
  { Fb, Ei },
  { E, Ei },
  //7,5
  { G, Qt },
  { 0, Si },
  { Fb, Si },
  { Fb, Ei },
  { HC, Ei },
  { B, Ei },
  //7,6
  { A, Qt },
  { A, Si },
  { G, Si },
  { G, Ei },
  { Fb, Ei },
  { E, Ei },
  //8,1
  { G, Qt },
  { HC, Si },
  { A, Si },
  { A, Qt },
  { 0, Si },
  { Fb, Si },
  //8,2
  { HC, Ei },
  { B, Ei },
  { B, Ei },
  { A, Ei },
  { G, Ei },
  { Fb, Ei },
  //8,3
  { G, Qt },
  { HC, Si },
  { A, Si },
  { A, Qt },
  { A, Ei },
  //8,4
  { A, Ei },
  { G, Ei },
  { Fb, Si },
  { G, Si },
  { G, Qt },
  { 0, Si },
  { A, Si },
  //8,5
  { G, Ei },
  { Fb, Ei },
  { E, Ei },
  { Fb, Ei },
  { G, Ei },
  { Fb, Ei },
  //8,6
  { A, Qt },
  { A, Ei },
  { G, Ei },
  { A, Ei },
  { HC, Si },
  { G, Si },
  //9,1
  { G, Dq },
  { G, Qt },
  { 0, Ei },
  //9,2
  { D, Dq },
  { A, Si },
  { A, Si },
  { A, Ei },
  { G, Ei },
  { Fb, Ei },
  //9,3
  { HC, Qt },
  { G, Ei },
  { G, Qt },
  { Fb, Si },
  { E, Si },
  //9,4
  { D, Ei },
  { E, Ei },
  { Fb, Ei },
  { G, Qt },
  { HC, Si },
  { A, Si },
  //9,5
  { A, Dq },
  { 0, Ei },
  { Fb, Ei },
  { G, Ei },
  //9,6
  { A, Qt },
  { A, Ei },
  { A, Ei },
  { G, Ei },
  { Fb, Ei },
  //10,1
  { E, Ei },
  { Fb, Ei },
  { G, Ei },
  { 0, Si },
  { A, Si },
  //10,2
  { G, Ei },
  { Fb, Ei },
  { Fb, Si },
  { A, Si },
  { G, Ei },
  { Fb, Ei },
  { E, Si },
  { Fb, Si },
  //10,3
  { Fb, Dq },
  { 0, Dq },
  //10,4
  { 0, Ei },
  { Fb, Dq },
  { E, Ei },
  { Fb, Ei },
  { A, Ei },
  { Fb, Ei },
  //10,5
  { 0, Ei },
  { Fb, Dq },
  { E, Ei },
  { Fb, Ei },
  { A, Ei },
  { Fb, Ei },
  //10,6
  { 0, Ei },
  { Fb, Si },
  { E, Si },
  { Fb, Si },
  { G, Si },
  { A, Ei },
  { Fb, Si },
  { E, Si },
  { Fb, Si },
  { G, Si },
  //11,1
  { A, Ei },
  { Fb, Si },
  { E, Si },
  { Fb, Si },
  { G, Si },
  { A, Ei },
  { HC, Ei },
  { A, Ei },
  //11,2
  { 0, Ei },
  { Fb, Dq },
  { E, Ei },
  { Fb, Ei },
  { A, Ei },
  { Fb, Ei },
  //11,3
  { 0, Ei },
  { Fb, Dq },
  { E, Ei },
  { Fb, Ei },
  { HC, Ei },
  { A, Ei },
  //11,4
  { 0, Ei },
  { Fb, Si },
  { E, Si },
  { Fb, Si },
  { G, Ei },
  { Fb, Si },
  { E, Si },
  { Fb, Si },
  { G, Si },
  //11,5
  { A, Ei },
  { Fb, Si },
  { E, Si },
  { Fb, Si },
  { G, Si },
  { A, Ei },
  { HC, Ei },
  { A, Ei },
};




const Melody melody3[] PROGMEM = {
  //1,1
  { HDs, Si },
  { HE, Si },
  //1,2
  { HFs, Dq },
  { HE, Ei },
  { HE, Ei },
  { HDs, Ei },
  { HDs, Dq },
  { HCs, Ei },
  { HCs, Ei },
  { B, Ei },
  //1,3
  { HCs, Ei },
  { HDs, Si },
  { B, Si },
  { B, Ei },
  { Fs, Ei },
  { HCs, Ei },
  { HDs, Si },
  { B, Si },
  { B, Ei },
  { HDs, Si },
  { HE, Si },
  //1,4
  { HFs, Dq },
  { HE, Ei },
  { HE, Ei },
  { HDs, Ei },
  { HDs, Dq },
  { HCs, Ei },
  { HCs, Ei },
  { B, Ei },
  //1,5
  { HCs, Ei },
  { HDs, Si },
  { B, Si },
  { B, Ei },
  { Fs, Ei },
  { HCs, Ei },
  { HDs, Si },
  { B, Si },
  { B, Ei },
  { HDs, Si },
  { HE, Si },
  // 2,1
  { HFs, Dq },
  { HE, Ei },
  { HE, Ei },
  { HDs, Ei },
  { HE, Ei },
  { HFs, Si },
  { HGs, Si },
  { HHA, Si },
  { HHA, Si },
  { HHCs, Si },
  { HHDs, Si },
  { HHFs, Si },
  //2,2
  { HHFs, Ei },
  { HHG, Si },
  { HHB, Si },
  { HHB, Si },
  { HHA, Ei },
  { HHB, Si },
  { HHB, Si },
  { HHA, Si },
  { HG, Si },
  { HFs, Si },
  { HDs, Si },
  { HCs, Si },
  { B, Si },
  { A, Si },
  //2,3
  { HDs, Dq },
  { HE, Ei },
  { HE, Ei },
  { HFs, Ei },
  { HDs, Dq },
  { HCs, Ei },
  { HCs, Ei },
  { B, Si },
  //2,4
  { HCs, Ei },
  { HDs, Si },
  { B, Si },
  { B, Ei },
  { Fs, Ei },
  { HCs, Ei },
  { HDs, Si },
  { B, Si },
  { B, Ei },
  { HDs, Si },
  { HE, Si },
};

// 탄지로의 노래 - 귀멸의 칼날
const Melody melody4[] PROGMEM = {
  //1,1
  { HC, Qt },
  { HE, Qt },
  { B, Half },
  //1,2
  { A, Wh },
  //1,3
  { HC, Qt },
  { HE, Qt },
  { B, Half },
  //1,4
  { A, Wh },
  //1,5
  { HA, Dh },
  { 0, Ei },
  { HC, Si },
  { B, Si },
  //2,1
  { HC, Qt },
  { HE, Qt },
  { B, Dq },
  { A, Si },
  { G, Si },
  //2,2
  { A, Qt },
  { HC, Qt },
  { HE, Dq },
  { HF, Si },
  { HE, Si },
  //2,3
  { HF, Qt },
  { HA, Qt },
  { HE, Dq },
  { HD, Si },
  { HC, Si },
  //2,4
  { HD, Qt },
  { A, Qt },
  { HE, Dq },
  { HC, Si },
  { A, Si },
  //3,1
  { HC, Qt },
  { HE, Qt },
  { B, Dq },
  { A, Si },
  { G, Si },
  //3,2
  { A, Qt },
  { HC, Qt },
  { HE, Dq },
  { HF, Si },
  { HE, Si },
  //3,3
  { HF, Qt },
  { HA, Qt },
  { HE, Dq },
  { HD, Si },
  { HC, Si },
  //3,4
  { HD, Qt },
  { A, Qt },
  { HE, Half },
  //4,1
  { HC, 15 },
  { A, 15 },
  { HC, Qt },
  { HE, Qt },
  { A, Half },
  //4,2
  { A, Wh },
  //4,3
  { HC, 20 },
  { A, 20 },
  { HC, Qt },
  { HE, Qt },
  { HG, Half },
  //4,4
  { HA, Wh },
  //5,1
  { C, Qt },
  { E, Qt },
  { LB, Half },
  //5,2
  { LB, Half },
  { LA, Qt },
  { C, Ei },
  { D, Ei },
  //5,3
  { E, Half },
  { C, Half },
  //5,4
  { LB, Half },
  { E, Qt },
  { C, Ei },
  { LB, Ei },
  //6,1
  { C, Qt },
  { E, Qt },
  { LB, Half },
  //6,2
  { E, Qt },
  { LA, Qt },
  { C, Qt },
  { D, Qt },
  //6,3
  { E, Half },
  { C, Half },
  //6,4
  { LB, Half },
  { LB, Half },
  //7,1
  { C, Dq },
  { LA, Qt },
  { LA, Qt },
  { C, Ei },
  { D, Ei },
  //7,2
  { E, QE },
  { C, Si },
  { C, Ei },
  { C, Ei },
  { C, Si },
  { LA, QE },
  { LA, Qt },
  //7,3
  { LLA, 10 },
  { LLB, 10 },
  { LD, Wh },
  //7,4
  { HG, Dh },
  { 0, Ei },
};
// Dinosour - 악동 뮤지션
const Melody melody5[] PROGMEM = {
  //1,1
  { 0, Dq },
  { Fb, Ei },
  { G, Ei },
  //1,2
  { A, Ei },
  { G, Ei },
  { Fb, Ei },
  { D, Ei },
  { 0, Half },
  //1,3
  { 0, Half },
  { A, Ei },
  { G, Ei },
  { Fb, Ei },
  { D, Ei },
  //1,4
  { A, Ei },
  { HC, Ei },
  { A, Ei },
  { HC, Ei },
  { A, Qt },
  { 0, Qt },
  //1,5
  { 0, Qt },
  { 0, Ei },
  { Fb, Ei },
  { Fb, Ei },
  { G, Ei },
  //2,1
  { A, Ei },
  { G, Ei },
  { Fb, Ei },
  { D, Ei },
  { 0, Half },
  //2,2
  { 0, Half },
  { A, Ei },
  { G, Ei },
  { Fb, Ei },
  { D, Ei },
  //2,3
  { A, Ei },
  { HC, Ei },
  { A, Ei },
  { HC, Ei },
  { A, Qt },
  { 0, Qt },
  //2,4
  { 0, Qt },
  { 0, Ei },
  { Fb, Ei },
  { HC, Ei },
  { B, Ei },
  //3,1
  { A, Ei },
  { G, Ei },
  { Fb, Ei },
  { 0, Ei },
  { Fb, Si },
  { G, Ei },
  { G, Si },
  //3,2
  { G, Ei },
  { G, Ei },
  { G, Ei },
  { A, Ei },
  { C, Ei },
  { 0, Ei },
  { 0, Qt },
  //3,3
  { Fb, Si },
  { G, Ei },
  { G, Si },
  { G, Ei },
  { G, Ei },
  { G, Ei },
  { G, Ei },
  //3,4
  { G, Ei },
  { G, Si },
  { G, Si },
  { G, Ei },
  { A, Ei },
  { C, Qt },
  { 0, Qt },
  //4,1
  { C, QE },
  { D, Si },
  { D, Ei },
  { Fb, Ei },
  { Fb, Si },
  { G, QE },
  { A, Ei },
  { G, Ei },
  //4,2
  { G, Qt },
  { 0, Qt },
  { 0, Qt },
  { 0, Ei },
  { C, Ei },
  //4,3
  { C, Ei },
  { C, Si },
  { D, Si },
  { D, Si },
  { D, Si },
  { Fb, Si },
  { G, QE },
  { A, Ei },
  { G, Ei },
  //4,4
  { G, Qt },
  { 0, Qt },
  { 0, Half },
  //5,1
  { Fb, Ei },
  { G, Ei },
  { A, Ei },
  { Fb, Ei },
  { Fb, Qt },
  { Bb, Ei },
  { A, Ei },
  //5,2
  { Fb, Ei },
  { G, Ei },
  { G, Qt },
  { Fb, Qt },
  { Bb, Ei },
  { A, Ei },
  //5,3
  { Fb, Qt },
  { Bb, Ei },
  { A, Ei },
  { Fb, Qt },
  { Bb, Ei },
  { A, Ei },
  //5,4
  { Fb, Ei },
  { G, Ei },
  { G, Ei },
  { Fb, Ei },
  { Fb, Qt },
  { Fb, Qt },
  //6,1
  { Fb, Ei },
  { HC, Si },
  { HC, Si },
  { HC, Ei },
  { HC, Ei },
  { 0, Qt },
  { 0, Ei },
  { C, Ei },
  //6,2
  { Fb, Ei },
  { HC, Si },
  { HC, Si },
  { HC, Ei },
  { HC, Ei },
  { 0, Qt },
  { 0, Ei },
  { C, Ei },
  //6,3
  { Fb, Ei },
  { HC, Si },
  { HC, Si },
  { HC, Ei },
  { HC, Ei },
  { 0, Half },
  //6,4
  { 0, Half },
  { G, Ei },
  { Fb, Ei },
  { Fb, Qt },
  //7,1
  { Fb, QE },
  { G, Si },
  { G, Qt },
  { 0, Ei },
  { Fb, Ei },
  { Bb, Ei },
  { A, Ei },
  //7,2
  { G, Qt },
  { 0, Ei },
  { C, Ei },
  { HC, Ei },
  { A, Ei },
  { A, Ei },
  { G, Ei },
  //7,3
  { G, Qt },
  { 0, Ei },
  { Fb, Ei },
  { HC, Ei },
  { A, Ei },
  { A, Ei },
  { G, Ei },
  //7,4
  { G, Qt },
  { 0, Qt },
  { G, Ei },
  { Fb, Ei },
  { Fb, Qt },
  //8,1
  { Fb, QE },
  { G, Si },
  { G, Qt },
  { 0, Ei },
  { Fb, Ei },
  { Bb, Ei },
  { A, Ei },
  //8,2
  { G, Qt },
  { 0, Ei },
  { C, Qt },
  { HC, Ei },
  { A, Ei },
  { A, Ei },
  { G, Ei },
  //8,3
  { G, Qt },
  { 0, Ei },
  { Fb, Ei },
  { HC, Ei },
  { A, Ei },
  { A, Ei },
  { G, Ei },
  //8,4
  { G, Qt },
  { 0, Qt },
  { 0, Half },
};

// Sparkle - 너의 이름은
const Melody melody6[] PROGMEM = {
  //1,1
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  //1,2
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  //1,3
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  //1,4
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  // 2,1
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  // 2,2
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  // 2,3
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  //2,4
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  //3,1
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  //3,2
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  //3,3
  { 0, Qt },
  { HE, Ei_3_of_one },
  { HE, Ei_3_of_one },
  { HE, Ei_3_of_one },
  { HE, Ei },
  { HD, Ei },
  { HD, Ei },
  { HC, Ei },
  //3,4
  { HC, Wh },
  //4,1
  { HE, Ei_3_of_one },
  { HE, Ei_3_of_one },
  { HE, Ei_3_of_one },
  { HE, Ei },
  { HD, Ei },
  { HD, Ei },
  { HC, Ei },
  //4,2
  { HE, Qt },
  { HE, Ei_3_of_one },
  { HE, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HD, Qt },
  { HC, Qt },
  //4,3
  { 0, Qt },
  { HE, Ei_3_of_one },
  { HE, Ei_3_of_one },
  { HE, Ei_3_of_one },
  { HE, Ei },
  { HD, Ei },
  { HD, Ei },
  { HC, Ei },
  //4,4
  { HC, Wh },
  //5,1
  { 0, Qt },
  { HE, Ei_3_of_one },
  { HE, Ei_3_of_one },
  { HE, Ei_3_of_one },
  { HE, Ei },
  { HD, Ei },
  { HD, Ei },
  { HC, Ei },
  //5,2
  { HC, Wh },
  //5,3
  { 0, Qt },
  { HE, Ei_3_of_one },
  { HE, Ei_3_of_one },
  { HE, Ei_3_of_one },
  { HE, Ei },
  { HF, Ei },
  { HD, Ei },
  { HC, Ei },
  //5,4
  { HC, Wh },
  //6,1
  { 0, Qt },
  { HE, Ei_3_of_one },
  { HE, Ei_3_of_one },
  { HE, Ei_3_of_one },
  { HE, Ei },
  { HD, Ei },
  { HD, Ei },
  { HC, Ei },
  //6,2
  { HE, Qt },
  { HE, Ei },
  { HG, Ei },
  { HD, Qt },
  { HC, Qt },
  //6,3
  { 0, Qt },
  { HE, Ei_3_of_one },
  { HE, Ei_3_of_one },
  { HE, Ei_3_of_one },
  { HE, Ei },
  { HD, Ei },
  { HD, Ei },
  { HC, Ei },
  //6,4
  { HC, Qt },
  { HC, Qt },
  { HC, Half },
  // 7,1
  { 0, Qt },
  { HD, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HD, Ei },
  { HE, Ei },
  { HD, Ei },
  { HC, Ei },
  //7,2
  { 0, Wh },
  //7,3
  { HC, Qt },
  { HHC, Qt },
  { HHD, Qt / 3 },
  { HHC, Qt / 3 },
  { HG, Qt / 3 },
  //7,4
  { HF, Qt },
  { HF, Qt },
  { HF, Ei },
  { HF, Ei },
  { HC, Qt },
  //8,1
  { HE, Ei },
  { HHC, Ei },
  { HE, Ei },
  { HA, Ei },
  { HA, Ei },
  { HA, Ei },
  { HG, Qt },
  //8,2
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HD, Ei_3_of_one },
  { HG, Ei_3_of_one },
  //8,3
  { HC, Qt },
  { HHC, Qt },
  { HHD, Qt / 3 },
  { HHC, Qt / 3 },
  { HG, Qt / 3 },
  // 8,4
  { HF, Qt },
  { HF, Qt },
  { HF, Ei_3_of_one },
  { HC, Ei_3_of_one },
  { HG, Ei_3_of_one },
  { HF, Qt },
  // 9,1
  { HHC, Qt / 3 },
  { HHE, Qt / 3 },
  { HG, Qt / 3 },
  { HF, Qt },
  { HG, Qt },
  //9,2
  { HHC, Qt },
  { HHC, Qt / 3 },
  { HHC, Qt / 3 },
  { HHD, Qt / 3 },
  { HHG, Half },
  //9,3
  { 0, Qt },
  { HE, Qt / 3 },
  { HD, Qt / 3 },
  { HD, Qt / 3 },
  { HD, Ei },
  { HC, Ei },
  { HD, Ei },
  { HE, Ei },
  //9,4
  { HC, Wh },
  //10,1
  { 0, Qt },
  { HE, Qt / 3 },
  { HE, Qt / 3 },
  { HE, Qt / 3 },
  { HE, Ei },
  { HD, Ei },
  { HD, Ei },
  { HC, Ei },
  //10,2
  { HE, Qt },
  { HE, Ei },
  { HG, Ei },
  { HD, Qt },
  { HC, Qt },
  //10,3
  { 0, Qt },
  { HE, Qt / 3 },
  { HE, Qt / 3 },
  { HE, Qt / 3 },
  { HE, Ei },
  { HF, Ei },
  { HE, Ei },
  { HD, Ei },
  //10,4
  { HC, Wh },

  //11,1
  { 0, Qt },
  { HD, Qt / 3 },
  { HD, Qt / 3 },
  { HD, Qt / 3 },
  { HD, Ei },
  { HE, Ei },
  { HD, Ei },
  { HC, Ei },
  //11,2
  { HC, Wh },
  //11,3
  { 0, Qt },
  { HE, Qt / 3 },
  { HE, Qt / 3 },
  { HE, Qt / 3 },
  { HE, Ei },
  { HF, Ei },
  { HE, Ei },
  { HD, Ei },
  //11,4
  { HC, Wh },
  //12,1
  { 0, Qt },
  { HE, Qt / 3 },
  { HE, Qt / 3 },
  { HE, Qt / 3 },
  { HE, Ei },
  { HD, Ei },
  { HD, Ei },
  { HC, Ei },
  //12,2
  { HE, Qt },
  { HE, Ei },
  { HG, Ei },
  { HD, Qt },
  { HC, Qt },
  //12,3
  { 0, Qt },
  { HE, Qt / 3 },
  { HE, Qt / 3 },
  { HE, Qt / 3 },
  { HE, Ei },
  { HD, Ei },
  { HC, Ei },
  { HD, Ei },
  //12,4
  { HC, Wh },
  //13,1
  { 0, Qt },
  { HD, Qt },
  { HD, Ei },
  { HE, Ei },
  { HD, Ei },
  { HC, Ei },
  //13,2
  { 0, Wh },
  //13,3
  { HG, Qt / 3 },
  { HG, Qt / 3 },
  { HG, Qt / 3 },
  { HG, Ei },
  { HG, Ei },
  { HG, Ei },
  { HF, Ei },
  { HE, Ei },
  { HD, Ei },
  //13,4
  { HC, Ei },
  { HC, Ei },
  { HC, Ei },
  { HD, Ei },
  { HE, Ei },
  { HD, Ei },
  { HD, Qt },
  //14,1
  { HG, Qt / 3 },
  { HG, Qt / 3 },
  { HG, Qt / 3 },
  { HG, Ei },
  { HG, Ei },
  { HG, Ei },
  { HF, Ei },
  { HE, Ei },
  { HD, Ei },
  //14,2
  { HE, Qt },
  { HE, Qt / 3 },
  { HD, Qt / 3 },
  { HC, Qt / 3 },
  { HD, Half },
  //14,3
  { HC, Ei },
  { HD, Ei },
  { HE, Ei },
  { HF, Ei },
  { HF, Ei },
  { HE, Ei },
  { HD, Ei },
  { HC, Ei },
  //14,4
  { HC, Ei },
  { HE, Ei },
  { HC, Ei },
  { HD, Ei },
  { HD, Half },
  //15,1
  { HC, Ei },
  { HD, Ei },
  { HE, Ei },
  { HF, Ei },
  { HF, Ei },
  { HE, Ei },
  { HF, Ei },
  { HG, Ei },
  //15,2
  { HG, Ei },
  { HF, Ei },
  { HE, Ei },
  { HE, Ei },
  { HE, Ei },
  { HD, Ei },
  { HC, Ei },
  { HC, Ei },
  //15,3
  { HC, Wh },
  //15,4
  { HF, Dh },
  { HG, Qt },
  //16,1
  { HG, Wh },
  //16,2
  { A, Qt / 3 },
  { HD, Qt / 3 },
  { HG, Qt / 3 },
  { A, Qt / 3 },
  { HD, Qt / 3 },
  { HG, Qt / 3 },
  { HG, Qt },
  { HC, Qt },
  //16,3
  { HC, Qt },
  { HC, Ei },
  { HG, Ei },
  { HG, Qt },
  { HC, Ei },
  { HC, Ei },
  //16,4
  { HC, Qt },
  { HC, Ei },
  { HA, Ei },
  { HG, Qt },
  { HG, Qt / 3 },
  { HC, Qt / 3 },
  { HC, Qt / 3 },
  //17,1
  { HD, Qt },
  { HD, Qt / 3 },
  { HD, Qt / 3 },
  { HE, Qt / 3 },
  { HF, Qt },
  { HF, Qt / 3 },
  { HE, Qt / 3 },
  { HD, Qt / 3 },
  //17,2
  { HC, Qt },
  { HC, Ei },
  { HD, Ei },
  { HC, Qt },
  { HC, Ei },
  { G, Ei },
  //17,3
  { HC, Qt },
  { HC, Ei },
  { HC, Ei },
  { HC, Ei },
  { G, Ei },
  { G, Qt },
  //17,4
  { HC, Ei },
  { HC, Qt },
  { HD, Ei },
  { HC, Qt },
  { HC, Ei },
  { G, Ei },
  //18,1
  { HD, Qt },
  { HD, Qt / 3 },
  { HD, Qt / 3 },
  { HD, Qt / 3 },
  { HF, Qt },
  { HF, Qt / 3 },
  { HE, Qt / 3 },
  { HD, Qt / 3 },
  //18,2
  { HC, Qt },
  { HC, Qt / 3 },
  { B, Qt / 3 },
  { HC, Qt / 3 },
  { HD, Qt },
  { HD, Ei },
  { G, Ei },
  //18,3
  { HC, Qt },
  { HC, Ei },
  { HG, Ei },
  { HG, Ei },
  { HC, Ei },
  { HC, Ei },
  { HC, Ei },
  { HC, Ei },
  //18,4
  { HC, Qt },
  { HC, Ei },
  { HA, Ei },
  { HG, Qt },
  { HG, Ei },
  { HC, Ei },
  //19,1
  { HD, Qt / 3 },
  { HC, Qt / 3 },
  { HD, Qt / 3 },
  { HD, Ei },
  { HE, Ei },
  { HF, Qt },
  { HF, Qt / 3 },
  { HE, Qt / 3 },
  { HD, Qt / 3 },
  //19,2
  { HC, Qt },
  { HC, Ei },
  { HC, Ei },
  { HC, Half },
  //19,3
  { HC, Qt },
  { HC, Ei },
  { HC, Ei },
  { HC, Ei },
  { G, Ei },
  { G, Qt },
  //19,4
  { HC, Qt },
  { HC, Qt / 3 },
  { HC, Qt / 3 },
  { HD, Qt / 3 },
  { HC, Qt },
  { HG, Qt },
  //20,1
  { HC, Qt },
  { HC, Ei },
  { A, Ei },
  { HC, Qt },
  { HG, Qt },
  //20,2
  { HC, Qt },
  { HC, Ei },
  { A, Ei },
  { HC, Qt },
  { HC, Ei },
  { G, Ei },
  //20,3
  { HE, Dh },
  { HE, Qt / 3 },
  { HD, Qt / 3 },
  { HC, Qt / 3 },
  //20,4
  { HD, Dh },
  { HD, Ei },
  { HC, Ei },
};
const Melody melody7[] PROGMEM = {
  //1,1
  { HB, QE },
  { HA, Si },
  { HA, QE },
  { HHF, Si },
  { HB, Qt },
  { HA, Ei },
  { HG, Ei },
  //1,2
  { HFs, QE },
  { HG, Si },
  { HG, Si },
  { HFs, QE },
  { HD, Qt },
  { HD, Si },
  { HD, Si },
  { HG, Si },
  { HA, Si },
  //1,3
  { HB, QE },
  { HA, Si },
  { HA, Si },
  { HHD, QE },
  { HHB, Qt },
  { HHFs, Ei },
  { HHG, Ei },
  //1,4
  { HHFs, QE },
  { HHD, Si },
  { HHD, Ei },
  { HB, Ei },
  { HA, Qt },
  { HG, Qt },
  //2,1
  { HB, QE },
  { HA, Si },
  { HA, Si },
  { HHD, QE },
  { HB, Qt },
  { HA, Ei },
  { HG, Ei },
  //2,2
  { HFs, QE },
  { HG, Si },
  { HG, Si },
  { HA, QE },
  { HD, Dq },
  { HD, Ei },
  //2,3
  { HD, Qt },
  { HD, Ei },
  { HB, Ei },
  { HB, Half },
  //2,4
  { HG, Half },
  { HFs, Half },
  //3,1
  { LB, QE },
  { LFs, Si },
  { LG, Si },
  { D, Si },
  { LFs, Ei },
  { LFs, QE },
  { LFs, Si },
  { LG, Si },
  { D, Si },
  { LG, Si },
  { LFs, Si },
  //3,2
  { LFs, QE },
  { LFs, Si },
  { LG, Si },
  { D, Si },
  { LFs, Ei },
  { LFs, Half },
  //3,3
  { B, QE },
  { A, Si },
  { A, QE },
  { HD, Si },
  { B, QE },
  { A, Si },
  { A, Si },
  { HD, QE },
  //4,1
  { A, QE },
  { G, Si },
  { G, Ei },
  { Fs, Ei },
  { D, Qt },
  { LB, Qt },
  //4,2
  { B, QE },
  { A, Si },
  { A, Si },
  { HD, QE },
  { A, Qt },
  { HFs, Ei },
  { HG, Ei },
  //4,3
  { HFs, QE },
  { HD, Si },
  { HD, Ei },
  { D, Si },
  { B, Si },
  { B, Si },
  { D, QE },
  { D, Ei },
  { D, Ei },
  //5,1
  { B, QE },
  { A, Si },
  { A, Si },
  { HD, QE },
  { B, QE },
  { A, Si },
  { A, Si },
  { HD, QE },
  //5,2
  { Fs, QE },
  { G, Si },
  { G, Ei },
  { F, Ei },
  { D, Qt },
  { LG, Ei },
  { D, Ei },
  //5,3
  { E, QE },
  { B, Si },
  { D, Ei },
  { C, Ei },
  { Ds, Si },
  { A, Ei },
  { B, Si },
  //6,1
  { Fs, Qt },
  { D, QE },
  { E, Si },
  { Fs, Half },
  { E, Ei },
  { B, Si },
  { B, Si },
  { B, Qt },
  { E, Ei },
  { B, Si },
  { Fs, Si },
  { Fs, Si },
  { D, Si },
  { D, Ei },
  { HD, QE },
  { A, Si },
  { A, Si },
  { B, Ei },
  { A, Si },
  { A, Ei },
  { E, Si },
  { G, Si },
  { G, Si },
  { Fs, Si },
  { A, Si },
  { Fs, Si },
  //7,1
  { E, QE },
  { B, Si },
  { B, Si },
  { C, Si },
  { B, Ei },
  { Fs, QE },
  { HD, Si },
  { HD, Si },
  { HC, QE },
  //7,2
  { D, Qt },
  { LA, Si },
  { LB, Si },
  { D, Si },
  { G, Si },
  { B, Dq },
  { D, Ei },
  //7,3
  { E, Ei },
  { C, Si },
  { E, Si },
  { D, Si },
  { E, Si },
  { B, Ei },
  { Fs, Ei },
  { D, Si },
  { Fs, Si },
  { Fs, Si },
  { D, Si },
  { Fs, Ei },
  //8,1
  { B, Qt },
  { HFs, Ei },
  { HG, Ei },
  { HFs, QE },
  { HD, Si },
  { HD, Si },
  { B, QE },
  //8,2
  { E, Qt },
  { E, Ei },
  { G, Ei },
  { G, QE },
  { A, Si },
  { A, Ei },
  { B, Ei },
  //8,3
  { D, Half },
  { F, Qt },
  { HHB, Qt },
  //9,1
  { E, Si },
  { HC, Ei },
  { B, Si },
  { B, Si },
  { A, QE },
  { HD, Qt },
  { HC, Ei },
  { B, Ei },
  //9,2
  { A, Ei },
  { G, Si },
  { A, Si },
  { A, Si },
  { B, Ei },
  { D, Si },
  { D, Qt },
  { D, Si },
  { D, Si },
  { G, Si },
  { HD, Si },
  //9,3
  { HC, QE },
  { E, Si },
  { E, Si },
  { B, QE },
  { A, Qt },
  { HFs, Qt },
  //10,1
  { HD, QE },
  { E, Si },
  { B, Qt },

};
const Melody melody8[] PROGMEM = {
  //1,1
  { B, Qt },
  { D, Qt },
  { B, Qt },
  { D, Qt },
  //1,2
  { Fs, Qt },
  { Fs, Qt },
  { Fs, Half },
  //1,3
  { G, Half },
  { E, Half },
  //1,4
  { G, Half },
  { 0, Qt },
  { A, QE },
  { A, Si },
  //2,1
  { B, Half },
  { 0, Ei },
  { B, Si },
  { B, Si },
  { B, Si },
  { HC, Si },
  //2,2
  { HC, Si },
  { B, QE },
  { B, Ei },
  { HC, Ei },
  { HC, Si },
  { B, QE },
  { 0, Ei },
  { A, Ei },
  //2,3
  { G, Qt },
  { G, Ei },
  { G, Si },
  { A, Si },
  { A, Ei },
  { G, Si },
  { A, Si },
  { A, QE },
  { G, Si },
  //2,4
  { HC, QE },
  { HC, Si },
  { HC, Si },
  { B, QE },
  { 0, QE },
  { G, Si },
  { G, Ei },
  { A, Si },
  { B, Si },
  //3,1
  { B, Half },
  { 0, Ei },
  { B, Ei },
  { B, Si },
  { B, Si },
  { B, Si },
  { B, Si },
  //3,2
  { B, Si },
  { A, QE },
  { A, Qt },
  { 0, Ei },
  { B, Ei },
  { B, Ei },
  { B, Si },
  { A, Si },
  //3,3
  { A, Si },
  { G, QE },
  { G, Qt },
  { 0, Half },
  //3,4
  { 0, Half },
  { 0, Qt },
  { G, Ei },
  { A, Ei },
  //4,1
  { B, Si },
  { B, QE },
  { B, Qt },
  { 0, Ei },
  { B, Ei },
  { B, Ei },
  { B, Si },
  { HC, Si },
  //4,2
  { B, Qt },
  { 0, Ei },
  { HC, Ei },
  { HC, Ei },
  { B, Si },
  { A, Si },
  { A, Ei },
  { A, Si },
  { A, Si },
  //4,3
  { B, Si },
  { G, QE },
  { 0, Qt },
  { HC, QE },
  { B, Si },
  { B, Ei },
  { A, Si },
  { A, Si },
  //4,4
  { A, Ei },
  { B, Si },
  { G, Si },
  { G, Qt },
  { 0, Qt },
  { G, Ei },
  { A, Si },
  { B, Si },
  //5,1
  { HD, Ei },
  { HD, Si },
  { HD, Si },
  { HD, Ei },
  { B, Si },
  { HD, Si },
  { HD, Ei },
  { HD, Si },
  { HD, Si },
  { HD, Si },
  { HDs, Si },
  { HD, Ei },
  //5,2
  { HD, Qt },
  { 0, Ei },
  { HDs, Ei },
  { HDs, Si },
  { B, QE },
  { B, Ei_3_of_one },
  { B, Ei_3_of_one },
  { A, Ei_3_of_one },
  //5,3
  { G, Qt },
  { 0, Qt },
  { 0, Half },
  //5,4
  { 0, Half },
  { 0, Qt },
  { G, Ei },
  { A, Si },
  { B, Si },
  //6,1
  { B, Half },
  { 0, Qt },
  { B, Ei },
  { B, Si },
  { B, Si },
  //6,2
  { B, Si },
  { A, QE },
  { A, Qt },
  { 0, Ei },
  { B, Ei },
  { B, Si },
  { B, QE },
  //6,3
  { B, Ei },
  { A, Si },
  { G, Si },
  { G, Qt },
  { 0, Half },
  //6,4
  { 0, Half },
  { 0, Qt },
  { 0, Ei },
  { G, Ei },
  //7,1
  { B, Ei },
  { B, Dq },
  { 0, Ei },
  { B, Ei },
  { B, Ei },
  { B, Si },
  { HC, Si },
  //7,2
  { HC, Ei },
  { B, Qt },
  { HDs, Ei },
  { HDs, Ei },
  { B, Ei },
  { B, Ei },
  { A, Si },
  { A, Si },
  //7,3
  { G, Qt },
  { 0, Ei },
  { HE, Ei },
  { HE, Ei },
  { B, Ei },
  { B, Ei },
  { A, Si },
  { A, Si },
  //7,4
  { A, Si },
  { G, QE },
  { G, Qt },
  { 0, Qt },
  { G, Ei },
  { A, Si },
  { B, Si },
  //8,1
  { B, Ei },
  { B, Si },
  { B, Si },
  { B, Ei },
  { B, Si },
  { B, Si },
  { B, Ei },
  { B, Si },
  { B, Si },
  { B, Ei },
  { B, Si },
  { HC, Si },
  //8,2
  { HC, Si },
  { B, QE },
  { 0, Ei },
  { B, Ei },
  { B, Si },
  { B, QE },
  { B, Ei_3_of_one },
  { B, Ei_3_of_one },
  { A, Ei_3_of_one },
  //8,3
  { A, Qt },
  { 0, Qt },
  { 0, Half },
  //8,4
  { 0, Half },
  { G, QE },
  { A, Si },
  { A, Qt },
  //9,1
  { HD, Ei },
  { HD, Si },
  { HD, Si },
  { HD, Ei },
  { B, Si },
  { HD, Si },
  { HD, Ei },
  { HD, Si },
  { HD, Si },
  { HD, Si },
  { HDs, Si },
  //9,2
  { HDs, Qt },
  { 0, Ei },
  { HDs, Ei },
  { HD, Si },
  { B, QE },
  { B, Ei_3_of_one },
  { B, Ei_3_of_one },
  { A, Ei_3_of_one },
  //9,3
  { G, Qt },
  { 0, Qt },
  { 0, Half },
  //9,4
  { 0, Half },
  { 0, Qt },
  { HD, Ei },
  { HD, Si },
  { HD, Si },
  //10,1
  { HD, Si },
  { B, QE },
  { B, Qt },
  { 0, Si },
  { HD, QE },
  { HD, Si },
  { HD, Si },
  { B, Si },
  { HDs, Si },
  //10,2
  { HDs, Ei },
  { B, Qt },
  { HD, Ei },
  { HD, Ei },
  { B, Ei },
  { B, Ei },
  { A, Si },
  { A, Si },
  //10,3
  { G, Qt },
  { 0, Ei },
  { HE, Ei },
  { HE, Ei },
  { B, Qt },
  { A, Si },
  { A, Si },
  //10,4
  { A, Si },
  { G, QE },
  { 0, Qt },
  { 0, Qt },
  { G, Ei },
  { G, Si },
  { HD, Si },
  //11,1
  { HD, Half },
  { 0, Qt },
  { B, Ei },
  { B, Si },
  { B, Si },
  //11,2
  { B, Si },
  { A, QE },
  { A, Qt },
  { 0, Ei },
  { B, Ei },
  { B, Si },
  { B, QE },
  //11,3
  { A, Si },
  { G, QE },
  { G, Qt },
  { 0, Half },
  //11,4
  { 0, Half },
  { G, Qt },
  { A, Qt },
  //12,1
  { B, Ei },
  { B, Si },
  { B, Si },
  { B, Ei },
  { B, Si },
  { B, Si },
  { B, Ei },
  { B, Si },
  { B, Si },
  { B, Ei },
  { B, Si },
  { HC, Si },
  { HC, Si },
  { B, QE },
  { 0, Qt },
  { G, QE },
  { A, Si },
  { A, Qt },
  //12,2
  { HD, Ei },
  { HD, Si },
  { HD, Si },
  { HD, Ei },
  { B, Si },
  { HDs, Si },
  { HDs, Ei },
  { HD, Si },
  { HD, Si },
  { HD, Si },
  { HD, Ei },
  { B, Si },
  { Fs, Si },
  //12,3
  { Fs, Si },
  { E, QE },
  { 0, Ei },
  { B, Ei },
  { B, Si },
  { B, QE },
  { B, Ei_3_of_one },
  { B, Ei_3_of_one },
  { A, Ei_3_of_one },
  //12,4
  { G, Qt },
  { 0, Qt },
  { 0, Qt },
  { G, Ei },
  { A, Ei },
  { B, Ei },
  //13,1
  { B, Half },
  { 0, Qt },
  { B, Ei },
  { B, Si },
  { B, Si },
  //13,2
  { B, Si },
  { A, QE },
  { A, Qt },
  { 0, Ei },
  { B, Ei },
  { B, Si },
  { B, QE },
  //13,3
  { B, QE },
  { A, Si },
  { G, Qt },
  { 0, Half },
  //13,4
  { 0, Half },

};
const Melody melody9[] PROGMEM = {
  // 이전까지 반주
  //2,4
  { 0, Dh },
  { E, Ei },
  { Fs, Ei },
  // 3,1
  { Gs, Qt },
  { Fs, Ei },
  { E, Ei },
  { Ds, Ei },
  { Cs, Ei },
  { LB, Ei },
  { Cs, Ei },
  //3,2
  { Cs, Dh },
  { E, Ei },
  { Fs, Ei },
  //3,3
  { Gs, Qt },
  { Gs, Ei },
  { E, Ei },
  { Fs, Ei },
  { B, Qt },
  { HCs, Ei },
  //3,4
  { HCs, Dh },
  { HCs, Ei },
  { HDs, Ei },
  //4,1
  { HE, Qt },
  { HFs, Ei },
  { HE, Ei },
  { HDs, Ei },
  { HCs, Ei },
  { 0, Ei },
  { B, Ei },
  //4,2
  { HCs, Ei },
  { Gs, Ei },
  { Gs, Half },
  { Fs, Ei },
  { E, Ei },
  //4,3
  { E, Qt },
  { E, Ei },
  { Gs, Ei },
  { Fs, Ei },
  { E, Qt },
  { Ds, Ei },
  { Cs, Half },
  { E, Ei },
  { Fs, Ei },
  // 도돌
  // 3,1
  { Gs, Qt },
  { Fs, Ei },
  { E, Ei },
  { Ds, Ei },
  { Cs, Ei },
  { LB, Ei },
  { Cs, Ei },
  //3,2
  { Cs, Dh },
  { E, Ei },
  { Fs, Ei },
  //3,3
  { Gs, Qt },
  { Gs, Ei },
  { E, Ei },
  { Fs, Ei },
  { B, Qt },
  { HCs, Ei },
  //3,4
  { HCs, Dh },
  { HCs, Ei },
  { HDs, Ei },
  //4,1
  { HE, Qt },
  { HFs, Ei },
  { HE, Ei },
  { HDs, Ei },
  { HCs, Ei },
  { 0, Ei },
  { B, Ei },
  //4,2
  { HCs, Ei },
  { Gs, Ei },
  { Gs, Half },
  { Fs, Ei },
  { E, Ei },
  //4,3
  { E, Qt },
  { E, Ei },
  { Gs, Ei },
  { Fs, Ei },
  { E, Qt },
  { Ds, Ei },
  // 4,4
  { Cs, Half },
  { 0, Ei },
  { Gs, Ei },
  { A, Ei },
  { B, Ei },
  //5,1
  { HCs, Dq },
  { HCs, Ei },
  { B, Ei },
  { A, Qt },
  { Gs, Si },
  { Fs, Si },
  //5,2
  { Fs, Si },
  { Gs, QE },
  { Gs, Qt },
  { 0, Ei },
  { HCs, Si },
  { HE, Si },
  { HGs, Ei },
  { HE, Ei },
  //5,3
  { HFs, Half },
  { 0, Ei },
  { HFs, Si },
  { HE, Si },
  { HFs, QE },
  { HGs, Si },
  //5,4
  { HE, Ei },
  { HDs, Si },
  { HCs, Si },
  { HCs, Qt },
  { 0, Si },
  { HGs, QE },
  { HGs, Si },
  { HFs, Si },
  { HE, Ei },
  //6,1
  { HCs, Dq },
  { HCs, Ei },
  { B, Ei },
  { A, Ei },
  { Gs, Ei },
  { Fs, Ei },
  //6,2
  { Gs, Qt },
  { B, Qt },
  { HE, Dq },
  { HCs, Si },
  { HE, Si },
  //6,3
  { HFs, Half },
  { 0, Si },
  { HFs, Si },
  { HE, Ei },
  { HFs, Si },
  { HGs, Si },
  //6,4
  { HE, Ei },
  { HDs, Si },
  { HCs, Si },
  { HCs, Qt },
  { 0, Si },
  { HGs, QE },
  { HGs, Si },
  { HFs, Si },
  { HE, Ei },
  // 도돌이표
  //5,1
  { HCs, Dq },
  { HCs, Ei },
  { B, Ei },
  { A, Qt },
  { Gs, Si },
  { Fs, Si },
  //5,2
  { Fs, Si },
  { Gs, QE },
  { Gs, Qt },
  { 0, Ei },
  { HCs, Si },
  { HE, Si },
  { HGs, Ei },
  { HE, Ei },
  //5,3
  { HFs, Half },
  { 0, Ei },
  { HFs, Si },
  { HE, Si },
  { HFs, QE },
  { HGs, Si },
  //5,4
  { HE, Ei },
  { HDs, Si },
  { HCs, Si },
  { HCs, Qt },
  { 0, Si },
  { HGs, QE },
  { HGs, Si },
  { HFs, Si },
  { HE, Ei },
  //6,1
  { HCs, Dq },
  { HCs, Ei },
  { B, Ei },
  { A, Ei },
  { Gs, Ei },
  { Fs, Ei },
  //6,2
  { Gs, Qt },
  { B, Qt },
  { HE, Dq },
  { HCs, Si },
  { HE, Si },
  //6,3
  { HFs, Half },
  { 0, Si },
  { HFs, Si },
  { HE, Ei },
  { HFs, Si },
  { HGs, Si },
  //7,1
  { HE, Ei },
  { HDs, Si },
  { HCs, Si },
  { HCs, Dh },
};





void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  for (int i = 2; i < 9; i++)
    pinMode(i, OUTPUT);

  digitalWrite(10, HIGH);
}

void loop() {
  int light = analogRead(A0);
  int potentiometer1 = analogRead(A1);
  int potentiometer2 = analogRead(A2);
  int speed = map(potentiometer1, 0, 1023, 0, 10);
  uint8_t mode = map(potentiometer2, 0, 1023, 0, 9);
  displayDigit(mode);
  Serial.println(light);
  if (light <= 1010) {
    if (speed >= 1) {
      digitalWrite(12, HIGH);

      playMelody(mode);
    }
  }
  digitalWrite(12, LOW);

  delay(50);
}

// 멜로디 재생 함수: PROGMEM 쓰면 주소 참조 방식이 잘 안됌.
void playMelody(uint8_t melodyIndex) {
  int melodyLength;
  switch (melodyIndex) {
    case 0:
      melodyLength = sizeof(melody0) / sizeof(Melody);
      for (int i = 0; i < melodyLength; i++) {
        int potentiometer1 = analogRead(A1);
        int speed = map(potentiometer1, 0, 1023, 1, 10);
        if (speed <= 0) return;
        Melody currentNote;
        memcpy_P(&currentNote, &melody0[i], sizeof(Melody));
        if (currentNote.pitch == 0) {
          delay(currentNote.beat * speed);
        } else {
          tone(13, currentNote.pitch, currentNote.beat * speed);
          delay(currentNote.beat * speed);
          noTone(13);
        }
        delay(50);
      }
      break;

    case 1:
      melodyLength = sizeof(melody1) / sizeof(Melody);
      for (int i = 0; i < melodyLength; i++) {
        int potentiometer1 = analogRead(A1);
        int speed = map(potentiometer1, 0, 1023, 0, 100);
        if (speed <= 0) return;
        Melody currentNote;
        memcpy_P(&currentNote, &melody1[i], sizeof(Melody));
        if (currentNote.pitch == 0) {
          delay(currentNote.beat * speed);
        } else {
          tone(13, currentNote.pitch, currentNote.beat * speed);
          delay(currentNote.beat * speed);
          noTone(13);
        }
        delay(50);
      }
      break;

    case 2:
      melodyLength = sizeof(melody2) / sizeof(Melody);
      for (int i = 0; i < melodyLength; i++) {
        int potentiometer1 = analogRead(A1);
        int speed = map(potentiometer1, 0, 1023, 0, 100);
        if (speed <= 0) return;
        Melody currentNote;
        memcpy_P(&currentNote, &melody2[i], sizeof(Melody));
        if (currentNote.pitch == 0) {
          delay(currentNote.beat * speed);
        } else {
          tone(13, currentNote.pitch, currentNote.beat * speed);
          delay(currentNote.beat * speed);
          noTone(13);
        }
        delay(50);
      }
      break;

    case 3:
      melodyLength = sizeof(melody3) / sizeof(Melody);
      for (int i = 0; i < melodyLength; i++) {
        int potentiometer1 = analogRead(A1);
        int speed = map(potentiometer1, 0, 1023, 0, 100);
        if (speed <= 0) return;
        Melody currentNote;
        memcpy_P(&currentNote, &melody3[i], sizeof(Melody));
        if (currentNote.pitch == 0) {

          delay(currentNote.beat * speed);
        } else {
          tone(13, currentNote.pitch, currentNote.beat * speed);
          delay(currentNote.beat * speed);
          noTone(13);
        }
        delay(50);
      }
      break;

    case 4:
      melodyLength = sizeof(melody4) / sizeof(Melody);
      for (int i = 0; i < melodyLength; i++) {
        int potentiometer1 = analogRead(A1);
        int speed = map(potentiometer1, 0, 1023, 0, 100);
        if (speed <= 0) return;
        Melody currentNote;
        memcpy_P(&currentNote, &melody4[i], sizeof(Melody));
        if (currentNote.pitch == 0) {
          delay(currentNote.beat * speed);
        } else {
          tone(13, currentNote.pitch, currentNote.beat * speed);
          delay(currentNote.beat * speed);
          noTone(13);
        }
        delay(50);
      }
      break;

    case 5:
      melodyLength = sizeof(melody5) / sizeof(Melody);

      for (int i = 0; i < melodyLength; i++) {
        int potentiometer1 = analogRead(A1);
        int speed = map(potentiometer1, 0, 1023, 0, 100);
        if (speed <= 0) return;
        Melody currentNote;
        memcpy_P(&currentNote, &melody5[i], sizeof(Melody));
        if (currentNote.pitch == 0) {
          delay(currentNote.beat * speed);
        } else {
          tone(13, currentNote.pitch, currentNote.beat * speed);
          delay(currentNote.beat * speed);
          noTone(13);
        }
        delay(50);
      }
      break;

    case 6:
      melodyLength = sizeof(melody6) / sizeof(Melody);
      for (int i = 0; i < melodyLength; i++) {
        int potentiometer1 = analogRead(A1);
        int speed = map(potentiometer1, 0, 1023, 0, 100);
        if (speed <= 0) return;
        Melody currentNote;
        memcpy_P(&currentNote, &melody6[i], sizeof(Melody));

        if (currentNote.pitch == 0) {
          delay(currentNote.beat * speed);
        } else {
          tone(13, currentNote.pitch, currentNote.beat * speed);
          delay(currentNote.beat * speed);
          noTone(13);
        }
        delay(50);
      }
      break;

    case 7:
      melodyLength = sizeof(melody7) / sizeof(Melody);
      for (int i = 0; i < melodyLength; i++) {
        int potentiometer1 = analogRead(A1);
        int speed = map(potentiometer1, 0, 1023, 0, 100);
        if (speed <= 0) return;
        Melody currentNote;
        memcpy_P(&currentNote, &melody7[i], sizeof(Melody));
        Serial.println(currentNote.beat);
        if (currentNote.pitch == 0) {
          delay(currentNote.beat * speed);
        } else {
          tone(13, currentNote.pitch, currentNote.beat * speed);
          delay(currentNote.beat * speed);
          noTone(13);
        }
        delay(50);
      }
      break;

    case 8:
      melodyLength = sizeof(melody8) / sizeof(Melody);
      for (int i = 0; i < melodyLength; i++) {
        int potentiometer1 = analogRead(A1);
        int speed = map(potentiometer1, 0, 1023, 0, 100);
        if (speed <= 0) return;
        Melody currentNote;
        memcpy_P(&currentNote, &melody8[i], sizeof(Melody));
        if (currentNote.pitch == 0) {
          delay(currentNote.beat * speed);
        } else {
          tone(13, currentNote.pitch, currentNote.beat * speed);
          delay(currentNote.beat * speed);
          noTone(13);
        }
        delay(50);
      }
      break;

    case 9:
      melodyLength = sizeof(melody9) / sizeof(Melody);
      for (int i = 0; i < melodyLength; i++) {
        int potentiometer1 = analogRead(A1);
        int speed = map(potentiometer1, 0, 1023, 0, 100);
        if (speed <= 0) return;
        Melody currentNote;
        memcpy_P(&currentNote, &melody9[i], sizeof(Melody));
        if (currentNote.pitch == 0) {
          delay(currentNote.beat * speed);
        } else {
          tone(13, currentNote.pitch, currentNote.beat * speed);
          delay(currentNote.beat * speed);
          noTone(13);
        }
        delay(50);
      }
      break;
  }
}
void displayDigit(int num) {
  int pin = 2;
  for (int i = 0; i < 7; i++) {
    digitalWrite(pin + i, digits[num][i]);
  }
}
