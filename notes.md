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

  
* 手算法开根的优化方向  
  * 基础  
    __在base具有一定长度的情况下__，使用 target(0, 6)/base(0, 5) 快速预判下一位数，带来的不确定因素可以通过试算进行审核。  
    预判数用est表示，则最终结果只可能是 est, est-1 或者 0  
  * 2019-01-21  
    __加法__  
    更新 base 的代码 `base = s_plus( base + "0", to_string(dbmid) );`  
    有很大的优化空间，dbmid 小于10的时候，可以直接叠加而不需要s_plus。  
    当dbmid大于10，而base+"0"之前的最后一位小于9，可以直接修改而不需要s_plus。  

    同时 s_plus 内部也可以进行相同的优化，a+b，当b已经完全遍历，并且pool<1时，高位的数字可以直接复制，而不需要计算。  

    实际测试添加判断后，s_plus根本没有被调用过  
    ```
    dbmid = mid*2;
    if (dbmid > 9)
        if ( base.back() < '9' )
            base.back() += 1, base += (dbmid-10)+'0';
        else
            base = s_plus( base + "0", to_string(dbmid) );
    else
        base += dbmid+'0';
    ```
    原因是每一次 base更新，都是叠加mid*2，因此base末尾只可能是偶数，不可能达到9。  
    耗时减小大约 1/6  

    __乘法__  
    `s_mp = s_mp_single( base+itoc[mid], itos[mid] );`
    由于是乘以单个数字，当mid是1的时候，可以直接返回参数a，当mid是0的时候，可以直接返回0。  

  

  

