#include <utility>
#include <sstream>

#include "tiny-scope.h"

#include "config.h"
#include "system.h"

namespace Tiny
{

void
Scope::insert (Symbol *s)
{
  gcc_assert (s != NULL);
  std::pair<Map::iterator, bool> p
    = map.insert (std::make_pair (s->get_name (), s));

  std::stringstream ss;
  ss << s->get_name () << "_" << scope_id;
  s->set_global_name (ss.str ());

  gcc_assert (p.second);
}

Symbol *
Scope::query_in_scope (const std::string &str)
{
  Map::iterator it = map.find (str);
  if (it != map.end ())
    {
      return it->second;
    }
  return NULL;
}

Symbol *
Scope::query (const std::string &str)
{
  Scope *sc = this;
  while (sc != NULL)
    {
      if (Symbol *sym = sc->query_in_scope (str))
	{
	  return sym;
	}
      sc = sc->enclosing;
    }
  return NULL;
}
}
