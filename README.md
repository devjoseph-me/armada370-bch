# BCH 분석

TARGET 의 BCH 는 일반적인 Binary BCH 코드와는 차이가 있다.

하지만 m=15,t=16,size=(2048+32),prim_poly=0x8003 으로 BCH ECC 코드를 생성했을 때,

Normal BCH 와 Target BCH 의 XOR 차이가 특정 패턴을 보인다.

아래에는 00 으로 채워진 값과, FF 으로 채워진 값에 대해서 Normal BCH, Target BCH 두개의 차이를 출력한다.

### TEST 00

#### INPUT :

```text
00000000  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000800  FF FF FF FF FF FF FF FF  FF FF FF FF FF FF FF FF
00000810  FF FF FF FF FF FF FF FF  FF FF FF FF FF FF FF FF
```

#### OUTPUT (Normal BCH) :

- parameters : m=15, t=16, size=2048+32

```text
77 5d f9 64 6c 5c 3d 97  09 ba c1 f2 2d 25 b5 07
62 66 d4 66 65 d5 9f 73  85 57 c5 55 7e 45
```

#### OUTPUT (Target BCH) :

```text
EE AB F9 62 63 A3 CB 9E  09 D5 38 F4 4B 4A DA 0E
64 66 B2 66 6A BA 9F EC  1A AE 3A AA E7 2A
```

#### XOR DIFF

```text
99 f6 00 06 0f ff f6 09  00 6f f9 06 66 6f 6f 09
06 00 66 00 0f 6f 00 9f  9f f9 ff ff 99 6f 
```

### TEST FF

#### INPUT :

```text
00000000  FF FF FF FF FF FF FF FF  FF FF FF FF FF FF FF FF  |................|
*
00000800  FF FF FF FF FF FF FF FF  FF FF FF FF FF FF FF FF
00000810  FF FF FF FF FF FF FF FF  FF FF FF FF FF FF FF FF
```

#### OUTPUT (Normal BCH) :

- parameters : m=15, t=16, size=2048+32

```text
ed c4 08 be 6c 6f c1 f8  3e 12 58 5d 1b d7 cf e8
12 14 e8 99 01 9f 53 ed  a4 5d 7f 5c 87 fc
```

#### OUTPUT (Target BCH) :

```text
7B 32 01 D7 63 6F 38 F1  C7 84 A1 AB 8D BE 3F 71
84 82 71 99 08 9F AC 7B  52 AB EF A3 1E F3
```

#### XOR DIFF

```text
96 f6 09 69 0f 00 f9 09  f9 96 f9 f6 96 69 f0 99
96 96 99 00 09 00 ff 96  f6 f6 90 ff 99 0f 
```

# 코드 빌드 방법


```bash
$ make && ./bch_test

FILLED 00) DUMP:77 5d f9 64 6c 5c 3d 97 09 ba c1 f2 2d 25 b5 07 62 66 d4 66 65 d5 9f 73 85 57 c5 55 7e 45 
DIFF FROM TARGET) DUMP:99 f6 00 06 0f ff f6 09 00 6f f9 06 66 6f 6f 09 06 00 66 00 0f 6f 00 9f 9f f9 ff ff 99 6f 
FILLED FF) DUMP:ed c4 08 be 6c 6f c1 f8 3e 12 58 5d 1b d7 cf e8 12 14 e8 99 01 9f 53 ed a4 5d 7f 5c 87 fc 
DIFF FROM TARGET) DUMP:96 f6 09 69 0f 00 f9 09 f9 96 f9 f6 96 69 f0 99 96 96 99 00 09 00 ff 96 f6 f6 90 ff 99 0f 
```