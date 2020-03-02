module Cipher where

import Data.Char

caesar :: Int -> String -> String
caesar n s = map 
    (\c -> shift n c) 
    s

uncaesar :: Int -> String -> String
uncaesar n s = caesar (-n) s

shift :: Int -> Char -> Char
shift n c 
    | elem c [' ','.', ',', '?', '!'] = c
    | otherwise = chr $ mod ((ord c - b) + n) 26 + b
        where b = if isUpper c then ord 'A' else ord 'a'

unshift :: Int -> Char -> Char
unshift n = shift (-n)

vigenere :: String -> String -> String
vigenere encoder s = map 
    (\(ix, c) -> shift (getShift encoder ix) c)
    $ zip [0..] s
    
unvigenere :: String -> String -> String
unvigenere encoder s = map 
    (\(ix, c) -> shift (-(getShift encoder ix)) c)
    $ zip [0..] s

getShift :: String -> Int -> Int
getShift encoder pos =
    ord (encoder !! mod pos (length encoder)) - ord 'A'