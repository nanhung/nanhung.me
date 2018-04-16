initParms <- function(newParms = NULL) {
  parms <- c(
    PPM_per_mg_per_l = 0.0,
    mg_per_l_per_PPM = 0.0,
    tau = 1,
    InhMag = 0.0,
    Period = 0.0,
    Exposure = 0.0,
    IngDose = 0.0,
    LeanBodyWt = 55,
    Pct_M_fat = .16,
    Pct_LM_liv = .03,
    Pct_LM_wp = .17,
    Pct_LM_pp = .70,
    Pct_Flow_fat = .09,
    Pct_Flow_liv = .34,
    Pct_Flow_wp = .50,
    Pct_Flow_pp = .07,
    PC_fat = 144,
    PC_liv = 4.6,
    PC_wp = 8.7,
    PC_pp = 1.4,
    PC_art = 12.0,
    Flow_pul = 8.0,
    Vent_Perf = 1.14,
    sc_Vmax = .0026,
    Km = 1.0,
    BodyWt = 0.0,
    V_fat = 0.0,
    V_liv = 0.0,
    V_wp = 0.0,
    V_pp = 0.0,
    Flow_fat = 0,
    Flow_liv = 0,
    Flow_wp = 0,
    Flow_pp = 0,
    Flow_tot = 0,
    Flow_alv = 0,
    Vmax = 0
  )

  if (!is.null(newParms)) {
    if (!all(names(newParms) %in% c(names(parms)))) {
      stop("illegal parameter name")
    }
    parms[names(newParms)] <- newParms
  }

  parms <- within(as.list(parms), {
    PPM_per_mg_per_l = 72.0 / 0.488;
    mg_per_l_per_PPM = 1/PPM_per_mg_per_l;
    BodyWt = LeanBodyWt / (1 - Pct_M_fat);
    V_fat = Pct_M_fat  * BodyWt/0.92;
    V_liv = Pct_LM_liv * LeanBodyWt;
    V_wp = Pct_LM_wp  * LeanBodyWt;
    V_pp = 0.9 * LeanBodyWt - V_liv - V_wp;
  })
  out <- .C("getParms",  as.double(parms),
            out=double(length(parms)),
            as.integer(length(parms)))$out
  names(out) <- names(parms)
  out
}

Outputs <- c(
    "C_liv",
    "old_Q_liv",
    "C_alv",
    "C_exh",
    "C_ven",
    "Pct_metabolized",
    "C_exh_ug",
    "Q_tot"
)

initStates <- function(parms, newStates = NULL) {
  Y <- c(
    Q_fat = 0.0,
    Q_wp = 0.0,
    Q_pp = 0.0,
    Q_liv = 0.0,
    Q_exh = 0.0,
    Q_met = 0.0
  )

  if (!is.null(newStates)) {
    if (!all(names(newStates) %in% c(names(Y)))) {
      stop("illegal state variable name in newStates")
    }
    Y[names(newStates)] <- newStates
  }

.C("initState", as.double(Y));
Y
}
