* __KaratsubaMultiply__
  试算
  A = 1111111, B = 1111111, base=10
  n0 = 5

  * __LEVEL 1__
    n = A.length(), k = ceil(n/2) = 4
    (A0,B0) = (A,B) mod base^k = (1111,1111)
    (A1,B1) = (A,B) / base^k = (111,111)
    sA = A0 > A1 ? 1 : -1 = 1;
    sB = B0 > B1 ? 1 : -1 = 1;
    C0 = kmp(A0, B0) = kmp(1111, 1111)
    * __LEVEL 2__
        A = 1111, B = 1111, n = 4
        n < 5, return BasecaseMultiply(A,B) = 1234321
    C1 = kmp(A1, B1) = kmp(111, 111)
    * __LEVEL 2__
        A = 111, B = 111, n = 3
        n < 5, return BasecaseMultiply(A,B) = 12321
    C2 = kmp(|A0-A1|, |B0-B1|) = kmp(1000, 1000)
    * __LEVEL 2__
        A = 1000, B = 1000, n = 4
        n < 5, return BasecaseMultiply(A,B) = 1000000

    C = C0+(C0+C1-SaSbC2)\*10^k + C1\*10^(2k)
      = 1234321 + (1234321+12321-1*1*1000000)\*10^4 + 12321\*10^8
      = 1234567654321



* BasecaseMultiply 向量版
  BUG 2019-02-01: 
      {777, 666666} * {1,1} 结果显示 667443666666
      实际应为 777667443666666
      丢失开头的数字，原因：
      ```cpp
      t = vec_mp_single(a, b[bi]);
      shift(t, indent);
      c = vec_plus(c, t);
      ```
      t末尾追加0后，数值比c更大，调用 vec_plus 函数时 t 应该在前面
      同时应该添加 `b[bi]` 值为零的判断



