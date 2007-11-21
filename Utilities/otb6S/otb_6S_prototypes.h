/* Include prototype headers. */
#include "6SV1.0B/AATSR.h"
#include "6SV1.0B/ABSTRA.h"
#include "6SV1.0B/AEROSO.h"
#include "6SV1.0B/AERROF.P.h"
#include "6SV1.0B/AKTOOL.h"
#include "6SV1.0B/ATMREF.h"
#include "6SV1.0B/AVHRR.h"
#include "6SV1.0B/BBM.h"
#include "6SV1.0B/BDM.h"
#include "6SV1.0B/BRDFGRID.h"
#include "6SV1.0B/CHAND.h"
#include "6SV1.0B/CLEARW.h"
#include "6SV1.0B/CSALBR.h"
#include "6SV1.0B/DICA1.h"
#include "6SV1.0B/DICA2.h"
#include "6SV1.0B/DICA3.h"
#include "6SV1.0B/DISCOM.h"
#include "6SV1.0B/DISCRE.h"
#include "6SV1.0B/DUST.h"
#include "6SV1.0B/ECINTERP.P.h"
#include "6SV1.0B/ENVIRO.h"
#include "6SV1.0B/EQUIVWL.h"
#include "6SV1.0B/GAUSS.h"
#include "6SV1.0B/GLI.h"
#include "6SV1.0B/GOES.h"
#include "6SV1.0B/HKALBE.P.h"
#include "6SV1.0B/HKBRDF.P.h"
#include "6SV1.0B/HRV.h"
#include "6SV1.0B/IIALBE.P.h"
#include "6SV1.0B/IIBRDF.P.h"
#include "6SV1.0B/IITOOLS.P.h"
#include "6SV1.0B/INTE.P.h"
#include "6SV1.0B/ISO.h"
#include "6SV1.0B/KERNEL.h"
#include "6SV1.0B/KERNEOL.P.h"
#include "6SV1.0B/LAKEW.h"
#include "6SV1.0B/LIE2.P.h"
#include "6SV1.0B/LIN2.P.h"
#include "6SV1.0B/LINE.P.h"
#include "6SV1.0B/LINT.P.h"
#include "6SV1.0B/main.h"
#include "6SV1.0B/MAS.h"
#include "6SV1.0B/MERIS.h"
#include "6SV1.0B/METEO.h"
#include "6SV1.0B/METH1.h"
#include "6SV1.0B/METH2.h"
#include "6SV1.0B/METH3.h"
#include "6SV1.0B/METH4.h"
#include "6SV1.0B/METH5.h"
#include "6SV1.0B/METH6.h"
#include "6SV1.0B/MIDSUM.h"
#include "6SV1.0B/MIDWIN.h"
#include "6SV1.0B/MIE.h"
#include "6SV1.0B/MINNALBE.h"
#include "6SV1.0B/MINNBRDF.h"
#include "6SV1.0B/MOCA1.h"
#include "6SV1.0B/MOCA2.h"
#include "6SV1.0B/MOCA3.h"
#include "6SV1.0B/MOCA4.h"
#include "6SV1.0B/MOCA5.h"
#include "6SV1.0B/MOCA6.h"
#include "6SV1.0B/MODISALBE.h"
#include "6SV1.0B/MODISBRDF.h"
#include "6SV1.0B/MODIS.h"
#include "6SV1.0B/MSS.h"
#include "6SV1.0B/NIOX1.h"
#include "6SV1.0B/NIOX2.h"
#include "6SV1.0B/NIOX3.h"
#include "6SV1.0B/NIOX4.h"
#include "6SV1.0B/NIOX5.h"
#include "6SV1.0B/NIOX6.h"
#include "6SV1.0B/OCEAALBE.h"
#include "6SV1.0B/OCEABRDFFAST.h"
#include "6SV1.0B/OCEABRDF.h"
#include "6SV1.0B/OCEA.h"
#include "6SV1.0B/OCEATOOLS.h"
#include "6SV1.0B/ODA550.h"
#include "6SV1.0B/ODRAYL.h"
#include "6SV1.0B/OOL.P.h"
#include "6SV1.0B/OS.h"
#include "6SV1.0B/OXYG3.h"
#include "6SV1.0B/OXYG4.h"
#include "6SV1.0B/OXYG5.h"
#include "6SV1.0B/OXYG6.h"
#include "6SV1.0B/OZON1.h"
#include "6SV1.0B/RAHMALBE.h"
#include "6SV1.0B/RAHMBRDF.h"
#include "6SV1.0B/ROUJALBE.h"
#include "6SV1.0B/ROUJBRDF.h"
#include "6SV1.0B/SAND.h"
#include "6SV1.0B/SCATRA.h"
#include "6SV1.0B/SEAWIFS.h"
#include "6SV1.0B/SOLIRR.h"
#include "6SV1.0B/SOOT.h"
#include "6SV1.0B/STM.h"
#include "6SV1.0B/SUBSUM.h"
#include "6SV1.0B/SUBWIN.h"
#include "6SV1.0B/TM.h"
#include "6SV1.0B/TRIC.P.h"
#include "6SV1.0B/TRUNCA.h"
#include "6SV1.0B/US62.h"
#include "6SV1.0B/VARSOL.h"
#include "6SV1.0B/VEGETA.h"
#include "6SV1.0B/VERSALBE.h"
#include "6SV1.0B/VERSBRDF.h"
#include "6SV1.0B/VERSTOOLS.h"
#include "6SV1.0B/WALTALBE.h"
#include "6SV1.0B/WALTBRDF.h"
#include "6SV1.0B/WATE.h"
#include "6SV1.0B/WAVA1.h"
#include "6SV1.0B/WAVA2.h"
#include "6SV1.0B/WAVA3.h"
#include "6SV1.0B/WAVA4.h"
#include "6SV1.0B/WAVA5.h"
#include "6SV1.0B/WAVA6.h"

/* otb 6S Main function */
#include "otb_main6S_function.h"
