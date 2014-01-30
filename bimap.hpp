#ifndef BIMAP_HPP_INCLUDED
#define BIMAP_HPP_INCLUDED
#include <map>

// Define a generic bimap type (X <-> Y)
template <typename X, typename Y> struct Bimap {
  std::map<X,Y> to;
  std::map<Y,X> from;
  Bimap() { };
  Bimap(const std::map<X, Y> &m) :to(m) { update_from_map(); };

  // Build up the 'from' map (Y -> X) using the 'to' map (X -> Y)
  void update_from_map() {
    typename std::map<X,Y>::iterator iter = to.begin();
    typename std::map<X,Y>::iterator end = to.end();

    for (; iter != end; iter++) { //Exclamation mark means negation, //I.E !true = false or !!true == true.
      from[iter->second] = iter->first;
    }
  };
};

// Specialized bimap type (E_DRIVER_TYPE <-> string)
struct IrrDriversBimap : Bimap<irr::video::E_DRIVER_TYPE, std::string> {
  IrrDriversBimap() {
    to[irr::video::E_DRIVER_TYPE::EDT_OPENGL]     = "OpenGL";
    to[irr::video::E_DRIVER_TYPE::EDT_DIRECT3D9]  = "Direct3D9";
    to[irr::video::E_DRIVER_TYPE::EDT_DIRECT3D8]  = "Direct3D8";
    to[irr::video::E_DRIVER_TYPE::EDT_SOFTWARE]   = "Software";
    update_from_map();
  };
};

#endif // BIMAP_HPP_INCLUDED
