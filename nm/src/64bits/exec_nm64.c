/*
** exec_nm.c for exec in /nm/src/
**
** Made by Frederic ODDOU
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Wed Feb 15 21:00:09 2017 Frederic ODDOU
** Last update Fri Feb 24 11:57:35 2017 Frederic ODDOU
*/

#include <stdio.h>
#include <string.h>
#include "nm.h"

static char		find_type_2(Elf64_Shdr	*shdr,
				    Elf64_Sym	*sym)
{
  char			c;

  if (sym->st_shndx == SHN_UNDEF)
    c = 'U';
  else if (sym->st_shndx == SHN_ABS)
    c = 'A';
  else if (sym->st_shndx == SHN_COMMON)
    c = 'C';
  else if (shdr[sym->st_shndx].sh_type == SHT_NOBITS &&
	   shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'B';
  else if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS &&
	   shdr[sym->st_shndx].sh_flags == SHF_ALLOC)
    c = 'R';
  else if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS &&
	   shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'D';
  else if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS &&
	   shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
    c = 'T';
  else if (shdr[sym->st_shndx].sh_type == SHT_DYNAMIC)
    c = 'D';
  else
    c = '?';
  return (c);
}

static char		find_type(Elf64_Ehdr	*ehdr,
				  Elf64_Shdr	*shdr,
				  Elf64_Sym	*sym)
{
  char			c;

  if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
    c = 'u';
  else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
    c = (sym->st_shndx == SHN_UNDEF) ? 'w' : 'W';
  else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK &&
	   ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
    c = (sym->st_shndx == SHN_UNDEF) ? 'v' : 'V';
  else
    c = find_type_2(shdr, sym);
  if (c == '?' &&
      (strcmp(&SECTION_STR[shdr[sym->st_shndx].sh_name], ".init_array") ||
       strcmp(&SECTION_STR[shdr[sym->st_shndx].sh_name], ".fini_array")))
    c = 'T';
  if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
    c += 32;
  return (c);
}

static bool		exec_symbol(t_nm	*nm,
				    t_flag	flags,
				    Elf64_Sym	*sym,
				    int		*i)
{
  Elf64_Ehdr		*ehdr;
  Elf64_Shdr		*shdr;
  Elf64_Shdr		*symtab;

  ehdr = (Elf64_Ehdr *)nm->ehdr;
  shdr = (Elf64_Shdr *)nm->shdr;
  symtab = (Elf64_Shdr *)nm->symtab;
  if ((sym->st_name > 0 && sym->st_info != STT_FILE) || flags[FLAG_DEBUG_SYMS])
    {
      nm->list[*i].sym = sym;
      if (sym->st_info == STT_SECTION &&
	  sym->st_shndx <= ehdr->e_shnum &&
	  sym->st_name == 0)
	nm->list[*i].name = &SECTION_STR[shdr[sym->st_shndx].sh_name];
      else
	nm->list[*i].name = &SYMB_STR[sym->st_name];
      nm->list[*i].value = sym->st_value;
      nm->list[*i].type = find_type(ehdr, shdr, sym);
      if (!check_end_map(nm, nm->list[*i].name))
	return (false);
      (*i)++;
    }
  return (true);
}

bool			exec_nm64(t_nm		*nm,
				  t_flag	flags)
{
  int			i;
  Elf64_Ehdr		*ehdr;
  Elf64_Sym		*sym;
  Elf64_Shdr		*symtab;

  ehdr = (Elf64_Ehdr *)nm->ehdr;
  symtab = (Elf64_Shdr *)nm->symtab;
  sym = (Elf64_Sym *)SYMB_LIST;
  i = 0;
  if ((nm->list = calloc(1, sizeof(t_list) * symtab->sh_size)) == NULL)
    return (print_error("calloc failled"));
  while ((void *)sym < (void *)(SYMB_LIST + symtab->sh_size))
    {
      if (!exec_symbol(nm, flags, sym, &i))
	return (false);
      sym++;
    }
  display_sym(nm, flags, i);
  return (true);
}
