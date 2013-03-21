/*
 * gcc long pointer support code for HPPA.
 * Copyright 1998, DIS International, Ltd.
 * Permission is granted to use this code under the GNU LIBRARY GENERAL
 * PUBLIC LICENSE, Version 2, June 1991.
 */
typedef struct {
  int           spaceid;
  unsigned int  offset;
  } LONGPOINTER, longpointer;

extern int __bind_mpe_getspaceid(void *source);
extern LONGPOINTER __bind_mpe_longaddr(void *source);
extern LONGPOINTER __bind_mpe_addtopointer(LONGPOINTER source, int len);
extern void __bind_mpe_longmove(int len, LONGPOINTER source, LONGPOINTER target);
extern int __bind_mpe_longpeek(LONGPOINTER source);
extern void __bind_mpe_longpoke(LONGPOINTER target, unsigned int val);
extern void __bind_mpe_move_fast(int len, void *source, void *target);
