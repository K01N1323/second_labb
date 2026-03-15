#ifndef IENUMERATOR_H
#define IENUMERATOR_H

template <class T> class IEnumerator {
public:
  virtual ~IEnumerator() {}

  virtual const T &GetCurrent() const = 0;

  virtual void MoveNext() = 0;

  virtual bool HasNext() const = 0;
};

#endif // ienumertor h