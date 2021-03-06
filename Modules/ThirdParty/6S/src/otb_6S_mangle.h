/*

This header file mangles all symbols exported from the otb_6s
library.  There are purposely no include blockers so translation units
can mangle/unmangle repeatedly.  It is included in all files while
building the library.

The following command was used to obtain the symbol list:

nm libotb_6s.a |grep " [TR] "

*/

/* Functions */
#define varsol_ otb_6s_varsol_
#define enviro_ otb_6s_enviro_
/* otb 6S Main function */
#define  ssssss_otb_main_function otb_6s_ssssss_otb_main_function 

#define adaptquad_ otb_6s_adaptquad_
#define balanc_ otb_6s_balanc_
#define balbak_ otb_6s_balbak_
#define calcsc_ otb_6s_calcsc_
#define caxpy_ otb_6s_caxpy_
#define ccopy_ otb_6s_ccopy_
#define cdiv_ otb_6s_cdiv_
#define cdotc_ otb_6s_cdotc_
#define cg_ otb_6s_cg_
#define chscdf_ otb_6s_chscdf_
#define cqrdc_ otb_6s_cqrdc_
#define cqrsl_ otb_6s_cqrsl_
#define cscal_ otb_6s_cscal_
#define csrot_ otb_6s_csrot_
#define csvdc_ otb_6s_csvdc_
#define cswap_ otb_6s_cswap_
#define cub_ otb_6s_cub_
#define dasum_ otb_6s_dasum_
#define daxpy_ otb_6s_daxpy_
#define dcabs1_ otb_6s_dcabs1_
#define dchscdf_ otb_6s_dchscdf_
#define dcopy_ otb_6s_dcopy_
#define ddot_ otb_6s_ddot_
#define dgecon_ otb_6s_dgecon_
#define dgemm_ otb_6s_dgemm_
#define dgemv_ otb_6s_dgemv_
#define dgeqr2_ otb_6s_dgeqr2_
#define dgeqrf_ otb_6s_dgeqrf_
#define dger_ otb_6s_dger_
#define dgerq2_ otb_6s_dgerq2_
#define dgesc2_ otb_6s_dgesc2_
#define dgetc2_ otb_6s_dgetc2_
#define dggbak_ otb_6s_dggbak_
#define dggbal_ otb_6s_dggbal_
#define dgges_ otb_6s_dgges_
#define dgghrd_ otb_6s_dgghrd_
#define dgpfa2f_ otb_6s_dgpfa2f_
#define dgpfa3f_ otb_6s_dgpfa3f_
#define dgpfa5f_ otb_6s_dgpfa5f_
#define dgpfa_ otb_6s_dgpfa_
#define dhgeqz_ otb_6s_dhgeqz_
#define dlabad_ otb_6s_dlabad_
#define dlabax_ otb_6s_dlabax_
#define dlabcm_ otb_6s_dlabcm_
#define dlabfc_ otb_6s_dlabfc_
#define dlacon_ otb_6s_dlacon_
#define dlacpy_ otb_6s_dlacpy_
#define dladiv_ otb_6s_dladiv_
#define dlaeig_ otb_6s_dlaeig_
#define dlag2_ otb_6s_dlag2_
#define dlager_ otb_6s_dlager_
#define dlagv2_ otb_6s_dlagv2_
#define dlamc1_ otb_6s_dlamc1_
#define dlamc2_ otb_6s_dlamc2_
#define dlamc3_ otb_6s_dlamc3_
#define dlamc4_ otb_6s_dlamc4_
#define dlamc5_ otb_6s_dlamc5_
#define dlamch_ otb_6s_dlamch_
#define dlange_ otb_6s_dlange_
#define dlanhs_ otb_6s_dlanhs_
#define dlapy2_ otb_6s_dlapy2_
#define dlapy3_ otb_6s_dlapy3_
#define dlaran_ otb_6s_dlaran_
#define dlarf_ otb_6s_dlarf_
#define dlarfb_ otb_6s_dlarfb_
#define dlarfg_ otb_6s_dlarfg_
#define dlarft_ otb_6s_dlarft_
#define dlartg_ otb_6s_dlartg_
#define dlascl_ otb_6s_dlascl_
#define dlaset_ otb_6s_dlaset_
#define dlassq_ otb_6s_dlassq_
#define dlasv2_ otb_6s_dlasv2_
#define dlaswp_ otb_6s_dlaswp_
#define dlatdf_ otb_6s_dlatdf_
#define dlatrs_ otb_6s_dlatrs_
#define dmvpc_ otb_6s_dmvpc_
#define dnlaso_ otb_6s_dnlaso_
#define dnorcdf_ otb_6s_dnorcdf_
#define dnppla_ otb_6s_dnppla_
#define dnrm2_ otb_6s_dnrm2_
#define dnwla_ otb_6s_dnwla_
#define dorg2r_ otb_6s_dorg2r_
#define dorgqr_ otb_6s_dorgqr_
#define dorgr2_ otb_6s_dorgr2_
#define dorm2r_ otb_6s_dorm2r_
#define dormqr_ otb_6s_dormqr_
#define dormr2_ otb_6s_dormr2_
#define dortqr_ otb_6s_dortqr_
#define dpmpar_ otb_6s_dpmpar_
#define dpoco_ otb_6s_dpoco_
#define dpodi_ otb_6s_dpodi_
#define dpofa_ otb_6s_dpofa_
#define dposl_ otb_6s_dposl_
#define dqrdc_ otb_6s_dqrdc_
#define dqrsl_ otb_6s_dqrsl_
#define drot_ otb_6s_drot_
#define drotg_ otb_6s_drotg_
#define drscl_ otb_6s_drscl_
#define dscal_ otb_6s_dscal_
#define dsvdc_ otb_6s_dsvdc_
#define dswap_ otb_6s_dswap_
#define dtgex2_ otb_6s_dtgex2_
#define dtgexc_ otb_6s_dtgexc_
#define dtgsen_ otb_6s_dtgsen_
#define dtgsy2_ otb_6s_dtgsy2_
#define dtgsyl_ otb_6s_dtgsyl_
#define dtrmm_ otb_6s_dtrmm_
#define dtrmv_ otb_6s_dtrmv_
#define dtrsv_ otb_6s_dtrsv_
#define dvsort_ otb_6s_dvsort_
#define dzasum_ otb_6s_dzasum_
#define dznrm2_ otb_6s_dznrm2_
#define elmhes_ otb_6s_elmhes_
#define eltran_ otb_6s_eltran_
#define enorm_ otb_6s_enorm_
#define epslon_ otb_6s_epslon_
#define fd_ otb_6s_fd_
#define fdjac2_ otb_6s_fdjac2_
#define fv_ otb_6s_fv_
#define fvd_ otb_6s_fvd_
#define fxshfr_ otb_6s_fxshfr_
#define gpfa2f_ otb_6s_gpfa2f_
#define gpfa3f_ otb_6s_gpfa3f_
#define gpfa5f_ otb_6s_gpfa5f_
#define gpfa_ otb_6s_gpfa_
#define hqr2_ otb_6s_hqr2_
#define hqr_ otb_6s_hqr_
#define idamax_ otb_6s_idamax_
#define ieeeck_ otb_6s_ieeeck_
#define ilaenv_ otb_6s_ilaenv_
#define ins_ otb_6s_ins_
#define isamax_ otb_6s_isamax_
#define izamax_ otb_6s_izamax_
#define lb1_ otb_6s_lb1_
#define lbfgs_ otb_6s_lbfgs_
#define lce_ otb_6s_lce_
#define lde_ otb_6s_lde_
#define lmder1_ otb_6s_lmder1_
#define lmder_ otb_6s_lmder_
#define lmdif_ otb_6s_lmdif_
#define lmpar_ otb_6s_lmpar_
#define lsame_ otb_6s_lsame_
#define lse_ otb_6s_lse_
#define lsqr_ otb_6s_lsqr_
#define mcsrch_ otb_6s_mcsrch_
#define mcstep_ otb_6s_mcstep_
#define newest_ otb_6s_newest_
#define nextk_ otb_6s_nextk_
#define pythag_ otb_6s_pythag_
#define qrfac_ otb_6s_qrfac_
#define qrsolv_ otb_6s_qrsolv_
#define quad_ otb_6s_quad_
#define quadit_ otb_6s_quadit_
#define quadsd_ otb_6s_quadsd_
#define realit_ otb_6s_realit_
#define rebak_ otb_6s_rebak_
#define reduc_ otb_6s_reduc_
#define refine_ otb_6s_refine_
#define rg_ otb_6s_rg_
#define rpoly_ otb_6s_rpoly_
#define rs_ otb_6s_rs_
#define rsg_ otb_6s_rsg_
#define saxpy_ otb_6s_saxpy_
#define sbeg_ otb_6s_sbeg_
#define sblas2_ otb_6s_sblas2_
#define schck1_ otb_6s_schck1_
#define schck2_ otb_6s_schck2_
#define schck3_ otb_6s_schck3_
#define schck4_ otb_6s_schck4_
#define schck5_ otb_6s_schck5_
#define scnrm2_ otb_6s_scnrm2_
#define scopy_ otb_6s_scopy_
#define sdiff_ otb_6s_sdiff_
#define sdot_ otb_6s_sdot_
#define setdgpfa_ otb_6s_setdgpfa_
#define setgpfa_ otb_6s_setgpfa_
#define sgbmv_ otb_6s_sgbmv_
#define sgemv_ otb_6s_sgemv_
#define sgeqpf_ otb_6s_sgeqpf_
#define sgeqr2_ otb_6s_sgeqr2_
#define sger_ otb_6s_sger_
#define sgerq2_ otb_6s_sgerq2_
#define sggsvd_ otb_6s_sggsvd_
#define sggsvp_ otb_6s_sggsvp_
#define simpru_ otb_6s_simpru_
#define slacpy_ otb_6s_slacpy_
#define slags2_ otb_6s_slags2_
#define slamc1_ otb_6s_slamc1_
#define slamc2_ otb_6s_slamc2_
#define slamc3_ otb_6s_slamc3_
#define slamc4_ otb_6s_slamc4_
#define slamc5_ otb_6s_slamc5_
#define slamch_ otb_6s_slamch_
#define slange_ otb_6s_slange_
#define slapll_ otb_6s_slapll_
#define slapmt_ otb_6s_slapmt_
#define slapy2_ otb_6s_slapy2_
#define slarf_ otb_6s_slarf_
#define slarfg_ otb_6s_slarfg_
#define slartg_ otb_6s_slartg_
#define slas2_ otb_6s_slas2_
#define slaset_ otb_6s_slaset_
#define slassq_ otb_6s_slassq_
#define slasv2_ otb_6s_slasv2_
#define smake_ otb_6s_smake_
#define smessg_ otb_6s_smessg_
#define snrm2_ otb_6s_snrm2_
#define sopen_ otb_6s_sopen_
#define sorg2r_ otb_6s_sorg2r_
#define sorm2r_ otb_6s_sorm2r_
#define sormr2_ otb_6s_sormr2_
#define sqrdc_ otb_6s_sqrdc_
#define sqrsl_ otb_6s_sqrsl_
#define srot_ otb_6s_srot_
#define srotg_ otb_6s_srotg_
#define srule_ otb_6s_srule_
#define ssbmv_ otb_6s_ssbmv_
#define sscal_ otb_6s_sscal_
#define sspmv_ otb_6s_sspmv_
#define sspr2_ otb_6s_sspr2_
#define sspr_ otb_6s_sspr_
#define ssvdc_ otb_6s_ssvdc_
#define sswap_ otb_6s_sswap_
#define ssymv_ otb_6s_ssymv_
#define ssyr2_ otb_6s_ssyr2_
#define ssyr_ otb_6s_ssyr_
#define stbmv_ otb_6s_stbmv_
#define stbsv_ otb_6s_stbsv_
#define stgsja_ otb_6s_stgsja_
#define stpmv_ otb_6s_stpmv_
#define stpsv_ otb_6s_stpsv_
#define strmv_ otb_6s_strmv_
#define strsv_ otb_6s_strsv_
#define tql1_ otb_6s_tql1_
#define tql2_ otb_6s_tql2_
#define tqlrat_ otb_6s_tqlrat_
#define trapru_ otb_6s_trapru_
#define tred1_ otb_6s_tred1_
#define tred2_ otb_6s_tred2_
#define urand_ otb_6s_urand_
#define xerbla_ otb_6s_xerbla_
#define xsimpru_ otb_6s_xsimpru_
#define xtrapru_ otb_6s_xtrapru_
#define zaxpy_ otb_6s_zaxpy_
#define zcopy_ otb_6s_zcopy_
#define zdotc_ otb_6s_zdotc_
#define zdotu_ otb_6s_zdotu_
#define zdrot_ otb_6s_zdrot_
#define zdscal_ otb_6s_zdscal_
#define zgebak_ otb_6s_zgebak_
#define zgebal_ otb_6s_zgebal_
#define zgeev_ otb_6s_zgeev_
#define zgehd2_ otb_6s_zgehd2_
#define zgehrd_ otb_6s_zgehrd_
#define zgemm_ otb_6s_zgemm_
#define zgemv_ otb_6s_zgemv_
#define zgerc_ otb_6s_zgerc_
#define zhseqr_ otb_6s_zhseqr_
#define zlacgv_ otb_6s_zlacgv_
#define zlacpy_ otb_6s_zlacpy_
#define zladiv_ otb_6s_zladiv_
#define zlahqr_ otb_6s_zlahqr_
#define zlahrd_ otb_6s_zlahrd_
#define zlange_ otb_6s_zlange_
#define zlanhs_ otb_6s_zlanhs_
#define zlarf_ otb_6s_zlarf_
#define zlarfb_ otb_6s_zlarfb_
#define zlarfg_ otb_6s_zlarfg_
#define zlarft_ otb_6s_zlarft_
#define zlarfx_ otb_6s_zlarfx_
#define zlascl_ otb_6s_zlascl_
#define zlaset_ otb_6s_zlaset_
#define zlassq_ otb_6s_zlassq_
#define zlatrs_ otb_6s_zlatrs_
#define zqrdc_ otb_6s_zqrdc_
#define zqrsl_ otb_6s_zqrsl_
#define zscal_ otb_6s_zscal_
#define zsvdc_ otb_6s_zsvdc_
#define zswap_ otb_6s_zswap_
#define ztrevc_ otb_6s_ztrevc_
#define ztrmm_ otb_6s_ztrmm_
#define ztrmv_ otb_6s_ztrmv_
#define ztrsv_ otb_6s_ztrsv_
#define zung2r_ otb_6s_zung2r_
#define zunghr_ otb_6s_zunghr_
#define zungqr_ otb_6s_zungqr_
