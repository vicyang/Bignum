### 大数开根 各种程序效率
CPU i7 4790K 4.00GHz

* __Perl__
  bignum模块，精度1W
  ```perl
  use bignum 'a'=>10000;
  printf "%s\n", sqrt(2);
  ```
  耗时4.5s

* __Python__
  Decimal模块，精度10W
  ```python
  from decimal import *
  getcontext().prec = 100000
  print(Decimal(2).sqrt())
  ```
  耗时 1.0s

* __CPP Decimal Solution__
  2019-01-18 初始版本 精度1W
  耗时 0.9s

* __GNU MP Library__
  100W精度，含输出，1.5秒；不含输出，0.2秒
  1000W位有效数字 不含输出 2.5秒。
