# Multi-Word-Int v5.03
Library to provide multi-word (large) integers for the Free Pascal compiler.
Designed to be reasonably fast, and requiring minimal changes to existing code.
Provides basic arithmetic operations add, subtract, multiply, divide, exclusive-or, power, odd, even, bit shift.
Provides implicit/automatic conversions to other types wherever possible.
Will compile and run on 32bit and 64bit environments.
Written purely in Pascal to be portable to any target and reliable (no assembly or C language code).

Changes in this version:
-	IntToStr function with the same functionality as the .ToStr method (for greater compatibility with existing code)
-	Sqrt function with the same functionality as the Sqroot function (for greater compatibility with existing code)
