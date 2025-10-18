#include <stdio.h>
#include <stdlib.h>

#include "microdollar.h"

microdollar trim_price(microdollar md, long int decimal_places) {

  microdollar res;

  long int divisors[] = { 100000, 10000, 1000, 100, 10, 1 };
  
  res.dollars = md.dollars;

  {
    long int divisor;
    divisor = divisors[decimal_places - 1];
    res.microcents = divisor * md_trim(md.microcents, divisor);
  }
    
  return res;
  
}

void microdollar_tostr(microdollar md, long int decimal_places, char *fill_str) {

  long int mc_total;

  int retval;

  long int divisors[] = { 100000, 10000, 1000, 100, 10, 1 };
  
  {

    long int microdigits;

    int width;
    
    microdigits = md.microcents / divisors[decimal_places - 1];

    width = decimal_places;
    
    retval = sprintf(fill_str, "%ld.%0*ld", md.dollars, width, microdigits);

  }
		     
}

microdollar assign_cents(long int mc_total) {

  microdollar res_pr;

  res_pr.dollars = mc_total / 1000000;

  res_pr.microcents = mc_total - (1000000 * res_pr.dollars);
  
  return res_pr;

}

void mul_price(double multiple, microdollar cur_pr, microdollar *res_pr) {

  long int mc_total;

  mc_total = (1000000 * cur_pr.dollars) + cur_pr.microcents;

  mc_total *= multiple;

  {
    long int dollars;
    dollars = (mc_total / 1000000);
    res_pr->dollars = dollars;
    res_pr->microcents = mc_total - (1000000 * dollars);
  }
  
}

void div_price(double divisor, microdollar cur_pr, microdollar *res_pr) {

  long int mc_total;

  mc_total = (1000000 * cur_pr.dollars) + cur_pr.microcents;

  mc_total /= divisor;

  {
    long int dollars;
    dollars = (mc_total / 1000000);
    res_pr->dollars = dollars;
    res_pr->microcents = mc_total - (1000000 * dollars);
  }
  
}

void sub_price(microdollar diff_pr, microdollar start_pr, microdollar *res_pr) {

  long int mc_total;

  mc_total = (1000000 * start_pr.dollars) + start_pr.microcents;

  mc_total -= (1000000 * diff_pr.dollars) + diff_pr.microcents;

  if (mc_total < 0) {
    mc_total = 0;
  }

  *res_pr = assign_cents(mc_total);
  
}

void add_price(microdollar diff_pr, microdollar start_pr, microdollar *res_pr) {

  long int mc_total;

  mc_total = conv_totalcents(start_pr) + conv_totalcents(diff_pr);

  *res_pr = assign_cents(mc_total);
  
}

int cmp_price(microdollar a, microdollar b) {

  int dollar_diff;

  dollar_diff = (b.dollars - a.dollars);
  if (0 != dollar_diff) {
    return (dollar_diff > 0) ? -1 : 1;
  }

  if (a.microcents < b.microcents) {
    return -1;
  }

  if (a.microcents > b.microcents) {
    return 1;
  }

  return 0;
  
}

microdollar rnd_price(microdollar diff_pr) {

  microdollar res_pr;

  long int mc_total;
  
  mc_total = (1000000 * diff_pr.dollars) + diff_pr.microcents;

  mc_total *= drand48();

  res_pr = assign_cents(mc_total);
  
  return res_pr;
  
}
