module Homework1 where

toDigits :: Integer -> [Integer]
toDigits n 
    | n <= 0 = []
    | otherwise = revSeq(toDigitsRev(n))

toDigitsRev :: Integer -> [Integer]
toDigitsRev 0 = []
toDigitsRev n = (n `mod` 10 : toDigitsRev(n `div` 10))

revSeq :: [Integer] -> [Integer]
revSeq [] = []
revSeq (n:rest) = revSeq(rest) ++ [n]

doubleEveryOtherNormal :: [Integer] -> [Integer]
doubleEveryOtherNormal [] = []
doubleEveryOtherNormal (x:[]) = [x]
doubleEveryOtherNormal (x:y:seq) = (x:2*y: doubleEveryOtherNormal seq) 

doubleEveryOther :: [Integer] -> [Integer]
doubleEveryOther seq 
    = revSeq(
        doubleEveryOtherNormal(
            revSeq(seq)))

sumDigits :: [Integer] -> Integer
sumDigits [] = 0
sumDigits (x:xs) 
    | x `div` 10  == 0 = x + sumDigits(xs)
    | otherwise = sumDigits(toDigits(x)) + sumDigits(xs)

validate :: Integer -> Bool
validate n
    | n < 0 = False
    | otherwise = (sumDigits(doubleEveryOther(toDigits n))) `mod` 10 == 0

type Peg = String
type Move = (Peg, Peg)
hanoi :: Integer -> Peg -> Peg -> Peg -> [Move]
hanoi 0 p1 p2 p3 = []
hanoi n p1 p2 p3 = hanoi (n-1) p1 p3 p2 ++ [(p1, p2)] ++ hanoi (n-1) p3 p2 p1