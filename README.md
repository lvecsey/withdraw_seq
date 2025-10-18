
Pass in a retirement savings number (Amount USD) to the program.

The way you arrive at it is to take your current annual living needs, or expenses, and multiply by 25. This is the so called retirement investing "rule of 25"

The output will show the progression of your account, as funds are withdrawn during each retirement year.

*Compiling*

```console
make withdraw_seq
```

*Usage*

```console
./withdraw_seq [Savings] [#Years]
```

For each line of output, 4% of the savings is withdrawn. The results are shown.

*Growth rate*

You can edit the program to adjust or boost the expected growth rate. For each year that your money is withdrawn, the remaining savings are still growing.


