#ifndef MICRODOLLAR_H
#define MICRODOLLAR_H

typedef struct {

  long int dollars, microcents;
  
} microdollar;

enum { CP_OK, CP_REGFAIL, CP_QUOTEDFAIL };

#define conv_totalcents(md) ((1000000 * (md.dollars)) + (md.microcents))

#define md_trim(microcents, divisor) (microcents / divisor)

microdollar assign_cents(long int mc_total);

void microdollar_tostr(microdollar md, long int decimal_places, char *fill_str);

void sub_price(microdollar diff_pr, microdollar start_pr, microdollar *res_pr);
void add_price(microdollar diff_pr, microdollar start_pr, microdollar *res_pr);
void mul_price(double multiple, microdollar start_pr, microdollar *res_pr);
void div_price(double divisor, microdollar start_pr, microdollar *res_pr);

microdollar trim_price(microdollar md, long int decimal_places);

int cmp_price(microdollar a, microdollar b);

microdollar rnd_price(microdollar diff_pr);

#endif
