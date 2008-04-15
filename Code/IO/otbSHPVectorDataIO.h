/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __otbSHPVectorDataIO_h
#define __otbSHPVectorDataIO_h

#include "otbVectorDataIOBase.h"
#include <fstream>
#include <string>
#include <vector>


namespace otb
{

/** \class SHPVectorDataIO
 *
 * \brief ImageIO object for reading (not writing) SHP format vector data
 *
 */
class ITK_EXPORT SHPVectorDataIO : public VectorDataIOBase
{
public:

  /** Standard class typedefs. */
  typedef SHPVectorDataIO            Self;
  typedef VectorDataIOBase  Superclass;
  typedef itk::SmartPointer<Self>  Pointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(SHPVectorDataIO, VectorDataIOBase);

  /** Byte order typedef */
  typedef Superclass::ByteOrder  ByteOrder;
  

  /*-------- This part of the interface deals with reading data. ------ */

  /** Determine the file type. Returns true if this VectorDataIO can read the
   * file specified. */
  virtual bool CanReadFile(const char*);
  
  /** Determine the file type. Returns true if the VectorDataIO can stream read the specified file */
  virtual bool CanStreamRead(){  return true; };

  /** Set the spacing and dimention information for the set filename. */
  virtual void ReadVectorDataInformation();
 
  /** Reads the data from disk into the memory buffer provided. */
  virtual void Read(VectorDataBase* buffer);

  /*-------- This part of the interfaces deals with writing data. ----- */

  /** Determine the file type. Returns true if this ImageIO can read the
   * file specified. */
  virtual bool CanWriteFile(const char*);

  /** Determine the file type. Returns true if the ImageIO can stream write the specified file */
  virtual bool CanStreamWrite() { return true; };

  /** Writes the spacing and dimentions of the image.
   * Assumes SetFileName has been called with a valid file name. */
  virtual void WriteVectorDataInformation();

  /** Writes the data to disk from the memory buffer provided. Make sure
   * that the IORegion has been set properly. */
  virtual void Write(const VectorDataBase* buffer);
  
protected:
  /** Construtor.*/
  SHPVectorDataIO();
  /** Destructor.*/
  ~SHPVectorDataIO();

  void InternalReadVectorDataInformation();

  void PrintSelf(std::ostream& os, itk::Indent indent) const;

private:
  SHPVectorDataIO(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  /** Internal method to read header informations */
  bool InternalReadHeaderInformation(std::fstream & file, const bool reportError);

  bool    m_FlagWriteVectorDataInformation;
  VectorDataIOBase::ByteOrder m_FileByteOrder;
  std::fstream m_File;

};

} // end namespace otb

#endif // __otbSHPVectorDataIO_h
