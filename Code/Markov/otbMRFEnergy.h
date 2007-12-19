
#ifndef _otbMRFEnergy_h
#define _otbMRFEnergy_h

#include "itkConstNeighborhoodIterator.h"
#include "itkArray.h" 

namespace otb
{
  
    template< class TInput1, class TInput2>
      class ITK_EXPORT MRFEnergy : public itk::Object
//       class MRFEnergy : public itk::Object    
      {
        public:
          typedef MRFEnergy Self;
          typedef itk::Object Superclass;
          typedef itk::SmartPointer<Self>  Pointer;
          typedef itk::SmartPointer<const Self>  ConstPointer;
          
          typedef TInput1 InputImageType;
          typedef TInput2 LabelledImageType;
          typedef typename InputImageType::PixelType InputImagePixelType;
          typedef typename LabelledImageType::PixelType LabelledImagePixelType;
          
          typedef itk::ConstNeighborhoodIterator< LabelledImageType >  LabelledNeighborhoodIterator;
          typedef itk::ConstNeighborhoodIterator< InputImageType >  InputNeighborhoodIterator;
          
          typedef itk::Array< double > ParametersType;
    
          
          itkNewMacro(Self);
    
          itkTypeMacro(MRFEnergy,Object);
          
          unsigned int GetNumberOfParameters(void) const 
                        { return m_NumberOfParameters; }
          
          // Get the parameters
          const ParametersType& GetParameters( void ) const
          {
            return this->m_Parameters;
          }
          
          void SetParameters( const ParametersType & parameters )
          {
            bool modified = false;
            for( unsigned int i=0; i<m_NumberOfParameters; i++ )
              {
              if (m_Parameters[i] != parameters[i])
                {
                m_Parameters[i] = parameters[i];
                modified = true;
                }
              }
            if (modified)
              {
              this->Modified();
              }
          }
          
          virtual double GetSingleValue(const InputImagePixelType & value1,  const LabelledImagePixelType & value2){};
              
          double GetValue(const InputImagePixelType & value1,  const LabelledImagePixelType & value2)
          {
            return GetSingleValue(value1, value2);
          }
     
          double GetValue(const LabelledNeighborhoodIterator & it,  const LabelledImagePixelType & value2)
          {
            double result = 0.0;
            unsigned int centerIndex = it.GetCenterNeighborhoodIndex();
            InputImagePixelType value1; //TODO put also the other neighborhood ?
            bool isInside=false;
            unsigned int insideNeighbors = 0;
            for(unsigned long pos = 0; pos< it.Size(); ++pos)
            {
              if (pos !=  centerIndex)//TODO put outside loop for faster access ?
              {
                value1 = it.GetPixel(pos, isInside);
                if (isInside){
                  result += GetSingleValue(value1, value2);
                  insideNeighbors++;
                }
              }
            }
            return result/insideNeighbors;
          }
          
          double GetValue(const InputNeighborhoodIterator & it,  const LabelledImagePixelType & value2)
          {
            double result = 0.0;
            unsigned int centerIndex = it.GetCenterNeighborhoodIndex();
            InputImagePixelType value1; //TODO put also the other neighborhood ?
            bool isInside=false;
            unsigned int insideNeighbors = 0;
            for(unsigned long pos = 0; pos< it.Size(); ++pos)
            {
              if (pos !=  centerIndex)//TODO put outside loop for faster access ?
              {
                value1 = it.GetPixel(pos, isInside);
                if (isInside){
                  result += GetSingleValue(value1, value2);
                  insideNeighbors++;
                }
              }
            }
            return result/insideNeighbors;
          }
          
       protected:
      // The constructor and destructor.
          MRFEnergy() {};
          virtual ~MRFEnergy() {};
          int m_NumberOfParameters;
          ParametersType m_Parameters;
      };
      
      
      template< class TInput2>
      class ITK_EXPORT MRFEnergy<TInput2,TInput2> : public itk::Object
      {
        public:
          typedef MRFEnergy Self;
          typedef itk::Object Superclass;
          typedef itk::SmartPointer<Self>  Pointer;
          typedef itk::SmartPointer<const Self>  ConstPointer;
          
          typedef TInput2 LabelledImageType;
          typedef typename LabelledImageType::PixelType LabelledImagePixelType;
          
          typedef itk::ConstNeighborhoodIterator< LabelledImageType >  LabelledNeighborhoodIterator;
          
          typedef itk::Array< double > ParametersType;
    
          
          itkNewMacro(Self);
    
          itkTypeMacro(MRFEnergy,Object);
          
          unsigned int GetNumberOfParameters(void) const 
                        { return m_NumberOfParameters; }
          
          // Get the parameters
          const ParametersType& GetParameters( void ) const
          {
            return this->m_Parameters;
          }
          
          void SetParameters( const ParametersType & parameters )
          {
            bool modified = false;
            for( unsigned int i=0; i<m_NumberOfParameters; i++ )
              {
              if (m_Parameters[i] != parameters[i])
                {
                m_Parameters[i] = parameters[i];
                modified = true;
                }
              }
            if (modified)
              {
              this->Modified();
              }
          }
          
          virtual double GetSingleValue(const LabelledImagePixelType & value1,  const LabelledImagePixelType & value2){};
          
          
              
          double GetValue(const LabelledImagePixelType & value1,  const LabelledImagePixelType & value2)
          {
            return GetSingleValue(value1, value2);
          }
     
          double GetValue(const LabelledNeighborhoodIterator & it,  const LabelledImagePixelType & value2)
          {
            double result = 0.0;
            unsigned int centerIndex = it.GetCenterNeighborhoodIndex();
            LabelledImagePixelType value1; //TODO put also the other neighborhood ?
            bool isInside=false;
            unsigned int insideNeighbors = 0;
            for(unsigned long pos = 0; pos< it.Size(); ++pos)
            {
              if (pos !=  centerIndex)//TODO put outside loop for faster access ?
              {
                value1 = it.GetPixel(pos, isInside);
                if (isInside){
                  result += GetSingleValue(value1, value2);
                  insideNeighbors++;
                }
              }
            }
            return result/insideNeighbors;
          }
          

          
       protected:
      // The constructor and destructor.
          MRFEnergy() {};
          virtual ~MRFEnergy() {};
          unsigned int m_NumberOfParameters;
          ParametersType m_Parameters;
      };
}

#endif
