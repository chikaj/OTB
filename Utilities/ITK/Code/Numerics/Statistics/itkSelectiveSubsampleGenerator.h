/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkSelectiveSubsampleGenerator.h,v $
  Language:  C++
  Date:      $Date: 2003-12-15 01:00:46 $
  Version:   $Revision: 1.5 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkSelectiveSubsampleGenerator_h
#define __itkSelectiveSubsampleGenerator_h


#include "itkObject.h"
#include "itkMembershipSample.h"

namespace itk{
  namespace Statistics{

/** \class SelectiveSubsampleGenerator
 * \brief SelectiveSubsampleGenerator generates a Subsample object
 * that includes measurement vectors that belong to the classes that
 * are specified by the SetSelectedClassLabels method.
 *
 * To instantiate an object of this class you have to provide two 
 * template arguments: the type of the input sample and the type of 
 * class mask sample. 
 * 
 * The input sample is a sample that has all the measurement vectors and
 * the class mask sample contains class labels for their corresponding
 * measurement vectors in the input sample. Therefore, the sizes of both
 * should be the same.
 *
 * To generate a subsample that a part of the input sample that belongs
 * to a set of classes, you should call SetSelectedClassLabels method 
 * with the class labels that you want to include in the output. 
 *
 * \sa Subsample
 */

template< class TInputSample, class TClassMaskSample >
class ITK_EXPORT SelectiveSubsampleGenerator : 
      public Object
{
public:
  /** Standard class typedefs. */
  typedef SelectiveSubsampleGenerator Self;
  typedef Object Superclass ;
  typedef SmartPointer<Self> Pointer;
  typedef SmartPointer<const Self> ConstPointer;

  /** Standard Macros */
  itkTypeMacro(SelectiveSubsampleGenerator, Object);
  itkNewMacro(Self) ;

  /** Input sample types alias */
  typedef typename TInputSample::MeasurementVectorType MeasurementVectorType ;

  typedef typename TClassMaskSample::MeasurementType ClassLabelType ;
  typedef std::vector< ClassLabelType > ClassLabelVectorType ;

  /** Output: MembershipSample types */
  typedef Subsample< TInputSample > OutputType ;
  typedef typename OutputType::Pointer OutputPointer ;

  /** Stores the input sample */
  void SetInput(TInputSample* sample) ;
  
  /** Returns the input sample pointer */
  TInputSample* GetInput() ;

  /** Stores the class mask sample */
  void SetClassMask(const TClassMaskSample* classMask) ;

  /** Returns the class mask sample pointer*/
  const TClassMaskSample* GetClassMask() const;

  void SetSelectedClassLabels( const ClassLabelVectorType& classLabels )
  { m_SelectedClassLabels = classLabels ; }

  /** Returns the pointer to the MembershipSample object
   * that has been generated by this */
  const OutputType * GetOutput() const;

  /** The actual output generation procedure. */
  void GenerateData() ;

protected:
  SelectiveSubsampleGenerator() ;
  virtual ~SelectiveSubsampleGenerator() {}
  void PrintSelf(std::ostream& os, Indent indent) const;

private:
  TInputSample* m_Input ;
  const TClassMaskSample* m_ClassMask ;
  ClassLabelVectorType m_SelectedClassLabels ;
  OutputPointer m_Output ;
} ; // end of class

  } // end namespace Statistics
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkSelectiveSubsampleGenerator.txx"
#endif

#endif
