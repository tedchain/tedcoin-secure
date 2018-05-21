#pragma once

namespace epee
{

  template<class t_obj>
  struct enableable
  {
    t_obj v;
    bool enabled;

    enableable()
      : v(t_obj()), enabled(true)
    {	// construct from defaults
    }

    enableable(const t_obj& _v)
      : v(_v), enabled(true)
    {	// construct from specified values
    }

    enableable(const enableable<t_obj>& _v)
      : v(_v.v), enabled(_v.enabled)
    {	// construct from specified values
    }
  };
}