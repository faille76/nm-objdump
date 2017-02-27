/*
** exec_objdump64.c for obj64 in /home/fredoddou/Documents/Epitech/B4-Unix-System-Programming/PSU_2016_nmobjdump/objdump/src/64bits/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri Feb 24 15:43:49 2017 Frederic ODDOU
** Last update Fri Feb 24 15:43:49 2017 Frederic ODDOU
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objdump.h"

static char *g_skip_section[] = {
  "",
  ".bss",
  ".shstrtab",
  ".symtab",
  ".strtab",
  ".rela.text",
  ".rela.debug_info",
  ".rela.debug_aranges",
  ".rela.debug_line",
  ".rela.eh_frame",
  ".tbss",
  "__libc_freeres_ptrs",
  NULL
};

static bool		if_skip_section(Elf32_Ehdr	*ehdr,
					Elf32_Shdr	*shdr,
					int		tab)
{
  int			i;

  i = 0;
  if (!shdr[tab].sh_size)
    return (true);
  while (g_skip_section[i] != NULL)
    {
      if (!strcmp(g_skip_section[i], &SECTION_STR[shdr[tab].sh_name]))
	return (true);
      i++;
    }

  return (false);
}

static void		display_line(Elf32_Ehdr	*ehdr,
				     Elf32_Shdr	shdr)
{
  unsigned int		i;

  i = shdr.sh_offset;
  while (i < (unsigned int)(shdr.sh_offset + shdr.sh_size))
    {
      printf(" %04x ", (int)(shdr.sh_addr + i - shdr.sh_offset));
      display_hexa((unsigned char *)ehdr + i,
		   shdr.sh_offset + shdr.sh_size - i);
      i += 16;
      printf("\n");
    }
}

bool			exec_objdump32(t_objdump		*objdump,
				       t_flag			flags)
{
  int			i;
  Elf32_Ehdr		*ehdr;
  Elf32_Shdr		*shdr;

  ehdr = (Elf32_Ehdr *)objdump->ehdr;
  shdr = (Elf32_Shdr *)objdump->shdr;
  if (ehdr->e_type == ET_EXEC)
    ehdr->e_flags = 274;
  else if (ehdr->e_type == ET_DYN)
    ehdr->e_flags = 336;
  else if (ehdr->e_type == ET_REL)
    ehdr->e_flags = 17;
  display_header(objdump, flags);
  i = 0;
  while (i < ehdr->e_shnum)
    {
      if (!if_skip_section(ehdr, shdr, i))
	{
	  printf("Contents of section %s:\n", &SECTION_STR[shdr[i].sh_name]);
	  display_line(ehdr, shdr[i]);
	}
      i++;
    }
  return (true);
}
