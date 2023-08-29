#pragma once

void showBall(int i);
int ballCollideWithPlatform(int sprite1, int sprite2, int b);
void initBalls(void);
void explodeABall(int a);
void explodeAllBall(void);
int createBigBall(double posx, double posy, int hdirection, int vdirection);
int createNormalBall(double posx, double posy, int hdirection, int vdirection);
int createSmallBall(double posx, double posy, int hdirection, int vdirection);
int createMicroBall(double posx, double posy, int hdirection, int vdirection);
int createBall(double posx, double posy, int typeBall, int hdirection, int vdirection);
void updateBalls(int i);
