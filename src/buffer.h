

#ifndef CLIEDITOR_BUFFER_H
#define CLIEDITOR_BUFFER_H

char* buffer;
long size;

void b_resize(int);
void b_add(char);
void b_del(void);
void b_delf(void);
void b_deli(int);
void b_free(void);
void b_init(char*);


#endif //CLIEDITOR_BUFFER_H
