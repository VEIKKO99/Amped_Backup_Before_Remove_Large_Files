/**
 * valve.h
 * @copyright (C)2015 HoRNet Plugins
 *
 * This file contains the function that makes the lookup & interpolation in the
 * tube tables generated with tube_transfer.py
 */

#ifndef SRC_HEADERS_VALVE_H_
#define SRC_HEADERS_VALVE_H_

/****************************************************************
 * 1-dimensional function tables for linear interpolation
 *
 * table1d and table1d_imp<size> must only differ in the last
 * element, so that the typecast for tubetab below will work.
 * Can't use inheritance because then C initializers will not
 * work and initialization will be more awkward or less efficient.
 */

struct table1d   // 1-dimensional function table
{
  float low;
  float high;
  float istep;
  int size;
	float fLp;
  float data[];
};

template <int tab_size>
struct table1d_imp
{
  float low;
  float high;
  float istep;
  int size;
	float fLp;
  float data[tab_size];
  operator table1d&() const
  {
    return *(table1d*)this;
  }
};

#include "tube_tables/12ax7.h"
#include "tube_tables/12ay7.h"
#include "tube_tables/12at7.h"
#include "tube_tables/ECC83.h"
#include "tube_tables/ECC81.h"
#include "tube_tables/7025.h"
#include "tube_tables/6L6CG.h"
#include "tube_tables/EL34.h"
#include "tube_tables/EL84.h"
#include "tube_tables/6550.h"
#include "tube_tables/KT88.h"
#include "tube_tables/KT66.h"

enum {
    TUBE_TABLE_12AX7_68k,
    TUBE_TABLE_12AX7_250k,
		TUBE_TABLE_12AY7_68k,
		TUBE_TABLE_12AY7_250k,
		TUBE_TABLE_12AT7_68k,
		TUBE_TABLE_12AT7_250k,
		TUBE_TABLE_ECC83_68k,
		TUBE_TABLE_ECC83_250k,
		TUBE_TABLE_ECC81_68k,
		TUBE_TABLE_ECC81_250k,
		TUBE_TABLE_7025_68k,
		TUBE_TABLE_7025_250k,
    TUBE_TABLE_6L6CG_68k,
    TUBE_TABLE_6L6CG_250k,
    TUBE_TABLE_EL34_68k,
    TUBE_TABLE_EL34_250k,
    TUBE_TABLE_EL84_68k,
    TUBE_TABLE_EL84_250k,
		TUBE_TABLE_6550_68k,
		TUBE_TABLE_6550_250k,
		TUBE_TABLE_KT88_68k,
		TUBE_TABLE_KT88_250k,
		TUBE_TABLE_KT66_68k,
		TUBE_TABLE_KT66_250k,
    TUBE_TABLE_SIZE
};


static table1d *tubetab[TUBE_TABLE_SIZE] = {
    &static_cast<table1d&>(tubetable_12AX7[0]),
    &static_cast<table1d&>(tubetable_12AX7[1]),
		&static_cast<table1d&>(tubetable_12AY7[0]),
		&static_cast<table1d&>(tubetable_12AY7[1]),
		&static_cast<table1d&>(tubetable_12AT7[0]),
		&static_cast<table1d&>(tubetable_12AT7[1]),
		&static_cast<table1d&>(tubetable_ECC83[0]),
		&static_cast<table1d&>(tubetable_ECC83[1]),
		&static_cast<table1d&>(tubetable_ECC81[0]),
		&static_cast<table1d&>(tubetable_ECC81[1]),
		&static_cast<table1d&>(tubetable_7025[0]),
		&static_cast<table1d&>(tubetable_7025[1]),
    &static_cast<table1d&>(tubetable_6L6CG[0]),
    &static_cast<table1d&>(tubetable_6L6CG[1]),
    &static_cast<table1d&>(tubetable_EL34[0]),
    &static_cast<table1d&>(tubetable_EL34[1]),
    &static_cast<table1d&>(tubetable_EL84[0]),
    &static_cast<table1d&>(tubetable_EL84[1]),
		&static_cast<table1d&>(tubetable_6550[0]),
		&static_cast<table1d&>(tubetable_6550[1]),
		&static_cast<table1d&>(tubetable_KT88[0]),
		&static_cast<table1d&>(tubetable_KT88[1]),
		&static_cast<table1d&>(tubetable_KT66[0]),
		&static_cast<table1d&>(tubetable_KT66[1]),
};


static inline double Ftube(int table, double Vgk)
{
  const table1d& tab = *tubetab[table];
  double f = (Vgk - tab.low) * tab.istep;
  int i = static_cast<int>(f);
  if (i < 0)
    return tab.data[0];
  if (i >= tab.size-1)
    return tab.data[tab.size-1];
  f -= i;
  return tab.data[i]*(1-f) + tab.data[i+1]*f;
}

#endif
