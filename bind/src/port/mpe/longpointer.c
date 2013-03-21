/*
 * gcc long pointer support code for HPPA.
 * Copyright 1998, DIS International, Ltd.
 * Permission is granted to use this code under the GNU LIBRARY GENERAL
 * PUBLIC LICENSE, Version 2, June 1991.
 */

#include "longpointer.h"

int __bind_mpe_getspaceid(void *source)
  {
  int val;
  /*
   * Given the short pointer, determine it's space ID.
   */

  /*
   * The colons separate output from input parameters. In this case,
   * the output of the instruction (output indicated by the "=" in the
   * constraint) is to a memory location (indicated by the "m"). The
   * input constraint indicates that the source to the instruction
   * is a register reference (indicated by the "r").
   * The general format is:
   *   asm("<instruction template>" : <output> : <input> : <clobbers>);
   *     where <output> and <input> are:
   *       "<constraint>" (<token>)
   *     <instruction template> is the PA-RISC instruction in template fmt.
   *     <clobbers> indicates those registers clobbered by the instruction
   *     and provides hints to the optimizer.
   *
   * Refer to the gcc documentation or http://www.dis.com/gnu/gcc_toc.html
   */
  asm volatile (
      "comiclr,= 0,%1,%%r28;
         ldsid (%%r0,%1),%%r28;
       stw %%r28, %0"
                        : "=m" (val)    // Output to val
                        : "r" (source)  // Source must be gen reg
                        : "%r28");      // Clobbers %r28
  return (val);
  };

LONGPOINTER __bind_mpe_longaddr(void *source)
  {
  LONGPOINTER lptr;
  /*
   * Return the long pointer for the address in sr5 space.
   */

  asm volatile (
      "comiclr,= 0,%2,%%r28;
         ldsid (%%r0,%2),%%r28;
       stw %%r28, %0;
       stw %2, %1"
                        : "=m" (lptr.spaceid),
                          "=m" (lptr.offset)    // Store to lptr
                        : "r" (source)          // Source must be gen reg
                        : "%r28");      // Clobbers %r28
  return (lptr);
  };

LONGPOINTER __bind_mpe_addtopointer(LONGPOINTER source,    // %r26 == source offset
                                                // %r25 == source space
                        int             len)    // %r24 == length in bytes
  {
  /*
   * Increment a longpointer.
   */

  asm volatile (
      "copy %0,%%r28;                           // copy space to r28
       add %1,%2,%%r29"                         // Increment the pointer
                        :                       // No output
                        : "r" (source.spaceid), // Source address
                          "r" (source.offset),
                          "r" (len)             // Length
                        : "%r28",               // Clobbers
                          "%r29");
  };

void __bind_mpe_longmove(int len,                  // %r26 == byte length
              LONGPOINTER source,       // %r23 == source space, %r24 == off
              LONGPOINTER target)       // sp-#56 == target space, sp-#52== off
  {
  /*
   * Move data between two buffers in long pointer space.
   */

  asm volatile (
      ".import $$lr_unk_unk_long,MILLICODE;
       mtsp %0,%%sr1;                           // copy source space to sr1
       copy %1,%%r26;                           // load source offset to r26
       copy %4,%%r24;                           // load length to r24
       copy %3,%%r25;                           // load target offset to r25
       bl $$lr_unk_unk_long,%%r31;              // start branch to millicode
       mtsp %2,%%sr2"                           // copy target space to sr2
                        :                       // No output
                        : "r" (source.spaceid), // Source address
                          "r" (source.offset),
                          "r" (target.spaceid), // Target address
                          "r" (target.offset),
                          "r" (len)             // Byte length
                        : "%r1",                // Clobbers
                          "%r24",
                          "%r25",
                          "%r26",
                          "%r31");
  };

int __bind_mpe_longpeek(LONGPOINTER source)
  {
  /*
   * Fetch the int in long pointer space.
   */
  unsigned int val;

  asm volatile (
      "mtsp %1, %%sr1;
       copy %2, %%r28;
       ldw 0(%%sr1, %%r28), %%r28;
       stw %%r28, %0"
                        : "=m" (val)            // Output val
                        : "r" (source.spaceid), // Source space ID
                          "r" (source.offset)   // Source offset
                        : "%r28");              // Clobbers %r28

  return (val);
  };

void __bind_mpe_longpoke(LONGPOINTER target,       // %r25 == spaceid, %r26 == offset
          unsigned int val)             // %r24 == value
  {
  /*
   * Store the val into long pointer space.
   */
  asm volatile (
      "mtsp %0,%%sr1;
       copy %1, %%r28;
       stw %2, 0(%%sr1, %%r28)"
                        :                       // No output
                        : "r" (target.spaceid), // Target space ID
                          "r" (target.offset),  // Target offset
                          "r" (val)             // Value to store
                        : "%r28"                // Clobbers %r28
                        );                      // Copy space to %sr1
  };

void __bind_mpe_move_fast(int len,                 // %r26 == byte length
               void *source,            // %r25 == source addr
               void *target)            // %r24 == target addr
  {
  /*
   * Move using short pointers.
   */
  asm volatile (
      ".import $$lr_unk_unk,MILLICODE;
       copy %1, %%r26;                          // Move source addr into pos
       copy %2, %%r25;                          // Move target addr into pos
       bl $$lr_unk_unk,%%r31;                   // Start branch to millicode
       copy %0, %%r24"                          // Move length into position
                        :                       // No output
                        : "r" (len),            // Byte length
                          "r" (source),         // Source address
                          "r" (target)          // Target address
                        : "%r24",               // Clobbers
                          "%r25",
                          "%r26",
                          "%r31");
  };
