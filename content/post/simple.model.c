/* simple.model.c
   ___________________________________________________

   Model File:  simple.model

   Date:  Mon Jul 02 21:23:57 2018

   Created by:  "C:/Users/lenovo/nanhung/content/post/mod/mod.exe v6.0.1"
    -- a model preprocessor by Don Maszle
   ___________________________________________________

   Copyright (c) 1993-2018 Free Software Foundation, Inc.

   Model calculations for compartmental model:

   3 States:
     y0 -> 0.0;
     y1 -> 0.0;
     y2 -> 0.0;

   1 Output:
     yout -> 0.0;

   0 Inputs:

   3 Parameters:
     k1 = 1;
     k2 = 1;
     k3 = 1;
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
#define ID_y0 0x00000
#define ID_y1 0x00001
#define ID_y2 0x00002
#define ID_yout 0x00003

/* Inputs */

/* Parameters */
#define ID_k1 0x00004
#define ID_k2 0x00005
#define ID_k3 0x00006


/*----- Global Variables */

/* For export. Keep track of who we are. */
char szModelDescFilename[] = "simple.model";
char szModelSourceFilename[] = __FILE__;
char szModelGenAndVersion[] = "C:/Users/lenovo/nanhung/content/post/mod/mod.exe v6.0.1";

/* Externs */
extern BOOL vbModelReinitd;

/* Model Dimensions */
int vnStates = 3;
int vnOutputs = 1;
int vnModelVars = 4;
int vnInputs = 0;
int vnParms = 3;

/* States and Outputs*/
double vrgModelVars[4];

/* Inputs */
IFN vrgInputs[1];

/* Parameters */
double k1;
double k2;
double k3;

BOOL bDelays = 0;


/*----- Global Variable Map */

VMMAPSTRCT vrgvmGlo[] = {
  {"y0", (PVOID) &vrgModelVars[ID_y0], ID_STATE | ID_y0},
  {"y1", (PVOID) &vrgModelVars[ID_y1], ID_STATE | ID_y1},
  {"y2", (PVOID) &vrgModelVars[ID_y2], ID_STATE | ID_y2},
  {"yout", (PVOID) &vrgModelVars[ID_yout], ID_OUTPUT | ID_yout},
  {"k1", (PVOID) &k1, ID_PARM | ID_k1},
  {"k2", (PVOID) &k2, ID_PARM | ID_k2},
  {"k3", (PVOID) &k3, ID_PARM | ID_k3},
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

  vrgModelVars[ID_y0] = 0.0;
  vrgModelVars[ID_y1] = 0.0;
  vrgModelVars[ID_y2] = 0.0;
  vrgModelVars[ID_yout] = 0.0;
  k1 = 1;
  k2 = 1;
  k3 = 1;

  vbModelReinitd = TRUE;

} /* InitModel */


/*----- Dynamics section */

void CalcDeriv (double  rgModelVars[], double  rgDerivs[], PDOUBLE pdTime)
{

  CalcInputs (pdTime); /* Get new input vals */


  rgDerivs[ID_y0] = - k1 * rgModelVars[ID_y0] + k2 * rgModelVars[ID_y1] * rgModelVars[ID_y2] ;

  rgDerivs[ID_y2] = k3 * rgModelVars[ID_y1] * rgModelVars[ID_y1] ;

  rgDerivs[ID_y1] = - rgDerivs[ID_y0] - rgDerivs[ID_y2] ;

  rgModelVars[ID_yout] = rgModelVars[ID_y0] + rgModelVars[ID_y1] + rgModelVars[ID_y2] ;

} /* CalcDeriv */


/*----- Model scaling */

void ScaleModel (PDOUBLE pdTime)
{

} /* ScaleModel */


/*----- Jacobian calculations */

void CalcJacob (PDOUBLE pdTime, double rgModelVars[],
                long column, double rgdJac[])
{

} /* CalcJacob */


/*----- Outputs calculations */

void CalcOutputs (double  rgModelVars[], double  rgDerivs[], PDOUBLE pdTime)
{

}  /* CalcOutputs */


