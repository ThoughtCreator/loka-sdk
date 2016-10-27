/*
 * Singleton.h
 *
 *  Created on: Oct 11, 2016
 *      Author: pedro
 */

#ifndef INCLUDE_TC_RTOS_SINGLETON_H_
#define INCLUDE_TC_RTOS_SINGLETON_H_



#include <stddef.h>  // defines NULL

template <class T>
class Singleton
{
public:
  static T* Instance() {
      if(!m_pInstance) m_pInstance = new T;
      return m_pInstance;
  }
protected:
  Singleton();
  ~Singleton();
private:
  Singleton(Singleton const&);
  Singleton& operator=(Singleton const&);
  static T* m_pInstance;
};

template <class T> T* Singleton<T>::m_pInstance=NULL;




#endif /* INCLUDE_TC_RTOS_SINGLETON_H_ */
