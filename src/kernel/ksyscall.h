/**
 * \file ksyscall.h
 * \brief Handle the syscall interrupts.
 * \author Christophe Carasco
 * \version 0.1
 * \date 21 mai 2010
 *
 */

#ifndef __KSYSCALL_H
#define __KSYSCALL_H

#include "include/registers.h"
#include "include/types.h"

enum
{
  FOURCHETTE,
  PRINT,
  PRINTLN,
  FPRINT,
  SLEEP,
  BLOCK,
  WAKEUP,
  WAIT,
  SEND,
  RECV,
  PERROR,
  GERROR,
  SERROR,
  GETPINFO,
  GETPID,
  CHGPPRI,
  KILL,
  EXIT
};

int32_t         syscall_none(int32_t scode);
int32_t         syscall_one(int32_t p1, int32_t scode);
int32_t         syscall_two(int32_t p1, int32_t p2, int32_t scode);
int32_t         syscall_three(int32_t p1, int32_t p2, int32_t p3,
                              int32_t scode);

void            syscall_handler(registers_t * regs);

#endif
