/*
** exec_nm.c for exec in /nm/src/
**
** Made by Frederic ODDOU
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Wed Feb 15 21:00:09 2017 Frederic ODDOU
** Last update Fri Feb 24 12:20:34 2017 Frederic ODDOU
*/

#include <stdio.h>
#include <string.h>
#include "nm.h"

bool			exec_nm(t_nm		*nm,
				t_flag		flags)
{
  if (g_architecture == A32BITS)
    return (exec_nm32(nm, flags));
  return (exec_nm64(nm, flags));
}
