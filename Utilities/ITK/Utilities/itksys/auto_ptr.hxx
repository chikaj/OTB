/*=========================================================================

  Program:   KWSys - Kitware System Library
  Module:    $RCSfile: auto_ptr.hxx.in,v $

  Copyright (c) Kitware, Inc., Insight Consortium.  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef itksys_auto_ptr_hxx
#define itksys_auto_ptr_hxx

namespace itksys
{

// C++98 Standard Section 20.4.5 - Template class auto_ptr.
template <class X>
class auto_ptr
{
  template <class Y> struct auto_ptr_ref
  {
    auto_ptr<Y>& p_;
    explicit auto_ptr_ref(auto_ptr<Y>& p): p_(p) {}
  };
  X* x_;
public:
  typedef X element_type;

  template <class Y>
  auto_ptr(auto_ptr<Y>& a) throw(): x_(a.release()) {}
  template <class Y>
  auto_ptr& operator=(auto_ptr<Y>& a) throw()
    { reset(a.release()); return *this; }

  explicit auto_ptr(X* p=0) throw(): x_(p) {}
  auto_ptr(auto_ptr& a) throw(): x_(a.release()) {}
  auto_ptr& operator=(auto_ptr& a) throw() { reset(a.release()); return *this; }
  ~auto_ptr() throw() { delete get(); }

  X& operator*() const throw() { return *get(); }
  X* operator->() const throw() { return get(); }
  X* get() const throw() { return x_; }
  X* release() throw() { X* x = x_; x_ = 0; return x; }
  void reset(X* p=0) throw() { if(get() != p) { delete get(); x_ = p; } }

  auto_ptr(auto_ptr_ref<X> r) throw(): x_(r.p_.release()) {}
  template <class Y> operator auto_ptr_ref<Y>() throw() { return *this; }
  template <class Y> operator auto_ptr<Y>() throw() { return release(); }
  auto_ptr& operator=(auto_ptr_ref<X> r) throw() { x_ = r.p_.release(); return *this; }
};

} // namespace itksys

#endif
