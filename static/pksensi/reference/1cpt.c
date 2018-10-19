/* 1cpt.c
   ___________________________________________________

   Model File:  1cpt.model

   Date:  Fri Oct 19 07:05:08 2018

   Created by:  "mod v5.6.6"
    -- a model preprocessor by Don Maszle
   ___________________________________________________

   Copyright (c) 1993-2017 Free Software Foundation, Inc.

   Model calculations for compartmental model:

   2 States:
     Q_rest -> 0.0;
     Q_elim -> 0.0;

   4 Outputs:
     C_rest -> 0.0;
     C_elim -> 0.0;
     Q_total -> 0.0;
     lnC_rest -> 0.0;

   1 Input:
     Oral_input (is a function)

   31 Parameters:
     BW = 70;
     MW = 100;
     V_dist = 1;
     lnV_dist = log(1.);
     k_a = 1.0;
     lnk_a = log(1.0);
     k_e = 0.1;
     lnk_e = log(.1);
     Absdose = 0;
     IngDose = 1.0;
     Fgutabs = 1.0;
     Period = 24.0;
     Tlag = 0.0;
     M_V_dist = 0;
     M_lnV_dist = 0;
     M_k_e = 0;
     M_lnk_e = 0;
     M_k_a = 0;
     M_lnk_a = 0;
     M_Fgutabs = 0;
     M_lnFgutabs = 0;
     V_V_dist = 0;
     V_lnV_dist = 0;
     V_k_e = 0;
     V_lnk_e = 0;
     V_k_a = 0;
     V_lnk_a = 0;
     V_Fgutabs = 0;
     V_lnFgutabs = 0;
     Ve_C_rest = 0;
     Ve_lnC_rest = 0;
*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include "modelu.h"
#include "random.h"
#include "yourcode.h"


/*----- Indices to Global Variables */

/* Model variables: States and other outputs */
#define ID_Q_rest 0x00000
#define ID_Q_elim 0x00001
#define ID_C_rest 0x00002
#define ID_C_elim 0x00003
#define ID_Q_total 0x00004
#define ID_lnC_rest 0x00005

/* Inputs */
#define ID_Oral_input 0x00000

/* Parameters */
#define ID_BW 0x00007
#define ID_MW 0x00008
#define ID_V_dist 0x00009
#define ID_lnV_dist 0x0000a
#define ID_k_a 0x0000b
#define ID_lnk_a 0x0000c
#define ID_k_e 0x0000d
#define ID_lnk_e 0x0000e
#define ID_Absdose 0x0000f
#define ID_IngDose 0x00010
#define ID_Fgutabs 0x00011
#define ID_Period 0x00012
#define ID_Tlag 0x00013
#define ID_M_V_dist 0x00014
#define ID_M_lnV_dist 0x00015
#define ID_M_k_e 0x00016
#define ID_M_lnk_e 0x00017
#define ID_M_k_a 0x00018
#define ID_M_lnk_a 0x00019
#define ID_M_Fgutabs 0x0001a
#define ID_M_lnFgutabs 0x0001b
#define ID_V_V_dist 0x0001c
#define ID_V_lnV_dist 0x0001d
#define ID_V_k_e 0x0001e
#define ID_V_lnk_e 0x0001f
#define ID_V_k_a 0x00020
#define ID_V_lnk_a 0x00021
#define ID_V_Fgutabs 0x00022
#define ID_V_lnFgutabs 0x00023
#define ID_Ve_C_rest 0x00024
#define ID_Ve_lnC_rest 0x00025


/*----- Global Variables */

/* For export. Keep track of who we are. */
char szModelDescFilename[] = "1cpt.model";
char szModelSourceFilename[] = __FILE__;
char szModelGenAndVersion[] = "mod v5.6.6";

/* Externs */
extern BOOL vbModelReinitd;

/* Model Dimensions */
int vnStates = 2;
int vnOutputs = 4;
int vnModelVars = 6;
int vnInputs = 1;
int vnParms = 31;

/* States and Outputs*/
double vrgModelVars[6];

/* Inputs */
IFN vrgInputs[1];

/* Parameters */
double BW;
double MW;
double V_dist;
double lnV_dist;
double k_a;
double lnk_a;
double k_e;
double lnk_e;
double Absdose;
double IngDose;
double Fgutabs;
double Period;
double Tlag;
double M_V_dist;
double M_lnV_dist;
double M_k_e;
double M_lnk_e;
double M_k_a;
double M_lnk_a;
double M_Fgutabs;
double M_lnFgutabs;
double V_V_dist;
double V_lnV_dist;
double V_k_e;
double V_lnk_e;
double V_k_a;
double V_lnk_a;
double V_Fgutabs;
double V_lnFgutabs;
double Ve_C_rest;
double Ve_lnC_rest;

BOOL bDelays = 1;


/*----- Global Variable Map */

VMMAPSTRCT vrgvmGlo[] = {
  {"Q_rest", (PVOID) &vrgModelVars[ID_Q_rest], ID_STATE | ID_Q_rest},
  {"Q_elim", (PVOID) &vrgModelVars[ID_Q_elim], ID_STATE | ID_Q_elim},
  {"C_rest", (PVOID) &vrgModelVars[ID_C_rest], ID_OUTPUT | ID_C_rest},
  {"C_elim", (PVOID) &vrgModelVars[ID_C_elim], ID_OUTPUT | ID_C_elim},
  {"Q_total", (PVOID) &vrgModelVars[ID_Q_total], ID_OUTPUT | ID_Q_total},
  {"lnC_rest", (PVOID) &vrgModelVars[ID_lnC_rest], ID_OUTPUT | ID_lnC_rest},
  {"Oral_input", (PVOID) &vrgInputs[ID_Oral_input], ID_INPUT | ID_Oral_input},
  {"BW", (PVOID) &BW, ID_PARM | ID_BW},
  {"MW", (PVOID) &MW, ID_PARM | ID_MW},
  {"V_dist", (PVOID) &V_dist, ID_PARM | ID_V_dist},
  {"lnV_dist", (PVOID) &lnV_dist, ID_PARM | ID_lnV_dist},
  {"k_a", (PVOID) &k_a, ID_PARM | ID_k_a},
  {"lnk_a", (PVOID) &lnk_a, ID_PARM | ID_lnk_a},
  {"k_e", (PVOID) &k_e, ID_PARM | ID_k_e},
  {"lnk_e", (PVOID) &lnk_e, ID_PARM | ID_lnk_e},
  {"Absdose", (PVOID) &Absdose, ID_PARM | ID_Absdose},
  {"IngDose", (PVOID) &IngDose, ID_PARM | ID_IngDose},
  {"Fgutabs", (PVOID) &Fgutabs, ID_PARM | ID_Fgutabs},
  {"Period", (PVOID) &Period, ID_PARM | ID_Period},
  {"Tlag", (PVOID) &Tlag, ID_PARM | ID_Tlag},
  {"M_V_dist", (PVOID) &M_V_dist, ID_PARM | ID_M_V_dist},
  {"M_lnV_dist", (PVOID) &M_lnV_dist, ID_PARM | ID_M_lnV_dist},
  {"M_k_e", (PVOID) &M_k_e, ID_PARM | ID_M_k_e},
  {"M_lnk_e", (PVOID) &M_lnk_e, ID_PARM | ID_M_lnk_e},
  {"M_k_a", (PVOID) &M_k_a, ID_PARM | ID_M_k_a},
  {"M_lnk_a", (PVOID) &M_lnk_a, ID_PARM | ID_M_lnk_a},
  {"M_Fgutabs", (PVOID) &M_Fgutabs, ID_PARM | ID_M_Fgutabs},
  {"M_lnFgutabs", (PVOID) &M_lnFgutabs, ID_PARM | ID_M_lnFgutabs},
  {"V_V_dist", (PVOID) &V_V_dist, ID_PARM | ID_V_V_dist},
  {"V_lnV_dist", (PVOID) &V_lnV_dist, ID_PARM | ID_V_lnV_dist},
  {"V_k_e", (PVOID) &V_k_e, ID_PARM | ID_V_k_e},
  {"V_lnk_e", (PVOID) &V_lnk_e, ID_PARM | ID_V_lnk_e},
  {"V_k_a", (PVOID) &V_k_a, ID_PARM | ID_V_k_a},
  {"V_lnk_a", (PVOID) &V_lnk_a, ID_PARM | ID_V_lnk_a},
  {"V_Fgutabs", (PVOID) &V_Fgutabs, ID_PARM | ID_V_Fgutabs},
  {"V_lnFgutabs", (PVOID) &V_lnFgutabs, ID_PARM | ID_V_lnFgutabs},
  {"Ve_C_rest", (PVOID) &Ve_C_rest, ID_PARM | ID_Ve_C_rest},
  {"Ve_lnC_rest", (PVOID) &Ve_lnC_rest, ID_PARM | ID_Ve_lnC_rest},
  {"", NULL, 0} /* End flag */
};  /* vrgpvmGlo[] */


/*----- InitModel
   Should be called to initialize model variables at
   the beginning of experiment before reading
   variants from the simulation spec file.
*/

void InitModel(void)
{
  /* Initialize things in the order that they appear in
     model definition file so that dependencies are
     handled correctly. */

  vrgModelVars[ID_Q_rest] = 0.0;
  vrgModelVars[ID_Q_elim] = 0.0;
  vrgModelVars[ID_C_rest] = 0.0;
  vrgModelVars[ID_C_elim] = 0.0;
  vrgModelVars[ID_Q_total] = 0.0;
  vrgModelVars[ID_lnC_rest] = 0.0;
  vrgInputs[ID_Oral_input].iType = IFN_PEREXP;
  vrgInputs[ID_Oral_input].dTStartPeriod = 0;
  vrgInputs[ID_Oral_input].bOn = FALSE;
  vrgInputs[ID_Oral_input].dMag = 0.000000;
  vrgInputs[ID_Oral_input].dT0 = 0.000000;
  vrgInputs[ID_Oral_input].dTexp = 0.000000;
  vrgInputs[ID_Oral_input].dDecay = 0.000000;
  vrgInputs[ID_Oral_input].dTper = 0.000000;
  vrgInputs[ID_Oral_input].hMag = 0x4000f;
  vrgInputs[ID_Oral_input].hT0 = 0x40013;
  vrgInputs[ID_Oral_input].hTexp = 0;
  vrgInputs[ID_Oral_input].hDecay = 0x4000b;
  vrgInputs[ID_Oral_input].hTper = 0x40012;
  vrgInputs[ID_Oral_input].dVal = 0.0;
  vrgInputs[ID_Oral_input].nDoses = 0;
  BW = 70;
  MW = 100;
  V_dist = 1;
  lnV_dist = log(1.);
  k_a = 1.0;
  lnk_a = log(1.0);
  k_e = 0.1;
  lnk_e = log(.1);
  Absdose = 0;
  IngDose = 1.0;
  Fgutabs = 1.0;
  Period = 24.0;
  Tlag = 0.0;
  M_V_dist = 0;
  M_lnV_dist = 0;
  M_k_e = 0;
  M_lnk_e = 0;
  M_k_a = 0;
  M_lnk_a = 0;
  M_Fgutabs = 0;
  M_lnFgutabs = 0;
  V_V_dist = 0;
  V_lnV_dist = 0;
  V_k_e = 0;
  V_lnk_e = 0;
  V_k_a = 0;
  V_lnk_a = 0;
  V_Fgutabs = 0;
  V_lnFgutabs = 0;
  Ve_C_rest = 0;
  Ve_lnC_rest = 0;

  vbModelReinitd = TRUE;

} /* InitModel */


/*----- Dynamics section */

void CalcDeriv (double  rgModelVars[], double  rgDerivs[], PDOUBLE pdTime)
{

  CalcInputs (pdTime); /* Get new input vals */


  rgDerivs[ID_Q_rest] = k_a * vrgInputs[ID_Oral_input].dVal - k_e * rgModelVars[ID_Q_rest] ;

  rgDerivs[ID_Q_elim] = k_e * rgModelVars[ID_Q_rest] ;

} /* CalcDeriv */


/*----- Model scaling */

void ScaleModel (PDOUBLE pdTime)
{

  Absdose = IngDose * Fgutabs * BW ;

} /* ScaleModel */


/*----- Jacobian calculations */

void CalcJacob (PDOUBLE pdTime, double rgModelVars[],
                long column, double rgdJac[])
{

} /* CalcJacob */


/*----- Outputs calculations */

void CalcOutputs (double  rgModelVars[], double  rgDerivs[], PDOUBLE pdTime)
{

  rgModelVars[ID_C_rest] = rgModelVars[ID_Q_rest] / V_dist / MW * 1000 ;
  rgModelVars[ID_C_elim] = rgModelVars[ID_Q_elim] / MW * 1000 ;
  rgModelVars[ID_Q_total] = rgModelVars[ID_Q_rest] + rgModelVars[ID_Q_elim] ;

  rgModelVars[ID_lnC_rest] = ( rgModelVars[ID_C_rest] > 0 ? log ( rgModelVars[ID_C_rest] ) : -20. ) ;

}  /* CalcOutputs */


