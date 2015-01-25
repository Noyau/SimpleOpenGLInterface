#ifndef UTILS_HPP
#define UTILS_HPP

template<typename T>
static inline const T &clamp(const T &v, const T &min, const T &max)
{
  return v < min ? min : (v > max ? max : v);
}

template<typename T>
static inline bool isInBounds(const T &v, const T &min, const T &max)
{
  return v >= min && v <= max;
}

template<typename P, typename T>
static inline bool isPointInBounds(const P &p, const P &pMin, const P &pMax)
{
  return isInBounds<T>(p.x(), pMin.x(), pMax.x()) && isInBounds<T>(p.y(), pMin.y(), pMax.y());
}

#endif // UTILS_HPP
