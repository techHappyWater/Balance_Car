#ifndef LCD1602
#define LCD1602

#define RS PBout(12)
#define E  PBout(13)
#define D0 PBout(14)
#define D1 PBout(15)
#define D2 PAout(8)
#define D3 PAout(11)
#define D4 PAout(12)
#define D5 PAout(15)
#define D6 PBout(3)
#define D7 PBout(4)

void PB15_8_Write(u8 data);
void LCD1602_Init(void);
void LCD1602_Display(void);

extern u8 hang1[16];
extern u8 hang2[16];

#endif
