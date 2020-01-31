#ifndef PROCESSES_H_INCLUDED
#define PROCESSES_H_INCLUDED

void PlayerInput(int pipe);
void ghostProcess(int pipeOut, point initial_position, int ghost_id, int direction_hint);
int CoreProcess(int pipeIn, int pipeOut);
void BulletProcess(int pipeOut, point initial_position, int direction, int id, int target);
#endif