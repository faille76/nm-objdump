/*
** get_sym64.c for 64 in /home/fredoddou/Documents/Epitech/B4-Unix-System-Programming/PSU_2016_nmobjdump/nm/src/64bits/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri Feb 24 08:28:53 2017 Frederic ODDOU
** Last update Fri Feb 24 08:28:53 2017 Frederic ODDOU
*/

#include <unistd.h>
#include <string.h>
#include "nm.h"

static bool	get_sym32_check_end(t_nm	*nm,
				    Elf32_Shdr	*shdr,
				    Elf32_Ehdr	*ehdr,
				    Elf32_Shdr	*symtab)
{

  if (!check_end_map(nm, SYMB_STR) ||
      !check_end_map(nm, SECTION_STR) ||
      !check_end_map(nm, (char *)SYMB_LIST + symtab->sh_size))
    return (false);
  return (true);
}

bool		get_sym32(t_nm		*nm)
{
  int		i;
  Elf32_Shdr	*shdr;
  Elf32_Ehdr	*ehdr;
  Elf32_Shdr	*symtab;

  i = 0;
  ehdr = (Elf32_Ehdr *)nm->ehdr;
  shdr = (Elf32_Shdr *)nm->shdr;
  symtab = NULL;
  if (!check_end_map(nm, shdr + 1) ||
      !check_end_map(nm, &(shdr[ehdr->e_shnum])))
    return (false);
  while (i < ehdr->e_shnum)
    {
      if (shdr[i].sh_type == SHT_SYMTAB)
	{
	  nm->symtab = ((Elf64_Shdr *)&(shdr[i]));
	  symtab = (Elf32_Shdr *)nm->symtab;
	}
      i++;
    }
  if (!nm->symtab)
    return (print_error("no symbols"));
  return (get_sym32_check_end(nm, shdr, ehdr, symtab));
}
