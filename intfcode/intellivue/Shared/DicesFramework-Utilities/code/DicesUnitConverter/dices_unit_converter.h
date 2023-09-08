#ifndef DICES_UNIT_CONVERTER_H_
#define DICES_UNIT_CONVERTER_H_

#include <typeinfo>
#include <string>
#include "../../Nomenclature/dimension_util.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include "units.hpp"

/*****************************************************************************/

// IEEE 11073:10101 Required Units
namespace units
{
namespace units
{
struct part; // See parts per thousand, etc
struct ph;
struct dB;
struct drop;
struct beat;
struct pulse;
struct breath;
struct cough;
struct sigh;
struct RBC; // Red blood cell count
struct cell; // White blood cell count
struct PCV; // Packed Cell Volume
struct PVC; // Premature Ventricular Contractions
struct count;
struct complex;

// These three are amounts of things, but their relationships to mole and each
// other are substance-dependent, so they CANNOT be converted to each other
// without more context.
struct osmole;
struct eq;
struct iu;

typedef compose<compose<g, cm>, pow<s, -2>> dyn;
typedef scale<kilo<Pa>::type, 1, 100> bar;
typedef scale<Pa, 10000, 1333224> mmHg;
typedef scale<Pa, 10000, 980665> cmH2O;
typedef scale<zepto<J>::type, 10000, 1602176> eV;
typedef scale<J, 1000, 4184> cal;

template <typename TxType, const long TxX>
struct Tx
{
};

template<typename TxType> struct Tx<TxType, MDC_DIM_DIMLESS>
{
  typedef value<TxType, unit> xType;
  typedef value<TxType, unit> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PERCENT>
{
  typedef value<TxType, percent> xType;
  typedef value<TxType, percent> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PARTS_PER_THOUSAND>
// Also MDC_DIM_PARTS_PER_10_TO_MINUS_3
{
  typedef value<TxType, compose<part, pow<kilo<unit>::type, -1>>> xType;
  typedef value<TxType, compose<part, pow<unit, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PARTS_PER_MILLION>
// Also MDC_DIM_PARTS_PER_10_TO_MINUS_6
{
  typedef value<TxType, compose<part, pow<mega<unit>::type, -1>>> xType;
  typedef value<TxType, compose<part, pow<unit, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PPMD>
// Also MDC_DIM_PARTS_PER_10_TO_MINUS_9
{
  typedef value<TxType, compose<part, pow<giga<unit>::type, -1>>> xType;
  typedef value<TxType, compose<part, pow<unit, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PARTS_PER_BILLION>
// Also MDC_DIM_PARTS_PER_10_TO_MINUS_12
{
  typedef value<TxType, compose<part, pow<tera<unit>::type, -1>>> xType;
  typedef value<TxType, compose<part, pow<unit, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PARTS_PER_TRILLION>
// Also MDC_DIM_PARTS_PER_10_TO_MINUS_18
{
  typedef value<TxType, compose<part, pow<exa<unit>::type, -1>>> xType;
  typedef value<TxType, compose<part, pow<unit, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_ANG_DEG>
{
  typedef value<TxType, degree> xType;
  typedef value<TxType, rad> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_ANG_RAD>
{
  typedef value<TxType, rad> xType;
  typedef value<TxType, rad> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_G>
{
  typedef value<TxType, compose<g, pow<g, -1>>> xType;
  typedef value<TxType, compose<g, pow<g, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_G_PER_KG>
{
  typedef value<TxType, compose<g, pow<kg, -1>>> xType;
  typedef value<TxType, compose<g, pow<g, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_MOLE_PER_MOLE>
{
  typedef value<TxType, compose<mol, pow<mol, -1>>> xType;
  typedef value<TxType, compose<mol, pow<mol, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_L>
{
  typedef value<TxType, compose<liter, pow<liter, -1>>> xType;
  typedef value<TxType, compose<liter, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_CUBIC_X_M_PER_M_CUBE>
{
  typedef value<TxType, compose<m3, pow<m3, -1>>> xType;
  typedef value<TxType, compose<m3, pow<m3, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_CUBIC_X_M_PER_CM_CUBE>
{
  typedef value<TxType, compose<m3, pow<cm3, -1>>> xType;
  typedef value<TxType, compose<m3, pow<m3, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PH>
{
  typedef value<TxType, ph> xType;
  typedef value<TxType, ph> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_DROP>
{
  typedef value<TxType, drop> xType;
  typedef value<TxType, drop> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_RBC>
{
  typedef value<TxType, RBC> xType;
  typedef value<TxType, RBC> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_BEAT>
{
  typedef value<TxType, beat> xType;
  typedef value<TxType, beat> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_BREATH>
{
  typedef value<TxType, breath> xType;
  typedef value<TxType, breath> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_CELL>
{
  typedef value<TxType, cell> xType;
  typedef value<TxType, cell> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_COUGH>
{
  typedef value<TxType, cough> xType;
  typedef value<TxType, cough> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_SIGH>
{
  typedef value<TxType, sigh> xType;
  typedef value<TxType, sigh> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PCT_PCV>
{
  typedef value<TxType, PCV> xType;
  typedef value<TxType, PCV> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_M>
{
  typedef value<TxType, m> xType;
  typedef value<TxType, m> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_YARD>
{
  typedef value<TxType, yard> xType;
  typedef value<TxType, m> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_FOOT>
{
  typedef value<TxType, foot> xType;
  typedef value<TxType, m> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_INCH>
{
  typedef value<TxType, inch> xType;
  typedef value<TxType, m> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_M_SQ>
{
  typedef value<TxType, compose<liter, pow<m2, -1>>> xType;
  typedef value<TxType, m> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PER_X_M>
{
  typedef value<TxType, pow<m, -1>> xType;
  typedef value<TxType, pow<m, -1>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_SQ_X_M>
{
  typedef value<TxType, m2> xType;
  typedef value<TxType, m2> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_SQ_X_INCH>
{
  typedef value<TxType, inch2> xType;
  typedef value<TxType, m2> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PER_SQ_X_M>
{
  typedef value<TxType, pow<m2, -1>> xType;
  typedef value<TxType, pow<m2, -1>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_CUBIC_X_M>
{
  typedef value<TxType, m3> xType;
  typedef value<TxType, liter> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L>
{
  typedef value<TxType, liter> xType;
  typedef value<TxType, liter> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_BREATH>
{
  typedef value<TxType, compose<liter, pow<breath, -1>>> xType;
  typedef value<TxType, compose<liter, pow<breath, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PER_CUBIC_X_M>
{
  typedef value<TxType, pow<m3, -1>> xType;
  typedef value<TxType, pow<liter, -1>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PER_X_L>
{
  typedef value<TxType, pow<liter, -1>> xType;
  typedef value<TxType, pow<liter, -1>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G>
{
  typedef value<TxType, g> xType;
  typedef value<TxType, kg> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_LB>
// Also MDC_DIM_LIB
{
  typedef value<TxType, lb> xType;
  typedef value<TxType, kg> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_OZ>
{
  typedef value<TxType, oz> xType;
  typedef value<TxType, kg> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PER_X_G>
// Also MDC_DIM_PER_GRAM
{
  typedef value<TxType, pow<g, -1>> xType;
  typedef value<TxType, pow<kg, -1>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_M>
{
  typedef value<TxType, compose<g, m>> xType;
  typedef value<TxType, compose<kg, m>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_M_PER_M_SQ>
{
  typedef value<TxType, compose<compose<g, m>, pow<m2, -1>>> xType;
  typedef value<TxType, compose<kg, pow<m, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_M_SQ>
{
  typedef value<TxType, compose<g, m2>> xType;
  typedef value<TxType, compose<kg, m2>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_KG_PER_M_SQ>
{
  typedef value<TxType, compose<kg, pow<m2, -1>>> xType;
  typedef value<TxType, compose<kg, pow<m2, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_M_CUBE>
{
  typedef value<TxType, compose<g, pow<m3, -1>>> xType;
  typedef value<TxType, compose<kg, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_CM_CUBE>
{
  typedef value<TxType, compose<g, pow<cm3, -1>>> xType;
  typedef value<TxType, compose<kg, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_L>
{
  typedef value<TxType, compose<g, pow<liter, -1>>> xType;
  typedef value<TxType, compose<kg, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_CL>
{
  typedef value<TxType, compose<g, pow<cl, -1>>> xType;
  typedef value<TxType, compose<kg, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_DL>
{
  typedef value<TxType, compose<g, pow<dl, -1>>> xType;
  typedef value<TxType, compose<kg, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_ML>
{
  typedef value<TxType, compose<g, pow<ml, -1>>> xType;
  typedef value<TxType, compose<kg, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_SEC>
// Also MDC_DIM_SEC
{
  typedef value<TxType, s> xType;
  typedef value<TxType, s> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_MIN>
{
  typedef value<TxType, minute> xType;
  typedef value<TxType, s> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_HR>
{
  typedef value<TxType, hour> xType;
  typedef value<TxType, s> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_DAY>
{
  typedef value<TxType, day> xType;
  typedef value<TxType, s> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_WEEKS>
{
  typedef value<TxType, week> xType;
  typedef value<TxType, s> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_MON>
{
  typedef value<TxType, month> xType;
  typedef value<TxType, month> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_YR>
{
  typedef value<TxType, year> xType;
  typedef value<TxType, month> baseType;
};

// MDC_DIM_TOD and MDC_DIM_DATE are unusual cases, in that they represent
// specific times with respect to some constant value.  I could forsee being
// able to incorporate timezones and epochs into such a system; 11073 does not
// do this and currently neither has anything it converts to.

template<typename TxType> struct Tx<TxType, MDC_DIM_PER_X_SEC>
{
  typedef value<TxType, pow<s, -1>> xType;
  typedef value<TxType, pow<s, -1>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_HZ>
{
  typedef value<TxType, Hz> xType;
  typedef value<TxType, pow<s, -1>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PER_MIN>
{
  typedef value<TxType, pow<minute, -1>> xType;
  typedef value<TxType, pow<s, -1>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PER_HR>
{
  typedef value<TxType, pow<hour, -1>> xType;
  typedef value<TxType, pow<s, -1>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PER_DAY>
{
  typedef value<TxType, pow<day, -1>> xType;
  typedef value<TxType, pow<s, -1>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PER_WK>
{
  typedef value<TxType, pow<week, -1>> xType;
  typedef value<TxType, pow<s, -1>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PER_MO>
{
  typedef value<TxType, pow<month, -1>> xType;
  typedef value<TxType, pow<month, -1>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PER_YR>
{
  typedef value<TxType, pow<year, -1>> xType;
  typedef value<TxType, pow<month, -1>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_BEAT_PER_MIN>
{
  typedef value<TxType, compose<beat, pow<minute, -1>>> xType;
  typedef value<TxType, compose<beat, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PULS_PER_MIN>
{
  typedef value<TxType, compose<pulse, pow<minute, -1>>> xType;
  typedef value<TxType, compose<pulse, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_RESP_PER_MIN>
{
  typedef value<TxType, compose<breath, pow<minute, -1>>> xType;
  typedef value<TxType, compose<breath, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_M_PER_SEC>
{
  typedef value<TxType, meters_per_second> xType;
  typedef value<TxType, meters_per_second> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_M_SQ>
{
  typedef value<TxType, compose<compose<liter, pow<minute, -1>>, pow<m2, -1>>> xType;
  typedef value<TxType, meters_per_second> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_SQ_X_M_PER_SEC>
{
  typedef value<TxType, compose<m2, pow<s, -1>>> xType;
  typedef value<TxType, compose<m2, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_CUBIC_X_M_PER_SEC>
{
  typedef value<TxType, compose<m3, pow<s, -1>>> xType;
  typedef value<TxType, compose<liter, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_CUBIC_X_M_PER_MIN>
{
  typedef value<TxType, compose<m3, pow<minute, -1>>> xType;
  typedef value<TxType, compose<liter, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_CUBIC_X_M_PER_HR>
{
  typedef value<TxType, compose<m3, pow<hour, -1>>> xType;
  typedef value<TxType, compose<liter, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_CUBIC_X_M_PER_DAY>
{
  typedef value<TxType, compose<m3, pow<day, -1>>> xType;
  typedef value<TxType, compose<liter, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_SEC>
{
  typedef value<TxType, compose<liter, pow<s, -1>>> xType;
  typedef value<TxType, compose<liter, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_MIN>
{
  typedef value<TxType, compose<liter, pow<minute, -1>>> xType;
  typedef value<TxType, compose<liter, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_HR>
{
  typedef value<TxType, compose<liter, pow<hour, -1>>> xType;
  typedef value<TxType, compose<liter, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_DAY>
{
  typedef value<TxType, compose<liter, pow<day, -1>>> xType;
  typedef value<TxType, compose<liter, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_KG>
{
  typedef value<TxType, compose<liter, pow<kg, -1>>> xType;
  typedef value<TxType, compose<liter, pow<kg, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_CUBIC_X_L_PER_KG>
{
  // NOTE: 11073:10101 made this code a typo, should be MDC_DIM_CUBIC_X_M_PER_KG
  typedef value<TxType, compose<m3, pow<kg, -1>>> xType;
  typedef value<TxType, compose<liter, pow<kg, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_M_PER_PASCAL_SEC>
{
  typedef value<TxType, compose<compose<m, pow<Pa, -1>>, s>> xType;
  typedef value<TxType, compose<compose<m, pow<Pa, -1>>, s>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_ML_HG>
{
  // NOTE: 11073:10101 made this code a typo, should be MDC_DIM_X_L_PER_MIN_PER_MM_HG
  typedef value<TxType, compose<compose<liter, pow<minute, -1>>, pow<mmHg, -1>>> xType;
  typedef value<TxType, compose<compose<liter, pow<s, -1>>, pow<Pa, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_SEC>
{
  typedef value<TxType, compose<g, pow<s, -1>>> xType;
  typedef value<TxType, compose<kg, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_MIN>
{
  typedef value<TxType, compose<g, pow<minute, -1>>> xType;
  typedef value<TxType, compose<kg, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_HR>
{
  typedef value<TxType, compose<g, pow<hour, -1>>> xType;
  typedef value<TxType, compose<kg, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_DAY>
{
  typedef value<TxType, compose<g, pow<day, -1>>> xType;
  typedef value<TxType, compose<kg, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_KG_PER_SEC>
{
  typedef value<TxType, compose<compose<g, pow<kg, -1>>, pow<s, -1>>> xType;
  typedef value<TxType, compose<compose<kg, pow<kg, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_KG_PER_MIN>
{
  typedef value<TxType, compose<compose<g, pow<kg, -1>>, pow<minute, -1>>> xType;
  typedef value<TxType, compose<compose<kg, pow<kg, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_KG_PER_HR>
{
  typedef value<TxType, compose<compose<g, pow<kg, -1>>, pow<hour, -1>>> xType;
  typedef value<TxType, compose<compose<kg, pow<kg, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_KG_PER_DAY>
{
  typedef value<TxType, compose<compose<g, pow<kg, -1>>, pow<day, -1>>> xType;
  typedef value<TxType, compose<compose<kg, pow<kg, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_L_PER_SEC>
{
  typedef value<TxType, compose<compose<g, pow<liter, -1>>, pow<s, -1>>> xType;
  typedef value<TxType, compose<compose<kg, pow<liter, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_L_PER_MIN>
{
  typedef value<TxType, compose<compose<g, pow<liter, -1>>, pow<minute, -1>>> xType;
  typedef value<TxType, compose<compose<kg, pow<liter, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_L_PER_HR>
{
  typedef value<TxType, compose<compose<g, pow<liter, -1>>, pow<hour, -1>>> xType;
  typedef value<TxType, compose<compose<kg, pow<liter, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_L_PER_DAY>
{
  typedef value<TxType, compose<compose<g, pow<liter, -1>>, pow<day, -1>>> xType;
  typedef value<TxType, compose<compose<kg, pow<liter, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_M_PER_SEC>
{
  typedef value<TxType, compose<compose<g, pow<m, -1>>, pow<s, -1>>> xType;
  typedef value<TxType, compose<compose<kg, pow<m, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_M_PER_SEC>
{
  typedef value<TxType, compose<compose<g, m>, pow<s, -1>>> xType;
  typedef value<TxType, compose<compose<kg, m>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_NEWTON_SEC>
{
  typedef value<TxType, compose<N, s>> xType;
  typedef value<TxType, compose<compose<kg, m>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_NEWTON>
{
  typedef value<TxType, N> xType;
  typedef value<TxType, N> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_DYNE>
{
  typedef value<TxType, dyn> xType;
  typedef value<TxType, N> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_PASCAL>
{
  typedef value<TxType, Pa> xType;
  typedef value<TxType, Pa> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_MMHG>
{
  typedef value<TxType, mmHg> xType;
  typedef value<TxType, Pa> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_CM_H2O>
{
  typedef value<TxType, cmH2O> xType;
  typedef value<TxType, Pa> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_BAR>
{
  typedef value<TxType, bar> xType;
  typedef value<TxType, Pa> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_JOULES>
{
  typedef value<TxType, J> xType;
  typedef value<TxType, J> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_EVOLT>
{
  typedef value<TxType, eV> xType;
  typedef value<TxType, J> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_WATT>
{
  typedef value<TxType, W> xType;
  typedef value<TxType, W> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_PASCAL_SEC_PER_M_CUBE>
{
  typedef value<TxType, compose<compose<Pa, s>, pow<m3, -1>>> xType;
  typedef value<TxType, compose<compose<Pa, s>, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_PASCAL_SEC_PER_L>
{
  typedef value<TxType, compose<compose<Pa, s>, pow<liter, -1>>> xType;
  typedef value<TxType, compose<compose<Pa, s>, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_DYNE_PER_SEC_PER_CM5>
// TODO: Currently believed to be a typo, intended MDC_DIM_X_DYNE_SEC_PER_CM5.
{
  typedef value<TxType, compose<compose<dyn, s>, pow<cm, -5>>> xType;
  typedef value<TxType, compose<compose<Pa, s>, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_AMPS>
{
  typedef value<TxType, A> xType;
  typedef value<TxType, A> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_COULOMB>
{
  typedef value<TxType, C> xType;
  typedef value<TxType, C> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_AMPS_PER_M>
{
  typedef value<TxType, compose<A, pow<m, -1>>> xType;
  typedef value<TxType, compose<A, pow<m, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_VOLT>
{
  typedef value<TxType, V> xType;
  typedef value<TxType, V> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_OHM>
{
  typedef value<TxType, Ohm> xType;
  typedef value<TxType, Ohm> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_OHM_M>
{
  typedef value<TxType, compose<Ohm, m>> xType;
  typedef value<TxType, compose<Ohm, m>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_FARAD>
{
  typedef value<TxType, F> xType;
  typedef value<TxType, F> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_KELVIN>
{
  typedef value<TxType, K> xType;
  typedef value<TxType, K> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_FAHR>
{
  typedef value<TxType, Fahrenheit> xType;
  typedef value<TxType, K> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_KELVIN_PER_X_WATT>
{
  typedef value<TxType, compose<K, pow<W, -1>>> xType;
  typedef value<TxType, compose<K, pow<W, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_CANDELA>
{
  typedef value<TxType, cd> xType;
  typedef value<TxType, cd> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_OSM>
{
  typedef value<TxType, osmole> xType;
  typedef value<TxType, osmole> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_MOLE>
{
  typedef value<TxType, mol> xType;
  typedef value<TxType, mol> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_EQUIV>
{
  typedef value<TxType, eq> xType;
  typedef value<TxType, eq> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_OSM_PER_L>
{
  typedef value<TxType, compose<osmole, pow<liter, -1>>> xType;
  typedef value<TxType, compose<osmole, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_MOLE_PER_CM_CUBE>
{
  typedef value<TxType, compose<mol, pow<cm3, -1>>> xType;
  typedef value<TxType, compose<mol, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_MOLE_PER_M_CUBE>
{
  typedef value<TxType, compose<mol, pow<m3, -1>>> xType;
  typedef value<TxType, compose<mol, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_MOLE_PER_L>
{
  typedef value<TxType, compose<mol, pow<liter, -1>>> xType;
  typedef value<TxType, compose<mol, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_MOLE_PER_ML>
{
  typedef value<TxType, compose<mol, pow<ml, -1>>> xType;
  typedef value<TxType, compose<mol, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_EQUIV_PER_CM_CUBE>
{
  typedef value<TxType, compose<eq, pow<cm3, -1>>> xType;
  typedef value<TxType, compose<eq, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_EQUIV_PER_M_CUBE>
{
  typedef value<TxType, compose<eq, pow<m3, -1>>> xType;
  typedef value<TxType, compose<eq, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_EQUIV_PER_L>
{
  typedef value<TxType, compose<eq, pow<liter, -1>>> xType;
  typedef value<TxType, compose<eq, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_EQUIV_PER_ML>
{
  typedef value<TxType, compose<eq, pow<ml, -1>>> xType;
  typedef value<TxType, compose<eq, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_OSM_PER_KG>
{
  typedef value<TxType, compose<osmole, pow<kg, -1>>> xType;
  typedef value<TxType, compose<osmole, pow<kg, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_MOLE_PER_KG>
{
  typedef value<TxType, compose<mol, pow<kg, -1>>> xType;
  typedef value<TxType, compose<mol, pow<kg, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_MOLE_PER_SEC>
{
  typedef value<TxType, compose<mol, pow<s, -1>>> xType;
  typedef value<TxType, compose<mol, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_MOLE_PER_MIN>
{
  typedef value<TxType, compose<mol, pow<minute, -1>>> xType;
  typedef value<TxType, compose<mol, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_MOLE_PER_HR>
{
  typedef value<TxType, compose<mol, pow<hour, -1>>> xType;
  typedef value<TxType, compose<mol, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_MOLE_PER_DAY>
{
  typedef value<TxType, compose<mol, pow<day, -1>>> xType;
  typedef value<TxType, compose<mol, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_EQUIV_PER_SEC>
{
  typedef value<TxType, compose<eq, pow<s, -1>>> xType;
  typedef value<TxType, compose<eq, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_EQUIV_PER_MIN>
{
  typedef value<TxType, compose<eq, pow<minute, -1>>> xType;
  typedef value<TxType, compose<eq, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_EQUIV_PER_HR>
{
  typedef value<TxType, compose<eq, pow<hour, -1>>> xType;
  typedef value<TxType, compose<eq, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_EQUIV_PER_DAY>
{
  typedef value<TxType, compose<eq, pow<day, -1>>> xType;
  typedef value<TxType, compose<eq, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_SEC>
{
  typedef value<TxType, compose<compose<mol, pow<kg, -1>>, pow<s, -1>>> xType;
  typedef value<TxType, compose<compose<mol, pow<kg, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_MIN>
{
  typedef value<TxType, compose<compose<mol, pow<kg, -1>>, pow<minute, -1>>> xType;
  typedef value<TxType, compose<compose<mol, pow<kg, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_HR>
{
  typedef value<TxType, compose<compose<mol, pow<kg, -1>>, pow<hour, -1>>> xType;
  typedef value<TxType, compose<compose<mol, pow<kg, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_DAY>
{
  typedef value<TxType, compose<compose<mol, pow<kg, -1>>, pow<day, -1>>> xType;
  typedef value<TxType, compose<compose<mol, pow<kg, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_SEC>
{
  typedef value<TxType, compose<compose<eq, pow<kg, -1>>, pow<s, -1>>> xType;
  typedef value<TxType, compose<compose<eq, pow<kg, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_MIN>
{
  typedef value<TxType, compose<compose<eq, pow<kg, -1>>, pow<minute, -1>>> xType;
  typedef value<TxType, compose<compose<eq, pow<kg, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_HR>
{
  typedef value<TxType, compose<compose<eq, pow<kg, -1>>, pow<hour, -1>>> xType;
  typedef value<TxType, compose<compose<eq, pow<kg, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_DAY>
{
  typedef value<TxType, compose<compose<eq, pow<kg, -1>>, pow<day, -1>>> xType;
  typedef value<TxType, compose<compose<eq, pow<kg, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_INTL_UNIT>
{
  typedef value<TxType, iu> xType;
  typedef value<TxType, iu> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_CM_CUBE>
{
  typedef value<TxType, compose<iu, pow<cm3, -1>>> xType;
  typedef value<TxType, compose<iu, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_M_CUBE>
{
  typedef value<TxType, compose<iu, pow<m3, -1>>> xType;
  typedef value<TxType, compose<iu, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_L>
{
  typedef value<TxType, compose<iu, pow<liter, -1>>> xType;
  typedef value<TxType, compose<iu, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_ML>
{
  typedef value<TxType, compose<iu, pow<ml, -1>>> xType;
  typedef value<TxType, compose<iu, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_SEC>
{
  typedef value<TxType, compose<iu, pow<s, -1>>> xType;
  typedef value<TxType, compose<iu, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_MIN>
{
  typedef value<TxType, compose<iu, pow<minute, -1>>> xType;
  typedef value<TxType, compose<iu, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_HR>
{
  typedef value<TxType, compose<iu, pow<hour, -1>>> xType;
  typedef value<TxType, compose<iu, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_DAY>
{
  typedef value<TxType, compose<iu, pow<day, -1>>> xType;
  typedef value<TxType, compose<iu, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_SEC>
{
  typedef value<TxType, compose<compose<iu, pow<kg, -1>>, pow<s, -1>>> xType;
  typedef value<TxType, compose<compose<iu, pow<kg, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_MIN>
{
  typedef value<TxType, compose<compose<iu, pow<kg, -1>>, pow<minute, -1>>> xType;
  typedef value<TxType, compose<compose<iu, pow<kg, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_HR>
{
  typedef value<TxType, compose<compose<iu, pow<kg, -1>>, pow<hour, -1>>> xType;
  typedef value<TxType, compose<compose<iu, pow<kg, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_DAY>
{
  typedef value<TxType, compose<compose<iu, pow<kg, -1>>, pow<day, -1>>> xType;
  typedef value<TxType, compose<compose<iu, pow<kg, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_CM_H2O>
{
  typedef value<TxType, compose<liter, pow<cmH2O, -1>>> xType;
  typedef value<TxType, compose<liter, pow<Pa, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_CM_H2O_PER_L_PER_SEC>
{
  typedef value<TxType, compose<compose<cmH2O, pow<liter, -1>>, pow<s, -1>>> xType;
  typedef value<TxType, compose<compose<Pa, pow<liter, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_SQ_PER_SEC>
{
  typedef value<TxType, compose<pow<liter, 2>, pow<s, -1>>> xType;
  typedef value<TxType, compose<pow<liter, 2>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_CM_H2O_PER_PERCENT>
{
  typedef value<TxType, compose<cmH2O, pow<percent, -1>>> xType;
  typedef value<TxType, Pa> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_DYNE_SEC_PER_M_SQ_PER_CM_5>
// Also MDC_DIM_DS_PER_M_SQ_PER_CM5
{
  typedef value<TxType, compose<compose<compose<dyn, s>, pow<m2, -1>>, pow<cm, -5>>> xType;
  typedef value<TxType, compose<compose<compose<Pa, s>, pow<m2, -1>>, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_DEGC>
{
  typedef value<TxType, Celsius> xType;
  typedef value<TxType, K> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_AMP_HR>
{
  typedef value<TxType, compose<A, hour>> xType;
  typedef value<TxType, compose<A, s>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_BEAT>
{
  typedef value<TxType, compose<liter, pow<beat, -1>>> xType;
  typedef value<TxType, compose<liter, pow<beat, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_CM_H2O_PER_L>
{
  typedef value<TxType, compose<cmH2O, pow<liter, -1>>> xType;
  typedef value<TxType, compose<Pa, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_MM_HG_PER_PERCENT>
{
  typedef value<TxType, compose<mmHg, pow<percent, -1>>> xType;
  typedef value<TxType, Pa> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_PA_PER_PERCENT>
{
  typedef value<TxType, compose<Pa, pow<percent, -1>>> xType;
  typedef value<TxType, Pa> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_VOL_PERCENT>
{
  typedef value<TxType, compose<compose<percent, liter>, pow<liter, -1>>> xType;
  typedef value<TxType, percent> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_MM_HG>
{
  typedef value<TxType, compose<liter, pow<mmHg, -1>>> xType;
  typedef value<TxType, compose<liter, pow<Pa, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_MM_PA>
{
  typedef value<TxType, compose<liter, pow<Pa, -1>>> xType;
  typedef value<TxType, compose<liter, pow<Pa, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_MM_HG_PER_X_L>
{
  typedef value<TxType, compose<mmHg, pow<liter, -1>>> xType;
  typedef value<TxType, compose<Pa, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PA_PER_X_L>
{
  typedef value<TxType, compose<Pa, pow<liter, -1>>> xType;
  typedef value<TxType, compose<Pa, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_DL>
{
  typedef value<TxType, compose<liter, pow<dl, -1>>> xType;
  typedef value<TxType, compose<liter, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_DECIBEL>
{
  typedef value<TxType, dB> xType;
  typedef value<TxType, dB> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_G_PER_MG>
// Also MDC_DIM_X_G_PER_MILLI_G
{
  typedef value<TxType, compose<g, pow<mg, -1>>> xType;
  typedef value<TxType, compose<kg, pow<kg, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_BEAT_PER_MIN_PER_X_L>
{
  typedef value<TxType, compose<compose<beat, pow<minute, -1>>, pow<liter, -1>>> xType;
  typedef value<TxType, compose<compose<beat, pow<s, -1>>, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PER_X_L_PER_MIN>
// Also MDC_DIM_PER_L_PER_MIN
{
  typedef value<TxType, compose<pow<liter, -1>, pow<minute, -1>>> xType;
  typedef value<TxType, compose<pow<liter, -1>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_M_PER_MIN>
{
  typedef value<TxType, compose<m, pow<minute, -1>>> xType;
  typedef value<TxType, meters_per_second> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PSI>
{
  typedef value<TxType, psi> xType;
  typedef value<TxType, Pa> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_M_PER_SEC_SQ>
{
  typedef value<TxType, compose<m, pow<s, -2>>> xType;
  typedef value<TxType, compose<m, pow<s, -2>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_RAD_PER_SEC_SQ>
{
  typedef value<TxType, compose<rad, pow<s, -2>>> xType;
  typedef value<TxType, compose<rad, pow<s, -2>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_RAD_PER_SEC>
{
  typedef value<TxType, compose<rad, pow<s, -1>>> xType;
  typedef value<TxType, compose<rad, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_LUMEN_PER_M_SQ>
{
  typedef value<TxType, compose<lm, pow<m, -2>>> xType;
  typedef value<TxType, compose<lm, pow<m, -2>>> baseType;
};

// Intellivue codes
template<typename TxType> struct Tx<TxType, MDC_DIM_COMPLEX>
{
  typedef value<TxType, complex> xType;
  typedef value<TxType, complex> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_COUNT>
{
  typedef value<TxType, count> xType;
  typedef value<TxType, count> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PART>
{
  typedef value<TxType, part> xType;
  typedef value<TxType, part> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PULS>
{
  typedef value<TxType, pulse> xType;
  typedef value<TxType, pulse> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_UV_PP>
{
  typedef value<TxType, micro<V>::type> xType;
  typedef value<TxType, V> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_UV_SQ>
{
  typedef value<TxType, pow<micro<V>::type, 2>> xType;
  typedef value<TxType, pow<V, 2>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_LUMEN>
{
  typedef value<TxType, lm> xType;
  typedef value<TxType, lm> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_LB_PER_INCH_SQ>
{
  // WARNING: Currently lb is treated as a mass and not a weight.  This seems
  // mostly okay BUT it breaks psi because the unit converter expects a
  // force/weight over an area, and mass over area makes less sense.
  typedef value<TxType, psi> xType;
  typedef value<TxType, Pa> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_MM_HG_PER_SEC>
{
  typedef value<TxType, compose<mmHg, pow<s, -1>>> xType;
  typedef value<TxType, compose<Pa, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_JOULE_PER_DAY>
{
  typedef value<TxType, compose<J, pow<day, -1>>> xType;
  typedef value<TxType, compose<J, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_CALORIE>
{
  typedef value<TxType, cal> xType;
  typedef value<TxType, J> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_CALORIE_PER_DAY>
{
  typedef value<TxType, compose<cal, pow<day, -1>>> xType;
  typedef value<TxType, compose<J, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_CALORIE_PER_ML>
{
  typedef value<TxType, compose<cal, pow<ml, -1>>> xType;
  typedef value<TxType, compose<J, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_JOULE_PER_ML>
{
  typedef value<TxType, compose<J, pow<ml, -1>>> xType;
  typedef value<TxType, compose<J, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_REV_PER_MIN>
{
  typedef value<TxType, rpm> xType;
  typedef value<TxType, pow<s, -1>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PER_L_PER_MIN_PER_KG>
{
  typedef value<TxType, compose<compose<pow<liter, -1>, pow<minute, -1>>, pow<kg, -1>>> xType;
  typedef value<TxType, compose<compose<pow<liter, -1>, pow<s, -1>>, pow<kg, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_MILLI_BAR>
{
  typedef value<TxType, compose<liter, pow<milli<bar>::type, -1>>> xType;
  typedef value<TxType, compose<liter, pow<Pa, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_KG_PER_HR>
{
  typedef value<TxType, compose<compose<liter, pow<kg, -1>>, pow<hour, -1>>> xType;
  typedef value<TxType, compose<compose<liter, pow<s, -1>>, pow<kg, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_BAR_PER_LITER_PER_SEC>
{
  typedef value<TxType, compose<compose<bar, pow<liter, -1>>, pow<s, -1>>> xType;
  typedef value<TxType, compose<compose<Pa, pow<liter, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_BAR_PER_LITER>
{
  typedef value<TxType, compose<bar, pow<liter, -1>>> xType;
  typedef value<TxType, compose<Pa, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_VOLT_PER_MILLI_VOLT>
{
  typedef value<TxType, compose<V, pow<milli<V>::type, -1>>> xType;
  typedef value<TxType, compose<V, pow<V, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_CM_H2O_PER_MICRO_VOLT>
{
  typedef value<TxType, compose<cmH2O, pow<micro<V>::type, -1>>> xType;
  typedef value<TxType, compose<Pa, pow<V, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_JOULE_PER_LITER>
{
  typedef value<TxType, compose<J, pow<liter, -1>>> xType;
  typedef value<TxType, compose<J, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_BAR>
{
  typedef value<TxType, compose<liter, pow<bar, -1>>> xType;
  typedef value<TxType, compose<liter, pow<Pa, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_M_PER_MILLI_VOLT>
{
  typedef value<TxType, compose<m, pow<milli<V>::type, -1>>> xType;
  typedef value<TxType, compose<m, pow<V, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_KG>
{
  typedef value<TxType, compose<compose<liter, pow<minute, -1>>, pow<kg, -1>>> xType;
  typedef value<TxType, compose<compose<liter, pow<s, -1>>, pow<kg, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_PASCAL_PER_L_PER_SEC>
{
  typedef value<TxType, compose<compose<Pa, pow<liter, -1>>, pow<s, -1>>> xType;
  typedef value<TxType, compose<compose<Pa, pow<liter, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_MILLI_L_PER_X_PASCAL>
{
  typedef value<TxType, compose<ml, pow<Pa, -1>>> xType;
  typedef value<TxType, compose<liter, pow<Pa, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_MM_HG_PER_X_L_PER_SEC>
{
  typedef value<TxType, compose<compose<mmHg, pow<liter, -1>>, pow<s, -1>>> xType;
  typedef value<TxType, compose<compose<Pa, pow<liter, -1>>, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_BEAT_PER_M_SQ>
{
  typedef value<TxType, compose<compose<liter, pow<beat, -1>>, pow<m2, -1>>> xType;
  typedef value<TxType, compose<compose<liter, pow<beat, -1>>, pow<m2, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_BAR_PER_SEC>
{
  typedef value<TxType, compose<bar, pow<s, -1>>> xType;
  typedef value<TxType, compose<Pa, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_PASCAL_PER_L>
{
  typedef value<TxType, compose<Pa, pow<liter, -1>>> xType;
  typedef value<TxType, compose<Pa, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_MM_HG_PER_L>
{
  typedef value<TxType, compose<mmHg, pow<liter, -1>>> xType;
  typedef value<TxType, compose<Pa, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_VOL_PERCENT_PER_L>
{
  typedef value<TxType, compose<percent, pow<liter, -1>>> xType;
  typedef value<TxType, compose<percent, pow<liter, -1>>> baseType;
};
// End Intellivue codes

// DocBox codes
template<typename TxType> struct Tx<TxType, MDC_DIM_PER_OHM>
{
  typedef value<TxType, pow<Ohm, -1>> xType;
  typedef value<TxType, pow<Ohm, -1>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_SEC_SQ>
{
  typedef value<TxType, pow<s, 2>> xType;
  typedef value<TxType, pow<s, 2>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_X_L_PER_K_OHM>
{
  typedef value<TxType, compose<liter, pow<Ohm, -1>>> xType;
  typedef value<TxType, compose<liter, pow<Ohm, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_PVC_PER_MIN>
{
  typedef value<TxType, compose<PVC, pow<minute, -1>>> xType;
  typedef value<TxType, compose<PVC, pow<s, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_BREATHS_PER_MIN_PER_L>
{
  typedef value<TxType, compose<compose<breath, pow<minute, -1>>, pow<liter, -1>>> xType;
  typedef value<TxType, compose<compose<breath, pow<s, -1>>, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_JOULES_PER_L>
{
  typedef value<TxType, compose<J, pow<liter, -1>>> xType;
  typedef value<TxType, compose<J, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_RESP_PER_MIN_PER_L>
{
  typedef value<TxType, compose<compose<breath, pow<minute, -1>>, pow<liter, -1>>> xType;
  typedef value<TxType, compose<compose<breath, pow<s, -1>>, pow<liter, -1>>> baseType;
};

template<typename TxType> struct Tx<TxType, MDC_DIM_RESP_PER_MIN_PER_L_PER_KILO_G>
{
  typedef value<TxType, compose<compose<compose<breath, pow<minute, -1>>, pow<liter, -1>>, pow<kg, -1>>> xType;
  typedef value<TxType, compose<compose<compose<breath, pow<s, -1>>, pow<liter, -1>>, pow<kg, -1>>> baseType;
};
// End DocBox codes

/* Regular expression to generate new Tx
 * Example Input:
MDC_DIM_X_LUMEN_PER_M_SQ
 * Find What:
(MDC_DIM_[A-Z0-9_]*)\n
 * Replace With:
template<typename TxType> struct Tx<TxType, $1>\n
{\n
  typedef value<TxType, YourTypeHere> xType;\n
  typedef value<TxType, BaseTypeHere> baseType;\n
};\n\n
 */

enum class DicesRcUnitConverter
{
  OK = 0,
  FAIL = 1
};

class UnitConverter
{
 public:

  template<typename TxType>
  static DicesRcUnitConverter ConvertValue(TxType value, const long from_unit_code,
    const long to_unit_code, TxType* to_value)
  {
    static const char* sfn = "UnitConverter::ConvertValue() ";
    log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

    try
    {
      log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(
        "log4cplus.properties"));
    }
    catch (std::exception &ex)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << " Exception occured while opening "
        "log4cplus.properties... " << ex.what());
      return DicesRcUnitConverter::FAIL;
    }

    if (to_value == nullptr)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << " Invalid null value for to_value parameter.");
      return DicesRcUnitConverter::FAIL;
    }

    short from_exp = 0;
    short from_offset = 0;
    long base_from_unit_code = from_unit_code;
    if (!(from_unit_code > 61440 && from_unit_code < 61536) &&
      !(from_unit_code > 62369))
    {
      from_offset = from_unit_code % 32;
      base_from_unit_code = from_unit_code - from_offset;
    }
    if (from_unit_code > MDC_DIM_X_L_PER_K_OHM &&
      from_unit_code < MDC_DIM_X_L_PER_K_OHM + 32)
    {
      from_offset = from_unit_code - MDC_DIM_X_L_PER_K_OHM;
      base_from_unit_code = MDC_DIM_X_L_PER_K_OHM;
    }
    switch (from_offset)
    {
      case 0: break;
      case DECA_OFFSET: from_exp = 1;
        break;
      case HECTO_OFFSET: from_exp = 2;
        break;
      case KILO_OFFSET: from_exp = 3;
        break;
      case MEGA_OFFSET: from_exp = 6;
        break;
      case GIGA_OFFSET: from_exp = 9;
        break;
      case TERA_OFFSET: from_exp = 12;
        break;
      case PETA_OFFSET: from_exp = 15;
        break;
      case EXA_OFFSET: from_exp = 18;
        break;
      case ZETTA_OFFSET: from_exp = 21;
        break;
      case YOTTA_OFFSET: from_exp = 24;
        break;
      case DECI_OFFSET: from_exp = -1;
        break;
      case CENTI_OFFSET: from_exp = -2;
        break;
      case MILLI_OFFSET: from_exp = -3;
        break;
      case MICRO_OFFSET: from_exp = -6;
        break;
      case NANO_OFFSET: from_exp = -9;
        break;
      case PICO_OFFSET: from_exp = -12;
        break;
      case FEMTO_OFFSET: from_exp = -15;
        break;
      case ATTO_OFFSET: from_exp = -18;
        break;
      case ZEPTO_OFFSET: from_exp = -21;
        break;
      case YOCTO_OFFSET: from_exp = -24;
        break;
      default:
        LOG4CPLUS_ERROR(root_logger, sfn << "Invalid offset " << from_offset <<
          " on from unit code " << from_unit_code);
        return DicesRcUnitConverter::FAIL;
        break;
    }
    switch (base_from_unit_code)
    {
      case MDC_DIM_SQ_X_M:
      case MDC_DIM_SQ_X_INCH:
      case MDC_DIM_SQ_X_M_PER_SEC:
        from_exp *= 2;
        break;
      
      case MDC_DIM_CUBIC_X_M_PER_M_CUBE:
      case MDC_DIM_CUBIC_X_M_PER_CM_CUBE:
      case MDC_DIM_CUBIC_X_M:
      case MDC_DIM_CUBIC_X_M_PER_SEC:
      case MDC_DIM_CUBIC_X_M_PER_MIN:
      case MDC_DIM_CUBIC_X_M_PER_HR:
      case MDC_DIM_CUBIC_X_M_PER_DAY:
      case MDC_DIM_CUBIC_X_L_PER_KG:
        from_exp *= 3;
        break;
        
      case MDC_DIM_PER_X_M:
      case MDC_DIM_PER_X_L:
      case MDC_DIM_PER_X_G:
      case MDC_DIM_PER_X_SEC:
      case MDC_DIM_KELVIN_PER_X_WATT:
      case MDC_DIM_MM_HG_PER_X_L:
      case MDC_DIM_PA_PER_X_L:
      case MDC_DIM_BEAT_PER_MIN_PER_X_L:
      case MDC_DIM_PER_X_L_PER_MIN:
      case MDC_DIM_MILLI_L_PER_X_PASCAL:
      case MDC_DIM_MM_HG_PER_X_L_PER_SEC:
        from_exp *= -1;
        break;
        
      case MDC_DIM_PER_SQ_X_M:
        from_exp *= -2;
        break;
        
      case MDC_DIM_PER_CUBIC_X_M:
        from_exp *= -3;
        break;
        
      default: break;
    }

    short to_exp = 0;
    short to_offset = 0;
    long base_to_unit_code = to_unit_code;
    if (!(to_unit_code > 61440 && to_unit_code < 61536) &&
      !(to_unit_code > 62369))
    {
      to_offset = to_unit_code % 32;
      base_to_unit_code = to_unit_code - to_offset;
    }
    if (to_unit_code > MDC_DIM_X_L_PER_K_OHM &&
      to_unit_code < MDC_DIM_X_L_PER_K_OHM + 32)
    {
      to_offset = to_unit_code - MDC_DIM_X_L_PER_K_OHM;
      base_to_unit_code = MDC_DIM_X_L_PER_K_OHM;
    }
    switch (to_offset)
    {
      case 0: break;
      case DECA_OFFSET: to_exp = 1;
        break;
      case HECTO_OFFSET: to_exp = 2;
        break;
      case KILO_OFFSET: to_exp = 3;
        break;
      case MEGA_OFFSET: to_exp = 6;
        break;
      case GIGA_OFFSET: to_exp = 9;
        break;
      case TERA_OFFSET: to_exp = 12;
        break;
      case PETA_OFFSET: to_exp = 15;
        break;
      case EXA_OFFSET: to_exp = 18;
        break;
      case ZETTA_OFFSET: to_exp = 21;
        break;
      case YOTTA_OFFSET: to_exp = 24;
        break;
      case DECI_OFFSET: to_exp = -1;
        break;
      case CENTI_OFFSET: to_exp = -2;
        break;
      case MILLI_OFFSET: to_exp = -3;
        break;
      case MICRO_OFFSET: to_exp = -6;
        break;
      case NANO_OFFSET: to_exp = -9;
        break;
      case PICO_OFFSET: to_exp = -12;
        break;
      case FEMTO_OFFSET: to_exp = -15;
        break;
      case ATTO_OFFSET: to_exp = -18;
        break;
      case ZEPTO_OFFSET: to_exp = -21;
        break;
      case YOCTO_OFFSET: to_exp = -24;
        break;
      default:
        LOG4CPLUS_ERROR(root_logger, sfn << "Invalid offset " << to_offset <<
          " on to unit code " << to_unit_code);
        return DicesRcUnitConverter::FAIL;
        break;
    }
    switch (base_to_unit_code)
    {
      case MDC_DIM_SQ_X_M:
      case MDC_DIM_SQ_X_INCH:
      case MDC_DIM_SQ_X_M_PER_SEC:
        to_exp *= 2;
        break;

      case MDC_DIM_CUBIC_X_M_PER_M_CUBE:
      case MDC_DIM_CUBIC_X_M_PER_CM_CUBE:
      case MDC_DIM_CUBIC_X_M:
      case MDC_DIM_CUBIC_X_M_PER_SEC:
      case MDC_DIM_CUBIC_X_M_PER_MIN:
      case MDC_DIM_CUBIC_X_M_PER_HR:
      case MDC_DIM_CUBIC_X_M_PER_DAY:
      case MDC_DIM_CUBIC_X_L_PER_KG:
        to_exp *= 3;
        break;

      case MDC_DIM_PER_X_M:
      case MDC_DIM_PER_X_L:
      case MDC_DIM_PER_X_G:
      case MDC_DIM_PER_X_SEC:
      case MDC_DIM_KELVIN_PER_X_WATT:
      case MDC_DIM_MM_HG_PER_X_L:
      case MDC_DIM_PA_PER_X_L:
      case MDC_DIM_BEAT_PER_MIN_PER_X_L:
      case MDC_DIM_PER_X_L_PER_MIN:
      case MDC_DIM_MILLI_L_PER_X_PASCAL:
      case MDC_DIM_MM_HG_PER_X_L_PER_SEC:
        to_exp *= -1;
        break;

      case MDC_DIM_PER_SQ_X_M:
        to_exp *= -2;
        break;

      case MDC_DIM_PER_CUBIC_X_M:
        to_exp *= -3;
        break;

      default: break;
    }
    
    // Probably more efficient than linking math.h.
    for (int ix = 0; ix < from_exp - to_exp; ix++) value *= 10;
    for (int ix = 0; ix > from_exp - to_exp; ix--) value /= 10;
    if (base_from_unit_code == base_to_unit_code) 
    {
      *to_value = value;
      return DicesRcUnitConverter::OK;
    }

    std::string from_type = "";
    std::string to_type = "";

    switch (base_from_unit_code)
    {
      case MDC_DIM_DIMLESS:
      {
        typename Tx<TxType, MDC_DIM_DIMLESS>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_DIMLESS>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_DIMLESS>::baseType).name());
        break;
      }
      case MDC_DIM_PERCENT:
      {
        typename Tx<TxType, MDC_DIM_PERCENT>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PERCENT>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PERCENT>::baseType).name());
        break;
      }
      case MDC_DIM_PARTS_PER_THOUSAND:
      {
        typename Tx<TxType, MDC_DIM_PARTS_PER_THOUSAND>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PARTS_PER_THOUSAND>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PARTS_PER_THOUSAND>::baseType).name());
        break;
      }
      case MDC_DIM_PARTS_PER_MILLION:
      {
        typename Tx<TxType, MDC_DIM_PARTS_PER_MILLION>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PARTS_PER_MILLION>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PARTS_PER_MILLION>::baseType).name());
        break;
      }
      case MDC_DIM_PPMD:
      {
        typename Tx<TxType, MDC_DIM_PPMD>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PPMD>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PPMD>::baseType).name());
        break;
      }
      case MDC_DIM_PARTS_PER_BILLION:
      {
        typename Tx<TxType, MDC_DIM_PARTS_PER_BILLION>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PARTS_PER_BILLION>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PARTS_PER_BILLION>::baseType).name());
        break;
      }
      case MDC_DIM_PARTS_PER_TRILLION:
      {
        typename Tx<TxType, MDC_DIM_PARTS_PER_TRILLION>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PARTS_PER_TRILLION>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PARTS_PER_TRILLION>::baseType).name());
        break;
      }
      case MDC_DIM_ANG_DEG:
      {
        typename Tx<TxType, MDC_DIM_ANG_DEG>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_ANG_DEG>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_ANG_DEG>::baseType).name());
        break;
      }
      case MDC_DIM_ANG_RAD:
      {
        typename Tx<TxType, MDC_DIM_ANG_RAD>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_ANG_RAD>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_ANG_RAD>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_G:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_G>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_G>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_G>::baseType).name());
        break;
      }
      case MDC_DIM_G_PER_KG:
      {
        typename Tx<TxType, MDC_DIM_G_PER_KG>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_G_PER_KG>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_G_PER_KG>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_MOLE:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_MOLE>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_MOLE>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_MOLE>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_L:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_CUBIC_X_M_PER_M_CUBE:
      {
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_M_CUBE>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_M_CUBE>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_M_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_CUBIC_X_M_PER_CM_CUBE:
      {
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_CM_CUBE>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_CM_CUBE>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_CM_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_PH:
      {
        typename Tx<TxType, MDC_DIM_PH>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PH>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PH>::baseType).name());
        break;
      }
      case MDC_DIM_DROP:
      {
        typename Tx<TxType, MDC_DIM_DROP>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_DROP>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_DROP>::baseType).name());
        break;
      }
      case MDC_DIM_RBC:
      {
        typename Tx<TxType, MDC_DIM_RBC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_RBC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_RBC>::baseType).name());
        break;
      }
      case MDC_DIM_BEAT:
      {
        typename Tx<TxType, MDC_DIM_BEAT>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_BEAT>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_BEAT>::baseType).name());
        break;
      }
      case MDC_DIM_BREATH:
      {
        typename Tx<TxType, MDC_DIM_BREATH>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_BREATH>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_BREATH>::baseType).name());
        break;
      }
      case MDC_DIM_CELL:
      {
        typename Tx<TxType, MDC_DIM_CELL>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_CELL>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_CELL>::baseType).name());
        break;
      }
      case MDC_DIM_COUGH:
      {
        typename Tx<TxType, MDC_DIM_COUGH>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_COUGH>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_COUGH>::baseType).name());
        break;
      }
      case MDC_DIM_SIGH:
      {
        typename Tx<TxType, MDC_DIM_SIGH>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_SIGH>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_SIGH>::baseType).name());
        break;
      }
      case MDC_DIM_PCT_PCV:
      {
        typename Tx<TxType, MDC_DIM_PCT_PCV>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PCT_PCV>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PCT_PCV>::baseType).name());
        break;
      }
      case MDC_DIM_X_M:
      {
        typename Tx<TxType, MDC_DIM_X_M>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_M>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_M>::baseType).name());
        break;
      }
      case MDC_DIM_X_YARD:
      {
        typename Tx<TxType, MDC_DIM_X_YARD>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_YARD>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_YARD>::baseType).name());
        break;
      }
      case MDC_DIM_X_FOOT:
      {
        typename Tx<TxType, MDC_DIM_X_FOOT>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_FOOT>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_FOOT>::baseType).name());
        break;
      }
      case MDC_DIM_X_INCH:
      {
        typename Tx<TxType, MDC_DIM_X_INCH>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_INCH>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INCH>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_M_SQ:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_M_SQ>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_M_SQ>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_M_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_PER_X_M:
      {
        typename Tx<TxType, MDC_DIM_PER_X_M>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PER_X_M>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_X_M>::baseType).name());
        break;
      }
      case MDC_DIM_SQ_X_M:
      {
        typename Tx<TxType, MDC_DIM_SQ_X_M>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_SQ_X_M>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_SQ_X_M>::baseType).name());
        break;
      }
      case MDC_DIM_SQ_X_INCH:
      {
        typename Tx<TxType, MDC_DIM_SQ_X_INCH>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_SQ_X_INCH>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_SQ_X_INCH>::baseType).name());
        break;
      }
      case MDC_DIM_PER_SQ_X_M:
      {
        typename Tx<TxType, MDC_DIM_PER_SQ_X_M>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PER_SQ_X_M>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_SQ_X_M>::baseType).name());
        break;
      }
      case MDC_DIM_CUBIC_X_M:
      {
        typename Tx<TxType, MDC_DIM_CUBIC_X_M>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_CUBIC_X_M>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_CUBIC_X_M>::baseType).name());
        break;
      }
      case MDC_DIM_X_L:
      {
        typename Tx<TxType, MDC_DIM_X_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_BREATH:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_BREATH>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_BREATH>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_BREATH>::baseType).name());
        break;
      }
      case MDC_DIM_PER_CUBIC_X_M:
      {
        typename Tx<TxType, MDC_DIM_PER_CUBIC_X_M>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PER_CUBIC_X_M>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_CUBIC_X_M>::baseType).name());
        break;
      }
      case MDC_DIM_PER_X_L:
      {
        typename Tx<TxType, MDC_DIM_PER_X_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PER_X_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_X_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_G:
      {
        typename Tx<TxType, MDC_DIM_X_G>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G>::baseType).name());
        break;
      }
      case MDC_DIM_X_LB:
      {
        typename Tx<TxType, MDC_DIM_X_LB>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_LB>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_LB>::baseType).name());
        break;
      }
      case MDC_DIM_X_OZ:
      {
        typename Tx<TxType, MDC_DIM_X_OZ>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_OZ>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_OZ>::baseType).name());
        break;
      }
      case MDC_DIM_PER_X_G:
      {
        typename Tx<TxType, MDC_DIM_PER_X_G>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PER_X_G>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_X_G>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_M:
      {
        typename Tx<TxType, MDC_DIM_X_G_M>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_M>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_M>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_M_PER_M_SQ:
      {
        typename Tx<TxType, MDC_DIM_X_G_M_PER_M_SQ>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_M_PER_M_SQ>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_M_PER_M_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_M_SQ:
      {
        typename Tx<TxType, MDC_DIM_X_G_M_SQ>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_M_SQ>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_M_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_KG_PER_M_SQ:
      {
        typename Tx<TxType, MDC_DIM_KG_PER_M_SQ>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_KG_PER_M_SQ>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_KG_PER_M_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_M_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_M_CUBE>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_M_CUBE>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_M_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_CM_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_CM_CUBE>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_CM_CUBE>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_CM_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_L:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_CL:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_CL>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_CL>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_CL>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_DL:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_DL>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_DL>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_DL>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_ML:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_ML>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_ML>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_ML>::baseType).name());
        break;
      }
      case MDC_DIM_X_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_MIN:
      {
        typename Tx<TxType, MDC_DIM_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_HR:
      {
        typename Tx<TxType, MDC_DIM_HR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_HR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_HR>::baseType).name());
        break;
      }
      case MDC_DIM_DAY:
      {
        typename Tx<TxType, MDC_DIM_DAY>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_DAY>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_WEEKS:
      {
        typename Tx<TxType, MDC_DIM_WEEKS>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_WEEKS>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_WEEKS>::baseType).name());
        break;
      }
      case MDC_DIM_MON:
      {
        typename Tx<TxType, MDC_DIM_MON>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_MON>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_MON>::baseType).name());
        break;
      }
      case MDC_DIM_YR:
      {
        typename Tx<TxType, MDC_DIM_YR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_YR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_YR>::baseType).name());
        break;
      }
      case MDC_DIM_PER_X_SEC:
      {
        typename Tx<TxType, MDC_DIM_PER_X_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PER_X_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_X_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_HZ:
      {
        typename Tx<TxType, MDC_DIM_HZ>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_HZ>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_HZ>::baseType).name());
        break;
      }
      case MDC_DIM_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_PER_HR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PER_HR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_PER_DAY>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PER_DAY>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_PER_WK:
      {
        typename Tx<TxType, MDC_DIM_PER_WK>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PER_WK>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_WK>::baseType).name());
        break;
      }
      case MDC_DIM_PER_MO:
      {
        typename Tx<TxType, MDC_DIM_PER_MO>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PER_MO>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_MO>::baseType).name());
        break;
      }
      case MDC_DIM_PER_YR:
      {
        typename Tx<TxType, MDC_DIM_PER_YR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PER_YR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_YR>::baseType).name());
        break;
      }
      case MDC_DIM_BEAT_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_BEAT_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_BEAT_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_BEAT_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_PULS_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_PULS_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PULS_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PULS_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_RESP_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_RESP_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_RESP_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_RESP_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_M_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_M_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_M_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_M_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_MIN_PER_M_SQ:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_M_SQ>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_M_SQ>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_M_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_SQ_X_M_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_SQ_X_M_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_SQ_X_M_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_SQ_X_M_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_CUBIC_X_M_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_CUBIC_X_M_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_CUBIC_X_M_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_HR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_HR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_CUBIC_X_M_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_DAY>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_DAY>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_HR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_HR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_DAY>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_DAY>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_KG:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_KG>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_KG>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_KG>::baseType).name());
        break;
      }
      case MDC_DIM_CUBIC_X_L_PER_KG:
      {
        typename Tx<TxType, MDC_DIM_CUBIC_X_L_PER_KG>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_CUBIC_X_L_PER_KG>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_CUBIC_X_L_PER_KG>::baseType).name());
        break;
      }
      case MDC_DIM_X_M_PER_PASCAL_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_M_PER_PASCAL_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_M_PER_PASCAL_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_M_PER_PASCAL_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_MIN_PER_ML_HG:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_ML_HG>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_ML_HG>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_ML_HG>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_HR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_HR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_DAY>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_DAY>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_KG_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_KG_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_KG_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_HR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_HR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_KG_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_DAY>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_DAY>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_L_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_L_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_L_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_HR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_HR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_L_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_DAY>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_DAY>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_M_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_M_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_M_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_M_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_M_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_G_M_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_M_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_M_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_NEWTON_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_NEWTON_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_NEWTON_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_NEWTON_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_NEWTON:
      {
        typename Tx<TxType, MDC_DIM_X_NEWTON>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_NEWTON>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_NEWTON>::baseType).name());
        break;
      }
      case MDC_DIM_X_DYNE:
      {
        typename Tx<TxType, MDC_DIM_X_DYNE>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_DYNE>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_DYNE>::baseType).name());
        break;
      }
      case MDC_DIM_X_PASCAL:
      {
        typename Tx<TxType, MDC_DIM_X_PASCAL>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_PASCAL>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_PASCAL>::baseType).name());
        break;
      }
      case MDC_DIM_MMHG:
      {
        typename Tx<TxType, MDC_DIM_MMHG>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_MMHG>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_MMHG>::baseType).name());
        break;
      }
      case MDC_DIM_CM_H2O:
      {
        typename Tx<TxType, MDC_DIM_CM_H2O>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_CM_H2O>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_CM_H2O>::baseType).name());
        break;
      }
      case MDC_DIM_X_BAR:
      {
        typename Tx<TxType, MDC_DIM_X_BAR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_BAR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_BAR>::baseType).name());
        break;
      }
      case MDC_DIM_X_JOULES:
      {
        typename Tx<TxType, MDC_DIM_X_JOULES>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_JOULES>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_JOULES>::baseType).name());
        break;
      }
      case MDC_DIM_EVOLT:
      {
        typename Tx<TxType, MDC_DIM_EVOLT>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_EVOLT>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_EVOLT>::baseType).name());
        break;
      }
      case MDC_DIM_X_WATT:
      {
        typename Tx<TxType, MDC_DIM_X_WATT>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_WATT>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_WATT>::baseType).name());
        break;
      }
      case MDC_DIM_X_PASCAL_SEC_PER_M_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_PASCAL_SEC_PER_M_CUBE>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_PASCAL_SEC_PER_M_CUBE>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_PASCAL_SEC_PER_M_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_PASCAL_SEC_PER_L:
      {
        typename Tx<TxType, MDC_DIM_X_PASCAL_SEC_PER_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_PASCAL_SEC_PER_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_PASCAL_SEC_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_DYNE_PER_SEC_PER_CM5:
      {
        typename Tx<TxType, MDC_DIM_X_DYNE_PER_SEC_PER_CM5>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_DYNE_PER_SEC_PER_CM5>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_DYNE_PER_SEC_PER_CM5>::baseType).name());
        break;
      }
      case MDC_DIM_X_AMPS:
      {
        typename Tx<TxType, MDC_DIM_X_AMPS>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_AMPS>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_AMPS>::baseType).name());
        break;
      }
      case MDC_DIM_X_COULOMB:
      {
        typename Tx<TxType, MDC_DIM_X_COULOMB>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_COULOMB>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_COULOMB>::baseType).name());
        break;
      }
      case MDC_DIM_X_AMPS_PER_M:
      {
        typename Tx<TxType, MDC_DIM_X_AMPS_PER_M>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_AMPS_PER_M>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_AMPS_PER_M>::baseType).name());
        break;
      }
      case MDC_DIM_X_VOLT:
      {
        typename Tx<TxType, MDC_DIM_X_VOLT>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_VOLT>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_VOLT>::baseType).name());
        break;
      }
      case MDC_DIM_X_OHM:
      {
        typename Tx<TxType, MDC_DIM_X_OHM>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_OHM>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_OHM>::baseType).name());
        break;
      }
      case MDC_DIM_X_OHM_M:
      {
        typename Tx<TxType, MDC_DIM_X_OHM_M>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_OHM_M>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_OHM_M>::baseType).name());
        break;
      }
      case MDC_DIM_X_FARAD:
      {
        typename Tx<TxType, MDC_DIM_X_FARAD>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_FARAD>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_FARAD>::baseType).name());
        break;
      }
      case MDC_DIM_KELVIN:
      {
        typename Tx<TxType, MDC_DIM_KELVIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_KELVIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_KELVIN>::baseType).name());
        break;
      }
      case MDC_DIM_FAHR:
      {
        typename Tx<TxType, MDC_DIM_FAHR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_FAHR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_FAHR>::baseType).name());
        break;
      }
      case MDC_DIM_KELVIN_PER_X_WATT:
      {
        typename Tx<TxType, MDC_DIM_KELVIN_PER_X_WATT>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_KELVIN_PER_X_WATT>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_KELVIN_PER_X_WATT>::baseType).name());
        break;
      }
      case MDC_DIM_X_CANDELA:
      {
        typename Tx<TxType, MDC_DIM_X_CANDELA>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_CANDELA>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_CANDELA>::baseType).name());
        break;
      }
      case MDC_DIM_X_OSM:
      {
        typename Tx<TxType, MDC_DIM_X_OSM>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_OSM>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_OSM>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV>::baseType).name());
        break;
      }
      case MDC_DIM_X_OSM_PER_L:
      {
        typename Tx<TxType, MDC_DIM_X_OSM_PER_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_OSM_PER_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_OSM_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_CM_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_CM_CUBE>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_CM_CUBE>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_CM_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_M_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_M_CUBE>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_M_CUBE>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_M_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_L:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_ML:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_ML>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_ML>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_ML>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_CM_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_CM_CUBE>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_CM_CUBE>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_CM_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_M_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_M_CUBE>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_M_CUBE>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_M_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_L:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_ML:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_ML>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_ML>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_ML>::baseType).name());
        break;
      }
      case MDC_DIM_X_OSM_PER_KG:
      {
        typename Tx<TxType, MDC_DIM_X_OSM_PER_KG>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_OSM_PER_KG>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_OSM_PER_KG>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_KG:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_HR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_HR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_DAY>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_DAY>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_HR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_HR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_DAY>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_DAY>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_KG_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_KG_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_KG_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_HR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_HR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_KG_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_DAY>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_DAY>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_KG_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_KG_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_KG_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_HR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_HR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_KG_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_DAY>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_DAY>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_CM_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_CM_CUBE>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_CM_CUBE>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_CM_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_M_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_M_CUBE>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_M_CUBE>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_M_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_L:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_ML:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_ML>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_ML>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_ML>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_HR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_HR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_DAY>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_DAY>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_KG_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_KG_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_KG_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_HR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_HR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_KG_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_DAY>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_DAY>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_CM_H2O:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_CM_H2O>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_CM_H2O>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_CM_H2O>::baseType).name());
        break;
      }
      case MDC_DIM_CM_H2O_PER_L_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_CM_H2O_PER_L_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_CM_H2O_PER_L_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_CM_H2O_PER_L_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_SQ_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_L_SQ_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_SQ_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_SQ_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_CM_H2O_PER_PERCENT:
      {
        typename Tx<TxType, MDC_DIM_CM_H2O_PER_PERCENT>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_CM_H2O_PER_PERCENT>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_CM_H2O_PER_PERCENT>::baseType).name());
        break;
      }
      case MDC_DIM_DYNE_SEC_PER_M_SQ_PER_CM_5:
      {
        typename Tx<TxType, MDC_DIM_DYNE_SEC_PER_M_SQ_PER_CM_5>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_DYNE_SEC_PER_M_SQ_PER_CM_5>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_DYNE_SEC_PER_M_SQ_PER_CM_5>::baseType).name());
        break;
      }
      case MDC_DIM_DEGC:
      {
        typename Tx<TxType, MDC_DIM_DEGC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_DEGC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_DEGC>::baseType).name());
        break;
      }
      case MDC_DIM_X_AMP_HR:
      {
        typename Tx<TxType, MDC_DIM_X_AMP_HR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_AMP_HR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_AMP_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_BEAT:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_BEAT>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_BEAT>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_BEAT>::baseType).name());
        break;
      }
      case MDC_DIM_CM_H2O_PER_L:
      {
        typename Tx<TxType, MDC_DIM_CM_H2O_PER_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_CM_H2O_PER_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_CM_H2O_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_MM_HG_PER_PERCENT:
      {
        typename Tx<TxType, MDC_DIM_MM_HG_PER_PERCENT>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_MM_HG_PER_PERCENT>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_MM_HG_PER_PERCENT>::baseType).name());
        break;
      }
      case MDC_DIM_X_PA_PER_PERCENT:
      {
        typename Tx<TxType, MDC_DIM_X_PA_PER_PERCENT>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_PA_PER_PERCENT>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_PA_PER_PERCENT>::baseType).name());
        break;
      }
      case MDC_DIM_VOL_PERCENT:
      {
        typename Tx<TxType, MDC_DIM_VOL_PERCENT>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_VOL_PERCENT>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_VOL_PERCENT>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_MM_HG:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_MM_HG>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_MM_HG>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_MM_HG>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_MM_PA:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_MM_PA>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_MM_PA>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_MM_PA>::baseType).name());
        break;
      }
      case MDC_DIM_MM_HG_PER_X_L:
      {
        typename Tx<TxType, MDC_DIM_MM_HG_PER_X_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_MM_HG_PER_X_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_MM_HG_PER_X_L>::baseType).name());
        break;
      }
      case MDC_DIM_PA_PER_X_L:
      {
        typename Tx<TxType, MDC_DIM_PA_PER_X_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PA_PER_X_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PA_PER_X_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_DL:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_DL>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_DL>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_DL>::baseType).name());
        break;
      }
      case MDC_DIM_DECIBEL:
      {
        typename Tx<TxType, MDC_DIM_DECIBEL>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_DECIBEL>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_DECIBEL>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_MG:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_MG>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_MG>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_MG>::baseType).name());
        break;
      }
      case MDC_DIM_BEAT_PER_MIN_PER_X_L:
      {
        typename Tx<TxType, MDC_DIM_BEAT_PER_MIN_PER_X_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_BEAT_PER_MIN_PER_X_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_BEAT_PER_MIN_PER_X_L>::baseType).name());
        break;
      }
      case MDC_DIM_PER_X_L_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_PER_X_L_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PER_X_L_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_X_L_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_M_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_M_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_M_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_M_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_PSI:
      {
        typename Tx<TxType, MDC_DIM_PSI>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PSI>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PSI>::baseType).name());
        break;
      }
      case MDC_DIM_X_M_PER_SEC_SQ:
      {
        typename Tx<TxType, MDC_DIM_X_M_PER_SEC_SQ>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_M_PER_SEC_SQ>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_M_PER_SEC_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_X_RAD_PER_SEC_SQ:
      {
        typename Tx<TxType, MDC_DIM_X_RAD_PER_SEC_SQ>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_RAD_PER_SEC_SQ>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_RAD_PER_SEC_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_X_RAD_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_RAD_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_RAD_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_RAD_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_LUMEN_PER_M_SQ:
      {
        typename Tx<TxType, MDC_DIM_X_LUMEN_PER_M_SQ>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_LUMEN_PER_M_SQ>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_LUMEN_PER_M_SQ>::baseType).name());
        break;
      }

    // Intellivue codes
      case MDC_DIM_COMPLEX:
      {
        typename Tx<TxType, MDC_DIM_COMPLEX>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_COMPLEX>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_COMPLEX>::baseType).name());
        break;
      }
      case MDC_DIM_COUNT:
      {
        typename Tx<TxType, MDC_DIM_COUNT>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_COUNT>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_COUNT>::baseType).name());
        break;
      }
      case MDC_DIM_PART:
      {
        typename Tx<TxType, MDC_DIM_PART>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PART>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PART>::baseType).name());
        break;
      }
      case MDC_DIM_PULS:
      {
        typename Tx<TxType, MDC_DIM_PULS>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PULS>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PULS>::baseType).name());
        break;
      }
      case MDC_DIM_UV_PP:
      {
        typename Tx<TxType, MDC_DIM_UV_PP>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_UV_PP>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_UV_PP>::baseType).name());
        break;
      }
      case MDC_DIM_UV_SQ:
      {
        typename Tx<TxType, MDC_DIM_UV_SQ>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_UV_SQ>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_UV_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_LUMEN:
      {
        typename Tx<TxType, MDC_DIM_LUMEN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_LUMEN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_LUMEN>::baseType).name());
        break;
      }
      case MDC_DIM_LB_PER_INCH_SQ:
      {
        typename Tx<TxType, MDC_DIM_LB_PER_INCH_SQ>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_LB_PER_INCH_SQ>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_LB_PER_INCH_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_MM_HG_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_MM_HG_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_MM_HG_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_MM_HG_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_JOULE_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_JOULE_PER_DAY>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_JOULE_PER_DAY>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_JOULE_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_CALORIE:
      {
        typename Tx<TxType, MDC_DIM_X_CALORIE>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_CALORIE>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_CALORIE>::baseType).name());
        break;
      }
      case MDC_DIM_X_CALORIE_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_CALORIE_PER_DAY>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_CALORIE_PER_DAY>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_CALORIE_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_CALORIE_PER_ML:
      {
        typename Tx<TxType, MDC_DIM_X_CALORIE_PER_ML>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_CALORIE_PER_ML>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_CALORIE_PER_ML>::baseType).name());
        break;
      }
      case MDC_DIM_X_JOULE_PER_ML:
      {
        typename Tx<TxType, MDC_DIM_X_JOULE_PER_ML>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_JOULE_PER_ML>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_JOULE_PER_ML>::baseType).name());
        break;
      }
      case MDC_DIM_X_REV_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_REV_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_REV_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_REV_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_PER_L_PER_MIN_PER_KG:
      {
        typename Tx<TxType, MDC_DIM_PER_L_PER_MIN_PER_KG>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PER_L_PER_MIN_PER_KG>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_L_PER_MIN_PER_KG>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_MILLI_BAR:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_MILLI_BAR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_MILLI_BAR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_MILLI_BAR>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_KG_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_KG_PER_HR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_KG_PER_HR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_KG_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_BAR_PER_LITER_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_BAR_PER_LITER_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_BAR_PER_LITER_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_BAR_PER_LITER_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_BAR_PER_LITER:
      {
        typename Tx<TxType, MDC_DIM_X_BAR_PER_LITER>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_BAR_PER_LITER>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_BAR_PER_LITER>::baseType).name());
        break;
      }
      case MDC_DIM_VOLT_PER_MILLI_VOLT:
      {
        typename Tx<TxType, MDC_DIM_VOLT_PER_MILLI_VOLT>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_VOLT_PER_MILLI_VOLT>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_VOLT_PER_MILLI_VOLT>::baseType).name());
        break;
      }
      case MDC_DIM_CM_H2O_PER_MICRO_VOLT:
      {
        typename Tx<TxType, MDC_DIM_CM_H2O_PER_MICRO_VOLT>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_CM_H2O_PER_MICRO_VOLT>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_CM_H2O_PER_MICRO_VOLT>::baseType).name());
        break;
      }
      case MDC_DIM_X_JOULE_PER_LITER:
      {
        typename Tx<TxType, MDC_DIM_X_JOULE_PER_LITER>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_JOULE_PER_LITER>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_JOULE_PER_LITER>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_BAR:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_BAR>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_BAR>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_BAR>::baseType).name());
        break;
      }
      case MDC_DIM_X_M_PER_MILLI_VOLT:
      {
        typename Tx<TxType, MDC_DIM_X_M_PER_MILLI_VOLT>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_M_PER_MILLI_VOLT>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_M_PER_MILLI_VOLT>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_MIN_PER_KG:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_KG>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_KG>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_KG>::baseType).name());
        break;
      }
      case MDC_DIM_X_PASCAL_PER_L_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_PASCAL_PER_L_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_PASCAL_PER_L_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_PASCAL_PER_L_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_MILLI_L_PER_X_PASCAL:
      {
        typename Tx<TxType, MDC_DIM_MILLI_L_PER_X_PASCAL>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_MILLI_L_PER_X_PASCAL>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_MILLI_L_PER_X_PASCAL>::baseType).name());
        break;
      }
      case MDC_DIM_MM_HG_PER_X_L_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_MM_HG_PER_X_L_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_MM_HG_PER_X_L_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_MM_HG_PER_X_L_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_BEAT_PER_M_SQ:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_BEAT_PER_M_SQ>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_BEAT_PER_M_SQ>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_BEAT_PER_M_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_X_BAR_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_BAR_PER_SEC>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_BAR_PER_SEC>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_BAR_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_PASCAL_PER_L:
      {
        typename Tx<TxType, MDC_DIM_X_PASCAL_PER_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_PASCAL_PER_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_PASCAL_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_MM_HG_PER_L:
      {
        typename Tx<TxType, MDC_DIM_MM_HG_PER_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_MM_HG_PER_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_MM_HG_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_VOL_PERCENT_PER_L:
      {
        typename Tx<TxType, MDC_DIM_VOL_PERCENT_PER_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_VOL_PERCENT_PER_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_VOL_PERCENT_PER_L>::baseType).name());
        break;
      }
    // End Intellivue codes

    // DocBox codes
      case MDC_DIM_PER_OHM:
      {
        typename Tx<TxType, MDC_DIM_PER_OHM>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PER_OHM>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_OHM>::baseType).name());
        break;
      }
      case MDC_DIM_SEC_SQ:
      {
        typename Tx<TxType, MDC_DIM_SEC_SQ>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_SEC_SQ>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_SEC_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_K_OHM:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_K_OHM>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_K_OHM>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_K_OHM>::baseType).name());
        break;
      }
      case MDC_DIM_PVC_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_PVC_PER_MIN>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_PVC_PER_MIN>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_PVC_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_BREATHS_PER_MIN_PER_L:
      {
        typename Tx<TxType, MDC_DIM_BREATHS_PER_MIN_PER_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_BREATHS_PER_MIN_PER_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_BREATHS_PER_MIN_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_JOULES_PER_L:
      {
        typename Tx<TxType, MDC_DIM_JOULES_PER_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_JOULES_PER_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_JOULES_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_RESP_PER_MIN_PER_L:
      {
        typename Tx<TxType, MDC_DIM_RESP_PER_MIN_PER_L>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_RESP_PER_MIN_PER_L>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_RESP_PER_MIN_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_RESP_PER_MIN_PER_L_PER_KILO_G:
      {
        typename Tx<TxType, MDC_DIM_RESP_PER_MIN_PER_L_PER_KILO_G>::xType x_val(value);
        typename Tx<TxType, MDC_DIM_RESP_PER_MIN_PER_L_PER_KILO_G>::baseType base_val(x_val);
        value = base_val.get();
        from_type.assign(typeid(typename Tx<TxType, MDC_DIM_RESP_PER_MIN_PER_L_PER_KILO_G>::baseType).name());
        break;
      }
    // End DocBox codes

      default:
        LOG4CPLUS_ERROR(root_logger, sfn << "Invalid from unit code " << base_from_unit_code);
        return DicesRcUnitConverter::FAIL;
        break;
    }
    
/* Regular expression to generate new "from" case
 * Example Input:
MDC_DIM_X_LUMEN_PER_M_SQ
 * Find What:
(MDC_DIM_[A-Z0-9_]*)\n
 * Replace With:
      case $1:\n
      {\n
        typename Tx<TxType, $1>::xType x_val(value);\n
        typename Tx<TxType, $1>::baseType base_val(x_val);\n
        value = base_val.get();\n
        from_type.assign(typeid(typename Tx<TxType, $1>::baseType).name());\n
        break;\n
      }\n
 */

    switch (base_to_unit_code)
    {
      case MDC_DIM_DIMLESS:
      {
        typename Tx<TxType, MDC_DIM_DIMLESS>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_DIMLESS>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_DIMLESS>::baseType).name());
        break;
      }
      case MDC_DIM_PERCENT:
      {
        typename Tx<TxType, MDC_DIM_PERCENT>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PERCENT>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PERCENT>::baseType).name());
        break;
      }
      case MDC_DIM_PARTS_PER_THOUSAND:
      {
        typename Tx<TxType, MDC_DIM_PARTS_PER_THOUSAND>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PARTS_PER_THOUSAND>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PARTS_PER_THOUSAND>::baseType).name());
        break;
      }
      case MDC_DIM_PARTS_PER_MILLION:
      {
        typename Tx<TxType, MDC_DIM_PARTS_PER_MILLION>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PARTS_PER_MILLION>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PARTS_PER_MILLION>::baseType).name());
        break;
      }
      case MDC_DIM_PPMD:
      {
        typename Tx<TxType, MDC_DIM_PPMD>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PPMD>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PPMD>::baseType).name());
        break;
      }
      case MDC_DIM_PARTS_PER_BILLION:
      {
        typename Tx<TxType, MDC_DIM_PARTS_PER_BILLION>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PARTS_PER_BILLION>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PARTS_PER_BILLION>::baseType).name());
        break;
      }
      case MDC_DIM_PARTS_PER_TRILLION:
      {
        typename Tx<TxType, MDC_DIM_PARTS_PER_TRILLION>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PARTS_PER_TRILLION>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PARTS_PER_TRILLION>::baseType).name());
        break;
      }
      case MDC_DIM_ANG_DEG:
      {
        typename Tx<TxType, MDC_DIM_ANG_DEG>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_ANG_DEG>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_ANG_DEG>::baseType).name());
        break;
      }
      case MDC_DIM_ANG_RAD:
      {
        typename Tx<TxType, MDC_DIM_ANG_RAD>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_ANG_RAD>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_ANG_RAD>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_G:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_G>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_G>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_G>::baseType).name());
        break;
      }
      case MDC_DIM_G_PER_KG:
      {
        typename Tx<TxType, MDC_DIM_G_PER_KG>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_G_PER_KG>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_G_PER_KG>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_MOLE:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_MOLE>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_MOLE>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_MOLE>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_L:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_CUBIC_X_M_PER_M_CUBE:
      {
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_M_CUBE>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_M_CUBE>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_M_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_CUBIC_X_M_PER_CM_CUBE:
      {
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_CM_CUBE>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_CM_CUBE>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_CM_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_PH:
      {
        typename Tx<TxType, MDC_DIM_PH>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PH>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PH>::baseType).name());
        break;
      }
      case MDC_DIM_DROP:
      {
        typename Tx<TxType, MDC_DIM_DROP>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_DROP>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_DROP>::baseType).name());
        break;
      }
      case MDC_DIM_RBC:
      {
        typename Tx<TxType, MDC_DIM_RBC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_RBC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_RBC>::baseType).name());
        break;
      }
      case MDC_DIM_BEAT:
      {
        typename Tx<TxType, MDC_DIM_BEAT>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_BEAT>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_BEAT>::baseType).name());
        break;
      }
      case MDC_DIM_BREATH:
      {
        typename Tx<TxType, MDC_DIM_BREATH>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_BREATH>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_BREATH>::baseType).name());
        break;
      }
      case MDC_DIM_CELL:
      {
        typename Tx<TxType, MDC_DIM_CELL>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_CELL>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_CELL>::baseType).name());
        break;
      }
      case MDC_DIM_COUGH:
      {
        typename Tx<TxType, MDC_DIM_COUGH>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_COUGH>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_COUGH>::baseType).name());
        break;
      }
      case MDC_DIM_SIGH:
      {
        typename Tx<TxType, MDC_DIM_SIGH>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_SIGH>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_SIGH>::baseType).name());
        break;
      }
      case MDC_DIM_PCT_PCV:
      {
        typename Tx<TxType, MDC_DIM_PCT_PCV>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PCT_PCV>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PCT_PCV>::baseType).name());
        break;
      }
      case MDC_DIM_X_M:
      {
        typename Tx<TxType, MDC_DIM_X_M>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_M>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_M>::baseType).name());
        break;
      }
      case MDC_DIM_X_YARD:
      {
        typename Tx<TxType, MDC_DIM_X_YARD>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_YARD>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_YARD>::baseType).name());
        break;
      }
      case MDC_DIM_X_FOOT:
      {
        typename Tx<TxType, MDC_DIM_X_FOOT>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_FOOT>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_FOOT>::baseType).name());
        break;
      }
      case MDC_DIM_X_INCH:
      {
        typename Tx<TxType, MDC_DIM_X_INCH>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_INCH>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INCH>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_M_SQ:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_M_SQ>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_M_SQ>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_M_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_PER_X_M:
      {
        typename Tx<TxType, MDC_DIM_PER_X_M>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PER_X_M>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_X_M>::baseType).name());
        break;
      }
      case MDC_DIM_SQ_X_M:
      {
        typename Tx<TxType, MDC_DIM_SQ_X_M>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_SQ_X_M>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_SQ_X_M>::baseType).name());
        break;
      }
      case MDC_DIM_SQ_X_INCH:
      {
        typename Tx<TxType, MDC_DIM_SQ_X_INCH>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_SQ_X_INCH>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_SQ_X_INCH>::baseType).name());
        break;
      }
      case MDC_DIM_PER_SQ_X_M:
      {
        typename Tx<TxType, MDC_DIM_PER_SQ_X_M>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PER_SQ_X_M>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_SQ_X_M>::baseType).name());
        break;
      }
      case MDC_DIM_CUBIC_X_M:
      {
        typename Tx<TxType, MDC_DIM_CUBIC_X_M>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_CUBIC_X_M>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_CUBIC_X_M>::baseType).name());
        break;
      }
      case MDC_DIM_X_L:
      {
        typename Tx<TxType, MDC_DIM_X_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_BREATH:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_BREATH>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_BREATH>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_BREATH>::baseType).name());
        break;
      }
      case MDC_DIM_PER_CUBIC_X_M:
      {
        typename Tx<TxType, MDC_DIM_PER_CUBIC_X_M>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PER_CUBIC_X_M>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_CUBIC_X_M>::baseType).name());
        break;
      }
      case MDC_DIM_PER_X_L:
      {
        typename Tx<TxType, MDC_DIM_PER_X_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PER_X_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_X_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_G:
      {
        typename Tx<TxType, MDC_DIM_X_G>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G>::baseType).name());
        break;
      }
      case MDC_DIM_X_LB:
      {
        typename Tx<TxType, MDC_DIM_X_LB>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_LB>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_LB>::baseType).name());
        break;
      }
      case MDC_DIM_X_OZ:
      {
        typename Tx<TxType, MDC_DIM_X_OZ>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_OZ>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_OZ>::baseType).name());
        break;
      }
      case MDC_DIM_PER_X_G:
      {
        typename Tx<TxType, MDC_DIM_PER_X_G>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PER_X_G>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_X_G>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_M:
      {
        typename Tx<TxType, MDC_DIM_X_G_M>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_M>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_M>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_M_PER_M_SQ:
      {
        typename Tx<TxType, MDC_DIM_X_G_M_PER_M_SQ>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_M_PER_M_SQ>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_M_PER_M_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_M_SQ:
      {
        typename Tx<TxType, MDC_DIM_X_G_M_SQ>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_M_SQ>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_M_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_KG_PER_M_SQ:
      {
        typename Tx<TxType, MDC_DIM_KG_PER_M_SQ>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_KG_PER_M_SQ>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_KG_PER_M_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_M_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_M_CUBE>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_M_CUBE>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_M_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_CM_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_CM_CUBE>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_CM_CUBE>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_CM_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_L:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_CL:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_CL>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_CL>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_CL>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_DL:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_DL>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_DL>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_DL>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_ML:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_ML>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_ML>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_ML>::baseType).name());
        break;
      }
      case MDC_DIM_X_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_MIN:
      {
        typename Tx<TxType, MDC_DIM_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_HR:
      {
        typename Tx<TxType, MDC_DIM_HR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_HR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_HR>::baseType).name());
        break;
      }
      case MDC_DIM_DAY:
      {
        typename Tx<TxType, MDC_DIM_DAY>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_DAY>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_WEEKS:
      {
        typename Tx<TxType, MDC_DIM_WEEKS>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_WEEKS>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_WEEKS>::baseType).name());
        break;
      }
      case MDC_DIM_MON:
      {
        typename Tx<TxType, MDC_DIM_MON>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_MON>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_MON>::baseType).name());
        break;
      }
      case MDC_DIM_YR:
      {
        typename Tx<TxType, MDC_DIM_YR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_YR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_YR>::baseType).name());
        break;
      }
      case MDC_DIM_PER_X_SEC:
      {
        typename Tx<TxType, MDC_DIM_PER_X_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PER_X_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_X_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_HZ:
      {
        typename Tx<TxType, MDC_DIM_HZ>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_HZ>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_HZ>::baseType).name());
        break;
      }
      case MDC_DIM_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_PER_HR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PER_HR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_PER_DAY>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PER_DAY>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_PER_WK:
      {
        typename Tx<TxType, MDC_DIM_PER_WK>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PER_WK>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_WK>::baseType).name());
        break;
      }
      case MDC_DIM_PER_MO:
      {
        typename Tx<TxType, MDC_DIM_PER_MO>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PER_MO>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_MO>::baseType).name());
        break;
      }
      case MDC_DIM_PER_YR:
      {
        typename Tx<TxType, MDC_DIM_PER_YR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PER_YR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_YR>::baseType).name());
        break;
      }
      case MDC_DIM_BEAT_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_BEAT_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_BEAT_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_BEAT_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_PULS_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_PULS_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PULS_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PULS_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_RESP_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_RESP_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_RESP_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_RESP_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_M_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_M_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_M_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_M_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_MIN_PER_M_SQ:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_M_SQ>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_M_SQ>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_M_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_SQ_X_M_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_SQ_X_M_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_SQ_X_M_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_SQ_X_M_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_CUBIC_X_M_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_CUBIC_X_M_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_CUBIC_X_M_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_HR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_HR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_CUBIC_X_M_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_DAY>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_DAY>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_CUBIC_X_M_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_HR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_HR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_DAY>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_DAY>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_KG:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_KG>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_KG>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_KG>::baseType).name());
        break;
      }
      case MDC_DIM_CUBIC_X_L_PER_KG:
      {
        typename Tx<TxType, MDC_DIM_CUBIC_X_L_PER_KG>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_CUBIC_X_L_PER_KG>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_CUBIC_X_L_PER_KG>::baseType).name());
        break;
      }
      case MDC_DIM_X_M_PER_PASCAL_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_M_PER_PASCAL_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_M_PER_PASCAL_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_M_PER_PASCAL_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_MIN_PER_ML_HG:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_ML_HG>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_ML_HG>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_ML_HG>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_HR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_HR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_DAY>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_DAY>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_KG_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_KG_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_KG_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_HR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_HR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_KG_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_DAY>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_DAY>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_KG_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_L_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_L_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_L_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_HR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_HR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_L_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_DAY>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_DAY>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_L_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_M_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_M_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_M_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_M_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_M_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_G_M_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_M_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_M_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_NEWTON_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_NEWTON_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_NEWTON_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_NEWTON_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_NEWTON:
      {
        typename Tx<TxType, MDC_DIM_X_NEWTON>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_NEWTON>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_NEWTON>::baseType).name());
        break;
      }
      case MDC_DIM_X_DYNE:
      {
        typename Tx<TxType, MDC_DIM_X_DYNE>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_DYNE>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_DYNE>::baseType).name());
        break;
      }
      case MDC_DIM_X_PASCAL:
      {
        typename Tx<TxType, MDC_DIM_X_PASCAL>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_PASCAL>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_PASCAL>::baseType).name());
        break;
      }
      case MDC_DIM_MMHG:
      {
        typename Tx<TxType, MDC_DIM_MMHG>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_MMHG>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_MMHG>::baseType).name());
        break;
      }
      case MDC_DIM_CM_H2O:
      {
        typename Tx<TxType, MDC_DIM_CM_H2O>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_CM_H2O>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_CM_H2O>::baseType).name());
        break;
      }
      case MDC_DIM_X_BAR:
      {
        typename Tx<TxType, MDC_DIM_X_BAR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_BAR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_BAR>::baseType).name());
        break;
      }
      case MDC_DIM_X_JOULES:
      {
        typename Tx<TxType, MDC_DIM_X_JOULES>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_JOULES>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_JOULES>::baseType).name());
        break;
      }
      case MDC_DIM_EVOLT:
      {
        typename Tx<TxType, MDC_DIM_EVOLT>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_EVOLT>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_EVOLT>::baseType).name());
        break;
      }
      case MDC_DIM_X_WATT:
      {
        typename Tx<TxType, MDC_DIM_X_WATT>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_WATT>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_WATT>::baseType).name());
        break;
      }
      case MDC_DIM_X_PASCAL_SEC_PER_M_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_PASCAL_SEC_PER_M_CUBE>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_PASCAL_SEC_PER_M_CUBE>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_PASCAL_SEC_PER_M_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_PASCAL_SEC_PER_L:
      {
        typename Tx<TxType, MDC_DIM_X_PASCAL_SEC_PER_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_PASCAL_SEC_PER_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_PASCAL_SEC_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_DYNE_PER_SEC_PER_CM5:
      {
        typename Tx<TxType, MDC_DIM_X_DYNE_PER_SEC_PER_CM5>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_DYNE_PER_SEC_PER_CM5>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_DYNE_PER_SEC_PER_CM5>::baseType).name());
        break;
      }
      case MDC_DIM_X_AMPS:
      {
        typename Tx<TxType, MDC_DIM_X_AMPS>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_AMPS>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_AMPS>::baseType).name());
        break;
      }
      case MDC_DIM_X_COULOMB:
      {
        typename Tx<TxType, MDC_DIM_X_COULOMB>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_COULOMB>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_COULOMB>::baseType).name());
        break;
      }
      case MDC_DIM_X_AMPS_PER_M:
      {
        typename Tx<TxType, MDC_DIM_X_AMPS_PER_M>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_AMPS_PER_M>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_AMPS_PER_M>::baseType).name());
        break;
      }
      case MDC_DIM_X_VOLT:
      {
        typename Tx<TxType, MDC_DIM_X_VOLT>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_VOLT>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_VOLT>::baseType).name());
        break;
      }
      case MDC_DIM_X_OHM:
      {
        typename Tx<TxType, MDC_DIM_X_OHM>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_OHM>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_OHM>::baseType).name());
        break;
      }
      case MDC_DIM_X_OHM_M:
      {
        typename Tx<TxType, MDC_DIM_X_OHM_M>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_OHM_M>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_OHM_M>::baseType).name());
        break;
      }
      case MDC_DIM_X_FARAD:
      {
        typename Tx<TxType, MDC_DIM_X_FARAD>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_FARAD>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_FARAD>::baseType).name());
        break;
      }
      case MDC_DIM_KELVIN:
      {
        typename Tx<TxType, MDC_DIM_KELVIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_KELVIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_KELVIN>::baseType).name());
        break;
      }
      case MDC_DIM_FAHR:
      {
        typename Tx<TxType, MDC_DIM_FAHR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_FAHR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_FAHR>::baseType).name());
        break;
      }
      case MDC_DIM_KELVIN_PER_X_WATT:
      {
        typename Tx<TxType, MDC_DIM_KELVIN_PER_X_WATT>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_KELVIN_PER_X_WATT>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_KELVIN_PER_X_WATT>::baseType).name());
        break;
      }
      case MDC_DIM_X_CANDELA:
      {
        typename Tx<TxType, MDC_DIM_X_CANDELA>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_CANDELA>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_CANDELA>::baseType).name());
        break;
      }
      case MDC_DIM_X_OSM:
      {
        typename Tx<TxType, MDC_DIM_X_OSM>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_OSM>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_OSM>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV>::baseType).name());
        break;
      }
      case MDC_DIM_X_OSM_PER_L:
      {
        typename Tx<TxType, MDC_DIM_X_OSM_PER_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_OSM_PER_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_OSM_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_CM_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_CM_CUBE>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_CM_CUBE>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_CM_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_M_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_M_CUBE>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_M_CUBE>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_M_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_L:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_ML:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_ML>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_ML>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_ML>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_CM_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_CM_CUBE>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_CM_CUBE>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_CM_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_M_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_M_CUBE>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_M_CUBE>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_M_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_L:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_ML:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_ML>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_ML>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_ML>::baseType).name());
        break;
      }
      case MDC_DIM_X_OSM_PER_KG:
      {
        typename Tx<TxType, MDC_DIM_X_OSM_PER_KG>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_OSM_PER_KG>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_OSM_PER_KG>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_KG:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_HR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_HR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_DAY>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_DAY>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_HR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_HR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_DAY>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_DAY>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_KG_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_KG_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_KG_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_HR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_HR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_MOLE_PER_KG_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_DAY>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_DAY>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_MOLE_PER_KG_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_KG_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_KG_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_KG_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_HR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_HR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_EQUIV_PER_KG_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_DAY>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_DAY>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_EQUIV_PER_KG_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_CM_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_CM_CUBE>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_CM_CUBE>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_CM_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_M_CUBE:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_M_CUBE>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_M_CUBE>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_M_CUBE>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_L:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_ML:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_ML>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_ML>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_ML>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_HR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_HR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_DAY>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_DAY>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_KG_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_KG_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_KG_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_HR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_HR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_INTL_UNIT_PER_KG_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_DAY>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_DAY>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_INTL_UNIT_PER_KG_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_CM_H2O:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_CM_H2O>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_CM_H2O>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_CM_H2O>::baseType).name());
        break;
      }
      case MDC_DIM_CM_H2O_PER_L_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_CM_H2O_PER_L_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_CM_H2O_PER_L_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_CM_H2O_PER_L_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_SQ_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_L_SQ_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_SQ_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_SQ_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_CM_H2O_PER_PERCENT:
      {
        typename Tx<TxType, MDC_DIM_CM_H2O_PER_PERCENT>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_CM_H2O_PER_PERCENT>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_CM_H2O_PER_PERCENT>::baseType).name());
        break;
      }
      case MDC_DIM_DYNE_SEC_PER_M_SQ_PER_CM_5:
      {
        typename Tx<TxType, MDC_DIM_DYNE_SEC_PER_M_SQ_PER_CM_5>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_DYNE_SEC_PER_M_SQ_PER_CM_5>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_DYNE_SEC_PER_M_SQ_PER_CM_5>::baseType).name());
        break;
      }
      case MDC_DIM_DEGC:
      {
        typename Tx<TxType, MDC_DIM_DEGC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_DEGC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_DEGC>::baseType).name());
        break;
      }
      case MDC_DIM_X_AMP_HR:
      {
        typename Tx<TxType, MDC_DIM_X_AMP_HR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_AMP_HR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_AMP_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_BEAT:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_BEAT>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_BEAT>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_BEAT>::baseType).name());
        break;
      }
      case MDC_DIM_CM_H2O_PER_L:
      {
        typename Tx<TxType, MDC_DIM_CM_H2O_PER_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_CM_H2O_PER_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_CM_H2O_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_MM_HG_PER_PERCENT:
      {
        typename Tx<TxType, MDC_DIM_MM_HG_PER_PERCENT>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_MM_HG_PER_PERCENT>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_MM_HG_PER_PERCENT>::baseType).name());
        break;
      }
      case MDC_DIM_X_PA_PER_PERCENT:
      {
        typename Tx<TxType, MDC_DIM_X_PA_PER_PERCENT>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_PA_PER_PERCENT>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_PA_PER_PERCENT>::baseType).name());
        break;
      }
      case MDC_DIM_VOL_PERCENT:
      {
        typename Tx<TxType, MDC_DIM_VOL_PERCENT>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_VOL_PERCENT>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_VOL_PERCENT>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_MM_HG:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_MM_HG>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_MM_HG>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_MM_HG>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_MM_PA:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_MM_PA>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_MM_PA>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_MM_PA>::baseType).name());
        break;
      }
      case MDC_DIM_MM_HG_PER_X_L:
      {
        typename Tx<TxType, MDC_DIM_MM_HG_PER_X_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_MM_HG_PER_X_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_MM_HG_PER_X_L>::baseType).name());
        break;
      }
      case MDC_DIM_PA_PER_X_L:
      {
        typename Tx<TxType, MDC_DIM_PA_PER_X_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PA_PER_X_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PA_PER_X_L>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_DL:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_DL>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_DL>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_DL>::baseType).name());
        break;
      }
      case MDC_DIM_DECIBEL:
      {
        typename Tx<TxType, MDC_DIM_DECIBEL>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_DECIBEL>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_DECIBEL>::baseType).name());
        break;
      }
      case MDC_DIM_X_G_PER_MG:
      {
        typename Tx<TxType, MDC_DIM_X_G_PER_MG>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_G_PER_MG>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_G_PER_MG>::baseType).name());
        break;
      }
      case MDC_DIM_BEAT_PER_MIN_PER_X_L:
      {
        typename Tx<TxType, MDC_DIM_BEAT_PER_MIN_PER_X_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_BEAT_PER_MIN_PER_X_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_BEAT_PER_MIN_PER_X_L>::baseType).name());
        break;
      }
      case MDC_DIM_PER_X_L_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_PER_X_L_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PER_X_L_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_X_L_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_X_M_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_M_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_M_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_M_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_PSI:
      {
        typename Tx<TxType, MDC_DIM_PSI>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PSI>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PSI>::baseType).name());
        break;
      }
      case MDC_DIM_X_M_PER_SEC_SQ:
      {
        typename Tx<TxType, MDC_DIM_X_M_PER_SEC_SQ>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_M_PER_SEC_SQ>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_M_PER_SEC_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_X_RAD_PER_SEC_SQ:
      {
        typename Tx<TxType, MDC_DIM_X_RAD_PER_SEC_SQ>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_RAD_PER_SEC_SQ>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_RAD_PER_SEC_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_X_RAD_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_RAD_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_RAD_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_RAD_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_LUMEN_PER_M_SQ:
      {
        typename Tx<TxType, MDC_DIM_X_LUMEN_PER_M_SQ>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_LUMEN_PER_M_SQ>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_LUMEN_PER_M_SQ>::baseType).name());
        break;
      }

    // Intellivue codes
      case MDC_DIM_COMPLEX:
      {
        typename Tx<TxType, MDC_DIM_COMPLEX>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_COMPLEX>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_COMPLEX>::baseType).name());
        break;
      }
      case MDC_DIM_COUNT:
      {
        typename Tx<TxType, MDC_DIM_COUNT>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_COUNT>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_COUNT>::baseType).name());
        break;
      }
      case MDC_DIM_PART:
      {
        typename Tx<TxType, MDC_DIM_PART>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PART>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PART>::baseType).name());
        break;
      }
      case MDC_DIM_PULS:
      {
        typename Tx<TxType, MDC_DIM_PULS>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PULS>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PULS>::baseType).name());
        break;
      }
      case MDC_DIM_UV_PP:
      {
        typename Tx<TxType, MDC_DIM_UV_PP>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_UV_PP>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_UV_PP>::baseType).name());
        break;
      }
      case MDC_DIM_UV_SQ:
      {
        typename Tx<TxType, MDC_DIM_UV_SQ>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_UV_SQ>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_UV_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_LUMEN:
      {
        typename Tx<TxType, MDC_DIM_LUMEN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_LUMEN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_LUMEN>::baseType).name());
        break;
      }
      case MDC_DIM_LB_PER_INCH_SQ:
      {
        typename Tx<TxType, MDC_DIM_LB_PER_INCH_SQ>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_LB_PER_INCH_SQ>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_LB_PER_INCH_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_MM_HG_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_MM_HG_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_MM_HG_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_MM_HG_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_JOULE_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_JOULE_PER_DAY>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_JOULE_PER_DAY>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_JOULE_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_CALORIE:
      {
        typename Tx<TxType, MDC_DIM_X_CALORIE>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_CALORIE>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_CALORIE>::baseType).name());
        break;
      }
      case MDC_DIM_X_CALORIE_PER_DAY:
      {
        typename Tx<TxType, MDC_DIM_X_CALORIE_PER_DAY>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_CALORIE_PER_DAY>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_CALORIE_PER_DAY>::baseType).name());
        break;
      }
      case MDC_DIM_X_CALORIE_PER_ML:
      {
        typename Tx<TxType, MDC_DIM_X_CALORIE_PER_ML>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_CALORIE_PER_ML>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_CALORIE_PER_ML>::baseType).name());
        break;
      }
      case MDC_DIM_X_JOULE_PER_ML:
      {
        typename Tx<TxType, MDC_DIM_X_JOULE_PER_ML>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_JOULE_PER_ML>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_JOULE_PER_ML>::baseType).name());
        break;
      }
      case MDC_DIM_X_REV_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_X_REV_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_REV_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_REV_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_PER_L_PER_MIN_PER_KG:
      {
        typename Tx<TxType, MDC_DIM_PER_L_PER_MIN_PER_KG>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PER_L_PER_MIN_PER_KG>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_L_PER_MIN_PER_KG>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_MILLI_BAR:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_MILLI_BAR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_MILLI_BAR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_MILLI_BAR>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_KG_PER_HR:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_KG_PER_HR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_KG_PER_HR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_KG_PER_HR>::baseType).name());
        break;
      }
      case MDC_DIM_X_BAR_PER_LITER_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_BAR_PER_LITER_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_BAR_PER_LITER_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_BAR_PER_LITER_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_BAR_PER_LITER:
      {
        typename Tx<TxType, MDC_DIM_X_BAR_PER_LITER>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_BAR_PER_LITER>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_BAR_PER_LITER>::baseType).name());
        break;
      }
      case MDC_DIM_VOLT_PER_MILLI_VOLT:
      {
        typename Tx<TxType, MDC_DIM_VOLT_PER_MILLI_VOLT>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_VOLT_PER_MILLI_VOLT>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_VOLT_PER_MILLI_VOLT>::baseType).name());
        break;
      }
      case MDC_DIM_CM_H2O_PER_MICRO_VOLT:
      {
        typename Tx<TxType, MDC_DIM_CM_H2O_PER_MICRO_VOLT>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_CM_H2O_PER_MICRO_VOLT>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_CM_H2O_PER_MICRO_VOLT>::baseType).name());
        break;
      }
      case MDC_DIM_X_JOULE_PER_LITER:
      {
        typename Tx<TxType, MDC_DIM_X_JOULE_PER_LITER>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_JOULE_PER_LITER>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_JOULE_PER_LITER>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_BAR:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_BAR>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_BAR>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_BAR>::baseType).name());
        break;
      }
      case MDC_DIM_X_M_PER_MILLI_VOLT:
      {
        typename Tx<TxType, MDC_DIM_X_M_PER_MILLI_VOLT>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_M_PER_MILLI_VOLT>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_M_PER_MILLI_VOLT>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_MIN_PER_KG:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_KG>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_KG>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_MIN_PER_KG>::baseType).name());
        break;
      }
      case MDC_DIM_X_PASCAL_PER_L_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_PASCAL_PER_L_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_PASCAL_PER_L_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_PASCAL_PER_L_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_MILLI_L_PER_X_PASCAL:
      {
        typename Tx<TxType, MDC_DIM_MILLI_L_PER_X_PASCAL>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_MILLI_L_PER_X_PASCAL>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_MILLI_L_PER_X_PASCAL>::baseType).name());
        break;
      }
      case MDC_DIM_MM_HG_PER_X_L_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_MM_HG_PER_X_L_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_MM_HG_PER_X_L_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_MM_HG_PER_X_L_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_BEAT_PER_M_SQ:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_BEAT_PER_M_SQ>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_BEAT_PER_M_SQ>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_BEAT_PER_M_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_X_BAR_PER_SEC:
      {
        typename Tx<TxType, MDC_DIM_X_BAR_PER_SEC>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_BAR_PER_SEC>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_BAR_PER_SEC>::baseType).name());
        break;
      }
      case MDC_DIM_X_PASCAL_PER_L:
      {
        typename Tx<TxType, MDC_DIM_X_PASCAL_PER_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_PASCAL_PER_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_PASCAL_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_MM_HG_PER_L:
      {
        typename Tx<TxType, MDC_DIM_MM_HG_PER_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_MM_HG_PER_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_MM_HG_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_VOL_PERCENT_PER_L:
      {
        typename Tx<TxType, MDC_DIM_VOL_PERCENT_PER_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_VOL_PERCENT_PER_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_VOL_PERCENT_PER_L>::baseType).name());
        break;
      }
    // End Intellivue codes

    // DocBox codes
      case MDC_DIM_PER_OHM:
      {
        typename Tx<TxType, MDC_DIM_PER_OHM>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PER_OHM>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PER_OHM>::baseType).name());
        break;
      }
      case MDC_DIM_SEC_SQ:
      {
        typename Tx<TxType, MDC_DIM_SEC_SQ>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_SEC_SQ>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_SEC_SQ>::baseType).name());
        break;
      }
      case MDC_DIM_X_L_PER_K_OHM:
      {
        typename Tx<TxType, MDC_DIM_X_L_PER_K_OHM>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_X_L_PER_K_OHM>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_X_L_PER_K_OHM>::baseType).name());
        break;
      }
      case MDC_DIM_PVC_PER_MIN:
      {
        typename Tx<TxType, MDC_DIM_PVC_PER_MIN>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_PVC_PER_MIN>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_PVC_PER_MIN>::baseType).name());
        break;
      }
      case MDC_DIM_BREATHS_PER_MIN_PER_L:
      {
        typename Tx<TxType, MDC_DIM_BREATHS_PER_MIN_PER_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_BREATHS_PER_MIN_PER_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_BREATHS_PER_MIN_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_JOULES_PER_L:
      {
        typename Tx<TxType, MDC_DIM_JOULES_PER_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_JOULES_PER_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_JOULES_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_RESP_PER_MIN_PER_L:
      {
        typename Tx<TxType, MDC_DIM_RESP_PER_MIN_PER_L>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_RESP_PER_MIN_PER_L>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_RESP_PER_MIN_PER_L>::baseType).name());
        break;
      }
      case MDC_DIM_RESP_PER_MIN_PER_L_PER_KILO_G:
      {
        typename Tx<TxType, MDC_DIM_RESP_PER_MIN_PER_L_PER_KILO_G>::baseType base_val(value);
        typename Tx<TxType, MDC_DIM_RESP_PER_MIN_PER_L_PER_KILO_G>::xType x_val(base_val);
        value = x_val.get();
        to_type.assign(typeid(typename Tx<TxType, MDC_DIM_RESP_PER_MIN_PER_L_PER_KILO_G>::baseType).name());
        break;
      }
    // End DocBox codes

      default:
        LOG4CPLUS_ERROR(root_logger, sfn << "Invalid to unit code " << base_to_unit_code);
        return DicesRcUnitConverter::FAIL;
        break;
    }

/* Regular expression to generate new "to" case
 * Example Input:
MDC_DIM_X_LUMEN_PER_M_SQ
 * Find What:
(MDC_DIM_[A-Z0-9_]*)\n
 * Replace With:
      case $1:\n
      {\n
        typename Tx<TxType, $1>::baseType base_val(value);\n
        typename Tx<TxType, $1>::xType x_val(base_val);\n
        value = x_val.get();\n
        to_type.assign(typeid(typename Tx<TxType, $1>::baseType).name());\n
        break;\n
      }\n
 */

    if (from_type.compare(to_type) != 0)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Unable to convert between " <<
        DimensionUtil::Dimension11073ToString(from_unit_code) << " and " <<
        DimensionUtil::Dimension11073ToString(to_unit_code));
        return DicesRcUnitConverter::FAIL;
    }

    *to_value = value;
    return DicesRcUnitConverter::OK;
  }

 private:

  UnitConverter() { }

  ~UnitConverter() { }

};

}
}

#endif
