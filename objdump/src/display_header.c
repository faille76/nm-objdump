/*
** display_header.c for display header in /objdump/src/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon Feb 20 20:01:56 2017 Frederic ODDOU
** Last update Tue Feb 21 01:16:33 2017 Fredoddou
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objdump.h"

static t_type g_machine[] = {
  {EM_386, "i386"},
  {EM_X86_64, "i386:x86-64"},
};

static t_type g_flags_type[] = {
  {HAS_RELOC, "HAS_RELOC"},
  {EXEC_P, "EXEC_P"},
  {HAS_LINENO, "HAS_LINENO"},
  {HAS_DEBUG, "HAS_DEBUG"},
  {HAS_SYMS, "HAS_SYMS"},
  {HAS_LOCALS, "HAS_LOCALS"},
  {DYNAMIC, "DYNAMIC"},
  {WP_TEXT, "WP_TEXT"},
  {D_PAGED, "D_PAGED"},
  {BFD_IS_RELAXABLE, "BFD_IS_RELAXABLE"},
  {HAS_LOAD_PAGE, "HAS_LOAD_PAGE"},
};

static void		display_flags(int		e_flags)
{
  int			i;
  char			*str;

  str = "";
  i = 0;
  while (i < (int)GET_SIZE(g_flags_type))
    {
      if (e_flags & g_flags_type[i].id)
	{
	  printf("%s%s", str, g_flags_type[i].value);
	  str = ", ";
	}
      i++;
    }
}

static char		*get_architecture(int		e_machine)
{
  int			i;

  i = 0;
  while (i < (int)GET_SIZE(g_machine))
    {
      if (g_machine[i].id == e_machine)
	return (g_machine[i].value);
      i++;
    }
  return ("Unknown");
}

static void		display_header64(t_objdump	*objdump,
					 t_flag		flags,
					 Elf64_Ehdr	*ehdr)
{
  (void)flags;
  printf("\n%s:     file format elf64-x86-64\n", objdump->name);
  printf("architecture: %s, flags 0x%08x:\n",
	 get_architecture(ehdr->e_machine), ehdr->e_flags);
  display_flags(ehdr->e_flags);
  printf("\nstart address 0x%016lx\n\n", ehdr->e_entry);
}

static void		display_header32(t_objdump	*objdump,
					 t_flag		flags,
					 Elf32_Ehdr	*ehdr)
{
  (void)flags;
  printf("\n%s:     file format elf32-i386\n", objdump->name);
  printf("architecture: %s, flags 0x%08x:\n",
	 get_architecture(ehdr->e_machine), ehdr->e_flags);
  display_flags(ehdr->e_flags);
  printf("\nstart address 0x%08x\n\n", ehdr->e_entry);
}

void			display_header(t_objdump	*objdump,
				       t_flag		flags)
{
  if (g_architecture == A32BITS)
    display_header32(objdump, flags, (Elf32_Ehdr *)objdump->ehdr);
  else
    display_header64(objdump, flags, (Elf64_Ehdr *)objdump->ehdr);
}
