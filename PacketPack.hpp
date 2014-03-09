#ifndef PACKETPACK_HPP_INCLUDED
#define PACKETPACK_HPP_INCLUDED
#include <cstdint>
#include <string>
#include <sstream>

// #include <arpa/inet.h> //!< might be needed for hton* functions

#include <irrlicht/vector3d.h>

#include "UDPSocket.hpp"

class PacketPack : public std::basic_stringstream<char> {
    PacketPack() {};

    PacketPack& operator <<(f32 v) {
        //!< Convert number to fixed-point
struct PacketPack : public std::basic_stringstream<char> {
    PacketPack() {};

    PacketPack& operator <<(f32 v) {
        //!< Convert number to fixed-point
        int32_t vv = ((double)v)*1000;
        std::basic_stringstream<char> &s = *this;
        s << ((uint8_t)((vv)       &0xff));
        s << ((uint8_t)((vv >> 8)  &0xff));
        s << ((uint8_t)((vv >> 16) &0xff));
        s << ((uint8_t)((vv >> 24) &0xff));
        return (*this);
    }

    PacketPack& operator <<(const core::vector3df& v) {
      (*this) << v.X << v.Y << v.Z;
      return (*this);
    }
};

class PacketUnpack : public std::basic_istringstream<char> {
struct PacketUnpack : public std::basic_istringstream<char> {
PacketUnpack(const std::basic_string<char> &s) :std::basic_istringstream<char>(s) {};

    PacketUnpack& operator >>(f32 &v) {
        uint8_t a, b, c, d;
        std::basic_istringstream<char> &s = *this;
        s >> a >> b >> c >> d;
        int32_t vv = a | (b<<8) | (c<<16) | (d<<24);
        //!< Convert number from fixed-point
        //!< Convert number from fixed-point
        v = ((double)vv)/1000;
        return (*this);
    }

    PacketUnpack& operator >>(core::vector3df& v) {
      (*this) >> v.X >> v.Y >> v.Z;
      return (*this);
    }

};
#endif //!< PACKETPACK_HPP_INCLUDED
