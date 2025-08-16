# Multi-Word-Int v5.13
Library to provide multi-word (large) integers for the Free Pascal compiler.
Designed to be reasonably fast, and requiring minimal changes to existing code.
Provides basic arithmetic operations add, subtract, multiply, divide, exclusive-or, power, odd, even, bit shift and square root.
Provides implicit/automatic conversions to other types wherever possible.
Will compile and run on 32bit and 64bit environments.
Written purely in Pascal to be portable to any target and reliable (no assembly or C language code).

Changes in this version:
-	Bug fixes in initialisation when using Multi_Int_XV and another Multi_Int_X2, Multi_Int_X3 or Multi_Int_X4 type in the same program.
