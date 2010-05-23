/**
 * \file process.h
 * \brief process functions
 * \author Adrien Forest
 * \version 0.1
 * \date 21 Mai 2010
 */

#ifndef __PROCESS_H
#define __PROCESS_H

#define MIN_PRI 0
#define MAX_PRI 30
#define BAS_PRI 15
#define MAX_ARG 4
#define ARG_SIZE 20
#define NSUPERVISED 40

#include <stdlib.h>

/**
 * \struct pcbinfo
 * \brief Copy of a process pcb.
 *
 * A copy has to be created and passed to make sure that the real pcb will not
 * be affected in any way.
 */
typedef struct
{
  int       pid;          /*!< Process identifier. */
  char            name[ARG_SIZE];       /*!< Process name. */
  int        pri;          /*!< Process priority. */
  int        supervised[NSUPERVISED];      /*!< List of supervised processes. */
  int        supervisor;   /*!< List of supervisor processes. */
  int        wait;
  bool            empty;
} pcbinfo;

int             kill(int pid);

int             fourchette(char *name, int prio, int argc, char *argv[]);

#endif //__PROCESS_H
