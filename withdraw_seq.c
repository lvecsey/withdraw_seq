
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <errno.h>

#include "microdollar.h"

int main(int argc, char *argv[]) {

  long int withdraw_idx;

  microdollar retirement_savings;
  
  long int withdraw_years;

  double growth_pct;

  int retval;
  
  growth_pct = 1.0475; 

  if (argc>1) {
    long int mc_total;
    long int dollars, cents;
    retval = sscanf(argv[1], "%ld.%ld", &dollars, &cents);
    if (retval != 2) {
      printf("Specify a savings amount in both dollars and cents.\n");
      return -1;
    }
    if (cents < 0 || cents >= 100) {
      printf("Specify a savings amount in dollars and cents only.\n");
      return -1;
    }
    mc_total = (dollars * 1000000) + cents;
    retirement_savings = assign_cents(mc_total);
  }

  else {
    retirement_savings.dollars = 850000;
    retirement_savings.microcents = 0;
  }
  
  withdraw_years = argc>2 ? strtol(argv[2], NULL, 10) : 30;

  for (withdraw_idx = 0; withdraw_idx < withdraw_years; withdraw_idx++) {

    microdollar afteryear_savings, withdrawn_amt;

    mul_price(0.96, retirement_savings, &afteryear_savings);
    mul_price(0.04, retirement_savings, &withdrawn_amt);    

    {
      char afteryear_str[20];
      char withdrawn_str[20];

      memset(afteryear_str, 0, sizeof(afteryear_str));
      memset(withdrawn_str, 0, sizeof(afteryear_str));      
      
      microdollar_tostr(afteryear_savings, 2, afteryear_str);
      microdollar_tostr(withdrawn_amt, 2, withdrawn_str);    

      printf("%s (%s USD)\n", afteryear_str, withdrawn_str);

    }
      
    retirement_savings = afteryear_savings;

    mul_price(growth_pct, retirement_savings, &retirement_savings);
    
  }

  return 0;

}
