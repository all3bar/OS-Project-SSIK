/*
 * example_timer:
 *   An example of how to setup the MIPS/Malta board
 *   to periodically increase a number on the display.
 */

#include <process.h>
#include <stdio.h>
#include <mips4kc.h>
#include <string.h>
#include "asm.h"
#include "malta.h"
#include "debug.h"
#include "kernel.h"
#include "kinout.h"
#include "kprocess.h"
//#include "test.h"
#include "uart.h"
#include "splash.h"
#include "kscheduler.h"
#include "kprogram.h"
#include "ksleep.h"

static registers_t regs;

/* kinit:
 *   Application-specific initialisation code, called
 *   from the boot code '_start' in 'asm.S'.
 */
void
kinit()
{
  char            hello[] = "Hello World";

  status_reg_t    and, or;
  and.reg = 0xFFFFFFFF;
  and.field.exl = 0;            // EXL clear
  and.field.um = 0;             // Kernel mode
  and.field.im = 0;             // Clear IMs
  and.field.bev = 0;            // normal exception vector
  and.field.erl = 0;            // ERL clear

  or.reg = 0x00000000;
  or.field.ie = 1;              //interrupts enabled
  or.field.im = 0x84;           //useful interrupts enabled (those used by tty0 and the timer)
  kset_sr(and.reg, or.reg);

  /*
   * Setup uart
   */
  uart_init();

  /* print hello world */
  kprintln(hello);

  /* Setup storage-area for saving registers on exception. */
  kset_registers(&regs);

  /* Update the status register to enable exceptions. */
  kset_sr(0xFFBF00E8, 0x10008001);

  /*
   * Print SSIK on the malta
   */
  kmaltaprint8("  SSIK  ");

  /*
   * Init the four list of pcb
   */
  pls_reset(&plsready);
  pls_reset(&plsrunning);
  pls_reset(&plswaiting);
  pls_reset(&plsterminate);

  reset_next_pid();
  reset_used_stack();
  init_mem();

  set_current_pcb(NULL);
  p_error = &kerror;

  /*
   * Launch Init
   */
  if (create_proc("init", MAX_PRI, 0, NULL) < 0)
  {
    kprintln("FAILNOOB");
    while (1);
  }

  /*
   * set the exeption timer
   */
  kload_timer(QUANTUM);

  uart_init();
  /* Forever do nothing. */
  while (1);
}

/**
 * @brief The ancestor of the ancestor.
 *
 * First process to be launched
 */
void
init()
{
  int             pid, status, shell;
  char            scroll_param[3][ARG_SIZE];
  char            arg[3][ARG_SIZE];


  strcpy("arg_test", arg[0]);
  strcpy("arg1", arg[1]);
  strcpy("arg2", arg[2]);

  pid = get_pid();

  if (pid != 0)
    while (1);

  /*
   * Print the splash screen
   */
  splash();

  strcpy("3", scroll_param[0]);
  strcpy("  SSIK  - The Simply and Stupidly Implemented Kernel",
         scroll_param[1]);
  strcpy("200", scroll_param[2]);

  if (create_proc("scroll", MAX_PRI, 3, (char **) scroll_param) < 0)
  {
    print("FAILNOOB\n");
    while (1);
  }

  shell = create_proc("coquille", BAS_PRI, 0, (char **) NULL);
  if (shell < 0)
  {
    print("FAILNOOB\n");
    while (1);
  }
  wait(shell, &status);

  print("\nYou can now shut down your computer ! :)");
  while (1);
}
