/*
** get_sym64.c for sym64 in /home/fredoddou/Documents/Epitech/B4-Unix-System-Programming/PSU_2016_nmobjdump/objdump/src/64bits/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri Feb 24 15:31:22 2017 Frederic ODDOU
** Last update Fri Feb 24 15:31:22 2017 Frederic ODDOU
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "objdump.h"

bool		get_sym64(t_objdump		*objdump)
{
  Elf64_Ehdr	*ehdr;
  Elf64_Shdr	*shdr;

  ehdr = objdump->ehdr;
  shdr = objdump->shdr;
  if (!check_end_map(objdump, shdr + 1) ||
      !check_end_map(objdump, SECTION_STR) ||
      !check_end_map(objdump, &(shdr[ehdr->e_shnum])))
    return (false);
  return (true);
}
