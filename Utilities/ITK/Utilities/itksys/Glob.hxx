/*=========================================================================

  Program:   KWSys - Kitware System Library
  Module:    $RCSfile: Glob.hxx.in,v $

  Copyright (c) Kitware, Inc., Insight Consortium.  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef itksys_Glob_hxx
#define itksys_Glob_hxx

#include <itksys/Configure.h>
#include <itksys/Configure.hxx>

#include <itksys/stl/string>
#include <itksys/stl/vector>

/* Define this macro temporarily to keep the code readable.  */
#if !defined (KWSYS_NAMESPACE) && !itksys_NAME_IS_KWSYS
# define kwsys_stl itksys_stl
#endif

namespace itksys
{

class GlobInternals;

/** \class Glob
 * \brief Portable globbing searches.
 *
 * Globbing expressions are much simpler than regular
 * expressions. This class will search for files using
 * globbing expressions.
 *
 * Finds all files that match a given globbing expression.
 */
class itksys_EXPORT Glob
{
public:
  Glob();
  ~Glob();

  //! Find all files that match the pattern.
  bool FindFiles(const kwsys_stl::string& inexpr);

  //! Return the list of files that matched.
  kwsys_stl::vector<kwsys_stl::string>& GetFiles();

  //! Set recurse to true to match subdirectories.
  void RecurseOn() { this->SetRecurse(true); }
  void RecurseOff() { this->SetRecurse(false); }
  void SetRecurse(bool i) { this->Recurse = i; }
  bool GetRecurse() { return this->Recurse; }

  //! Set relative to true to only show relative path to files.
  void SetRelative(const char* dir);
  const char* GetRelative();

protected:
  //! Process directory
  void ProcessDirectory(kwsys_stl::string::size_type start,
    const kwsys_stl::string& dir, bool dir_only);

  //! Process last directory, but only when recurse flags is on. That is
  // effectively like saying: /path/to/file/**/file
  void RecurseDirectory(kwsys_stl::string::size_type start,
    const kwsys_stl::string& dir, bool dir_only);

  //! Escape all non-alphanumeric characters in pattern.
  void Escape(int ch, char* buffer);

  //!
  // Translate a shell PATTERN to a regular expression.
  // There is no way to quote meta-characters.
  kwsys_stl::string ConvertExpression(const kwsys_stl::string& expr);

  //! Add regular expression
  void AddExpression(const char* expr);

  //! Add a file to the list
  void AddFile(kwsys_stl::vector<kwsys_stl::string>& files, const char* file);

  GlobInternals* Internals;
  bool Recurse;
  kwsys_stl::string Relative;
};

} // namespace itksys

#endif
