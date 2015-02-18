set(DOCUMENTATION "This module contains classes that allow measuring the
differences between two segmentations.")

otb_module(OTBMetrics 
  DEPENDS
    OTBCommon
  TEST_DEPENDS
    OTBLabelMap
    OTBTestKernel
  
  DESCRIPTION
    "${DOCUMENTATION}"
  )
