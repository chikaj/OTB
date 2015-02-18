set(DOCUMENTATION "This module contains additional geometric transformations
that are more suitable to remote sensing (compared to the ones already available in
itk -see itk::Transform-). this mainly concerns transformations of coordinates
from any map projection or sensor model to any map projection or sensor model.")

otb_module(OTBTransform 
  DEPENDS
    OTBITKPendingPatches
    OTBCommon
    OTBGDAL
    OTBBoost
    OTBOSSIMAdapters
    OTBInterpolation
  TEST_DEPENDS
    OTBTestKernel
  
  DESCRIPTION
    "${DOCUMENTATION}"
  )
